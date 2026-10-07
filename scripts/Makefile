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

# Diretorio de saida dos binarios de desenvolvimento
BIN_DIR = dist

# Arquivos de logica e estruturas de dados compartilhadas
COMMON_SRC = src/pokemon.c src/jogador.c src/loja.c src/ranking.c src/utils.c
HEADERS = $(wildcard include/*.h)

# Executavel com Interface Grafica (SDL2)
GUI_TARGET = $(BIN_DIR)/jogoAED_gui$(EXE)
GUI_SRC = $(COMMON_SRC) src/gui_draw.c src/gui_audio.c src/savegame.c src/gui.c src/main_gui.c

# Executavel de Terminal (CLI)
TERM_TARGET = $(BIN_DIR)/jogoAED$(EXE)
TERM_SRC = $(COMMON_SRC) src/batalha.c src/jogoAED.c

all: $(GUI_TARGET) $(TERM_TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

gui: $(BIN_DIR) $(GUI_TARGET)

term: $(BIN_DIR) $(TERM_TARGET)

run: gui
	./$(GUI_TARGET)

$(GUI_TARGET): $(GUI_SRC) $(HEADERS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $(GUI_SRC) $(SDL_LIBS) -o $(GUI_TARGET)

$(TERM_TARGET): $(TERM_SRC) $(HEADERS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(TERM_SRC) -o $(TERM_TARGET)

clean:
	$(RM) $(GUI_TARGET) $(TERM_TARGET) jogoAED_gui jogoAED_gui.exe jogoAED

# Alvo para compilar o executavel Windows (.exe)
win:
	@bash scripts/package_windows.sh

# Alvo para gerar o pacote AppImage na raiz do projeto
appimage:
	@bash scripts/package_linux.sh

.PHONY: all gui term run clean win appimage


