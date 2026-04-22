CXX = clang++
CXXFLAGS = -std=c++17 -Wall -O2

SDL_PREFIX := $(shell brew --prefix sdl2)
SDL_TTF_PREFIX := $(shell brew --prefix sdl2_ttf)
SDL_IMG_PREFIX := $(shell brew --prefix sdl2_image)

SDL_INC = -I$(SDL_PREFIX)/include \
	-I$(SDL_PREFIX)/include/SDL2 \
	-I$(SDL_TTF_PREFIX)/include \
	-I$(SDL_TTF_PREFIX)/include/SDL2 \
	-I$(SDL_IMG_PREFIX)/include \
	-I$(SDL_IMG_PREFIX)/include/SDL2

SDL_LIB = -L$(SDL_PREFIX)/lib -L$(SDL_TTF_PREFIX)/lib -L$(SDL_IMG_PREFIX)/lib

LIBS = -lSDL2 -lSDL2_ttf -lSDL2_image

TARGET = main
OBJ = \
	Board.o \
	Display.o \
	Game.o \
	Player.o \
	AIPlayer.o \
	main.o \

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "Linking [$@]"
	@$(CXX) $^ $(LIBS) $(SDL_LIB) -o $(TARGET)

%.o: %.cpp
	@echo "Compiling [$<]"
	@$(CXX) -c $< $(CXXFLAGS) $(SDL_INC) -o $@

clean:
	@rm -f $(TARGET)
	@rm -f $(OBJ)
