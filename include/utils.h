#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
  #include <windows.h>
  #include <conio.h>
#else
  #include <unistd.h>
  #include <termios.h>
#endif

extern const char *bold_red;
extern const char *reset_color;

/* Controle de terminal e cores cross-platform */
void setColor(int color);
void setColor2(int color);
void limparTela(void);
int getch(void);
void pausarSegundos(int segundos);

/* Funções de leitura segura para prevenir travamentos por teclas indesejadas */
void limparBuffer(void);
int lerInteiro(int min, int max, const char *mensagem);
char lerCaractereOpcao(const char *opcoesValidas, const char *mensagem);
void lerString(char *destino, int tamanhoMaximo, const char *mensagem);

/* Tela de abertura */
void inicioDoJogo(void);

#endif /* UTILS_H */
