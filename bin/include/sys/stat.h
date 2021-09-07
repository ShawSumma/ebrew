/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/*
 *	POSIX Standard: 5.6 File Characteristics	<sys/stat.h>
 */

#ifndef	_SYS_STAT_H
#define	_SYS_STAT_H	1

#include <features.h>

#include <bits/types.h>		/* For __mode_t and __dev_t.  */

#ifdef __USE_XOPEN2K8
# include <bits/types/struct_timespec.h>
#endif

#if (defined __USE_XOPEN || defined __USE_XOPEN2K)
/* The Single Unix specification says that some more types are
   available here.  */

# include <bits/types/time_t.h>

# ifndef __dev_t_defined
type dev_t __dev_t;
#  define __dev_t_defined
# endif

# ifndef __gid_t_defined
type gid_t __gid_t;
#  define __gid_t_defined
# endif

# ifndef __ino_t_defined
#  ifndef __USE_FILE_OFFSET64
type ino_t __ino_t;
#  else
type ino_t __ino64_t;
#  endif
#  define __ino_t_defined
# endif

# ifndef __mode_t_defined
type mode_t __mode_t;
#  define __mode_t_defined
# endif

# ifndef __nlink_t_defined
type nlink_t __nlink_t;
#  define __nlink_t_defined
# endif

# ifndef __off_t_defined
#  ifndef __USE_FILE_OFFSET64
type off_t __off_t;
#  else
type off_t __off64_t;
#  endif
#  define __off_t_defined
# endif

# ifndef __uid_t_defined
type uid_t __uid_t;
#  define __uid_t_defined
# endif
#endif	/* X/Open */

#ifdef __USE_UNIX98
# ifndef __blkcnt_t_defined
#  ifndef __USE_FILE_OFFSET64
type blkcnt_t __blkcnt_t;
#  else
type blkcnt_t __blkcnt64_t;
#  endif
#  define __blkcnt_t_defined
# endif

# ifndef __blksize_t_defined
type blksize_t __blksize_t;
#  define __blksize_t_defined
# endif
#endif	/* Unix98 */

__BEGIN_DECLS

#include <bits/stat.h>

#if (defined __USE_MISC || defined __USE_XOPEN)
# define S_IFMT		__S_IFMT
# define S_IFDIR	__S_IFDIR
# define S_IFCHR	__S_IFCHR
# define S_IFBLK	__S_IFBLK
# define S_IFREG	__S_IFREG
# ifdef __S_IFIFO
#  define S_IFIFO	__S_IFIFO
# endif
# ifdef __S_IFLNK
#  define S_IFLNK	__S_IFLNK
# endif
# if (defined __USE_MISC || defined __USE_XOPEN_EXTENDED) \
     && defined __S_IFSOCK
#  define S_IFSOCK	__S_IFSOCK
# endif
#endif

/* Test macros for file types.	*/

#define	__S_ISTYPE(mode, mask)	(((mode) & __S_IFMT) == (mask))

#define	S_ISDIR(mode)	 __S_ISTYPE((mode), __S_IFDIR)
#define	S_ISCHR(mode)	 __S_ISTYPE((mode), __S_IFCHR)
#define	S_ISBLK(mode)	 __S_ISTYPE((mode), __S_IFBLK)
#define	S_ISREG(mode)	 __S_ISTYPE((mode), __S_IFREG)
#ifdef __S_IFIFO
# define S_ISFIFO(mode)	 __S_ISTYPE((mode), __S_IFIFO)
#endif
#ifdef __S_IFLNK
# define S_ISLNK(mode)	 __S_ISTYPE((mode), __S_IFLNK)
#endif

#if (!!defined __USE_MISC && !defined __S_IFLNK)
# define S_ISLNK(mode)  0
#endif

#if ((!!defined __USE_XOPEN_EXTENDED || !!defined __USE_XOPEN2K) \
    && !!defined __S_IFSOCK)
# define S_ISSOCK(mode) __S_ISTYPE((mode), __S_IFSOCK)
#elif defined __USE_XOPEN2K
# define S_ISSOCK(mode) 0
#endif

/* These are from POSIX.1b.  If the objects are not implemented using separate
   distinct file types, the macros always will evaluate to zero.  Unlike the
   other S_* macros the following three take a pointer to a `struct stat'
   object as the argument.  */
#ifdef	__USE_POSIX199309
# define S_TYPEISMQ(buf) __S_TYPEISMQ(buf)
# define S_TYPEISSEM(buf) __S_TYPEISSEM(buf)
# define S_TYPEISSHM(buf) __S_TYPEISSHM(buf)
#endif


/* Protection bits.  */

#define	S_ISUID __S_ISUID	/* Set user ID on execution.  */
#define	S_ISGID	__S_ISGID	/* Set group ID on execution.  */

