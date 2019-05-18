/*
 * H2 Standard C Library
 * Copyright (C) 2019 Zoe & Alexis Knox. All rights reserved.
 *
 * Third-party code linked with this library may be distributed under any
 * terms, but this library itself may not be modified.
 */

#ifndef H2_STAT_H
#define H2_STAT_H

#include <types.h>

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

#define S_ISUID 04000
#define S_ISGID 02000
#define S_ISVTX 01000

#define S_IRUSR 0400
#define S_IWUSR 0200
#define S_IXUSR 0100
#define S_IRWXU (S_IRUSR|S_IWUSR|S_IXUSR)

#define S_IRGRP (S_IRUSR >> 3)
#define S_IWGRP (S_IWUSR >> 3)
#define S_IXGRP (S_IXUSR >> 3)
#define S_IRWXG (S_IRWXU >> 3)

#define S_IROTH (S_IRGRP >> 3)
#define S_IWOTH (S_IWGRP >> 3)
#define S_IXOTH (S_IXGRP >> 3)
#define S_IRWXO (S_IRWXG >> 3)

int stat(const char *path, struct stat *stbuf);
int fstat(int fd, struct stat *stbuf);

#endif
