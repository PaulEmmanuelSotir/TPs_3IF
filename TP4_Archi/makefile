############################################################################################
################################## GENERIC MAKEFILE ########################################
############################################################################################
# TODO: gÃrer les sous-dossiers / fichiers ayants le mÃªmes noms dans des dossiers diffÃ©rts
# TODO: gÃrer les extentions .hpp, .cxx, ...

# Compiler
CC = msp430-gcc
# Command used to remove files
RM = rm -f
# Compiler and pre-processor options
CPPFLAGS = -Wall -mmcu=msp430fg4618 -mcpu=430 -mdisable-watchdog -std=c99
#-Ofast
# Debug flags
DEBUGFLAGS = -g
# Resulting program file name
EXE_NAME = tp4.elf
LST_NAME = tp4.lst
# The source file extentions
SRC_EXT = c
# The header file types
# TODO allow .hpp header files
HDR_EXT = h

# Source directory
SRCDIR = 
# Headers directory
INCDIR = 
# Dependency files directory
DEPDIR = dep
# Libraries paths
LIB_DIRS = 
# Library file names (e.g. '-lboost_serialization-mt')
LIBS = -lm
# List of include paths
INCLUDES = 

# Source directory path
SRC_PATH = ./$(SRCDIR)
# Dependencies path
DEP_PATH = ./$(DEPDIR)

# List of source files
SOURCES = lcd.c ex1.c
# List of object files
OBJS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# List of dependency files
DEPS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(DEP_PATH)/%.d)

.PHONY: all clean rebuild prog

all: $(EXE_NAME)

clean:
	$(RM) *.o
	$(RM) $(EXE_NAME)
	$(RM) $(DEP_PATH)/*.d
	
rebuild: clean all

# Build object files
%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@mkdir -p $(DEP_PATH)
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -I $(INCLUDES) -MMD -M -MM -MP -MF $(DEP_PATH)/$*.d -c $< -o $@

# Build main target
$(EXE_NAME): $(OBJS)
	$(CC) $(LIB_DIRS) $(CPPFLAGS) -o $(EXE_NAME) $(OBJS) $(LIBS)
	msp430-objdump -d $(EXE_NAME) > $(LST_NAME)

prog: $(EXE_NAME)
	mspdebug -j -d /dev/ttyUSB0 uif


