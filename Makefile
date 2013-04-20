CFLAGS := $(CFLAGS) -Wall -O2 -mtune=native -g $(shell pkg-config --cflags fuse)
INC    := -Iinclude
LFLAGS := $(shell pkg-config --libs fuse) -lpthread
DEFINES:= $(DEFINES)
CC     := gcc
BINARY := tfs
DEPS   := build/main.o build/tfs_args.o build/tfs_operations.o

.PHONY: all dev install

all: bin/tfs

build:
	-mkdir build bin

dev:
	DEFINES="-DDEV" $(MAKE)

build/main.o: src/main.c
	$(CC) $(CFLAGS) $(DEFINES) $(INC) -c -o build/main.o src/main.c

build/tfs_args.o: src/tfs_args.c include/tfs_args.h
	$(CC) $(CFLAGS) $(DEFINES) $(INC) -c -o build/tfs_args.o src/tfs_args.c

build/tfs_operations.o: src/tfs_operations.c include/tfs_operations.h
	$(CC) $(CFLAGS) $(DEFINES) $(INC) -c -o build/tfs_operations.o src/tfs_operations.c

bin/tfs: build $(DEPS)
	$(CC) $(CFLAGS) $(DEFINES) -o bin/$(BINARY) $(DEPS) $(LFLAGS)

install: bin/tfs
	cp -f $(BINARY) /usr/bin/$(BINARY)

clean:
	rm -rfv $(BINARY) $(DEPS)

clang:
	$(MAKE) dev CC=clang
