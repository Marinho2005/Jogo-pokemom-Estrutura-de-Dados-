#include "jogador.h"
#include <stdio.h>
#include <stdlib.h>

int usarPokebola(Jogador *player) {
    if (player->pokebolas > 0) {
        player->pokebolas--;
        printf("Você usou uma Pokebola. Restantes: %d\n", player->pokebolas);
        return 1;
    } else {
        printf("Você não possui Pokebolas suficientes!\n");
        return 0;
    }
}

int tentarCapturarPokemon(Jogador *player, Pokemon *adversario) {
    if (!usarPokebola(player)) {
        return 0;
    }

    /* Taxa de captura baseada na vida restante */
    float taxaCaptura = (1.0f - ((float)adversario->vida / (float)adversario->vidamax)) * 100.0f;
    int chance = rand() % 100;

    if (chance < (int)taxaCaptura) {
        printf("Parabens! Voce capturou %s!\n", adversario->nome);
        return 1;
    } else {
        printf("O %s escapou da Pokebola!\n", adversario->nome);
        return 0;
    }
}

void adicionarPokemonCapturado(Jogador *player, Pokemon *capturado) {
    insereListaNoFim(&player->pokemonslista, *capturado);
    printf("%s foi adicionado ao seu time!\n", capturado->nome);
}
