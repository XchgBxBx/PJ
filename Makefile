
SOURCES=Main.cpp


INCLUDE_DIR="C:/Users/felipe.silva/Desktop/PJ/3rd/SDL2/i686-w64-mingw32/include"

LIB_DIR="C:/Users/felipe.silva/Desktop/PJ/3rd/SDL2/i686-w64-mingw32/lib"

ALL:
	g++ $(SOURCES) -I $(INCLUDE_DIR) -L $(LIB_DIR) -lmingw32 -lSDL2main -lSDL2 -lopengl32 -fpermissive
	a.exe