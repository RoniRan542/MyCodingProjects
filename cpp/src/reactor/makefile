#!/bin/bash

TARGET = $(shell basename  $(CURDIR))
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
INCLUDE_FLAG = -I ../../include
REACT_IMPL_CPP = reactor_imp.cpp
LOGGER_CPP = ../logger/logger.cpp
TPOOL_CPP = ../thread_pool/thread_pool.cpp

.PHONY: all	test release debug clean

test:  
	$(CC) $(LD_FLAGS) $(GD_FLAGS) $(INCLUDE_FLAG) -o reactor reactor_test.cpp $(TARGET).cpp $(REACT_IMPL_CPP) $(LOGGER_CPP) $(TPOOL_CPP)  -pthread

clean:
	rm -f reactor

