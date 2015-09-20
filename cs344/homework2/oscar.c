/*
 *Name: Taylor Fahlman
 *Email: fahlmant@onid.oregonstate.edu
 *Class: CS344-001
 *Assignment #2
 *EXTRA CREDIT IS ATTEMPTED
 *References: man pages of open, close, write, read, getopt, access, lseek, strncpy, sprintf, ctime, getpwduid, getgrgid 
 *http://stackoverflow.com/questions/22418827/strange-segmentation-fault-of-function-strcpy-in-linux-c-program
 *https://gcc.gnu.org/bugs/segfault.html
 *http://stackoverflow.com/questions/503878/how-to-know-what-the-errno-means
 *http://stackoverflow.com/questions/8268316/how-to-retrieve-the-user-name-from-the-user-id
 *http://stackoverflow.com/questions/6646039/printf-t-option
 *http://stackoverflow.com/questions/10323060/printing-file-permissions-like-ls-l-using-stat2-in-c
 *http://www.experts-exchange.com/Programming/Languages/C/Q_21652253.html
 *http://stackoverflow.com/questions/26473642/can-i-use-getopt-to-process-options-in-a-certain-order
 *http://stackoverflow.com/questions/11736060/how-to-read-all-files-in-a-folder-using-c
 *http://stackoverflow.com/questions/503878/how-to-know-what-the-errno-means
 *http://stackoverflow.com/questions/8268316/how-to-retrieve-the-user-name-from-the-user-id
 *http://stackoverflow.com/questions/13145777/c-char-to-int-conversion
 *http://stackoverflow.com/questions/8268316/how-to-retrieve-the-user-name-from-the-user-id



 *
 */


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <utime.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include "oscar.h"

void archive_file(int archive_d, char** argv, int argc, int next_arg, int arch_opt_flag, int verbose_flag );

//function takes in an archive name and creats the .oscar file
void create_archive(char *archive, int verbose_flag)
{
    //sets file descriptor to 0
    
    int archive_d = 0;
   //Sets the header  
    char *header = OSCAR_ID;

    //creates an archive with permissions 0644 in octal.
    //Gives users, group and other w+r permissions
    if(verbose_flag == 1){printf("Creating archive file with permissions -rw-r--r--\n");}
    archive_d = open(archive, O_CREAT | O_WRONLY, 0644);
    if(archive_d  == -1)
    {
        printf("Error creating the archive");
    }

    if(verbose_flag == 1){printf("Writing the header to the archive\n");}
    //write the header to the file
    write(archive_d, header, OSCAR_ID_LEN);
    
    //closes the file
    if(verbose_flag == 1){printf("Closing the archive\n");}
    int close_check = close(archive_d);
    if(close_check != 0)
    {
        printf("File did not close correctly \n");
    }
}

void append_archive(char* archive, char** argv, int argc, int next_arg, int arch_opt_flag, int verbose_flag)
{
    //Initialize all variables
    int archive_d = 0;
    int archive_d_read = 0;
    int file_d = 0;
    char* file_name = argv[next_arg];
    char header_buff[OSCAR_ID_LEN];

    //Opens archive twice, one for reading, one for writing
    if(verbose_flag == 1){printf("Opening archive to write to it\n");}
    archive_d_read = open(archive, O_RDONLY);
    archive_d = open(archive, O_APPEND);//O_WRONLY);

    if(archive_d == -1)
    {
        printf("Error opening archive to append!\n");
    }

    //Need to check if header exists
    int bytes_read = read(archive_d_read, header_buff, OSCAR_ID_LEN);
    if(verbose_flag == 1){printf("Checking header of archive to see if it's valid\n");}
    header_buff[OSCAR_ID_LEN] = '\0';
    
    if(strcmp(header_buff, OSCAR_ID) != 0)
    {
        printf("Archive is corrupt or is not an Oscar file");
    }

    if(verbose_flag == 1){printf("Archiving files\n");}
    if(arch_opt_flag == 0)
    {
        for(next_arg; next_arg < argc; next_arg++)
        {
            archive_d = open(archive, O_APPEND | O_WRONLY);
            archive_file(archive_d, argv, argc, next_arg, arch_opt_flag, verbose_flag);
            close(archive_d);
        }
    }

    if(verbose_flag == 1){printf("Closing archive\n");}
    close(file_d);
}

