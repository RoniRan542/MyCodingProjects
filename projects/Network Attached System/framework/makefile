#!/bin/bash

TARGET = framework
DEPEND = 

LIBS_DIR = ../libs
OBJ_DIR = ../obj

DEBUG_LIBSDIR = $(LIBS_DIR)/debug
RELEASE_LIBSDIR = $(LIBS_DIR)/release

DEBUG_OBJDIR = $(OBJ_DIR)/debug
RELEASE_OBJDIR = $(OBJ_DIR)/release
GD_FLAGS = -pedantic-errors -Wall -Wextra -g
GC_FLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
OBJs_FLAGS = -c -fpic
LD_FLAGS = -L$(DEBUG_LIBSDIR) -Wl,-rpath=$(DEBUG_LIBSDIR)

CC = g++ -std=c++11 
INCLUDE_FLAG = -I include
REACTOR = src/reactor/reactor.cpp
REACTOR_IMPL = src/reactor/reactor_imp.cpp
LOGGER = src/logger/logger.cpp
T_POOL = src/thread_pool/thread_pool.cpp
EVENT = src/event/event.cpp
FD_CPP = src/nbd/FileDesc.cpp
NBD_CPP = src/nbd/nbd_comm.cpp
FRAMEWORK_IO = src/framework/fw_io.cpp

.PHONY: all	test release debug clean

test:  
	$(CC) $(GD_FLAGS) $(INCLUDE_FLAG) -o $(TARGET).out src/framework/$(TARGET)_test.cpp $(REACTOR) $(REACTOR_IMPL) $(T_POOL) $(NBD_CPP) $(FD_CPP) $(LOGGER) $(FRAMEWORK_IO) $(EVENT) -pthread -DSHARED_LIBRARY

clean:
	rm -f $(TARGET).out reactor_logger.txt

