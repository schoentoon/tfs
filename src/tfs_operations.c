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

#include "tfs_operations.h"

#include "multicast.h"

#include <stdio.h>
#include <string.h>

#define TYPE_EXISTS 0
#define TYPE_UNLINK 1
#define TYPE_MOVE   2

int tfs_access(const char *path, int mask) {
  if (options.debug)
    fprintf(stderr, "tfs_access(%s, %d);\n", path, mask);
  return 0;
};

int tfs_getattr(const char *path, struct stat *stbuf) {
  if (options.debug)
    fprintf(stderr, "tfs_getattr(%s);\n", path);
  return 0;
};

int tfs_fgetattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi) {
  if (options.debug)
    fprintf(stderr, "tfs_fgetattr(%s);\n", path);
  return 0;
};

int tfs_open(const char *path, struct fuse_file_info *fi) {
  if (options.debug)
    fprintf(stderr, "tfs_open(%s);\n", path);
  multiCastRequest(TYPE_EXISTS, path, NULL, 0);
  return 0;
};

int tfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
  if (options.debug)
    fprintf(stderr, "tfs_read(%s, size = %ld, offset = %ld);\n", path, size, offset);
  return 0;
};

int tfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
  if (options.debug)
    fprintf(stderr, "tfs_write(%s, size = %ld, offset = %ld);\n", path, size, offset);
  return 0;
};

int tfs_create(const char *path, mode_t m, struct fuse_file_info *fi) {
  if (options.debug)
    fprintf(stderr, "tfs_create(%s, %d);\n", path, m);
  return 0;
};

int tfs_unlink(const char *path) {
  if (options.debug)
    fprintf(stderr, "tfs_unlink(%s);\n", path);
  multiCastRequest(TYPE_UNLINK, path, NULL, 0);
  return 0;
};

int tfs_truncate(const char *path, off_t o) {
  if (options.debug)
    fprintf(stderr, "tfs_truncate(%s, %ld);\n", path, o);
  return 0;
};

int tfs_rename(const char *src, const char *dst) {
  if (options.debug)
    fprintf(stderr, "tfs_rename(%s, %s);\n", src, dst);
  multiCastRequest(TYPE_MOVE, src, dst, strlen(dst)+1);
  return 0;
};