void big_a(char** argv, int argc, char* archive, int optind, int verbose_flag)
{
    int files = 0;
    char file_names[100][OSCAR_MAX_FILE_NAME_LEN];
    struct stat file_info;
    struct dirent *file;
    
    if(verbose_flag == 1){printf("Get present working dir\n");}

    char pwd[1000];
    getcwd(pwd, sizeof(pwd));
    DIR *pr_dir = opendir(pwd);

    memset(file_names, '\0', sizeof(file_names));

    strcpy(file_names[0], archive);

    file = readdir(pr_dir);
    if(verbose_flag == 1){printf("Get all files names in pwd\n");}
    while(file != NULL)
    {
        stat(file->d_name, &file_info);

        if(S_ISREG(file_info.st_mode))
        {
            files++;
            strcpy(file_names[files], file->d_name);
        }

        file = readdir(pr_dir);
    }
    if(verbose_flag == 1){printf("Write all files to archive\n");}
    int archive_fd = open(archive, O_CREAT | O_WRONLY, 0644);
    int file_fd;
    char buffer[sizeof(struct oscar_hdr)];
    write(archive_fd, OSCAR_ID, OSCAR_ID_LEN);
    close(archive_fd);

    int i; 
    for(i; i < files; i++)
    {
        int archive_d = open(archive, O_APPEND | O_WRONLY);
        struct stat stat_info;
        //makes sure the file exists
        if(access(file_names[i], F_OK) == -1)
        {
            printf("File does not exists\n");
        }
        else
        {

            struct oscar_hdr current_file;
            int file_name_len = strlen(file_names[i]);
            int i = 0;
            int file_size;
            //char 

            //initialized all character strings to spaces

           (void)memset((void*) &current_file, ' ', sizeof(struct oscar_hdr));
            
            //copies all stat info into oscar struct
            strncpy(current_file.oscar_name, file_names[i], OSCAR_MAX_FILE_NAME_LEN);
            if(verbose_flag == 1){printf("File Name: %s\n", current_file.oscar_name);}
            int file_d = open(current_file.oscar_name, O_RDONLY);
            fstat(file_d, &stat_info);
            file_size = stat_info.st_size;
            char* file_cont[file_size]; 
            sprintf(current_file.oscar_name, file_names[i], file_name_len);
            sprintf(current_file.oscar_name_len, "%d", file_name_len);
            sprintf(current_file.oscar_cdate, "%d", stat_info.st_ctime);
            sprintf(current_file.oscar_adate, "%d", stat_info.st_atime);
            sprintf(current_file.oscar_mdate, "%d", stat_info.st_mtime);
            sprintf(current_file.oscar_uid, "%d", stat_info.st_uid);
            sprintf(current_file.oscar_gid, "%d", stat_info.st_gid);
            sprintf(current_file.oscar_mode, "%o", stat_info.st_mode);
            sprintf(current_file.oscar_size, "%d", stat_info.st_size);
            current_file.oscar_deleted = ' '; 
            strcpy(current_file.oscar_hdr_end, OSCAR_HDR_END);
            
            //replaces all null terminators with spaces
            int j = 0;
            for(j; j < OSCAR_MAX_FILE_NAME_LEN; j++)
            {
                if(current_file.oscar_name[j] == '\0')
                {
                    current_file.oscar_name[j] = ' '; 
                }
                if(current_file.oscar_cdate[j] == '\0')
                {
                    current_file.oscar_cdate[j] = ' ';
                }
                if(current_file.oscar_mdate[j] == '\0')
                {
                    current_file.oscar_mdate[j] = ' ';
                }
                if(current_file.oscar_adate[j] == '\0')
                {
                    current_file.oscar_adate[j] = ' ';
                }
                if(current_file.oscar_uid[j] == '\0')
                {
                    current_file.oscar_uid[j] = ' ';
                }
                if(current_file.oscar_gid[j] == '\0')
                {
                    current_file.oscar_gid[j] = ' ';
                }
                if(current_file.oscar_mode[j] == '\0')
                {
                    current_file.oscar_mode[j] = ' ';
                }
                if(current_file.oscar_size[j] == '\0')
                {
                    current_file.oscar_size[j] = ' ';
                }
                if(current_file.oscar_name_len[j] == '\0')
                {
                    current_file.oscar_name_len[j] = ' ';
                }
                if(current_file.oscar_sha1[j] == '\0')
                {
                    current_file.oscar_sha1[j] = ' ';
                }
            }

            char oscar_del[1];
            oscar_del[0] = current_file.oscar_deleted;
            
            if(file_d == -1)
            {
                printf("File wasn't opened\n");
                printf("Error: %s\n", strerror(errno));
            }
            if(current_file.oscar_name_len[1] == ' ')
            {
                current_file.oscar_name_len[1] = current_file.oscar_name_len[0];
                current_file.oscar_name_len[0] = ' ';
            }
    if(verbose_flag == 1){printf("Writing all info to file\n");}
            //writes all info the the archive file
            lseek(archive_d, OSCAR_ID_LEN, SEEK_SET);
            write(archive_d, current_file.oscar_name, OSCAR_MAX_FILE_NAME_LEN);
            write(archive_d, current_file.oscar_name_len, 2);
            write(archive_d, current_file.oscar_cdate, OSCAR_DATE_SIZE);
            write(archive_d, current_file.oscar_adate, OSCAR_DATE_SIZE);
            write(archive_d, current_file.oscar_mdate, OSCAR_DATE_SIZE);
            write(archive_d, current_file.oscar_uid, OSCAR_UGID_SIZE);
            write(archive_d, current_file.oscar_gid, OSCAR_UGID_SIZE);
            write(archive_d, current_file.oscar_mode, OSCAR_MODE_SIZE);
            write(archive_d, current_file.oscar_size, sizeof(current_file.oscar_size));
            oscar_del[0] = ' ';
            write(archive_d, oscar_del, 1);
            write(archive_d, current_file.oscar_sha1, OSCAR_SHA_DIGEST_LEN);
            write(archive_d, current_file.oscar_hdr_end, 2);
            read(file_d, file_cont, file_size);
            write(archive_d, file_cont, file_size);

            //closes file
            close(file_d);
                  
        
        }        
    }

}

