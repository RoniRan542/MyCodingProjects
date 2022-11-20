#!/bin/bash

TARGET = nbd_comm
DEPEND = 

LIBS_DIR = ../libs
OBJ_DIR = ../obj

DEBUG_LIBSDIR = $(LIBS_DIR)/debug
RELEASE_LIBSDIR = $(LIBS_DIR)/release

DEBUG_OBJDIR = $(OBJ_DIR)/debug
RELEASE_OBJDIR = $(OBJ_DIR)/release

CC = g++ -std=c++11 
GD_FLAGS = -pedantic-errors -Wall -Wextra -g
GC_FLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
OBJs_FLAGS = -c -fpic
LD_FLAGS = -L$(DEBUG_LIBSDIR) -Wl,-rpath=$(DEBUG_LIBSDIR)
INCLUDE_FLAG = -I include
REACTOR = src/reactor/reactor.cpp
REACTOR_IMPL = src/reactor/reactor_imp.cpp
LOGGER = src/logger/logger.cpp
T_POOL = src/thread_pool/thread_pool.cpp
EVENT = src/event/event.cpp
FD_CPP = src/nbd/FileDesc.cpp

.PHONY: all	test release debug clean

test:  
	$(CC) $(GD_FLAGS) $(INCLUDE_FLAG) -o $(TARGET).out src/nbd/$(TARGET)_test.cpp src/nbd/$(TARGET).cpp $(REACTOR) $(REACTOR_IMPL) $(T_POOL) $(FD_CPP) $(LOGGER) $(EVENT) -pthread -DSHARED_LIBRARY

clean:
	rm -f $(TARGET).out reactor_logger.txt