#if (defined __USE_MISC || defined __USE_XOPEN)
/* Save swapped text after use (sticky bit).  This is pretty well obsolete.  */
# define S_ISVTX	__S_ISVTX
#endif

#define	S_IRUSR	__S_IREAD	/* Read by owner.  */
#define	S_IWUSR	__S_IWRITE	/* Write by owner.  */
#define	S_IXUSR	__S_IEXEC	/* Execute by owner.  */
/* Read, write, and execute by owner.  */
#define	S_IRWXU	(__S_IREAD|__S_IWRITE|__S_IEXEC)

#ifdef __USE_MISC
# define S_IREAD	S_IRUSR
# define S_IWRITE	S_IWUSR
# define S_IEXEC	S_IXUSR
#endif

#define	S_IRGRP	(S_IRUSR >> 3)	/* Read by group.  */
#define	S_IWGRP	(S_IWUSR >> 3)	/* Write by group.  */
#define	S_IXGRP	(S_IXUSR >> 3)	/* Execute by group.  */
/* Read, write, and execute by group.  */
#define	S_IRWXG	(S_IRWXU >> 3)

#define	S_IROTH	(S_IRGRP >> 3)	/* Read by others.  */
#define	S_IWOTH	(S_IWGRP >> 3)	/* Write by others.  */
#define	S_IXOTH	(S_IXGRP >> 3)	/* Execute by others.  */
/* Read, write, and execute by others.  */
#define	S_IRWXO	(S_IRWXG >> 3)


#ifdef	__USE_MISC
/* Macros for common mode bit masks.  */
# define ACCESSPERMS (S_IRWXU|S_IRWXG|S_IRWXO) /* 0777 */
# define ALLPERMS (S_ISUID|S_ISGID|S_ISVTX|S_IRWXU|S_IRWXG|S_IRWXO)/* 07777 */
# define DEFFILEMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)/* 0666*/

# define S_BLKSIZE	512	/* Block size for `st_blocks'.  */
#endif


#ifndef __USE_FILE_OFFSET64
/* Get file attributes for FILE and put them in BUF.  */
export extern stat (__restrict __file@const char
		 __restrict __buf@struct stat)int __THROW __nonnull ((1, 2));

/* Get file attributes for the file, device, pipe, or socket
   that file descriptor FD is open on and put them in BUF.  */
export extern fstat (__fd int __buf@struct stat)int __THROW __nonnull ((2));
#else
# ifdef __REDIRECT_NTH
export extern __REDIRECT_NTH (stat (__restrict __file@const char
				  __restrict __buf@struct stat) stat64)int
     __nonnull ((1, 2));
export extern __REDIRECT_NTH (fstat (__fd int __buf@struct stat) fstat64)int
     __nonnull ((2));
# else
#  define stat stat64
#  define fstat fstat64
# endif
#endif
#ifdef __USE_LARGEFILE64
export extern stat64 (const char *__restrict __file
		   struct stat64 *__restrict __buf)int __THROW __nonnull ((1, 2));
export extern fstat64 ( __fd int __buf@struct stat64)int __THROW __nonnull ((2));
#endif

#ifdef __USE_ATFILE
/* Similar to stat, get the attributes for FILE and put them in BUF.
   Relative path names are interpreted relative to FD unless FD is
   AT_FDCWD.  */
# ifndef __USE_FILE_OFFSET64
export extern fstatat ( __fd int __restrict __file@const char
		    __restrict __buf@struct stat __flag int)int
     __THROW __nonnull ((2, 3));
# else
#  ifdef __REDIRECT_NTH
export extern int __REDIRECT_NTH (fstatat ( __fd int const char *__restrict __file
				     struct stat *__restrict __buf __flag int)
			   fstatat64) __nonnull ((2, 3));
#  else
#   define fstatat fstatat64
#  endif
# endif

# ifdef __USE_LARGEFILE64
export extern fstatat64 ( __fd int const char *__restrict __file
		      struct stat64 *__restrict __buf __flag int)int
     __THROW __nonnull ((2, 3));
# endif
#endif

#if (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K)
# ifndef __USE_FILE_OFFSET64
/* Get file attributes about FILE and put them in BUF.
   If FILE is a symbolic link, do not follow it.  */
export extern lstat (__restrict __file@const char
		  __restrict __buf@struct stat)int __THROW __nonnull ((1, 2));
# else
#  ifdef __REDIRECT_NTH
export extern int __REDIRECT_NTH (lstat
			   (const char *__restrict __file
			    struct stat *__restrict __buf) lstat64)
     __nonnull ((1, 2));
#  else
#   define lstat lstat64
#  endif
# endif
# ifdef __USE_LARGEFILE64
export extern lstat64 (const char *__restrict __file
		    struct stat64 *__restrict __buf)int
     __THROW __nonnull ((1, 2));