void archive_file(int archive_d, char** argv, int argc, int next_arg, int arch_opt_flag, int verbose_flag )
{
    int file_d;

        //creates the stat struct
        struct stat stat_info;
        //makes sure the file exists
        if(access(argv[next_arg], F_OK) == -1)
        {
            printf("File does not exists\n");
        }
        else
        {
            struct oscar_hdr current_file;
            int file_name_len = strlen(argv[next_arg]);
            int i = 0;
            int file_size;
            //char 

            //initialized all character strings to spaces
    if(verbose_flag == 1){printf("Initilizing struct\n");}
           (void)memset((void*) &current_file, ' ', sizeof(struct oscar_hdr));
            
    if(verbose_flag == 1){printf("copying all stat info into oscar struct\n");}
            //copies all stat info into oscar struct
            strncpy(current_file.oscar_name, argv[next_arg], OSCAR_MAX_FILE_NAME_LEN);
            if(verbose_flag == 1){printf("File Name: %s\n", current_file.oscar_name);}
            int file_d = open(current_file.oscar_name, O_RDONLY);
            fstat(file_d, &stat_info);
            file_size = stat_info.st_size;
            char* file_cont[file_size]; 
            sprintf(current_file.oscar_name, argv[next_arg], file_name_len);
            sprintf(current_file.oscar_name_len, "%d", file_name_len);
            sprintf(current_file.oscar_cdate, "%d", stat_info.st_ctime);
            sprintf(current_file.oscar_adate, "%d", stat_info.st_atime);
            sprintf(current_file.oscar_mdate, "%d", stat_info.st_mtime);
            sprintf(current_file.oscar_uid, "%d", stat_info.st_uid);
            sprintf(current_file.oscar_gid, "%d", stat_info.st_gid);
            sprintf(current_file.oscar_mode, "%o", stat_info.st_mode);
            sprintf(current_file.oscar_size, "%d", stat_info.st_size);
            current_file.oscar_deleted = ' '; 
            strcpy(current_file.oscar_hdr_end, OSCAR_HDR_END);
            
            //replaces all null terminators with spaces
            int j = 0;
            for(j; j < OSCAR_MAX_FILE_NAME_LEN; j++)
            {
                if(current_file.oscar_name[j] == '\0')
                {
                    current_file.oscar_name[j] = ' '; 
                }
                if(current_file.oscar_cdate[j] == '\0')
                {
                    current_file.oscar_cdate[j] = ' ';
                }
                if(current_file.oscar_mdate[j] == '\0')
                {
                    current_file.oscar_mdate[j] = ' ';
                }
                if(current_file.oscar_adate[j] == '\0')
                {
                    current_file.oscar_adate[j] = ' ';
                }
                if(current_file.oscar_uid[j] == '\0')
                {
                    current_file.oscar_uid[j] = ' ';
                }
                if(current_file.oscar_gid[j] == '\0')
                {
                    current_file.oscar_gid[j] = ' ';
                }
                if(current_file.oscar_mode[j] == '\0')
                {
                    current_file.oscar_mode[j] = ' ';
                }
                if(current_file.oscar_size[j] == '\0')
                {
                    current_file.oscar_size[j] = ' ';
                }
                if(current_file.oscar_name_len[j] == '\0')
                {
                    current_file.oscar_name_len[j] = ' ';
                }
                if(current_file.oscar_sha1[j] == '\0')
                {
                    current_file.oscar_sha1[j] = ' ';
                }
            }

            char oscar_del[1];
            oscar_del[0] = current_file.oscar_deleted;
            
            if(file_d == -1)
            {
                printf("File wasn't opened\n");
                printf("Error: %s\n", strerror(errno));
            }
            if(current_file.oscar_name_len[1] == ' ')
            {
                current_file.oscar_name_len[1] = current_file.oscar_name_len[0];
                current_file.oscar_name_len[0] = ' ';
            }
    if(verbose_flag == 1){printf("Writing all info to file\n");}
            //writes all info the the archive file
            lseek(archive_d, OSCAR_ID_LEN, SEEK_SET);
            write(archive_d, current_file.oscar_name, OSCAR_MAX_FILE_NAME_LEN);
            write(archive_d, current_file.oscar_name_len, 2);
            write(archive_d, current_file.oscar_cdate, OSCAR_DATE_SIZE);
            write(archive_d, current_file.oscar_adate, OSCAR_DATE_SIZE);
            write(archive_d, current_file.oscar_mdate, OSCAR_DATE_SIZE);
            write(archive_d, current_file.oscar_uid, OSCAR_UGID_SIZE);
            write(archive_d, current_file.oscar_gid, OSCAR_UGID_SIZE);
            write(archive_d, current_file.oscar_mode, OSCAR_MODE_SIZE);
            write(archive_d, current_file.oscar_size, sizeof(current_file.oscar_size));
            oscar_del[0] = ' ';
            write(archive_d, oscar_del, 1);
            write(archive_d, current_file.oscar_sha1, OSCAR_SHA_DIGEST_LEN);
            write(archive_d, current_file.oscar_hdr_end, 2);
            read(file_d, file_cont, file_size);
            write(archive_d, file_cont, file_size);

            //closes file
            close(file_d);
    } 
}
int extract_file(int archive_fd, char* file_name, int o_write, int extract_flag, int verbose_flag);

void extract_handler(char**argv, char* archive, int argc, int next_arg, int o_write, int e_flag, int verbose_flag)
{
    char file_name[OSCAR_MAX_FILE_NAME_LEN];
    int archive_fd;
    char file_size[OSCAR_FILE_SIZE];
    char temp_buff[1];
    char test_buff[40];
    char* f_name;
    size_t bytes_r;
    int i = 0;

    if(next_arg < argc)
    {
    if(verbose_flag == 1){printf("Attempting to extract all member files\n");}
        for(next_arg; next_arg < argc; next_arg++)
        {
            strncpy(file_name, argv[next_arg], OSCAR_MAX_FILE_NAME_LEN);
            archive_fd = open(archive, O_RDONLY);
            //extract the file
            extract_file(archive_fd, file_name, o_write, e_flag, verbose_flag);
            read(archive_fd, test_buff, 40);
        }
    }
    else
    { 

    if(verbose_flag == 1){printf("Attempting to extract all files in archive\n");}

        archive_fd = open(archive, O_RDONLY);
        lseek(archive_fd, OSCAR_ID_LEN, SEEK_SET); 
        while(read(archive_fd, test_buff, 1) != 0)
        {
            lseek(archive_fd, -1, SEEK_CUR);
            char temp_name[OSCAR_MAX_FILE_NAME_LEN];
            read(archive_fd, temp_name, OSCAR_MAX_FILE_NAME_LEN);
            i = 0;
            char temp[strlen(temp_name)];
            for(i; i <strlen(temp_name); i ++)
            {
                if(temp_name[i] == ' ')
                {
                    temp_name[i] = '\0';
                }
            }
            int ret = extract_file(archive_fd, temp_name, o_write, e_flag, verbose_flag);
            if(ret == 1)
            {
                lseek(archive_fd, 2 + (3*OSCAR_DATE_SIZE) + (2*OSCAR_UGID_SIZE) + OSCAR_MODE_SIZE, SEEK_CUR);
                char size_buff[OSCAR_FILE_SIZE];
                read(archive_fd, size_buff, OSCAR_FILE_SIZE);
                lseek(archive_fd, 1 + OSCAR_SHA_DIGEST_LEN + OSCAR_HDR_END_LEN + atoi(size_buff), SEEK_CUR);
            }

        }
    }



}

