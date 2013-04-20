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

int main(int argc, char** argv) {
  struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
  char* mountpoint;
  int multithreaded;
  int foreground;
  if (fuse_opt_parse(&args, NULL, tfs_opts, tfs_opt_proc) == -1)
    return 1;
  if (fuse_parse_cmdline(&args, &mountpoint, &multithreaded, &foreground) == -1)
    return 1;
  return 0;
};