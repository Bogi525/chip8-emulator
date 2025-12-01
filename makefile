SRC_FILES = src/chip8.cpp src/main.cpp
OBJ_FILE = build/main.o
BUILD_FILE = build/chip8.exe

all:
	clean build_chip8

build_chip8:
	g++ -I D:\Libraries\SDL3-3.2.26\i686-w64-mingw32\include -c $(SRC_FILES) -o $(OBJ_FILE)
	g++ $(OBJ_FILE) -L D:\Libraries\SDL3-3.2.26\i686-w64-mingw32\lib -lSDL3 -o $(BUILD_FILE)

clean:
	- del $(BUILD_FILE) $(OBJ_FILE)

open_program:
	$(BUILD_FILE)