int extract_file(int archive_fd, char* file_name, int o_write, int extract_flag, int verbose_flag)
{
    //initilize varaibles
    char test[1];
    char arch_name_len[2];
    int arc_name;
    char marked[1];
    marked[0] = ' ';
    char archive_file_buff[OSCAR_MAX_FILE_NAME_LEN];
    char ctime_buff[OSCAR_DATE_SIZE];
    char atime_buff[OSCAR_DATE_SIZE];
    char mtime_buff[OSCAR_DATE_SIZE];
    char perm_buff[OSCAR_MODE_SIZE];
    char cont_size_buff[OSCAR_FILE_SIZE];
    int to_create_fd;
    struct utimbuf *times;

    //strncpy(file_name, argv[next_arg], OSCAR_MAX_FILE_NAME_LEN);
    //archive_fd = open(archive, O_RDONLY);
    lseek(archive_fd, OSCAR_ID_LEN, SEEK_SET);
 
    //mnake sure you're not at end of archive, or you already got the file
    while(read(archive_fd, test, 1) != 0 || strcmp(archive_file_buff, file_name) == 0)
    {
        //lseek back the byte
        lseek(archive_fd, -1, SEEK_CUR);
        //get the file name fomr the archivei
        lseek(archive_fd, OSCAR_MAX_FILE_NAME_LEN, SEEK_CUR);
        read(archive_fd, arch_name_len, 2);
        lseek(archive_fd, -2, SEEK_CUR);
        lseek(archive_fd, -OSCAR_MAX_FILE_NAME_LEN, SEEK_CUR);
        arc_name = atoi(arch_name_len);
        read(archive_fd, archive_file_buff, arc_name);
        lseek(archive_fd,  OSCAR_MAX_FILE_NAME_LEN - arc_name,  SEEK_CUR);
        archive_file_buff[arc_name] = '\0';
        lseek(archive_fd, 2 + (3*OSCAR_DATE_SIZE) + (2*OSCAR_UGID_SIZE) + OSCAR_MODE_SIZE + OSCAR_FILE_SIZE, SEEK_CUR);
        read(archive_fd, marked, 1);
        lseek(archive_fd, -(1 + 2 + (3*OSCAR_DATE_SIZE) + (2*OSCAR_UGID_SIZE) + OSCAR_MODE_SIZE + OSCAR_FILE_SIZE), SEEK_CUR);

        //if this is the file to extract
        if(marked[0] == ' ')
        {
            int str_len_of_file = strlen(file_name);
            if(strncmp(archive_file_buff, file_name, str_len_of_file) == 0)
            {
                //if overwrite is set
                if(o_write == 1)
                {
                    //create the file
                    to_create_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC);
                }   
                else
                {
                    if(access(file_name, F_OK) == -1)
                    {
                        to_create_fd = open(file_name, O_CREAT | O_WRONLY);
                    }
                    else
                    {
                        return 1;
                    }
                }
                if(verbose_flag==1){printf("Getting all information about file to extract\n");}
                    //if extract is set
                if(extract_flag == 0)
                {
                    //get times
                    lseek(archive_fd, 2, SEEK_CUR);
                    read(archive_fd, ctime_buff, OSCAR_DATE_SIZE);
                    ctime_buff[OSCAR_DATE_SIZE] = '\0';
                    read(archive_fd, atime_buff, OSCAR_DATE_SIZE);
                    atime_buff[OSCAR_DATE_SIZE] = '\0';
                    read(archive_fd, mtime_buff, OSCAR_DATE_SIZE);
                    lseek(archive_fd, OSCAR_UGID_SIZE, SEEK_CUR);
                    lseek(archive_fd, OSCAR_UGID_SIZE, SEEK_CUR);
                }

                else if(extract_flag == 1)
                {
                    //lseek to permissions
                    lseek(archive_fd, 2 + (3*OSCAR_DATE_SIZE) + (2*OSCAR_UGID_SIZE), SEEK_CUR);
                }

                if(verbose_flag==1){printf("Applying information about file to extracted file\n");}

                //get mode, contents size, and contents, write them to file
                read(archive_fd, perm_buff, OSCAR_MODE_SIZE);
                perm_buff[OSCAR_MODE_SIZE] = '\0';
                perm_buff[0] = ' ';
                read(archive_fd, cont_size_buff, OSCAR_FILE_SIZE);
                int cont_size = atoi(cont_size_buff);
                char cont_buff[cont_size];
                lseek(archive_fd, 1, SEEK_CUR);
                lseek(archive_fd, OSCAR_SHA_DIGEST_LEN, SEEK_CUR);
                lseek(archive_fd, 2, SEEK_CUR);
                read(archive_fd, cont_buff, cont_size);
                cont_buff[cont_size] = '\0';
                mode_t perm = strtol(perm_buff, NULL, 8);
                chmod(file_name, perm);
                write(to_create_fd, cont_buff, cont_size);
                if(extract_flag == 0)
                {
                    times->actime = atoi(atime_buff);
                    times->modtime = atoi(mtime_buff);
                    utime(file_name, times);
                }
            }
            else
            {
                lseek(archive_fd, -(OSCAR_MAX_FILE_NAME_LEN), SEEK_CUR);
                lseek(archive_fd, sizeof(struct oscar_hdr), SEEK_CUR);
            }
        }
        else
            return 1;
    
    }

    return 0;
}

