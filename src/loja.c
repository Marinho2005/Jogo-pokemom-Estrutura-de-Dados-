#include "loja.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListaLoja* inicializaListaLoja(void) {
    return NULL;
}

void insereItemNaLoja(ListaLoja** lista, const char* nome, int preco) {
    ListaLoja* novoItem = (ListaLoja*)malloc(sizeof(ListaLoja));
    if (novoItem == NULL) {
        printf("Erro de alocacao de memoria na loja!\n");
        exit(1);
    }
    strncpy(novoItem->nome, nome, sizeof(novoItem->nome) - 1);
    novoItem->nome[sizeof(novoItem->nome) - 1] = '\0';
    novoItem->preco = preco;
    novoItem->proximo = *lista;
    *lista = novoItem;
}

void exibeLoja(const ListaLoja* lista, const Jogador* jogador) {
    const ListaLoja* atu = lista;
    printf("Suas moedas: %d\n", jogador->moedas);
    printf("Itens a venda:\n");
    while (atu != NULL) {
        printf("%s - %d moedas\n", atu->nome, atu->preco);
        atu = atu->proximo;
    }
}

void destroiListaLoja(ListaLoja** lista) {
    ListaLoja* atu = *lista;
    while (atu != NULL) {
        ListaLoja* temp = atu;
        atu = atu->proximo;
        free(temp);
    }
    *lista = NULL;
}

char exibirLoja(ListaLoja* lista, Jogador* jogador, tp_listase **mortos, int *pontos) {
    char continuar;
    do {
        ListaLoja *atu = lista;
        printf("\nVoce tem %d moedas\n", jogador->moedas);
        printf("0. Sair da loja\n");

        int i = 1;
        while (atu != NULL) {
            printf("%d. %s (%d moedas)\n", i, atu->nome, atu->preco);
            atu = atu->proximo;
            i++;
        }

        int opcao = lerInteiro(0, 3, "Escolha uma opcao: ");

        if (opcao == 0) {
            limparTela();
            return '0';
        }

        if (opcao == 1) { // Reviver Pokémon (1000 moedas)
            tp_listase *cemiterio = *mortos;
            if (cemiterio == NULL) {
                printf("Nenhum Pokemon no cemiterio para reviver!\n");
                printf("Voltando ao menu da loja...\n");
                pausarSegundos(2);
            } else if (jogador->moedas < 1000) {
                printf("Moedas insuficientes! Reviver custa 1000 moedas (voce tem %d).\n", jogador->moedas);
                pausarSegundos(2);
            } else {
                int totalMortos = 0;
                tp_listase *temp = cemiterio;
                while (temp != NULL) {
                    totalMortos++;
                    printf("%d. %s (Vida: %d)\n", totalMortos, temp->info.nome, temp->info.vida);
                    temp = temp->prox;
                }

                int decida = lerInteiro(1, totalMortos, "Escolha o Pokemon para reviver: ");
                cemiterio = *mortos;
                for (int c = 1; c < decida && cemiterio != NULL; c++) {
                    cemiterio = cemiterio->prox;
                }

                if (cemiterio != NULL) {
                    jogador->moedas -= 1000;
                    cemiterio->info.vida = cemiterio->info.vidamax;
                    insereListaNoFim(&jogador->pokemonslista, cemiterio->info);
                    remove_listase(mortos, cemiterio->info);
                    printf("Pokemon revivido com sucesso!\n");
                    pausarSegundos(1);
                }
            }
        } else if (opcao == 2) { // Comprar Pokébola (200 moedas)
            atu = lista;
            for (int j = 1; j < opcao && atu != NULL; j++) {
                atu = atu->proximo;
            }

            if (atu != NULL && jogador->moedas >= atu->preco) {
                jogador->moedas -= atu->preco;
                jogador->pokebolas++;
                printf("Pokebola comprada com sucesso!\n");
                printf("Voce agora tem %d Pokebolas e %d moedas.\n", jogador->pokebolas, jogador->moedas);
            } else {
                printf("Moedas insuficientes para comprar Pokebola!\n");
            }
        } else if (opcao == 3) { // Poção de cura (500 moedas)
            atu = lista;
            for (int j = 1; j < opcao && atu != NULL; j++) {
                atu = atu->proximo;
            }

            if (atu != NULL && jogador->moedas >= atu->preco) {
                int numPokemons = tamanho_listase(jogador->pokemonslista);
                if (numPokemons == 0) {
                    printf("Voce nao tem nenhum Pokemon no time para curar!\n");
                } else {
                    printf("%s comprado!\n", atu->nome);
                    jogador->moedas -= atu->preco;

                    printf("Seus Pokemons:\n");
                    tp_listase *atuPoke = jogador->pokemonslista;
                    int count = 1;
                    while (atuPoke != NULL) {
                        printf("%d. %s (Vida: %d / %d)\n", count, atuPoke->info.nome, atuPoke->info.vida, atuPoke->info.vidamax);
                        atuPoke = atuPoke->prox;
                        count++;
                    }

                    int escolhaPoke = lerInteiro(1, numPokemons, "Escolha o Pokemon para aplicar a pocao: ");
                    atuPoke = jogador->pokemonslista;
                    for (int c = 1; c < escolhaPoke && atuPoke != NULL; c++) {
                        atuPoke = atuPoke->prox;
                    }

                    if (atuPoke != NULL) {
                        int cura_base = 30;
                        int aumento_por_pontos = (*pontos) / 10;
                        int cura_total = cura_base + (aumento_por_pontos * 5);

                        atuPoke->info.vida += cura_total;
                        if (atuPoke->info.vida > atuPoke->info.vidamax) {
                            atuPoke->info.vida = atuPoke->info.vidamax;
                        }
                        printf("Vida aumentada em %d pontos! (Vida atual: %d)\n", cura_total, atuPoke->info.vida);
                    }
                }
            } else {
                printf("Moedas insuficientes para comprar Pocao!\n");
            }
        }

        continuar = lerCaractereOpcao("SN", "Deseja continuar comprando? (S/N): ");
        if (continuar == 'N') {
            limparTela();
            return '0';
        }

    } while (continuar == 'S');

    limparTela();
    return '0';
}