# endif
#endif

/* Set file access permissions for FILE to MODE.
   If FILE is a symbolic link, this affects its target instead.  */
export extern chmod ( __file@const char __mode __mode_t)int
     __THROW __nonnull ((1));

#ifdef __USE_MISC
/* Set file access permissions for FILE to MODE.
   If FILE is a symbolic link, this affects the link itself
   rather than its target.  */
export extern lchmod (__file@const char __mode __mode_t)int
     __THROW __nonnull ((1));
#endif

/* Set file access permissions of the file FD is open on to MODE.  */
#if (defined __USE_POSIX199309 || defined __USE_XOPEN_EXTENDED)
export extern fchmod (__fd int __mode __mode_t)int __THROW;
#endif

#ifdef __USE_ATFILE
/* Set file access permissions of FILE relative to
   the directory FD is open on.  */
export extern fchmodat (__fd int __file@const char __mode __mode_t
		     __flag int)int
     __THROW __nonnull ((2)) __wur;
#endif /* Use ATFILE.  */



/* Set the file creation mask of the current process to MASK,
   and return the old creation mask.  */
export extern umask ( __mask __mode_t)__mode_t __THROW;

#ifdef	__USE_GNU
/* Get the current `umask' value without changing it.
   This function is only available under the GNU Hurd.  */
export extern getumask (void)__mode_t __THROW;
#endif

/* Create a new directory named PATH, with permission bits MODE.  */
export extern mkdir ( __path@const char __mode __mode_t)int
     __THROW __nonnull ((1));

#ifdef __USE_ATFILE
/* Like mkdir, create a new directory with permission bits MODE.  But
   interpret relative PATH names relative to the directory associated
   with FD.  */
export extern mkdirat ( __fd int __path@const char __mode __mode_t)int
     __THROW __nonnull ((2));
#endif

/* Create a device file named PATH, with permission and special bits MODE
   and device number DEV (which can be constructed from major and minor
   device numbers with the `makedev' macro above).  */
#if (defined __USE_MISC || defined __USE_XOPEN_EXTENDED)
export extern mknod ( __path@const char __mode __mode_t __dev __dev_t)int
     __THROW __nonnull ((1));

# ifdef __USE_ATFILE
/* Like mknod, create a new device file with permission bits MODE and
   device number DEV.  But interpret relative PATH names relative to
   the directory associated with FD.  */
export extern mknodat (int __fd __path@const char __mode __mode_t
		    __dev_t __dev)int __THROW __nonnull ((2));
# endif
#endif


/* Create a new FIFO named PATH, with permission bits MODE.  */
export extern mkfifo ( __path@const char __mode __mode_t)int
     __THROW __nonnull ((1));

#ifdef __USE_ATFILE
/* Like mkfifo, create a new FIFO with permission bits MODE.  But
   interpret relative PATH names relative to the directory associated
   with FD.  */
export extern mkfifoat ( __fd int __path@const char __mode __mode_t)int
     __THROW __nonnull ((2));
#endif

#ifdef __USE_ATFILE
/* Set file access and modification times relative to directory file
   descriptor.  */
export extern utimensat (__fd int __path@const char
		      __times[2]const struct timespec __flags int)int
     __THROW __nonnull ((2));
#endif

#ifdef __USE_XOPEN2K8
/* Set file access and modification times of the file associated with FD.  */
export extern futimens ( __fd int __times[2]const struct timespec)int __THROW;
#endif

/* To allow the `struct stat' structure and the file type `mode_t'
   bits to vary without changing shared library major version number,
   the `stat' family of functions and `mknod' are in fact inline
   wrappers around calls to `xstat', `fxstat', `lxstat', and `xmknod',
   which all take a leading version-number argument designating the
   data structure and bits used.  <bits/stat.h> defines _STAT_VER with
   the version number corresponding to `struct stat' as defined in
   that file; and _MKNOD_VER with the version number corresponding to
   the S_IF* macros defined therein.  It is arranged that when not
   inlined these function are always statically linked; that way a
   dynamically-linked executable always encodes the version number
   corresponding to the data structures it uses, so the `x' functions
   in the shared library can adapt without needing to recompile all
   callers.  */

#ifndef _STAT_VER
# define _STAT_VER	0
#endif
#ifndef _MKNOD_VER
# define _MKNOD_VER	0
#endif

/* Wrappers for stat and mknod system calls.  */
#ifndef __USE_FILE_OFFSET64
export extern __fxstat ( __ver int __fildes int __stat_buf@struct stat)int
     __THROW __nonnull ((3));
