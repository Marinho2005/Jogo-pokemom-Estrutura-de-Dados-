#ifndef JOGADOR_H
#define JOGADOR_H

#include "pokemon.h"

typedef struct {
    int moedas;
    tp_listase *pokemonslista;
    int pokebolas;
    int pontuacao;
    char nome[20];
} Jogador;

int usarPokebola(Jogador *player);
int tentarCapturarPokemon(Jogador *player, Pokemon *adversario);
void adicionarPokemonCapturado(Jogador *player, Pokemon *capturado);

#endif /* JOGADOR_H */
