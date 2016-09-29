/**
 * SBD
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/sched.h>
#include <linux/kernel.h>  /* printk() */
#include <linux/slab.h>        /* kmalloc() */
#include <linux/fs.h>      /* everything... */
#include <linux/errno.h>   /* error codes */
#include <linux/timer.h>
#include <linux/types.h>   /* size_t */
#include <linux/fcntl.h>   /* O_ACCMODE */
#include <linux/hdreg.h>   /* HDIO_GETGEO */
#include <linux/kdev_t.h>
#include <linux/vmalloc.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>
#include <linux/buffer_head.h> /* invalidate_bdev */
#include <linux/bio.h>
#include <linux/crypto.h>

MODULE_LICENSE("GPL");

static int sbd_major = 0;
module_param(sbd_major, int, 0);
static int hardsect_size = 512;
module_param(hardsect_size, int, 0);
static int nsectors = 1024;
module_param(nsectors, int, 0);
int ndevices = 4;
module_param(ndevices, int, 0);

//Enumerating the request modes
enum {
    RM_SIMPLE  = 0, /* The extra-simple request function */
    RM_FULL    = 1, /* The full-blown version */
    RM_NOQUEUE = 2, /* Use make_request */
};
static int request_mode = RM_SIMPLE;
module_param(request_mode, int, 0);

//Set minor numbers and partition management 
#define SBD_MINORS  16
#define MINOR_SHIFT 4
#define DEVNUM(kdevnum) (MINOR(kdev_t_to_nr(kdevnum)) >> MINOR_SHIFT

//Set sector number so kernel can talk to driver
#define KERNEL_SECTOR_SHIFT 9
#define KERNEL_SECTOR_SIZE  (1<<KERNEL_SECTOR_SHIFT)

//After some idle time, simulate media change
#define INVALIDATE_DELAY 30*HZ

static char *key = "hello";
module_param(key, charp, S_IRUGO);

#define KEY_SIZE 32
static char crypto_key[KEY_SIZE];
static int key_size = 0;


struct crypto_cipher *cipher;

//Struct to represent the device
struct sbd_dev {
        int size;                       /* Device size in sectors */
        u8 *data;                       /* The data array */
        short users;                    /* How many users */
        short media_change;             /* Flag a media change? */
        spinlock_t lock;                /* For mutual exclusion */
        struct request_queue *queue;    /* The device request queue */
        struct gendisk *gd;             /* The gendisk structure */
        struct timer_list timer;        /* For simulated media changes */
};

static struct sbd_dev *Devices = NULL;

ssize_t key_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    printk(KERN_DEBUG "crypt: Copying key\n");
    return scnprintf(buf, PAGE_SIZE, "%s\n", crypto_key);
}

ssize_t key_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    if(count != 16 && count !=24 && count != 32)
    {
        printk(KERN_WARNING "Crpyt: invalid key size %d\n", count);
        return -EINVAL;
    }

    printk(KERN_DEBUG "crpyt: storing key\n");
    snprintf(crypto_key, sizeof(crypto_key), "%.*s", (int)min(count, sizeof(crypto_key) - 1), buf);
    key_size = count;
    return count;
}

DEVICE_ATTR(key, 0600, key_show, key_store);



//Handle IO request at hte lowest level
static void sbd_transfer(struct sbd_dev *dev, unsigned long sector,
        unsigned long nsect, char *buffer, int write) {

    int i;
    unsigned long offset = sector*KERNEL_SECTOR_SIZE;
    unsigned long nbytes = nsect*KERNEL_SECTOR_SIZE;

    //For some reason, the key wasn't being set so I'm forcing it here
    if(key_size == 0)
    {
        crypto_cipher_clear_flags(cipher, ~0);
        crypto_cipher_setkey(cipher, key, strlen(key));
        key_size = strlen(key);
        printk("Key size %d\n", key_size);
        
    }
    else
    {
        crypto_cipher_clear_flags(cipher, ~0);
        crypto_cipher_setkey(cipher, crypto_key, key_size);
    }

    if((offset + nbytes) > dev->size)
    {
        printk(KERN_NOTICE "Beyond end write (%ld %ld)\n", offset, nbytes);
        return;
    }

    //If it's a write request
    if(write)
    {
        printk("Writing\n");
        if(key_size != 0)
        {
            printk("Encrypting\n");
            //Encrypt each byte
            //For each byte
            for(i = 0; i < nbytes; i += crypto_cipher_blocksize(cipher))
            {
                //Takes the cipher block, and encypts each byte then writes it in the buffer
                crypto_cipher_encrypt_one(cipher, dev->data+offset+i, buffer+i);
            }
        }
        else
        {
            memcpy(dev->data + offset, buffer, nbytes);
        }
    }
    //Else, it must be a read request
    else
    {
        printk("Reading\n");
        if(key_size != 0)
        {
            printk("decrypting\n");
            for(i = 0; i < nbytes; i += crypto_cipher_blocksize(cipher))
            {
                crypto_cipher_decrypt_one(cipher, dev->data+offset+i, buffer+i);
            }
        }
        else
        {
            memcpy(buffer, dev->data + offset, nbytes);
        }
    }
}

