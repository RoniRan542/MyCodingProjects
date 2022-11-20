NAME = $(shell basename $(CURDIR))
TARGET = $(NAME).out
OBJs = 

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GCFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
LDFLAGS = -L$(LIBS_DBUG) -Wl,-rpath=$(LIBS_DBUG)
IFLAG = -I../include

LIB = lib

LIBS_DBUG = ../libs/debug
LIBS_RELE = ../libs/release
OBJ_DBUG = ../obj/debug
OBJ_RELE = ../obj/release

.PHONY: all
all: debug release

#create .o and .so files /libs/debug + /obj/debug
# for patsubst replaces .o with the name of the dir and does 'make' command 
# $$i makes i as a variable for shell. i is for make
.PHONY: debug
debug: $(NAME).c
	mkdir -p $(LIBS_DBUG)
	mkdir -p $(OBJ_DBUG)
	for i in $(patsubst %.o,../%,$(OBJs)); do make debug -C $$i; done
	$(CC) $(CFLAGS) $(IFLAG) -c -fpic $(NAME).c -o $(NAME).o
	mv $(NAME).o $(OBJ_DBUG)
	$(CC) $(CFLAGS) -shared -o $(LIB)$(NAME).so $(OBJ_DBUG)/$(NAME).o
	mv $(LIB)$(NAME).so $(LIBS_DBUG)

#create .o and .so files /libs/release + /obj/release
.PHONY: release
release: $(NAME).c
	mkdir -p $(LIBS_RELE)
	mkdir -p $(OBJ_RELE)
	for i in $(patsubst %.o,../%,$(OBJs)); do make release -C $$i; done
	$(CC) $(GCFLAGS) $(IFLAG) -c -fpic $(NAME).c -o $(NAME).o
	mv $(NAME).o $(OBJ_RELE)
	$(CC) $(GCFLAGS) -shared -o $(LIB)$(NAME).so $(OBJ_RELE)/$(NAME).o
	mv $(LIB)$(NAME).so $(LIBS_RELE)

.PHONY: test
test: debug
	$(CC) $(LDFLAGS) $(CFLAGS) $(IFLAG) -o $(NAME).out $(NAME)_test.c \
	-l$(NAME) $(patsubst %.o,-l%,$(OBJs))

.PHONY: clean
clean:
	for i in $(patsubst %.o,../%,$(OBJs)); do make clean -C $$i; done
	rm -f $(OBJ_DBUG)/$(NAME).o
	rm -f $(OBJ_RELE)/$(NAME).o
	rm -f $(LIBS_DBUG)/$(LIB)$(NAME).so
	rm -f $(LIBS_RELE)/$(LIB)$(NAME).so
	rm -f $(NAME).out

# $^ all dependencies
# $< first dependency
# $@ the rule's target name
# % all of this type
