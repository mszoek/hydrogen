#ifndef H2_STAT_H
#define H2_STAT_H

struct stat
{
  UInt16    st_dev;         /* ID of device containing file */
  UInt64    st_ino;         /* Inode number */
  UInt32    st_mode;        /* File type and mode */
  UInt32    st_nlink;       /* Number of hard links */
  UInt32    st_uid;         /* User ID of owner */
  UInt32    st_gid;         /* Group ID of owner */
  UInt32    st_rdev;        /* Device ID (if special file) */
  UInt64    st_size;        /* Total size, in bytes */
  UInt32    st_blksize;     /* Block size for filesystem I/O */
  UInt64    st_blocks;      /* Number of 512B blocks allocated */
  UInt32    st_atime;       /* Time of last access */
  UInt32    st_mtime;       /* Time of last modification */
  UInt32    st_ctime;       /* Time of last status change */
};


#endif