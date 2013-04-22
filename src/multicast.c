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

#include "multicast.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
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

static int getBroadcastSocket() {
  static int sock = 0;
  if (sock == 0) {
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
      perror("Error creating socket.");
      exit(1);
    }
  }
  return sock;
};

static struct sockaddr* getBroadcastAddress() {
  static struct sockaddr_in saddr;
  static struct in_addr iaddr;
  static unsigned char init = 0;
  if (init == 0) {
    memset(&saddr, 0, sizeof(struct sockaddr_in));
    memset(&iaddr, 0, sizeof(struct in_addr));
    saddr.sin_family = PF_INET;
    saddr.sin_port = htons(0); // Use the first free port
    saddr.sin_addr.s_addr = htonl(INADDR_ANY); // bind socket to any interface
    if (bind(getBroadcastSocket(), (struct sockaddr *)&saddr, sizeof(struct sockaddr_in)) < 0) {
      perror("Error binding socket to interface");
      exit(1);
    }
    iaddr.s_addr = INADDR_ANY;
    setsockopt(getBroadcastSocket(), IPPROTO_IP, IP_MULTICAST_IF, &iaddr, sizeof(struct in_addr));
    unsigned char one = 1;
    setsockopt(getBroadcastSocket(), IPPROTO_IP, IP_MULTICAST_TTL, &one, sizeof(unsigned char));
    setsockopt(getBroadcastSocket(), IPPROTO_IP, IP_MULTICAST_LOOP, &one, sizeof(unsigned char));
    saddr.sin_family = PF_INET;
    saddr.sin_addr.s_addr = inet_addr("226.0.0.1");
    saddr.sin_port = htons(4096);
    init = 1;
  }
  return (struct sockaddr*) & saddr;
};

int initMultiCastListener() {
  if (multicast_listener_struct.running)
    return 1;
  multicast_listener_struct.stop = 0;
  return pthread_create(&multicast_listener_struct.thread, NULL, multicast_listener_thread, NULL);
};

int multiCastRequest(unsigned char type, const char* path, const char* data, size_t length) {
  char buffer[MAXBUFSIZE];
  buffer[0] = type;
  size_t path_len = strlen(path) + 1; /* Yes we want to send the '\0' as well.. */
  size_t i;
  for (i = 0; i < path_len; i++)
    buffer[i+1] = path[i];
  return sendto(getBroadcastSocket(), &buffer, strlen(buffer), 0, getBroadcastAddress(), sizeof(struct sockaddr_in));
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