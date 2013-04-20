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

#ifndef _TFS_ARGS_H
#define _TFS_ARGS_H

#define FUSE_USE_VERSION 26
#include <fuse.h>

#define HELP_ARG_KEY 0
#define VERSION_ARG_KEY 1
#define DEBUG_ARG_KEY 2

static struct options {
  unsigned char debug : 1;
} options;

static struct fuse_opt tfs_opts[] = {
  FUSE_OPT_KEY("-h", HELP_ARG_KEY),
  FUSE_OPT_KEY("--help", HELP_ARG_KEY),
  FUSE_OPT_KEY("-v", VERSION_ARG_KEY),
  FUSE_OPT_KEY("--version", VERSION_ARG_KEY),
  FUSE_OPT_KEY("-D", DEBUG_ARG_KEY),
  FUSE_OPT_KEY("--debug", DEBUG_ARG_KEY),
  FUSE_OPT_END
};

int tfs_opt_proc(void *data, const char *arg, int key, struct fuse_args *outargs);

#endif // _TFS_ARGS_H