void remove_file(char** argv, int argc, char* archive, int optind, int verbose_flag)
{

    char file_name[OSCAR_MAX_FILE_NAME_LEN];
    char file_size[OSCAR_FILE_SIZE];
    char oscar_rd_buff[OSCAR_ID_LEN];
    char marked[1];
    char temp_buff[1];
    int to_delete;
    char arch_buff[OSCAR_MAX_FILE_NAME_LEN];
    int i = 0;
    int end = 1;
    char buff[(OSCAR_DATE_SIZE * 3) + (OSCAR_UGID_SIZE * 2) + OSCAR_MODE_SIZE + OSCAR_MAX_FILE_NAME_LEN + OSCAR_MAX_MEMBER_FILE_SIZE + OSCAR_HDR_END_LEN] = {'\0'};
    archive = argv[optind];

    for(i; i < OSCAR_MAX_FILE_NAME_LEN; i++)
    {
        file_name[i] = ' ';

    }
    int archive_fd = open(argv[optind], O_RDONLY);

 

    lseek(archive_fd, 0,  SEEK_SET);
    read(archive_fd, oscar_rd_buff, OSCAR_ID_LEN);
    lseek(archive_fd, OSCAR_ID_LEN, SEEK_SET);
    oscar_rd_buff[OSCAR_ID_LEN] = '\0';
    if(strcmp(oscar_rd_buff, OSCAR_ID) != 0)
    {
        printf("Archive is corrupt or is not an Oscar file");
        exit(1);
    }
    int temp_arch_fd = open("temp.oscar", O_CREAT | O_WRONLY, 0644);
    write(temp_arch_fd, OSCAR_ID, OSCAR_ID_LEN);

    end = read(archive_fd, temp_buff, 1);
    if(verbose_flag == 1){printf("Searching archvie for file to removei\n");}
    while(end)
    {
        lseek(archive_fd, -1, SEEK_CUR);
        for(i = 0; i < OSCAR_MAX_FILE_NAME_LEN; i++)
        {
            file_name[i] = '\0';
        }
        read(archive_fd, file_name, OSCAR_MAX_FILE_NAME_LEN);

        for(i = 0; i < OSCAR_MAX_FILE_NAME_LEN; i++)
		{
			if(file_name[i] == ' ')
			{
				file_name[i] = '\0';
			}
		}

        lseek(archive_fd, 2 + OSCAR_DATE_SIZE + OSCAR_DATE_SIZE +  OSCAR_DATE_SIZE + OSCAR_UGID_SIZE + OSCAR_UGID_SIZE + OSCAR_MODE_SIZE, SEEK_CUR);
        read(archive_fd, file_size, OSCAR_FILE_SIZE);

        read(archive_fd, marked, 1);

        to_delete = 0;
        for(i = optind + 1; i < argc; i++)
        {
            if(!strcmp(argv[i], file_name) && marked[0] != 'y')
            {
                to_delete = 1;
                argv[i][0] = '\0';

            }
        }

        if(to_delete)
        {
            lseek(archive_fd, atoi(file_size) + OSCAR_HDR_END_LEN + OSCAR_SHA_DIGEST_LEN, SEEK_CUR);
        }
        else
        {

        lseek(archive_fd, -(OSCAR_MAX_FILE_NAME_LEN + 2 + (2*OSCAR_UGID_SIZE) + (3*OSCAR_DATE_SIZE) + OSCAR_MODE_SIZE + OSCAR_FILE_SIZE + 1), SEEK_CUR); 

            read(archive_fd, buff, (sizeof(struct oscar_hdr) + atoi(file_size)));
            
            temp_arch_fd = open("temp.oscar", O_WRONLY | O_APPEND);
            write(temp_arch_fd, buff,  (sizeof(struct oscar_hdr) + atoi(file_size)));
            close(temp_arch_fd);
         } 

         end = read(archive_fd, temp_buff, 1); 

    }
    close(archive_fd);
    remove(argv[optind]);
    rename("temp.oscar", argv[optind]);
}

mark_file(char** argv, int argc ,char* archive, int optind)
{

    char file_name[OSCAR_MAX_FILE_NAME_LEN];
    char file_size[OSCAR_FILE_SIZE];
    char oscar_rd_buff[OSCAR_ID_LEN];
    char marked[1];
    char temp_buff[1];
    int to_delete;
    char arch_buff[OSCAR_MAX_FILE_NAME_LEN];
    int i = 0;
    int end = 1;
    char y[1];
    y[0] = 'y';
    char buff[(OSCAR_DATE_SIZE * 3) + (OSCAR_UGID_SIZE * 2) + OSCAR_MODE_SIZE + OSCAR_MAX_FILE_NAME_LEN + OSCAR_MAX_MEMBER_FILE_SIZE + OSCAR_HDR_END_LEN] = {'\0'};
    archive = argv[optind];

    for(i; i < OSCAR_MAX_FILE_NAME_LEN; i++)
    {
        file_name[i] = ' ';

    }
    int archive_fd = open(argv[optind], O_RDWR);

 

    lseek(archive_fd, 0,  SEEK_SET);
    read(archive_fd, oscar_rd_buff, OSCAR_ID_LEN);
    lseek(archive_fd, OSCAR_ID_LEN, SEEK_SET);
    oscar_rd_buff[OSCAR_ID_LEN] = '\0';
    if(strcmp(oscar_rd_buff, OSCAR_ID) != 0)
    {
        printf("Archive is corrupt or is not an Oscar file");
        exit(1);
    }
    end = read(archive_fd, temp_buff, 1);

    while(end)
    {
        lseek(archive_fd, -1, SEEK_CUR);
        for(i = 0; i < OSCAR_MAX_FILE_NAME_LEN; i++)
        {
            file_name[i] = '\0';
        }
        read(archive_fd, file_name, OSCAR_MAX_FILE_NAME_LEN);

        for(i = 0; i < OSCAR_MAX_FILE_NAME_LEN; i++)
		{
			if(file_name[i] == ' ')
			{
				file_name[i] = '\0';
			}
		}

        lseek(archive_fd, 2 + OSCAR_DATE_SIZE + OSCAR_DATE_SIZE +  OSCAR_DATE_SIZE + OSCAR_UGID_SIZE + OSCAR_UGID_SIZE + OSCAR_MODE_SIZE, SEEK_CUR);
        read(archive_fd, file_size, OSCAR_FILE_SIZE);

        read(archive_fd, marked, 1);

        to_delete = 0;
        for(i = optind + 1; i < argc; i++)
        {
            if(!strcmp(argv[i], file_name) && marked[0] != 'y')
            {
                to_delete = 1;
                argv[i][0] = '\0';

            }
        }

        if(to_delete)
        {
            lseek(archive_fd, -1, SEEK_CUR);
            write(archive_fd, y, 1);
        }

        lseek(archive_fd, atoi(file_size) + OSCAR_HDR_END_LEN + OSCAR_SHA_DIGEST_LEN, SEEK_CUR);

          
        end = read(archive_fd, temp_buff, 1); 

    }
    close(archive_fd); 
}

