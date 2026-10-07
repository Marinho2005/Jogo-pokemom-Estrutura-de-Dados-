# ⚡ PokeRogue - Edição Estruturas de Dados (AED)

<p align="center">
  <img src="assets/preview.png" alt="PokeRogue - Tela Inicial" width="760"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Plataformas-Windows%20%7C%20Linux-brightgreen.svg" alt="Plataformas"/>
  <img src="https://img.shields.io/badge/Instalação-Portátil%20(Sem%20Dependências)-blue.svg" alt="Portátil"/>
  <img src="https://img.shields.io/badge/Versão-1.0.0-orange.svg" alt="Versão"/>
</p>

Um jogo de batalha e captura de Pokémon estilo *roguelike* com gráficos em pixel art e efeitos sonoros retrô. Você pode jogar tanto no **Windows** quanto no **Linux** sem precisar instalar nada além do próprio jogo!

---

## 📥 Como Baixar e Jogar

Os executáveis pré-compilados já estão disponíveis **diretamente na raiz deste repositório**! Basta clonar o repositório ou baixar o arquivo correspondente ao seu sistema operacional:

### 🪟 No Windows (Execução Direta)

1. Os arquivos necessários já estão juntos na raiz do projeto:
   * `PokeRogue-Windows-x64.exe`
   * `SDL2.dll`
2. Dê **duplo clique** em **`PokeRogue-Windows-x64.exe`** para jogar imediatamente!

> **💡 Dica:** Você pode criar um atalho de `PokeRogue-Windows-x64.exe` na sua Área de Trabalho para abrir mais rápido.

---

### 🐧 No Linux (AppImage Portátil)

O formato AppImage é portátil e funciona em praticamente qualquer sistema Linux (Ubuntu, Mint, Fedora, Debian, Manjaro, Arch, etc.):

1. Localize o executável na raiz:
   * `PokeRogue-Linux-x86_64.AppImage`
2. Certifique-se de que o arquivo possui permissão de execução:
   * **Pela interface gráfica:** Clique com o botão direito no arquivo > **Propriedades** > aba **Permissões** > marque a opção **"Permitir execução do arquivo como programa"**.
   * **Ou pelo terminal (se preferir):**
     ```bash
     chmod +x PokeRogue-Linux-x86_64.AppImage
     ```
3. Dê **duplo clique** no AppImage para abrir o jogo!

---

> 📦 **Downloads Compactados:** Se preferir baixar o pacote ZIP já fechado para Windows, acesse a página de **[Releases](https://github.com/Marinho2005/Jogo-pokemom-Estrutura-de-Dados-/releases)**.

---

## ⌨️ Controles do Jogo

| Controle / Tecla | Ação |
|---|---|
| **Botão Esquerdo do Mouse** | Navegar pelos menus, selecionar ataques, usar itens e interagir com o jogo. |
| **F11** | Alternar entre **Modo Janela** e **Tela Cheia** a qualquer momento. |
| **Bordas da Janela** | Arraste os cantos da janela para redimensionar livremente o tamanho da tela. |
| **Esc** | Voltar ao menu anterior ou fechar avisos. |
| **Enter / Espaço** | Confirmar opções de diálogo e avançar telas rapidamente. |

---

## ❓ Solução de Problemas Comuns

### 1. O Windows exibiu o aviso "O Windows protegeu o seu computador" (SmartScreen)
Isso é normal em jogos independentes baixados da internet que não possuem certificado corporativo pago da Microsoft:
* Clique em **"Mais informações"**.
* Depois clique em **"Executar assim mesmo"**.

### 2. O jogo não abre no Linux ao dar duplo clique no AppImage
Verifique se você concedeu a permissão de execução:
* Clique com o botão direito no arquivo `PokeRogue-Linux-x86_64.AppImage`, vá em **Propriedades** e garanta que **"Permitir execução como programa"** está ativado.
* Se estiver em distribuições como Ubuntu 22.04+ ou Fedora e nada acontecer, certifique-se de que o suporte a FUSE está ativo (pacote `libfuse2`).

### 3. Onde ficam salvos meu progresso e meus recordes?
* **No Windows:** Na mesma pasta onde você extraiu o jogo (`savegame.dat` e `ranking.txt`).
* **No Linux (AppImage):** Na pasta onde você mantém o AppImage.

### 4. Como ajustar o som ou colocar em tela cheia?
Dentro do jogo, acesse a aba **CONFIGURAÇÕES** no menu inicial ou no Lobby. Você pode ajustar o volume do som de 0% a 100%, ativar o modo mudo e alternar para tela cheia com um clique.

---

## 🛠️ Compilação a partir do Código-Fonte (Desenvolvedores)

Caso queira alterar o código em C e compilar o jogo manualmente:

```bash
# 1. Compilar e rodar a versão com interface gráfica no Linux:
make -f scripts/Makefile run

# 2. Apenas compilar o binário em dist/:
make -f scripts/Makefile gui

# 3. Gerar o pacote AppImage na raiz:
make -f scripts/Makefile appimage

# 4. Gerar o executável do Windows e pacote ZIP (requer MinGW):
make -f scripts/Makefile win
```

---

## 📁 Estrutura de Arquivos

```text
.
├── PokeRogue-Linux-x86_64.AppImage  # Executável portátil para Linux
├── PokeRogue-Windows-x64.exe        # Executável nativo para Windows
├── SDL2.dll                         # Biblioteca dinâmica necessária no Windows
├── ranking.txt                      # Hall da Fama e persistência de pontuação
├── assets/                          # Imagens, ícones e visualizações
├── dist/                            # Saída de compilação e arquivos de release
├── include/                         # Cabeçalhos do jogo (.h)
├── scripts/                         # Makefile e scripts de automação/build
└── src/                             # Código-fonte do jogo em C (.c)
```

---

## 🏆 Sobre o Jogo

O **PokeRogue - Edição Estruturas de Dados** é um jogo que combina o universo Pokémon com desafios táticos e estruturas de dados dinâmicas (filas circulares de ataques, pilhas de adversários e listas de Pokémons). Divirta-se tentando bater o recorde no Hall da Fama!

