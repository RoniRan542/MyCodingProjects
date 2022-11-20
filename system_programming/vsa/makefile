TARGET = vsa
OBJs = vsa_test1.o vsa.o
HEADERS = vsa.h
CFILES = vsa.c vsa_test1.c

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

.PHONY : all
	all : $(TARGET)

$(TARGET) : $(OBJs)
	$(CC) $(CFLAGS) $(OBJs) -o $(TARGET) 

$(OBJs): $(HEADERS) $(CFILES)

$(CFILES): $(HEADERS)

.PHONY : debug    
debug : 
	cgdb $(TARGET)
    
.PHONY : libncreat
libcreat :
	ar -r libfoo.ar $(OBJs)
    
.PHONY : clean    
clean :
	rm $(OBJs) $(TARGET)
    
.PHONY : libclean    
libclean :
	rm libfoo.ar