unmark_file(char** argv, int argc ,char* archive, int optind)
{

    char file_name[OSCAR_MAX_FILE_NAME_LEN];
    char file_size[OSCAR_FILE_SIZE];
    char oscar_rd_buff[OSCAR_ID_LEN];
    char marked[1];
    char temp_buff[1];
    int to_delete;
    char arch_buff[OSCAR_MAX_FILE_NAME_LEN];
    int i = 0;
    int end = 1;
    char y[1];
    y[0] = ' ';
    char buff[(OSCAR_DATE_SIZE * 3) + (OSCAR_UGID_SIZE * 2) + OSCAR_MODE_SIZE + OSCAR_MAX_FILE_NAME_LEN + OSCAR_MAX_MEMBER_FILE_SIZE + OSCAR_HDR_END_LEN] = {'\0'};
    archive = argv[optind];

    for(i; i < OSCAR_MAX_FILE_NAME_LEN; i++)
    {
        file_name[i] = ' ';

    }
    int archive_fd = open(argv[optind], O_RDWR);

 

    lseek(archive_fd, 0,  SEEK_SET);
    read(archive_fd, oscar_rd_buff, OSCAR_ID_LEN);
    lseek(archive_fd, OSCAR_ID_LEN, SEEK_SET);
    oscar_rd_buff[OSCAR_ID_LEN] = '\0';
    if(strcmp(oscar_rd_buff, OSCAR_ID) != 0)
    {
        printf("Archive is corrupt or is not an Oscar file");
        exit(1);
    }
    end = read(archive_fd, temp_buff, 1);

    while(end)
    {
        lseek(archive_fd, -1, SEEK_CUR);
        for(i = 0; i < OSCAR_MAX_FILE_NAME_LEN; i++)
        {
            file_name[i] = '\0';
        }
        read(archive_fd, file_name, OSCAR_MAX_FILE_NAME_LEN);

        for(i = 0; i < OSCAR_MAX_FILE_NAME_LEN; i++)
		{
			if(file_name[i] == ' ')
			{
				file_name[i] = '\0';
			}
		}

        lseek(archive_fd, 2 + OSCAR_DATE_SIZE + OSCAR_DATE_SIZE +  OSCAR_DATE_SIZE + OSCAR_UGID_SIZE + OSCAR_UGID_SIZE + OSCAR_MODE_SIZE, SEEK_CUR);
        read(archive_fd, file_size, OSCAR_FILE_SIZE);

        read(archive_fd, marked, 1);

        to_delete = 0;
        for(i = optind + 1; i < argc; i++)
        {
            if(!strcmp(argv[i], file_name) && marked[0] == 'y')
            {
                to_delete = 1;
                argv[i][0] = '\0';

            }
        }

        if(to_delete)
        {
            lseek(archive_fd, -1, SEEK_CUR);
            write(archive_fd, y, 1);
        }

        lseek(archive_fd, atoi(file_size) + OSCAR_HDR_END_LEN + OSCAR_SHA_DIGEST_LEN, SEEK_CUR);

          
        end = read(archive_fd, temp_buff, 1); 

    }
    close(archive_fd); 
}
    
void cleanse(char** argv, int argc, char* archive, int optind)
{

    char file_name[OSCAR_MAX_FILE_NAME_LEN];
    char file_size[OSCAR_FILE_SIZE];
    char oscar_rd_buff[OSCAR_ID_LEN];
    char marked[1];
    char temp_buff[1];
    int to_delete;
    char arch_buff[OSCAR_MAX_FILE_NAME_LEN];
    int i = 0;
    int end = 1;
    char buff[(OSCAR_DATE_SIZE * 3) + (OSCAR_UGID_SIZE * 2) + OSCAR_MODE_SIZE + OSCAR_MAX_FILE_NAME_LEN + OSCAR_MAX_MEMBER_FILE_SIZE + OSCAR_HDR_END_LEN] = {'\0'};
    archive = argv[optind];

    for(i; i < OSCAR_MAX_FILE_NAME_LEN; i++)
    {
        file_name[i] = ' ';

    }
    int archive_fd = open(argv[optind], O_RDONLY);

 

    lseek(archive_fd, 0,  SEEK_SET);
    read(archive_fd, oscar_rd_buff, OSCAR_ID_LEN);
    lseek(archive_fd, OSCAR_ID_LEN, SEEK_SET);
    oscar_rd_buff[OSCAR_ID_LEN] = '\0';
    if(strcmp(oscar_rd_buff, OSCAR_ID) != 0)
    {
        printf("Archive is corrupt or is not an Oscar file");
        exit(1);
    }
    int temp_arch_fd = open("temp.oscar", O_CREAT | O_WRONLY, 0644);
    write(temp_arch_fd, OSCAR_ID, OSCAR_ID_LEN);

    end = read(archive_fd, temp_buff, 1);

    while(end)
    {
        lseek(archive_fd, -1, SEEK_CUR);
        for(i = 0; i < OSCAR_MAX_FILE_NAME_LEN; i++)
        {
            file_name[i] = '\0';
        }
        read(archive_fd, file_name, OSCAR_MAX_FILE_NAME_LEN);

        for(i = 0; i < OSCAR_MAX_FILE_NAME_LEN; i++)
		{
			if(file_name[i] == ' ')
			{
				file_name[i] = '\0';
			}
		}

        lseek(archive_fd, 2 + OSCAR_DATE_SIZE + OSCAR_DATE_SIZE +  OSCAR_DATE_SIZE + OSCAR_UGID_SIZE + OSCAR_UGID_SIZE + OSCAR_MODE_SIZE, SEEK_CUR);
        read(archive_fd, file_size, OSCAR_FILE_SIZE);

        read(archive_fd, marked, 1);

        to_delete = 0;
            if(marked[0] == 'y')
            {
                to_delete = 1;

            }

        if(to_delete)
        {
            lseek(archive_fd, atoi(file_size) + OSCAR_HDR_END_LEN + OSCAR_SHA_DIGEST_LEN, SEEK_CUR);
        }
        else
        {

        lseek(archive_fd, -(OSCAR_MAX_FILE_NAME_LEN + 2 + (2*OSCAR_UGID_SIZE) + (3*OSCAR_DATE_SIZE) + OSCAR_MODE_SIZE + OSCAR_FILE_SIZE + 1), SEEK_CUR); 

            read(archive_fd, buff, (sizeof(struct oscar_hdr) + atoi(file_size)));
            
            temp_arch_fd = open("temp.oscar", O_WRONLY | O_APPEND);
            write(temp_arch_fd, buff,  (sizeof(struct oscar_hdr) + atoi(file_size)));
            close(temp_arch_fd);
         } 

         end = read(archive_fd, temp_buff, 1); 

    }
    close(archive_fd);
    remove(argv[optind]);
    rename("temp.oscar", argv[optind]);
}
void help_text()
{
    printf("Usage: myoscar [-options] [archive file] [files...]\n");
    printf("Command Line options: \n");
    printf("-a Archive file(s) given in command line to archive\n");
    printf("-A Archive all regular files in current directory\n");
    printf("-e Extract file(s) from archvie, restore time stamps\n");
    printf("-E Extract files(s) from archive, don't restore time stamps\n");
    printf("-d Remove files(s) from archive\n");
    printf("-o Overwrites file(s) if they exist while extracting\n");
    printf("-h Displays help\n");
    printf("-t Displays short table of contents for archive\n");
    printf("-T Displays long table of contents for archive\n");
    printf("-V Prints version informations\n");
    printf("-v Verbose processing\n");

}

