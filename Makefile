################################################## 
# Makefile for Spazy
##################################################

# Choose your C++ compiler here (in general g++ on Linux systems):
CC = g++

#Optimisation level, eg: -O3
OPT=-O2

# Source code 
VPATH=src/KingPin src/Spazy src

# New folders to be created
MKDIR_P = mkdir -p
NEWFOLDERS=lib lib/obj

CFLAGS= -std=c++11 -Wall $(OPT) -Idep/include -Isrc -w

# Location of .obj and .a files
OBJDIR=lib/obj
LIBDIR=lib

KINGPINSRC=$(subst src/KingPin/, , $(wildcard src/KingPin/*.cpp))
KINGPINOBJ=$(KINGPINSRC:.cpp=.o)

SPAZYSRC=$(subst src/Spazy/, , $(wildcard src/Spazy/*.cpp))
SPAZYOBJ:=$(SPAZYSRC:.cpp=.o)

#LDFLAGS is used for programs using created library in lib.
LDFLAGS+= -L/usr/lib64 -L$(LIBDIR) -lGLU -lGL -lglut -lSDL2main -lSDL2 -lglfw3 -lGLEW

LIBS=libSpazy.a libKingPin.a 
PROG=main

.PHONY: kingpin spazy clean distclean

all: createFolders kingpin spazy $(PROG)

createFolders: $(NEWFOLDERS)

# Creating folders in OUT_DIR
$(NEWFOLDERS):
	@ $(MKDIR_P) $(NEWFOLDERS)

#Compiler command for any .cpp .h files
$(OBJDIR)/%.o : %.cpp %.h
	$(CC) -c $< $(CFLAGS) -o $@

kingpin: $(addprefix $(LIBDIR)/, libKingPin.a) 

$(addprefix $(LIBDIR)/, libKingPin.a): $(addprefix $(OBJDIR)/, $(KINGPINOBJ)) 
	@ echo "Making KingPin library in $@"
	@ ar rcs $@ $(addprefix $(OBJDIR)/, $(KINGPINOBJ)) 

spacex: $(addprefix $(LIBDIR)/, libSpaceX.a)

$(addprefix $(LIBDIR)/, libSpazy.a): $(addprefix $(OBJDIR)/, $(SPAZYOBJ))
	@ echo "Making Spazy library in $@"
	@ ar rcs $@ $(addprefix $(OBJDIR)/, $(SPAZYOBJ))

# $(addprefix $(LIBDIR)/, $(LIB)): $(addprefix $(OBJDIR)/, $(OBJECTS))
# 	@ echo "Making library $@..."
# 	@ ar rcs $@ $(addprefix $(OBJDIR)/, $(OBJECTS))  

%: %.cpp $(addprefix $(LIBDIR)/, $(LIBS))
	$(CC) $(CFLAGS) $< $(addprefix $(LIBDIR)/, $(LIBS)) $(LDFLAGS) -o $@

clean:
	@ echo "Cleaning library"
	@ rm -f $(addprefix $(OBJDIR)/, *.o)
	@ rm -f $(addprefix $(LIBDIR)/, $(LIB))

distclean:
	@ make -s clean
	@ echo "Cleaning programs"
	@ rm -f $(PROG)
