TARGET = $(shell basename $(CURDIR))

DEPEND = 

TARGET_LIB = lib$(TARGET).so
TARGET_OBJ = $(TARGET).o

HEADERS_PATH = ../include
OBJ_PATH = ../obj
LDLIBS_PATH = ../libs
DEBUG_DIR = /debug
RELEASE_DIR = /release

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I $(HEADERS_PATH)

DEBUG_FLAGS = -g
RELEASE_FLAGS = -DNDEBUG -O3
OBJ_FLAGS = -c -fpic
SO_FLAGS = -shared
LDFLAGS = -L$(LDLIBS_PATH)$(DEBUG_DIR) -Wl,-rpath=$(LDLIBS_PATH)$(DEBUG_DIR)

LDLIBS = -l$(TARGET) $(patsubst %.o,-l%,$(DEPEND))

HEADERS = $(addprefix $(HEADERS_PATH)/,$(TARGET).h $(patsubst %.o,%.h,$(DEPEND)))

# target-specific variables definitions. prerequisites inherit those.
debug: CFLAGS := $(CFLAGS) $(DEBUG_FLAGS)
debug: OBJ_PATH := $(OBJ_PATH)$(DEBUG_DIR)
debug: LDLIBS_PATH := $(LDLIBS_PATH)$(DEBUG_DIR)
debug: MODE := debug
release: CFLAGS := $(CFLAGS) $(RELEASE_FLAGS)
release: OBJ_PATH := $(OBJ_PATH)$(RELEASE_DIR)
release: LDLIBS_PATH := $(LDLIBS_PATH)$(RELEASE_DIR)
release: MODE := release
test: CFLAGS := $(CFLAGS) $(DEBUG_FLAGS)

# custom conversion functions. used with $(call) later.
lib_to_c = $(subst lib,,$(subst .o,.c,$(notdir $(1))))
lib_to_obj = $(OBJ_PATH)/$(subst lib,,$(notdir $(1)))


.PHONY: test
test: | debug
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET).out $(TARGET)_test.c $(LDLIBS)
	
%.so: %.o $(TARGET).c
	$(CC) $(CFLAGS) $(SO_FLAGS) -o $@ $(call lib_to_obj,$<) 

%.o: $(HEADERS)
	@for i in $(patsubst %.o,../%,$(DEPEND)); do make $(MODE) -C $$i; done
	$(CC) $(CFLAGS) $(OBJ_FLAGS) -o $(call lib_to_obj,$@) $(call lib_to_c,$@)	

.PHONY: all
all: debug release

.SECONDEXPANSION:
.PHONY: debug
debug: $(TARGET).c $$(LDLIBS_PATH)/$(TARGET_LIB) | mkdirs

.PHONY: release
release: $(TARGET).c $$(LDLIBS_PATH)/$(TARGET_LIB) | mkdirs
	
.PHONY: mkdirs
mkdirs:
	@mkdir -p $(HEADERS_PATH)				
	@mkdir -p $(OBJ_PATH)					
	@mkdir -p $(LDLIBS_PATH)
	@echo "Made directories(if necessary)"				

.PHONY: clean
clean:
	for i in $(patsubst %.o,../%,$(DEPEND)); do make clean -C $$i; done
	@rm -f $(TARGET).out
	@rm -f $(OBJ_PATH)$(DEBUG_DIR)/$(TARGET_OBJ)
	@rm -f $(OBJ_PATH)$(RELEASE_DIR)/$(TARGET_OBJ)
	@rm -f $(LDLIBS_PATH)$(DEBUG_DIR)/$(TARGET_LIB)
	@rm -f $(LDLIBS_PATH)$(RELEASE_DIR)/$(TARGET_LIB)
	@echo "Removed $(TARGET) related .so, .o and .out files"
	
.PHONY: run
run:
	./$(TARGET).out

.PHONY: p
p:
	tree ./ ../libs ../obj

.PHONY: vlg
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET).out

.PHONY: cgdb
cgdb:
	cgdb ./$(TARGET).out