//Simple request handling
static void sbd_request(struct request_queue *q) {

    struct request *req;
    int ret;

    //Get next incomplete request in the queue
    req = blk_fetch_request(q);
    while (req) {
        struct sbd_dev *dev = req->rq_disk->private_data;
        //Make sure its a filesystem request   
        if (req->cmd_type != REQ_TYPE_FS) {
            printk (KERN_NOTICE "Skip non-fs request\n");
            ret = -EIO;
            goto done;
        }
        //Pass the request off the transfer
        sbd_transfer(dev, blk_rq_pos(req), blk_rq_cur_sectors(req), bio_data(req->bio), rq_data_dir(req));
        ret = 0;
    done:
        //Error handling and goingto the next request
        if(!__blk_end_request_cur(req, ret)){
            req = blk_fetch_request(q);
        }
    }
}

//Tranfer one bio structre
static int sbd_xfer_bio(struct sbd_dev *dev, struct bio *bio) {

    struct bio_vec bvec;
    struct bvec_iter iter;
    sector_t sector = bio->bi_iter.bi_sector;

    //Iterate throught each section
    bio_for_each_segment(bvec, bio, iter)
    {
        char *buffer = __bio_kmap_atomic(bio, iter);
        sbd_transfer(dev, sector, bio_cur_bytes(bio),
                buffer, bio_data_dir(bio) == WRITE);
        sector += bio_cur_bytes(bio);
        __bio_kunmap_atomic(bio);
    }
    return 0;
}

//Transfer of full request
static int sbd_xfer_request(struct sbd_dev *dev, struct request *req) {

    struct bio *bio;
    int nsect = 0;

    //steps through each request and sends it to xfer_bio
    __rq_for_each_bio(bio, req)
    {
        sbd_xfer_bio(dev, bio);
        nsect += bio->bi_iter.bi_size/KERNEL_SECTOR_SIZE;
    }

    return nsect;
}


//Request function that handles more complex things, like clusering
static void sbd_full_request(struct request_queue *q) {
    
    struct request *req;
    struct sbd_dev *dev = q->queuedata;
    int ret;

    //Takes request and sends i to xfer_reqest
    while ((req = blk_fetch_request(q)) != NULL)
    {
        if(req->cmd_type != REQ_TYPE_FS)
        {
            printk(KERN_NOTICE "Skips non-fs request\n");
            __blk_end_request(req, -EIO, blk_rq_cur_bytes(req));
            ret = -EIO;
            goto done;
        }
        sbd_xfer_request(dev, req);
        ret = 0;
    done:
        __blk_end_request_all(req, ret);
    }

}

//Directly make a request
static void sbd_make_request(struct request_queue *q, struct bio *bio) {

    struct sbd_dev *dev = q->queuedata;
    int status;

    //Goes through the bio request without a request queue
    status = sbd_xfer_bio(dev, bio);
    bio_endio(bio, status);
}

//Open the device
//
//This function basically keeps track of the number of users using the device
static int sbd_open(struct block_device *bdev, fmode_t mode) {
    
    struct sbd_dev *dev = bdev->bd_disk->private_data;

    //Remove the media timer
    del_timer_sync(&dev->timer);

    //Get the lock on the drive
    spin_lock(&dev->lock);
    if(!dev->users)
        //Check if media has changed
        check_disk_change(bdev);
    //Increase users
    dev->users++;
    //Release lock
    spin_unlock(&dev->lock);
    return 0;
}

//Release the device
//
//Inverse of open, decrements users
static void sbd_release(struct gendisk *disk, fmode_t mode) {

    struct sbd_dev *dev = disk->private_data;

    spin_lock(&dev->lock);
    dev->users--;

    //Start the timer to invaldidate teh drive if no one is using it
    if(!dev->users) {
        dev->timer.expires = jiffies + INVALIDATE_DELAY;
        add_timer(&dev->timer);
    }

    spin_unlock(&dev->lock);
}

//Handle media change
int sbd_media_changed(struct gendisk *gd) {

    struct sbd_dev *dev = gd->private_data;

    return dev->media_change;
}

//Revalidate after media change
int sbd_revalidate(struct gendisk *gd) {
    
    struct sbd_dev *dev = gd->private_data;

    if(dev->media_change) 
    {
        dev->media_change = 0;
        memset(dev->data, 0, dev->size);
    }
    return 0;
}

//Runs with device times, simulates media removal
void sbd_invalidate(unsigned long ldev){

    struct sbd_dev *dev = (struct sbd_dev *) ldev;

    spin_lock(&dev->lock);
    if(dev->users || !dev->data)
        printk(KERN_WARNING "sdb: timer sanity check failed\n");
    else
        dev->media_change = 1;
    spin_unlock(&dev->lock);
}

