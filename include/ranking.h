#ifndef RANKING_H
#define RANKING_H

#include <stdio.h>

typedef struct {
    char nome[20];
    int pontuacao;
} Registro;

void salvarRanking(const char *nomeJogador, int pontuacao);
void exibirRanking(void);
int comparaRanking(const void *n1, const void *n2);

#endif /* RANKING_H */
