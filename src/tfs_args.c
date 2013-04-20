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

#include "tfs_args.h"

#include <stdio.h>
#include <stdlib.h>

int tfs_opt_proc(void *data, const char *arg, int key, struct fuse_args *outargs) {
  switch (key) {
  case HELP_ARG_KEY:
    fprintf(stderr, "USAGE: tfs\n");
    fprintf(stderr, "-h, --help\tShow this help.\n");
    fprintf(stderr, "-v, --version\tShow the version.\n");
    fprintf(stderr, "-D, --debug\tEnable debugging.\n");
    exit(1);
    return 0;
  case VERSION_ARG_KEY:
    fprintf(stderr, "Work in progress build.\n");
    exit(1);
    return 0;
  case DEBUG_ARG_KEY:
    options.debug = 1;
    return 0;
  }
  return 1;
};