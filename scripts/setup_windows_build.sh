#!/usr/bin/env bash
set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

echo "=== Configurando ambiente de compilação Windows (MinGW + SDL2) ==="

# 1. Verifica se mingw-w64 está instalado
if ! command -v x86_64-w64-mingw32-gcc &> /dev/null; then
    echo "x86_64-w64-mingw32-gcc não encontrado!"
    echo "Por favor, instale o MinGW no seu terminal Ubuntu executando:"
    echo "  sudo apt update && sudo apt install -y mingw-w64"
    exit 1
fi

echo "MinGW encontrado!"

# 2. Baixar e preparar SDL2 para Windows (se ainda não existir)
SDL_VER="2.28.5"
SDL_TAR="SDL2-devel-${SDL_VER}-mingw.tar.gz"
SDL_URL="https://github.com/libsdl-org/SDL/releases/download/release-${SDL_VER}/${SDL_TAR}"

if [ ! -d "windows-libs" ]; then
    echo "Baixando SDL2 Windows ($SDL_VER)..."
    mkdir -p /tmp/sdl_win
    curl -L -o "/tmp/sdl_win/${SDL_TAR}" "$SDL_URL"
    tar -xzf "/tmp/sdl_win/${SDL_TAR}" -C /tmp/sdl_win

    mkdir -p windows-libs/include
    mkdir -p windows-libs/lib

    cp -r /tmp/sdl_win/SDL2-${SDL_VER}/x86_64-w64-mingw32/include/SDL2 windows-libs/include/
    cp -r /tmp/sdl_win/SDL2-${SDL_VER}/x86_64-w64-mingw32/lib/* windows-libs/lib/
    cp /tmp/sdl_win/SDL2-${SDL_VER}/x86_64-w64-mingw32/bin/SDL2.dll windows-libs/

    rm -rf /tmp/sdl_win
    echo "Bibliotecas do SDL2 Windows configuradas com sucesso em windows-libs/!"
fi

# 3. Compilar jogoAED_gui.exe
mkdir -p dist
echo "Compilando jogoAED_gui.exe para Windows (x86_64)..."
x86_64-w64-mingw32-gcc -Wall -Wextra -Iinclude -Iwindows-libs/include/SDL2 \
    src/pokemon.c src/jogador.c src/loja.c src/ranking.c src/utils.c \
    src/gui_draw.c src/gui_audio.c src/savegame.c src/gui.c src/main_gui.c \
    -Lwindows-libs/lib -lmingw32 -lSDL2main -lSDL2 -o dist/jogoAED_gui.exe

echo "=== Compilação concluída com sucesso! ==="
echo "Executável: dist/jogoAED_gui.exe gerado com sucesso."
