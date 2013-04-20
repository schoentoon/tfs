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
#include "tfs_operations.h"

#include <stdio.h>

int main(int argc, char** argv) {
  struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
  char* mountpoint;
  int multithreaded;
  int foreground;
  if (fuse_opt_parse(&args, NULL, tfs_opts, tfs_opt_proc) == -1)
    return 1;
  if (fuse_parse_cmdline(&args, &mountpoint, &multithreaded, &foreground) == -1)
    return 1;
  struct fuse_chan *ch = fuse_mount(mountpoint, &args);
  if (!ch)
    return 1;
  struct fuse *fuse = fuse_new(ch, &args, &tfs_oper, sizeof(struct fuse_operations), NULL);
  if (!fuse) {
    fuse_unmount(mountpoint, ch);
    return 1;
  }
  if (options.debug == 1 ||  foreground == 1) {
    if (fuse_daemonize(foreground) != -1)
      return 1;
  }
  if (fuse_set_signal_handlers(fuse_get_session(fuse)) == -1) {
    fuse_unmount(mountpoint, ch);
    fuse_destroy(fuse);
    return 1;
  }
  if (multithreaded)
    return fuse_loop_mt(fuse);
  if (!options.debug)
    fprintf(stderr, "Running single threaded and we are not debugging, your performance may suffer.\n");
  return fuse_loop(fuse);
};