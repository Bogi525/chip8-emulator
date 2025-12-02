SRC_FILES = src/chip8.cpp src/main.cpp
OBJ_FILES_BACKSLASH = build\chip8.o build\main.o
OBJ_FILES_SLASH = build/chip8.o build/main.o
BUILD_FILES_BACKSLASH = build\chip8.exe
BUILD_FILES_SLASH = build/chip8.exe

all: clean build_chip8

build_chip8: $(OBJ_FILES_SLASH)	
	g++ $(OBJ_FILES_SLASH) -L D:\Libraries\SDL3-3.2.26\i686-w64-mingw32\lib -lSDL3 -o $(BUILD_FILES_SLASH)

build/chip8.o: src/chip8.cpp
	g++ -I D:\Libraries\SDL3-3.2.26\i686-w64-mingw32\include -c src/chip8.cpp -o build/chip8.o

build/main.o: src/main.cpp
	g++ -I D:\Libraries\SDL3-3.2.26\i686-w64-mingw32\include -c src/main.cpp -o build/main.o

clean:
	- cmd /C del $(BUILD_FILES_BACKSLASH)
	- cmd /C del $(OBJ_FILES_BACKSLASH)

open_program:
	$(BUILD_FILES_BACKSLASH)

.PHONY: all build_chip8 clean open_program