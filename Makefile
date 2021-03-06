################################################## 
# Makefile for Spazy
##################################################

# Choose your C++ compiler here (in general g++ on Linux systems):
CC = g++

#Optimisation level, eg: -O3
OPT=-O3

# Source code 
VPATH=src/KingPin src/Spazy src dep/imgui

# New folders to be created
MKDIR_P = mkdir -p
NEWFOLDERS=lib lib/obj

CFLAGS= -std=c++11 -Wall $(OPT) -Idep/include -Isrc -w

# Location of .obj and .a files
OBJDIR=lib/obj
LIBDIR=lib
LDFLAGS+=-L$(LIBDIR)

KINGPINSRC=$(subst src/KingPin/, , $(wildcard src/KingPin/*.cpp))
# IMGUI
# The following three lines implements the ImGui source files
KINGPINSRC+=$(subst dep/imgui/, , $(wildcard dep/imgui/*.cpp))
CFLAGS+=-Idep/imgui -DIMGUI_IMPL_OPENGL_LOADER_GLEW `sdl2-config --cflags`
LDFLAGS+=-lGL -ldl `sdl2-config --libs`

# FMOD
# Implements audio
KINGPINSRC+=$(subst dep/fmod/, , $(wildcard dep/fmod/*.cpp))
LOWLEVEL_LIB =lib/libfmod.so
CFLAGS+=-Idep/fmod -m64 -pthread 
LDFLAGS+=-Wl,-rpath=\$$ORIGIN/$(dir ${LOWLEVEL_LIB}) ${LOWLEVEL_LIB}

KINGPINOBJ=$(KINGPINSRC:.cpp=.o)

SPAZYSRC=$(subst src/Spazy/, , $(wildcard src/Spazy/*.cpp))
SPAZYOBJ:=$(SPAZYSRC:.cpp=.o)

#LDFLAGS is used for programs using created library in lib.
LDFLAGS+=-L/usr/lib64 -lGLU -lGL -lglut -lSDL2main -lSDL2 -lglfw3 -lGLEW

LIBS=libSpazy.a libKingPin.a 
PROG=main sandbox

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

spazy: $(addprefix $(LIBDIR)/, libSpazy.a)

$(addprefix $(LIBDIR)/, libSpazy.a): $(addprefix $(OBJDIR)/, $(SPAZYOBJ))
	@ echo "Making Spazy library in $@"
	@ ar rcs $@ $(addprefix $(OBJDIR)/, $(SPAZYOBJ))

%: %.cpp $(addprefix $(LIBDIR)/, $(LIBS))
	$(CC) $< $(CFLAGS) $(addprefix $(LIBDIR)/, $(LIBS)) $(LDFLAGS) -o $@

clean:
	@ echo "Cleaning library"
	@ rm -f $(addprefix $(OBJDIR)/, *.o)
	@ rm -f $(addprefix $(LIBDIR)/, $(LIB))

distclean:
	@ make -s clean
	@ echo "Cleaning programs"
	@ rm -f $(PROG)