//Implementation of ioctl()
//
//Handles request for drives geometry
//Even though this is virtul, things like fdisk need this for stuff like partitioning
int sbd_ioctl (struct block_device *bdev, fmode_t mode,
                 unsigned int cmd, unsigned long arg){

    long size;
    struct hd_geometry geo;
    struct sbd_dev *dev = bdev->bd_disk->private_data;

    switch(cmd)
    {
        case HDIO_GETGEO:
            size = dev->size*(hardsect_size/KERNEL_SECTOR_SIZE);
            geo.cylinders = (size & ~0x3f) >>6;
            geo.heads = 4;
            geo.sectors = 16;
            geo.start = 4;
            if(copy_to_user((void __user *) arg, &geo, sizeof(geo)))
                return -EFAULT;

        return 0;
    }

    return -ENOTTY;
}


static struct block_device_operations sbd_ops = {
    .owner           = THIS_MODULE,
    .open            = sbd_open,
    .release     = sbd_release,
    .media_changed   = sbd_media_changed,
    .revalidate_disk = sbd_revalidate,
    .ioctl           = sbd_ioctl
};

static void setup_device(struct sbd_dev *dev, int which) {

     // Get some memory.
    memset (dev, 0, sizeof (struct sbd_dev));
    dev->size = nsectors*hardsect_size;
    dev->data = vmalloc(dev->size);
    if (dev->data == NULL) {
        printk (KERN_NOTICE "vmalloc failure.\n");
        return;
    }
    spin_lock_init(&dev->lock);
    
    // The timer which "invalidates" the device.
    init_timer(&dev->timer);
    dev->timer.data = (unsigned long) dev;
    dev->timer.function = sbd_invalidate;
    
     // The I/O queue, depending on whether we are using our own
     // make_request function or not.
    switch (request_mode) {
        case RM_NOQUEUE:
        dev->queue = blk_alloc_queue(GFP_KERNEL);
        if (dev->queue == NULL)
            goto out_vfree;
        blk_queue_make_request(dev->queue, sbd_make_request);
        break;

        case RM_FULL:
        dev->queue = blk_init_queue(sbd_full_request, &dev->lock);
        if (dev->queue == NULL)
            goto out_vfree;
        break;

        default:
        printk(KERN_NOTICE "Bad request mode %d, using simple\n", request_mode);
            /* fall into.. */
    
        case RM_SIMPLE:
        dev->queue = blk_init_queue(sbd_request, &dev->lock);
        if(dev->queue == NULL)
            goto out_vfree;
        break;
    }
    blk_queue_logical_block_size(dev->queue, hardsect_size);
    dev->queue->queuedata = dev;
    /*
     * And the gendisk structure.
     */
    dev->gd = alloc_disk(SBD_MINORS);
    if (! dev->gd) {
        printk (KERN_NOTICE "alloc_disk failure\n");
        goto out_vfree;
    }
    dev->gd->major = sbd_major;
    dev->gd->first_minor = which*SBD_MINORS;
    dev->gd->fops = &sbd_ops;
    dev->gd->queue = dev->queue;
    dev->gd->private_data = dev;
    snprintf (dev->gd->disk_name, 32, "sbfahlman%c", which + 'a');
    set_capacity(dev->gd, nsectors*(hardsect_size/KERNEL_SECTOR_SIZE));
    add_disk(dev->gd);
    return;

  out_vfree:
    if (dev->data)
        vfree(dev->data);
}

static int __init sbd_init(void) {

    int i;

    //Initialize the cipher as an aes cipher with default type and mask
    cipher = crypto_alloc_cipher("aes", 0, 16);
    key_size = strlen(crypto_key);


    sbd_major = register_blkdev(sbd_major, "sbd");
    if(sbd_major <= 0)
    {
        printk(KERN_WARNING "sbd: Can't get major number\n");
        return -EBUSY;
    }

   //Allocate device array, init them
    Devices = kmalloc(ndevices*sizeof (struct sbd_dev), GFP_KERNEL);
    if(Devices == NULL)
        goto out_unregister;
    for(i = 0; i < ndevices; i++)
        setup_device(Devices + i, i);

    return 0;

  out_unregister:
      crypto_free_cipher(cipher);
      unregister_blkdev(sbd_major, "sbd");
      return -ENOMEM;
}

static void sbd_exit(void) {

    int i;

    //Free the cipher
    crypto_free_cipher(cipher);
    for(i = 0; i < ndevices; i++)
    {
        struct sbd_dev *dev = Devices + i;
        
        del_timer_sync(&dev->timer);
        if(dev->gd) 
        {
            del_gendisk(dev->gd);
            put_disk(dev->gd);
        }
        if(dev->queue)
        {
            if(request_mode == RM_NOQUEUE)
                blk_put_queue(dev->queue);
            else
                blk_cleanup_queue(dev->queue);
        }
        if(dev->data)
            vfree(dev->data);

    }
    unregister_blkdev(sbd_major, "sbd");
    kfree(Devices);
}

module_init(sbd_init);
module_exit(sbd_exit);


