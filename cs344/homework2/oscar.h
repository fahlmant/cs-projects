/*
 * R Jesse Chaney
 * chaneyr@eecs.orst.edu
 * CS344-001
 * Fall 2014
 * School of EECS
 * Oregon State University
 * Corvallis, Oregon
 */

/*
 * oscar.h
 *
 */

/*
 * $Author: chaneyr $
 * $Date: 2014/10/17 03:54:32 $
 * $RCSfile: oscar.h,v $
 * $Revision: 1.1 $
 */

#ifndef OSCAR_H_
#define OSCAR_H_

# include <sys/cdefs.h>

/*
 * oscar archive files start with the OSCAR_ID identifying string.  Then follows a
 * `struct oscar_hdr', and as many bytes of member file data as its `oscar_size'
 * member indicates, for each member file.
 */

# define OSCAR_ID			"!<oscar>\n"/* String that begins an oscar archive file.  */
# define OSCAR_ID_LEN		9			/* Size of the oscar id string string.  */

# define OSCAR_HDR_END		"`\n"		/* String in at end of each member header.  */
# define OSCAR_HDR_END_LEN	2

# define OSCAR_MAX_FILE_NAME_LEN	32
# define OSCAR_SHA_DIGEST_LEN    	10
# define OSCAR_DATE_SIZE			12
# define OSCAR_UGID_SIZE			8
# define OSCAR_MODE_SIZE			8
# define OSCAR_FILE_SIZE			16
# define OSCAR_MAX_MEMBER_FILE_SIZE 1000000 /* Just make things a little easier. */

struct oscar_hdr
{
    char oscar_name[OSCAR_MAX_FILE_NAME_LEN]; /* Member file name, may not be NULL terminated    */
    char oscar_name_len[2];					/* The length of the member file name */
    char oscar_cdate[OSCAR_DATE_SIZE];		/* File create date, decimal seconds since Epoch.  */
    										/* We can store the file create time, but not set it. */
    char oscar_adate[OSCAR_DATE_SIZE];		/* File modify date, decimal seconds since Epoch.  */
    char oscar_mdate[OSCAR_DATE_SIZE];		/* File access date, decimal seconds since Epoch.  */
    char oscar_uid[OSCAR_UGID_SIZE];		/* user id in ASCII decimal */
	char oscar_gid[OSCAR_UGID_SIZE];		/* group id in ASCII decimal.  */
    char oscar_mode[OSCAR_MODE_SIZE];		/* File mode, in ASCII octal.  */
    char oscar_size[OSCAR_FILE_SIZE];		/* File size, in ASCII decimal.  */
    char oscar_deleted;						/* If member is deleted = y, otherwise a space  */
    char oscar_sha1[OSCAR_SHA_DIGEST_LEN];	/* SHA1 check bits - ***NOT USED*** */
    char oscar_hdr_end[OSCAR_HDR_END_LEN];	/* Always contains OSCAR_HDR_END.  */
};

#endif /* OSCAR_H_ */