void version_text()
{
    printf("Version 1.0 \nCreated by Taylor Fahlman\n");
}

void print_perms(char* permissions)
{
    mode_t perm = strtol(permissions, NULL, 8);
    printf((perm & S_IRUSR) ? "r" : "-");
    printf((perm & S_IWUSR) ? "w" : "-");
    printf((perm & S_IXUSR) ? "x" : "-");
    printf((perm & S_IRGRP) ? "r" : "-");
    printf((perm & S_IWGRP) ? "w" : "-");
    printf((perm & S_IXGRP) ? "x" : "-");
    printf((perm & S_IROTH) ? "r" : "-");
    printf((perm & S_IWOTH) ? "w" : "-");
    printf((perm & S_IXOTH) ? "x" : "-");
}

void table_of_contents(char* archive, char** argv, int next_arg, int table_flag, int verbose_flag)
{

    //create all variables needed
    int archive_fd = open(archive, O_RDONLY);
    char test_buff[1];
    char file_name_buff[OSCAR_MAX_FILE_NAME_LEN];
    char access_time_buff[OSCAR_DATE_SIZE];
    char create_time_buff[OSCAR_DATE_SIZE];
    char mod_time_buff[OSCAR_DATE_SIZE];
    char per_buff[OSCAR_MODE_SIZE];
    char uid_buff[OSCAR_UGID_SIZE];
    char gid_buff[OSCAR_UGID_SIZE];
    char file_len_buff[OSCAR_FILE_SIZE];
    char marked_buff[1];
    char file_name_len_buff[2];
    char marked;
    int len_of_file = 0;
    char file_name_len[2];
    struct passwd *pass;
    struct group *gr;
    time_t mod_time;
    time_t cre_time;
    time_t acc_time;
    char* mod_t_final;
    char* cre_t_final;
    char* acc_t_final;

    //all info after file name, puls 15 for maked bytes and end tag
    int len_before_file_size = OSCAR_DATE_SIZE + OSCAR_DATE_SIZE + OSCAR_DATE_SIZE + OSCAR_UGID_SIZE + OSCAR_UGID_SIZE + OSCAR_MODE_SIZE;
    int len_after_file_size = 15;
    //seeks past headeer
    lseek(archive_fd, OSCAR_ID_LEN, SEEK_SET);
    
    //Small table of contents
    if(table_flag == 0)
    {  
        printf("Short table of contents for oscar archive file: %s\n", argv[next_arg - 1]);
     
        while(read(archive_fd, test_buff, 1) != 0)
        {
            //go back the one byte read in the conditional statement
            lseek(archive_fd, -1, SEEK_CUR);

            //seeks parts name of file, reads how long the file name is
            //then converts it to an int
            lseek(archive_fd, OSCAR_MAX_FILE_NAME_LEN, SEEK_CUR);
            read(archive_fd, file_name_len_buff, 2);
            int len_file_name = atoi(file_name_len_buff) + 1;


            char short_file_name_buff[len_file_name];
            lseek(archive_fd, -(34), SEEK_CUR);

            read(archive_fd, short_file_name_buff, len_file_name);
            short_file_name_buff[len_file_name - 1] = '\0';

            
            lseek(archive_fd, (-1) * len_file_name, SEEK_CUR);

            printf("  %s\n", short_file_name_buff);
            read(archive_fd, file_name_buff, OSCAR_MAX_FILE_NAME_LEN);

            lseek(archive_fd, len_before_file_size, SEEK_CUR);
            read(archive_fd, file_len_buff, OSCAR_FILE_SIZE);
            len_of_file = atoi(file_len_buff);
            lseek(archive_fd, len_after_file_size + len_of_file, SEEK_CUR);

        } 
    }
    //Large table of contents
    else if(table_flag == 1)
    {
        printf("Long table of contents for oscar archive file: %s\n", argv[next_arg - 1]);

        while(read(archive_fd, test_buff, 1) != 0)
        {
            //go back the one byte read in the conditional statement
            lseek(archive_fd, -1, SEEK_CUR);
    
            //Reads the file name, and prints it
            read(archive_fd, file_name_buff, OSCAR_MAX_FILE_NAME_LEN - 1);
            file_name_buff[OSCAR_MAX_FILE_NAME_LEN - 1] = '\0'; 
        
            lseek(archive_fd, 1, SEEK_CUR);
            //seek through file name lenght
            read(archive_fd, file_name_len, 2);
            int i = 0;
            int len = atoi(file_name_len);
            char file_name[len];

            for(i; i < len; i++)
            {
                file_name[i] = file_name_buff[i];
            }
            lseek(archive_fd, -1, SEEK_CUR);
            //Gets the create time and prints
            read(archive_fd, create_time_buff, OSCAR_DATE_SIZE);
            create_time_buff[OSCAR_DATE_SIZE - 1] = '\0';

            //Gets the access time and prints it
            read(archive_fd, access_time_buff, OSCAR_DATE_SIZE);
            access_time_buff[OSCAR_DATE_SIZE - 1] = '\0';

            //gets the mod time and prints it
            read(archive_fd, mod_time_buff, OSCAR_DATE_SIZE);
            mod_time_buff[OSCAR_DATE_SIZE - 1] = '\0';

            //Gets user id and prints it out
            read(archive_fd, uid_buff, OSCAR_UGID_SIZE);
            uid_buff[OSCAR_UGID_SIZE - 1] = '\0';
            uid_buff[OSCAR_UGID_SIZE - 2] = '\0';

            //Gets group id and printsit out
            read(archive_fd, gid_buff, OSCAR_UGID_SIZE);
            gid_buff[OSCAR_UGID_SIZE - 1] = '\0';
            gid_buff[OSCAR_UGID_SIZE - 2] = '\0';

            //Seeks past file type
            lseek(archive_fd, 1, SEEK_CUR); 
            
            //Gets the permissions and prints them out
            read(archive_fd, per_buff, OSCAR_MODE_SIZE - 1);
            per_buff[OSCAR_MODE_SIZE - 1] = '\0';
            lseek(archive_fd, 1, SEEK_CUR);
            char f_length_buff[2];
            char permissions_buff[4];
            permissions_buff[0] = per_buff[2];
            permissions_buff[1] = per_buff[3];
            permissions_buff[2] = per_buff[4];
            permissions_buff[3] = per_buff[5];
            permissions_buff[4] = '\0';

            //Gets size of the file and prints it out
            read(archive_fd, file_len_buff, OSCAR_FILE_SIZE);
            file_len_buff[OSCAR_FILE_SIZE - 1] = '\0';
            int j = 0;
            for(j; j < OSCAR_FILE_SIZE; j++)
            {       
                if(file_len_buff[j] == ' ')
                {
                    file_len_buff[j] = '\0';
                }
            }
            
            pass = getpwuid(atoi(uid_buff));
            gr = getgrgid(atoi(gid_buff));
            //Gets the marked char and prints it out
            read(archive_fd, marked_buff, 1);
            marked = marked_buff[0];

            cre_time = atoi(create_time_buff);
            cre_t_final = ctime(&cre_time);
            printf("  File name: %s  \n", file_name);
            printf("\t File size:   %s bytes\n", file_len_buff);
            printf("\t Permissions: ");
            print_perms(permissions_buff);
            printf(" (%s)  \n", permissions_buff);
            printf("\t File owner:  %s (uid:%s) \n", pass->pw_name, uid_buff);
            printf("\t File group:  %s (gid:%s) \n", gr->gr_name, gid_buff);

            create_time_buff[0] = ' ';
            cre_time = atoi(create_time_buff);
            cre_t_final = ctime(&cre_time);
            printf("\t Create date: %s", cre_t_final);

            acc_time = atoi(access_time_buff);
            acc_t_final = ctime(&acc_time);

            printf("\t Access date: %s", acc_t_final);

            mod_time = atoi(mod_time_buff);
            mod_t_final = ctime(&mod_time);
            printf("\t Modify date: %s", mod_t_final);
            if(marked == ' ')
            {
                printf("\t Marked deleted: no\n");   
            }
            else if(marked == 'y')
            {
                printf("\t Marked deleted: yes\n");    
            }

            len_of_file = atoi(file_len_buff);
            //seek past end of archive entry, 12 bytes between maked and end char
            //then adds the len of file contents
            lseek(archive_fd, 12 + len_of_file, SEEK_CUR);
        }
    }
}

