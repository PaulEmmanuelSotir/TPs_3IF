
# Debug mode (comment this line to build project in release mode)
DEBUG = true

# Compiler
CC = g++
# Command used to remove files
RM = rm -f
# Compiler and pre-processor options
CPPFLAGS = -Wall -std=c++14 -O3 
# Resulting program file name
EXE_NAME = a.out
# The source file extentions
SRC_EXT = cpp
# The header file types
# TODO allow .hpp header files
HDR_EXT = h

# Source directory
SRCDIR = source
# Headers directory
INCDIR = includes
# Main output directory
OUTPUT_DIR = bin
# Dependencies path
DEP_PATH = ./$(OUTPUT_DIR)/.d
# Release output directory
RELEASEDIR = release
# Debug output directory
DEBUGDIR = debug
# Libraries paths
LIBS = 
# Additional include paths
INCLUDES = 

ifdef DEBUG
CPPFLAGS = $(CPPFLAGS) -g
BUILD_PATH = ./$(OUTPUT_DIR)/$(DEBUGDIR)
else
BUILD_PATH = ./$(OUTPUT_DIR)/$(RELEASEDIR)
endif

# List of include paths
INCLUDES = ./$(INCDIR) $(INCLUDES)
# List of source files
SOURCES = $(wildcard *.$(SRC_EXT))
# List of object files
OBJS = $(SOURCES:%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# List of dependency files
DEP = $(SOURCES:%.$(SRC_EXT)=$(DEP_PATH)/%.d)
# Source directory path
SRC_PATH = ./$(SRCDIR)


.PHONY: all clean rebuild help

all: $(EXE_NAME)

clean:
	$(RM) $(BUILD_PATH)/*.o
	$(RM) $(BUILD_PATH)/$(EXE_NAME)
	
rebuild: clean all

help:
	echo '				### MAKEFILE HELP ###'
	echo 'TARGETS:'
	echo '	all 	...'
	echo '	clean 	...'
	echo '	rebuild ...'
	echo '	help	...'

# Build object files
# TODO: generate dependency files
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	$(CC) $(CPPFLAGS) -I $(INCLUDES) $(SRC_PATH) -l $(LIBS) -MMD -MP -c $< -o $@

# Build main target
$(EXE_NAME): $(OBJS)
	$(CC) $(OBJS) -o $(EXE_NAME)

