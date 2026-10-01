#ifndef POKEMON_H
#define POKEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HABILIDADES 10

typedef struct {
    char name[20];
    int dano;
} Habilidade;

typedef struct {
    int inicial, final, quantidade;
    Habilidade valores[MAX_HABILIDADES];
} Fila;

typedef struct {
    char nome[20];
    Fila filadeatk;
    int vida;
    char criterio[10];
    int vidamax;
} Pokemon;

/* Pilha dinâmica de Pokémon */
typedef struct {
    Pokemon *pokemons;
    int topo;
    int capacidade;
} Pilha;

/* Lista simplesmente encadeada de Pokémon */
typedef struct tp_no {
    Pokemon info;
    struct tp_no *prox;
} tp_listase;

/* Funções de Habilidade */
Habilidade criarHabilidade(const char *pont, int damage);

/* Funções de Pokémon */
Pokemon criarPokemon(const char *nome, int vida);
void embaralharPokemons(Pokemon *pokemons, int n);
void aplicarDano(Pokemon *alvo, int danoBase);
void aplicarDanoAdversario(Pokemon *alvo, int danoBase, int pontos);

/* Funções da Fila (Habilidades) */
int criarFila(Fila *p1);
int vaziaFila(const Fila *p1);
int cheiaFila(const Fila *p1);
int retirarFila(Fila *p1, Habilidade *e);
int inserirFila(Fila *p1, const char *nome, int dano);
void imprimaFila(Fila m);
int quantidadeFila(const Fila *f1);
void exibeHabilidades(const Fila *fila, Pokemon p1);
Habilidade* escolherHabilidadePorIndice(Fila *fila, int indice);

/* Funções da Pilha (Pokémons) */
void criarPilha(Pilha *pilha, int capacidade);
int pushPilha(Pilha *pilha, Pokemon pokemon);
int vaziaPilha(const Pilha *pilha);
int cheiaPilha(const Pilha *pilha);
Pokemon popPilha(Pilha *pilha, Pokemon *resto);
void imprimaPilha(Pilha p);
void destroiPilha(Pilha *pilha);

/* Funções da Lista Encadeada (Time e Mortos) */
tp_listase *inicializaListase(void);
int listaVazia(const tp_listase *lista);
tp_listase *alocaListase(void);
int insereListaNoFim(tp_listase **l, Pokemon e);
void imprime_listase(const tp_listase *lista);
void imprime_listasevivos(const tp_listase *lista);
int remove_listase(tp_listase **lista, Pokemon p);
tp_listase *busca_listase(tp_listase *lista, Pokemon p);
int tamanho_listase(const tp_listase *lista);
void destroi_listase(tp_listase **l);

#endif /* POKEMON_H */
