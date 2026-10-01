#include "batalha.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char realizarBatalha(Jogador *player, Pilha *pilhaPokAdversario, tp_listase **mortos, int *pontos, Pilha *pilha, Pokemon *pokemonsrest) {
    Pokemon adversario;

    if (!vaziaPilha(pilhaPokAdversario)) {
        popPilha(pilhaPokAdversario, &adversario);
    } else {
        /* Repopula a pilha se estiver vazia */
        for (int i = 0; i < 12; i++) {
            pushPilha(pilhaPokAdversario, pokemonsrest[i]);
        }
        popPilha(pilhaPokAdversario, &adversario);
    }

    printf("\nVoce esta enfrentando %s!\n", adversario.nome);

    int totalVivos = tamanho_listase(player->pokemonslista);
    if (totalVivos == 0) {
        printf("Voce nao tem nenhum Pokemon disponivel para combate!\n");
        return 'f';
    }

    /* Seleção do Pokémon do jogador */
    printf("\nEscolha um Pokemon para o combate:\n");
    tp_listase *atu = player->pokemonslista;
    int count = 1;
    while (atu != NULL) {
        printf("%d. %s (Vida: %d / %d)\n", count, atu->info.nome, atu->info.vida, atu->info.vidamax);
        atu = atu->prox;
        count++;
    }

    int escolha = lerInteiro(1, totalVivos, "Digite o numero do seu Pokemon: ");

    atu = player->pokemonslista;
    for (int i = 1; i < escolha && atu != NULL; i++) {
        atu = atu->prox;
    }

    if (atu == NULL) {
        printf("Escolha invalida. Batalha cancelada.\n");
        return '0';
    }

    Pokemon *jogadorPokemon = &atu->info;

    /* Loop de combate por turnos */
    while (adversario.vida > 0 && jogadorPokemon->vida > 0) {
        printf("\n================ COMBATE ================\n");
        printf("Seu Pokemon: %s (Vida: %d / %d)\n", jogadorPokemon->nome, jogadorPokemon->vida, jogadorPokemon->vidamax);
        printf("Adversario : %s (Vida: %d / %d)\n", adversario.nome, adversario.vida, adversario.vidamax);
        printf("Pokebolas disponiveis: %d\n", player->pokebolas);
        printf("-----------------------------------------\n");
        printf("1. Atacar\n");
        printf("2. Usar Pokebola\n");

        int acao = lerInteiro(1, 2, "Escolha sua acao: ");

        if (acao == 1) {
            printf("\nEscolha uma habilidade para atacar:\n");
            int indice = jogadorPokemon->filadeatk.inicial;
            for (int i = 0; i < jogadorPokemon->filadeatk.quantidade; i++) {
                printf("%d. %s (Dano: %d)\n", i + 1, jogadorPokemon->filadeatk.valores[indice].name, jogadorPokemon->filadeatk.valores[indice].dano);
                indice = (indice + 1) % MAX_HABILIDADES;
            }

            int escolha_hab = lerInteiro(1, jogadorPokemon->filadeatk.quantidade, "Escolha a habilidade: ");
            Habilidade *hab_jogador = escolherHabilidadePorIndice(&jogadorPokemon->filadeatk, escolha_hab - 1);

            if (hab_jogador != NULL) {
                aplicarDano(&adversario, hab_jogador->dano);
                printf("\nVoce usou %s e causou %d de dano!\n", hab_jogador->name, hab_jogador->dano);
            }

            if (adversario.vida <= 0) {
                printf("\n>>> Parabens! %s foi derrotado! <<<\n", adversario.nome);
                player->moedas += 250;
                (*pontos)++;
                player->pontuacao++;
                printf("Voce ganhou 250 moedas e 1 ponto de pontuacao!\n");
                pausarSegundos(2);
                return '0';
            }

        } else if (acao == 2) {
            if (player->pokebolas == 0) {
                printf("Voce tem 0 Pokebolas disponiveis!\n");
                pausarSegundos(1);
                continue;
            }

            if (tentarCapturarPokemon(player, &adversario)) {
                adicionarPokemonCapturado(player, &adversario);
                printf("\nBatalha terminada! Voce capturou %s.\n", adversario.nome);
                player->moedas += 100;
                (*pontos)++;
                player->pontuacao++;
                pausarSegundos(2);
                return '0';
            } else {
                printf("A captura falhou! A batalha continua...\n");
            }
        }

        /* Turno do adversário */
        if (adversario.vida > 0) {
            if (adversario.filadeatk.quantidade > 0) {
                int hab_index = rand() % adversario.filadeatk.quantidade;
                Habilidade *hab_adversario = escolherHabilidadePorIndice(&adversario.filadeatk, hab_index);
                if (hab_adversario != NULL) {
                    aplicarDanoAdversario(jogadorPokemon, hab_adversario->dano, *pontos);
                    printf("%s usou %s e causou %d de dano!\n", adversario.nome, hab_adversario->name, hab_adversario->dano);
                }
            }
        }

        /* Verifica se o Pokémon do jogador foi derrotado */
        if (jogadorPokemon->vida <= 0) {
            printf("\nSeu %s foi derrotado!\n", jogadorPokemon->nome);
            printf("Pressione [ESPACO] ou [ENTER] para voltar ao lobby.\n");
            getch();
            limparTela();

            jogadorPokemon->vida = jogadorPokemon->vidamax;
            pushPilha(pilha, adversario);

            insereListaNoFim(mortos, *jogadorPokemon);
            remove_listase(&player->pokemonslista, *jogadorPokemon);

            if (listaVazia(player->pokemonslista)) {
                printf("Todos os seus Pokemons foram derrotados!\n");
                pausarSegundos(2);
                return 'f';
            }
            return '0';
        }
    }

    return '0';
}
