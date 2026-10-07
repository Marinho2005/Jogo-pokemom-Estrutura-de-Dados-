#!/usr/bin/env bash
set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

echo "=== Empacotando PokeRogue para Linux (x86_64) ==="

DIST_DIR="dist"
APPIMAGE_OUTPUT="${PROJECT_ROOT}/PokeRogue-Linux-x86_64.AppImage"
mkdir -p "$DIST_DIR"

# 1. Compila o binário Linux nativo
echo "Compilando jogoAED_gui para Linux..."
make -f scripts/Makefile clean
make -f scripts/Makefile gui


# 2. Prepara ícone se não existir
if [ ! -f "assets/icon.png" ]; then
    echo "Gerando assets/icon.png..."
    convert -size 256x256 xc:none \
      -fill "#222222" -draw "circle 128,128 128,14" \
      -fill "#E53935" -draw "arc 20,20 236,236 180 360" \
      -fill "#FAFAFA" -draw "arc 20,20 236,236 0 180" \
      -fill "#222222" -draw "rectangle 14,120 242,136" \
      -fill "#222222" -draw "circle 128,128 128,92" \
      -fill "#FFFFFF" -draw "circle 128,128 128,104" \
      -fill "#EEEEEE" -draw "circle 128,128 128,114" \
      assets/icon.png
fi

# ==========================================
# 3. Geração do AppImage Portátil
# ==========================================
APPDIR="/tmp/pokerogue-appdir"
rm -rf "$APPDIR"
mkdir -p "$APPDIR/usr/bin"
mkdir -p "$APPDIR/usr/lib"
mkdir -p "$APPDIR/usr/share/pokerogue"
mkdir -p "$APPDIR/usr/share/applications"
mkdir -p "$APPDIR/usr/share/icons/hicolor/256x256/apps"

# Copia binário e dados
cp dist/jogoAED_gui "$APPDIR/usr/bin/"
cp ranking.txt "$APPDIR/usr/share/pokerogue/"

# Copia dependência libSDL2 para dentro do AppImage (para máxima portabilidade)
SDL2_LIB=$(ldd ./dist/jogoAED_gui | grep libSDL2 | awk '{print $3}')
if [ -n "$SDL2_LIB" ] && [ -f "$SDL2_LIB" ]; then
    cp -L "$SDL2_LIB" "$APPDIR/usr/lib/libSDL2-2.0.so.0"
fi

# Desktop Entry
cat << 'DESK_EOF' > "$APPDIR/pokerogue.desktop"
[Desktop Entry]
Type=Application
Name=PokeRogue AED
GenericName=Pokemon Roguelike
Comment=Jogo Roguelike Pokemon em C com SDL2
Exec=jogoAED_gui
Icon=pokerogue
Categories=Game;
Terminal=false
DESK_EOF

cp "$APPDIR/pokerogue.desktop" "$APPDIR/usr/share/applications/"

# Ícones
cp assets/icon.png "$APPDIR/pokerogue.png"
cp assets/icon.png "$APPDIR/usr/share/icons/hicolor/256x256/apps/pokerogue.png"

# Script AppRun
cat << 'APPRUN_EOF' > "$APPDIR/AppRun"
#!/bin/sh
HERE="$(dirname "$(readlink -f "${0}")")"
export LD_LIBRARY_PATH="${HERE}/usr/lib:${LD_LIBRARY_PATH}"

# Cria arquivo ranking.txt local se não existir
if [ ! -f "ranking.txt" ] && [ -f "${HERE}/usr/share/pokerogue/ranking.txt" ]; then
    cp "${HERE}/usr/share/pokerogue/ranking.txt" ./
fi

exec "${HERE}/usr/bin/jogoAED_gui" "$@"
APPRUN_EOF
chmod +x "$APPDIR/AppRun"

# Baixa appimagetool se necessário
APPIMAGETOOL="/tmp/appimagetool"
if [ ! -f "$APPIMAGETOOL" ]; then
    echo "Baixando appimagetool..."
    curl -L -s -o "$APPIMAGETOOL" https://github.com/AppImage/appimagetool/releases/download/continuous/appimagetool-x86_64.AppImage
    chmod +x "$APPIMAGETOOL"
fi

echo "Gerando AppImage portátil..."
ARCH=x86_64 "$APPIMAGETOOL" --appimage-extract-and-run "$APPDIR" "$APPIMAGE_OUTPUT"
chmod +x "$APPIMAGE_OUTPUT"
echo "=== AppImage gerado com sucesso: $APPIMAGE_OUTPUT ==="

rm -rf "$APPDIR"
