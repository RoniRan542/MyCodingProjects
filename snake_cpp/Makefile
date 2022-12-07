TARGET = $(shell basename  \$(CURDIR))

LIBS_DIR = ../libs
OBJ_DIR = ../obj

DEBUG_LIBSDIR = \$(LIBS_DIR)/debug
RELEASE_LIBSDIR = \$(LIBS_DIR)/release

DEBUG_OBJDIR = $(OBJ_DIR)/debug
RELEASE_OBJDIR = $(OBJ_DIR)/release

CC = g++ -std=c++11 
GD_FLAGS = -pedantic-errors -Wall -Wextra -g
GC_FLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
OBJs_FLAGS = -c -fpic
LD_FLAGS = -L$(DEBUG_LIBSDIR) -Wl,-rpath=\$(DEBUG_LIBSDIR)
INCLUDE_FLAG = -I include
SRC_CPP = board/board.cpp snake/snake.cpp game/game.cpp square/square.cpp
.PHONY: all	test release debug clean

test:  
	$(CC) $(GD_FLAGS) $(INCLUDE_FLAG) -o $(TARGET).out $(TARGET)_main.cpp $(SRC_CPP) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

clean:
	rm -f $(TARGET).out