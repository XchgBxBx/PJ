
SOURCES= \
  Node.cpp \
  \
  Game/Quad.cpp \
  \
  Main.cpp


INCLUDE_DIR= \
  -I "./3rd/SDL2/i686-w64-mingw32/include" \
  -I "./3rd/GLEW/include"

LIB_DIR= \
  -L "./3rd/SDL2/i686-w64-mingw32/lib" \
  -L "./3rd/GLEW/lib/Release/Win32"

LIBS = \
  -lmingw32 \
  -lSDL2main \
  -lSDL2 \
  -lglu32 \
  -lglew32s \
  -lopengl32

FLAGS = \
  -fpermissive

all: build
	a.exe

build:
	g++ $(SOURCES) $(INCLUDE_DIR) $(LIB_DIR) $(LIBS) $(FLAGS)