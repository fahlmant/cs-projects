/*
 * elevator look
 */
#include <linux/blkdev.h>
#include <linux/elevator.h>
#include <linux/bio.h>
#include <linux/module.h>
#include <linux/slab.h>

struct look_data {
    struct list_head queue;
    sector_t head_position;
    int direction;
};

static void look_merged_requests
(struct request_queue *q, struct request *rq, struct request *next)
{
    list_del_init(&next->queuelist);
}

static int look_dispatch(struct request_queue *q, int force)
{
    struct look_data *nd = q->elevator->elevator_data;
    
    printk("Here is the start of dispatch\n");
    //If request queue is not empty
    if(!list_empty(&nd->queue))
    {
        struct request *next_req, *prev_req, *req;

        //neq_req gets the next closest request grater than the current node
        next_req = list_entry(nd->queue.next, struct request, queuelist);
        //prev_req gets the closest request less than the current node
        prev_req = list_entry(nd->queue.prev, struct request, queuelist);

        //Time to set rq
        
        //Check if the next is the previous, if there one element in the list
        if(prev_req == next_req)
        {
            printk("One request\n");
            req = prev_req;   
        }
        else
        {
            printk("Mutliple requests\n");   
            //If direction is going forward
            if(nd->direction == 1)
            {
                printk("Going forward\n");
                //If the next request is further forward
                if(next_req->__sector > nd->head_position)
                {
                    //The request gets the next request
                    req = next_req;
                }
                //Then the next request must be behind the current request
                else
                {
                    //Switch directions to backward
                    nd->direction = 0;
                    req = prev_req;
                }
            }
            //If the direction is backward
            else
            {
                printk("Going backward\n");
                //If the next request behind
                if(prev_req->__sector < nd->head_position)
                {
                    //The request gets the previous request
                    req = prev_req;
                }
                //Then it must be in front
                else
                {
                    //Switch direction to forward
                    nd->direction = 1;
                    req = next_req;
                }
            }
        }
        printk("Executing\n");   
        //Remove it from the queue we just got it from
        list_del_init(&req->queuelist);
        //get the new position for the read head
        nd->head_position = blk_rq_pos(req) + blk_rq_sectors(req);
        //give request to the elevator 
        elv_dispatch_add_tail(q, req);
        printk("Done Executing\n");
        printk("Taylor's LOOK accessing %llu\n",(unsigned long long) req->__sector);
        return 1;

    }   
    return 0;
}

static void look_add_request(struct request_queue *q, struct request *rq)
{
    struct look_data *nd = q->elevator->elevator_data;
    struct request *next_req, *prev_req;
    sector_t next_req_sector, current_req_sector;
 
    printk("Starting add\n");
    //If list is empty
    if(list_empty(&nd->queue))
    {
        printk("List is empty\n");
        //Just add the request
        list_add(&rq->queuelist, &nd->queue);
    }
    else
    {
        printk("Finding place for request\n");
        //Find where the request fits into the list of requests
        next_req = list_entry(nd->queue.next, struct request, queuelist);
        prev_req = list_entry(nd->queue.prev, struct request, queuelist);
        
        //Get the current sector and the next sector
        next_req_sector = blk_rq_pos(next_req);
        current_req_sector = blk_rq_pos(rq);

        //Find exact spot where the new request fits
        while(current_req_sector > next_req_sector)
        {
            next_req = list_entry(nd->queue.next, struct request, queuelist);
            prev_req = list_entry(nd->queue.prev, struct request, queuelist);
            next_req_sector = blk_rq_pos(rq);
        }
        //Adds the current request between the two nodes
        __list_add(&rq->queuelist, &prev_req->queuelist, &next_req->queuelist);
        printk("Found it\n");
    }
    printk("Taylor's LOOK adding %llu\n", (unsigned long long) rq->__sector);
}

static struct request * 
look_former_request(struct request_queue *q, struct request *rq)
{
    struct look_data *nd = q->elevator->elevator_data;

    if(rq->queuelist.next == &nd->queue)
        return NULL;
    return list_entry(rq->queuelist.next, struct request, queuelist);
}

static struct request * 
look_latter_request(struct request_queue *q, struct request *rq)
{
    struct look_data *nd = q->elevator->elevator_data;

    if(rq->queuelist.next == &nd->queue)
        return NULL;
    return list_entry(rq->queuelist.next, struct request, queuelist);
    return NULL;
}

static void* look_init_queue(struct request_queue *q, struct elevator_type *e)
{
    struct look_data *nd;
    struct elevator_queue *eq;

    eq = elevator_alloc(q, e);
    if(!eq)
        return NULL;

    nd = kmalloc_node(sizeof(*nd), GFP_KERNEL, q->node);
    if(!nd)
    {
       kobject_put(&eq->kobj);
        return NULL;
    }
    
    eq->elevator_data = nd;

    INIT_LIST_HEAD(&nd->queue);
    nd->direction = 1;
    nd->head_position = 0;
    spin_lock_irq(q->queue_lock);
    q->elevator = eq;
    spin_unlock_irq(q->queue_lock);
    return nd;
}

static void look_exit_queue(struct elevator_queue *e)
{
    struct look_data *nd = e->elevator_data;

    BUG_ON(!list_empty(&nd->queue));
    kfree(nd);
}

static struct elevator_type elevator_look = {
    .ops = {
        .elevator_merge_req_fn = look_merged_requests,
        .elevator_dispatch_fn = look_dispatch,
        .elevator_add_req_fn = look_add_request,
        .elevator_former_req_fn = look_former_request,
        .elevator_latter_req_fn = look_latter_request,
        .elevator_init_fn = look_init_queue,
        .elevator_exit_fn = look_exit_queue,
    },
    .elevator_name = "look",
    .elevator_owner = THIS_MODULE,

};

static int __init look_init(void)
{
	return elv_register(&elevator_look);
}

static void __exit look_exit(void)
{
	elv_unregister(&elevator_look);
}

module_init(look_init);
module_exit(look_exit);


MODULE_AUTHOR("Taylor Fahlman");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LOOK IO scheduler");
