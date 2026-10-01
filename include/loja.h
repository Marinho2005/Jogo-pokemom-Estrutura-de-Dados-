#ifndef LOJA_H
#define LOJA_H

#include "jogador.h"
#include "pokemon.h"

typedef struct NoLoja {
    char nome[50];
    int preco;
    struct NoLoja* proximo;
} ListaLoja;

ListaLoja* inicializaListaLoja(void);
void insereItemNaLoja(ListaLoja** lista, const char* nome, int preco);
void exibeLoja(const ListaLoja* lista, const Jogador* jogador);
char exibirLoja(ListaLoja* lista, Jogador* jogador, tp_listase **mortos, int *pontos);
void destroiListaLoja(ListaLoja** lista);

#endif /* LOJA_H */
