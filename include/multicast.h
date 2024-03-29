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

#ifndef _MULTICAST_LISTENER_H
#define _MULTICAST_LISTENER_H

#include <stddef.h>

#define MAXBUFSIZE 65536 // Max UDP Packet size is 64 Kbyte

int initMultiCastListener();

int multiCastRequest(unsigned char type, const char* path, const char* data, size_t length);

#endif //_MULTICAST_LISTENER_H