CC ?= gcc
CFLAGS ?= -Wall -Wextra -Iinclude

# Deteccao automatica do sistema operacional (Windows vs Linux / POSIX)
ifeq ($(OS),Windows_NT)
    EXE = .exe
    RM = del /Q /F 2>nul || rm -f
    SDL_CFLAGS ?= $(shell pkg-config --cflags sdl2 2>/dev/null || echo -Iinclude/SDL2)
    SDL_LIBS ?= $(shell pkg-config --libs sdl2 2>/dev/null || echo -lmingw32 -lSDL2main -lSDL2)
else
    EXE =
    RM = rm -f
    SDL_CFLAGS ?= $(shell pkg-config --cflags sdl2 2>/dev/null || echo -D_REENTRANT -I/usr/include/SDL2)
    SDL_LIBS ?= $(shell pkg-config --libs sdl2 2>/dev/null || echo -lSDL2) -lm
endif

# Arquivos de logica e estruturas de dados compartilhadas
COMMON_SRC = src/pokemon.c src/jogador.c src/loja.c src/ranking.c src/utils.c
HEADERS = $(wildcard include/*.h)

# Executavel com Interface Grafica (SDL2)
GUI_TARGET = jogoAED_gui$(EXE)
GUI_SRC = $(COMMON_SRC) src/gui_draw.c src/gui_audio.c src/savegame.c src/gui.c src/main_gui.c

# Executavel de Terminal (CLI)
TERM_TARGET = jogoAED$(EXE)
TERM_SRC = $(COMMON_SRC) src/batalha.c src/jogoAED.c

all: $(GUI_TARGET) $(TERM_TARGET)

gui: $(GUI_TARGET)

term: $(TERM_TARGET)

$(GUI_TARGET): $(GUI_SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $(GUI_SRC) $(SDL_LIBS) -o $(GUI_TARGET)

$(TERM_TARGET): $(TERM_SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(TERM_SRC) -o $(TERM_TARGET)

clean:
	$(RM) $(GUI_TARGET) $(TERM_TARGET)

# Alvos para compilar e testar a versao Windows direto no Linux via Wine
win:
	@bash scripts/setup_windows_build.sh

wine:
	wine ./jogoAED_gui.exe

.PHONY: all gui term clean win wine