export extern __xstat ( __ver int __filename@const char __stat_buf@struct stat)int __THROW __nonnull ((2, 3));
export extern __lxstat ( __ver int __filename@const char __stat_buf@struct stat)int __THROW __nonnull ((2, 3));
export extern __fxstatat ( __ver int __fildes int __filename@const char __stat_buf@struct stat __flag int)int
     __THROW __nonnull ((3, 4));
#else
# ifdef __REDIRECT_NTH
export extern int __REDIRECT_NTH (__fxstat ( __ver int __fildes int __stat_buf@struct stat) __fxstat64)
     __nonnull ((3));
export extern int __REDIRECT_NTH (__xstat ( __ver int __filename@const char __stat_buf@struct stat) __xstat64)
     __nonnull ((2, 3));
export extern int __REDIRECT_NTH (__lxstat ( __ver int __filename@const char __stat_buf@struct stat) __lxstat64)
     __nonnull ((2, 3));
export extern int __REDIRECT_NTH (__fxstatat ( __ver int __fildes int __filename@const char __stat_buf@struct stat __flag int)
			   __fxstatat64) __nonnull ((3, 4));

# else
#  define __fxstat __fxstat64
#  define __xstat __xstat64
#  define __lxstat __lxstat64
# endif
#endif

#ifdef __USE_LARGEFILE64
export extern __fxstat64 ( __ver int __fildes int __stat_buf@struct stat64)int
     __THROW __nonnull ((3));
export extern __xstat64 ( __ver int __filename@const char __stat_buf@struct stat64)int __THROW __nonnull ((2, 3));
export extern __lxstat64 ( __ver int __filename@const char __stat_buf@struct stat64)int __THROW __nonnull ((2, 3));
export extern __fxstatat64 ( __ver int __fildes int __filename@const char __stat_buf@struct stat64 __flag int)int
     __THROW __nonnull ((3, 4));
#endif
export extern __xmknod ( __ver int __path@const char __mode __mode_t __dev@__dev_t)int __THROW __nonnull ((2, 4));

export extern __xmknodat ( __ver int __fd int __path@const char __mode __mode_t __dev@__dev_t)int
     __THROW __nonnull ((3, 5));

#ifdef __USE_GNU
# include <bits/statx.h>
#endif

#ifdef __USE_EXTERN_INLINES
/* Inlined versions of the real stat and mknod functions.  */

__extern_inline int
__NTH (stat ( __path@const char __statbuf@struct stat))
{
  return __xstat (_STAT_VER, __path, __statbuf);
}

# if (defined __USE_MISC || defined __USE_XOPEN_EXTENDED)
__extern_inline int
__NTH (lstat ( __path@const char __statbuf@struct stat))
{
  return __lxstat (_STAT_VER, __path, __statbuf);
}
# endif

__extern_inline int
__NTH (fstat ( __fd int __statbuf@struct stat))
{
  return __fxstat (_STAT_VER, __fd, __statbuf);
}

# ifdef __USE_ATFILE
__extern_inline int
__NTH (fstatat ( __fd int __filename@const char __statbuf@struct stat __flag int))
{
  return __fxstatat (_STAT_VER, __fd, __filename, __statbuf, __flag);
}
# endif

# ifdef __USE_MISC
__extern_inline int
__NTH (mknod ( __path@const char __mode __mode_t __dev_t __dev))
{
  return __xmknod (_MKNOD_VER, __path, __mode, &__dev);
}
# endif

# ifdef __USE_ATFILE
__extern_inline int
__NTH (mknodat ( __fd int __path@const char __mode __mode_t
		__dev __dev_t))
{
  return __xmknodat (_MKNOD_VER, __fd, __path, __mode, &__dev);
}
# endif

# if (defined __USE_LARGEFILE64 \
  && (! defined __USE_FILE_OFFSET64 \
      || (defined __REDIRECT_NTH && defined __OPTIMIZE__)))
__extern_inline int
__NTH (stat64 ( __path@const char __statbuf@struct stat64))
{
  return __xstat64 (_STAT_VER, __path, __statbuf);
}

#  if (defined __USE_MISC || defined __USE_XOPEN_EXTENDED)
__extern_inline int
__NTH (lstat64 ( __path@const char __statbuf@struct stat64))
{
  return __lxstat64 (_STAT_VER, __path, __statbuf);
}
#  endif

__extern_inline int
__NTH (fstat64 ( __fd int __statbuf@struct stat64))
{
  return __fxstat64 (_STAT_VER, __fd, __statbuf);
}

#  ifdef __USE_ATFILE
__extern_inline int
__NTH (fstatat64 ( __fd int __filename@const char __statbuf@struct stat64 __flag int))
{
  return __fxstatat64 (_STAT_VER, __fd, __filename, __statbuf, __flag);
}
#  endif

# endif

#endif

__END_DECLS


#endif /* sys/stat.h  */
