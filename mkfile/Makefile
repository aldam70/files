# Name of makefile
MAKEFILE=Makefile

# Base for target name
NAME=

# destination base path for libraries and programs
DEST=.

# $(SRCS) is the list of source files used.
SRCS=$(shell ls *.c *.cpp *.C 2>/dev/null)

# List of object files to be created
OBJS_L=$(SRCS:.l=.o)
OBJS_Y=$(OBJS_L:.y=.o)
OBJS_C=$(OBJS_Y:.C=.o)
OBJS_CPP=$(OBJS_C:.cpp=.o)
OBJS=$(sort $(OBJS_CPP:.c=.o))

# shared libraries to be linked to target
SH_LIBS=

# system libraries to be linked to target
SYSLIBS=

# External object files required to build target
EXTERNAL_OBJS=

# Compilers to be used.
CC=/usr/bin/gcc -m64
CXX=/usr/bin/g++ -m64

# Compile flags to be used
CFLAGS= -DStd=std
CFLAGS_DEBUG=-g -DStd=std
CXXFLAGS= -DStd=std
CXXFLAGS_DEBUG=-g -DStd=std

LD=$(CXX)
LDFLAGS=

# Include path
INCLUDES=

# Files to remove in make clean or make clobber
CLEAN_FILES=$(OBJS) core *~
CLOBBER_FILES=$(PROGRAM) 

# Rules to create an executable
PROGRAM=$(DEST)/bin/$(NAME)

all:	$(PROGRAM)
$(PROGRAM):     $(OBJS) $(EXTERNAL_OBJS)
		rm -f $(PROGRAM)
		$(CXX) -Wl,-z,now $(LDFLAGS) $(OBJS) $(EXTERNAL_OBJS) $(SH_LIBS) $(SYSLIBS) \
		-o $(PROGRAM)

debug:
	$(MAKE) -f $(MAKEFILE) CFLAGS='$(CFLAGS_DEBUG)' CXXFLAGS='$(CXXFLAGS_DEBUG)' all

clean:
	rm -f $(CLEAN_FILES)

clobber:
	rm -f $(CLEAN_FILES) $(CLOBBER_FILES)

depend: 

install:
	@echo "nothing to be installed"

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -c
