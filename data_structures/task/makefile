# Task FILE

OBJs = uid.o

FNAME = $(shell basename $(CURDIR))

#FILES VARIABLES 
HEADERS = $(HEADER_PATH)/$(FNAME).h
OBJ_SOURCE = $(OBJ_DEB_PATH)/$(FNAME).o 
OBJ_TEST = $(OBJ_DEB_PATH)/$(FNAME)_test.o 
OBJS = $(OBJ_SOURCE) $(OBJ_TEST)
CFILES = $(FNAME).c $(FNAME)_test.c
LIB = $(LIB_DEB_PATH)/lib$(FNAME).so

#FILES PATHS
HEADER_PATH = ../include/
OBJ_DEB_PATH = ../obj/debug
LIB_DEB_PATH = ../libs/debug
OBJ_REL_PATH = ../obj/release
LIB_REL_PATH = ../libs/release

#COMPILATION
CC = gcc
GDFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GCFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
OBJFLAGS = -c -fpic
SOFLAG = -shared
SOLINK = -L$(LIB_DEB_PATH) -Wl,-rpath=$(LIB_DEB_PATH)

.PHONY : all
all : test release debug clean

.PHONY : debug    
debug: $(CFILES) $(HEADERS) 
	for d in $(patsubst %.o,../%,$(OBJs)); do make debug -C $$d; done
	$(CC) $(GDFLAGS) $(OBJFLAGS) -I ../include $(FNAME).c
	$(CC) $(SOFLAG) -o lib$(FNAME).so $(FNAME).o
	mv $(FNAME).o $(OBJ_DEB_PATH)
	mv lib$(FNAME).so $(LIB_DEB_PATH)	

.PHONY : release    
release : $(CFILES) $(HEADERS) 
	for d in $(patsubst %.o,../%,$(OBJs)); do make release -C $$d; done
	$(CC) $(GCFLAGS) $(OBJFLAGS) -I ../include $(FNAME).c
	$(CC) $(SOFLAG) -o lib$(FNAME).so $(FNAME).o
	mv $(FNAME).o $(OBJ_REL_PATH)
	mv lib$(FNAME).so $(LIB_REL_PATH)	
	
.PHONY : test    
test : 
	$(CC) $(SOLINK) $(GDFLAGS) -I ../include -o $(FNAME) $(FNAME)_test.c -l$(FNAME) $(patsubst %.o,-l%,$(OBJs))

debug_release_dir:
	mkdir -p $(LIB_DEB_PATH)
	mkdir -p $(LIB_REL_PATH)
	mkdir -p $(OBJ_DEB_PATH)
	mkdir -p $(OBJ_REL_PATH)

.PHONY : clean    
clean:
	for d in $(patsubst %.o,../%,$(OBJs)); do make clean -C $$d; done
	rm -f $(OBJ_DEB_PATH)/$(FNAME).o
	rm -f $(OBJ_REL_PATH)/$(FNAME).o
	rm -f $(LIB_DEB_PATH)/lib$(FNAME).so
	rm -f $(LIB_REL_PATH)/lib$(FNAME).so
	rm -f $(FNAME)