void opt_handler(int* options, int optind, char** argv, int argc)
{
    int verbose_flag = 0;
    char* archive;
    int table_flag;
    int over_flag;
    char oscar_check[OSCAR_ID_LEN];


    if(options[0] == 1)
    {
        printf("Verbose processing has been selected \n");
        verbose_flag = 1;
        printf("Set verbose flag to 1\n");
    }
    if(options[1] == 1)
    {
        printf("Help has been selected \n");
        help_text();
        exit(0);
    }
    if(options[2] == 1)
    {
        printf("Verion information has been selected \n");
        version_text();
        exit(0);
    }
        if(options[3] == 1)
    {
         printf("Add Members to archive\n");
         archive = argv[optind];
        if(access(archive, F_OK) == -1)
        {
            create_archive(archive, verbose_flag);
        }
        append_archive(argv[optind],argv, argc, optind + 1, 0, verbose_flag);
        exit(0);
    }
    if(options[4] == 1)
    {
         printf("Add all regular files to the archive\n");
         archive = argv[optind];
         if(access(archive, F_OK) == -1)
         {
            create_archive(archive, verbose_flag);
         }
         big_a(argv, argc, archive, optind, verbose_flag);
         exit(0);
    }

    if(options[5] == 1)
    {
        table_flag = 0;
        archive = argv[optind];
        table_of_contents(archive, argv, optind + 1, table_flag, verbose_flag);
        exit(0);
    }
    if(options[6] == 1)
    {
        table_flag = 1;
        archive = argv[optind];
        table_of_contents(archive, argv, optind + 1, table_flag, verbose_flag);
        exit(0);
    }
    if(options[7] == 1)
    {
        archive = argv[optind];
        over_flag = options[13];
        extract_handler(argv, archive, argc, optind + 1, over_flag, 0, verbose_flag); 
        exit(0);

    }
    if(options[8] == 1)
    {
        archive = argv[optind];
        over_flag = options[13];
        extract_handler(argv, archive, argc, optind + 1, over_flag, 1, verbose_flag); 
        exit(0);
    }
    if(options[9] == 1)
    {
        printf("Delete members\n");
        remove_file(argv, argc, argv[optind], optind, verbose_flag);
        exit(0);
    }
    if(options[10] == 1)
    {
        printf("Mark members\n");
        mark_file(argv, argc, argv[optind], optind);
        exit(0);
    }
    if(options[11] == 1)
    {
        printf("Unmark members\n");
        unmark_file(argv, argc, argv[optind], optind);
        exit(0);
    }
    if(options[12] == 1)
    {
        printf("Cleanse marked files\n");
        cleanse(argv, argc, argv[optind], optind);
        exit(0);
    }
}

int main(int argc, char** argv)
{
    int option;
    int next_arg;
    int table_flag = 0;
    int over_flag = 0;
    char* archive;
    int verbose_flag = 0;
    int options[14];

    while((option = getopt(argc, argv, "aACdeEhmotTuvV")) != -1)
    {
        switch(option)
        {
            //Option sets the verbose flag to 1
            case('v'):
                options[0] = 1;
                break;
            case('h'):
                options[1] = 1;
                break;
            case('V'):
                options[2] = 1;
                break;
            case('a'):
                options[3] = 1;
                break;
            case('A'):
                options[4] = 1;
                break;
            case('t'):
                options[5] = 1;
                break;
            case('T'):
                options[6] = 1;
                break;
            case('e'):
                options[7] = 1;
 
               break;
            case('E'):
                options[8] = 1;

                break;
            case('d'):
                options[9] = 1;

                break;
            case('m'):
                options[10] = 1;

                break;
            case('u'):
               options[11] = 1;  
                break;
            case('C'):
               options[12] = 1;
              break;
            case('o'):
                options[13] = 1;
                break;
        }
    }
   opt_handler(options, optind, argv, argc);


    return 0;
}


