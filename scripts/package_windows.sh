#!/usr/bin/env bash
set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

echo "=== Empacotando PokeRogue para Windows (x64) ==="

# Verifica MinGW
if ! command -v x86_64-w64-mingw32-gcc &> /dev/null; then
    echo "Erro: x86_64-w64-mingw32-gcc não encontrado!"
    exit 1
fi

# Garante dependências do Windows (SDL2.dll)
if [ ! -f "SDL2.dll" ] || [ ! -d "windows-libs" ]; then
    bash scripts/setup_windows_build.sh
fi

DIST_DIR="dist"
WIN_PKG_DIR="${DIST_DIR}/PokeRogue-Windows-x64"
ZIP_FILE="${DIST_DIR}/PokeRogue-Windows-x64.zip"

rm -rf "$WIN_PKG_DIR" "$ZIP_FILE"
mkdir -p "$WIN_PKG_DIR"

echo "Compilando executável nativo Windows (jogoAED_gui.exe)..."
x86_64-w64-mingw32-gcc -O2 -Wall -Wextra -Iinclude -Iwindows-libs/include/SDL2 \
    src/pokemon.c src/jogador.c src/loja.c src/ranking.c src/utils.c \
    src/gui_draw.c src/gui_audio.c src/savegame.c src/gui.c src/main_gui.c \
    -Lwindows-libs/lib -lmingw32 -lSDL2main -lSDL2 -mwindows -o "${WIN_PKG_DIR}/jogoAED_gui.exe"

cp SDL2.dll "$WIN_PKG_DIR/"
cp ranking.txt "$WIN_PKG_DIR/"

cat << 'DOC_EOF' > "${WIN_PKG_DIR}/COMO_JOGAR.txt"
============================================================
              POKEROGUE - ESTRUTURA DE DADOS (AED)
============================================================

COMO JOGAR NO WINDOWS:
1. Extraia todo o conteudo deste arquivo ZIP em qualquer pasta
   (ex: Area de Trabalho ou Documentos).
2. De dois cliques no arquivo:
      jogoAED_gui.exe
3. Divirta-se!

DICAS:
- Pressione F11 a qualquer momento para entrar/sair da Tela Cheia.
- Voce tambem pode redimensionar a janela arrastando os cantos.
- Seu progresso e ranking ficam salvos automaticamente na mesma pasta.
============================================================
DOC_EOF

echo "Criando arquivo compactado ${ZIP_FILE}..."
(cd "$DIST_DIR" && zip -r "PokeRogue-Windows-x64.zip" "PokeRogue-Windows-x64")

echo "=== Pacote Windows gerado com sucesso em: ${ZIP_FILE} ==="
