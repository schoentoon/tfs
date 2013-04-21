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

#include "multicast_listener.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

static struct multicast_listener_struct {
  unsigned char running : 1;
  unsigned char stop : 1;
  pthread_t thread;
} multicast_listener_struct;

static void* multicast_listener_thread(void* ptr);

int initMultiCastListener() {
  if (multicast_listener_struct.running)
    return 1;
  multicast_listener_struct.stop = 0;
  return pthread_create(&multicast_listener_struct.thread, NULL, multicast_listener_thread, NULL);
};

static void* multicast_listener_thread(void* ptr) {
  int sock;
  char buffer[MAXBUFSIZE];
  struct sockaddr_in saddr;
  struct ip_mreq imreq;
  memset(&saddr, 0, sizeof(struct sockaddr_in));
  memset(&imreq, 0, sizeof(struct ip_mreq));
  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
  if (sock < 0) {
    perror("Error creating socket");
    return NULL;
  }
  saddr.sin_family = PF_INET;
  saddr.sin_port = htons(4096);
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(sock, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in)) < 0) {
    perror("Error binding socket to interface");
    return NULL;
  }
  imreq.imr_multiaddr.s_addr = inet_addr("226.0.0.1");
  imreq.imr_interface.s_addr = INADDR_ANY;
  setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP
            ,(const void*)&imreq, sizeof(struct ip_mreq));
  multicast_listener_struct.running = 1;
  socklen_t socklen = sizeof(struct sockaddr_in);
  while (multicast_listener_struct.stop == 0) {
     recvfrom(sock, buffer, MAXBUFSIZE, 0
             ,(struct sockaddr *)&saddr, &socklen);
     fprintf(stderr, "Buffer: %s\n", buffer);
  }
  shutdown(sock, 2);
  close(sock);
  return NULL;
};