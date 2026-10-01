#ifndef BATALHA_H
#define BATALHA_H

#include "jogador.h"
#include "pokemon.h"

char realizarBatalha(Jogador *player, Pilha *pilhaPokAdversario, tp_listase **mortos, int *pontos, Pilha *pilha, Pokemon *pokemonsrest);

#endif /* BATALHA_H */
