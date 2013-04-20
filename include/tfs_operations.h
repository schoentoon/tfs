/*  tfs
 *  Copyright (C) 2013  Toon Schoenmakers
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _TFS_OPERATIONS_H
#define _TFS_OPERATIONS_H

#include "tfs_args.h"

int tfs_access(const char *path, int mask);
int tfs_getattr(const char *path, struct stat *stbuf);
int tfs_fgetattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi);
int tfs_open(const char *path, struct fuse_file_info *fi);
int tfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
int tfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
int tfs_create(const char *path, mode_t m, struct fuse_file_info *fi);
int tfs_unlink(const char *path);
int tfs_truncate(const char *path, off_t o);
int tfs_rename(const char *src, const char *dst);

static struct fuse_operations tfs_oper = {
  .access = tfs_access,
  .getattr = tfs_getattr,
  .fgetattr = tfs_fgetattr,
  .open = tfs_open,
  .read = tfs_read,
  .write = tfs_write,
  .create = tfs_create,
  .unlink = tfs_unlink,
  .truncate = tfs_truncate,
  .rename = tfs_rename,
};

#endif // _TFS_OPERATIONS_H
