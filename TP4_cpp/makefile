############################################################################################
################################## GENERIC MAKEFILE ########################################
############################################################################################
# TODO: g√rer les sous-dossiers / fichiers ayants le m√™mes noms dans des dossiers diff√©rts
# TODO: g√rer les extentions .hpp, .cxx, ...

# Debug mode (comment this line to build project in release mode)
#DEBUG = true

# Compiler
CC = g++
# Command used to remove files
RM = rm -f
# Compiler and pre-processor options
CPPFLAGS = -Wall -std=c++11 -Ofast
# Debug flags
DEBUGFLAGS = -g
# Resulting program file name
EXE_NAME = geometry
# The source file extentions
SRC_EXT = cpp
# The header file types
# TODO allow .hpp header files
HDR_EXT = h

TEST_SCRIPT = ./tests/mktest.sh ./tests

# Source directory
SRCDIR = src
# Headers directory
INCDIR = src
# Main output directory
OUTPUT_DIR = bin
# Release output directory
RELEASEDIR = release
# Debug output directory
DEBUGDIR = debug
# Dependency files directory
DEPDIR = dep
# Libraries paths
LIB_DIRS = -L /mingw64/lib
# Library file names (e.g. '-lboost_serialization-mt')
LIBS = -lboost_serialization-mt
# List of include paths
INCLUDES = ./$(INCDIR) #"/c/Program Files (x86)/boost_1_60_0"

ifdef DEBUG
BUILD_PATH = ./$(OUTPUT_DIR)/$(DEBUGDIR)
else
DEBUGFLAGS = 
BUILD_PATH = ./$(OUTPUT_DIR)/$(RELEASEDIR)
endif
# Source directory path
SRC_PATH = ./$(SRCDIR)
# Dependencies path
DEP_PATH = ./$(BUILD_PATH)/$(DEPDIR)

# List of source files
SOURCES = $(wildcard $(SRC_PATH)/*.$(SRC_EXT))
# List of object files
OBJS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# List of dependency files
DEPS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(DEP_PATH)/%.d)

.PHONY: all clean rebuild help test

all: $(BUILD_PATH)/$(EXE_NAME)

clean:
	$(RM) $(BUILD_PATH)/*.o
	$(RM) $(BUILD_PATH)/$(EXE_NAME)
	$(RM) $(DEP_PATH)/*.d
	
rebuild: clean all

help:
	@echo '				### MAKEFILE HELP ###'
	@echo 'PHONY TARGETS:'
	@echo '	all 	...'
	@echo '	clean 	...'
	@echo '	rebuild ...'
	@echo '	help	...'

test:
	@cd tests/
	$(TEST_SCRIPT)

# Build object files
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@mkdir -p $(DEP_PATH)
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -I $(INCLUDES) -MMD -MP -MF $(DEP_PATH)/$*.d -c $< -o $@

# Build main target
$(BUILD_PATH)/$(EXE_NAME): $(OBJS)
	$(CC) $(LIB_DIRS) -o $(BUILD_PATH)/$(EXE_NAME) $(OBJS) $(LIBS)

# -lboost_serialization

