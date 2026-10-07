#include "ranking.h"
#include <stdlib.h>
#include <string.h>

int comparaRanking(const void *n1, const void *n2) {
    const Registro *a = (const Registro *)n1;
    const Registro *b = (const Registro *)n2;
    if (a->pontuacao == b->pontuacao) return 0;
    else if (a->pontuacao < b->pontuacao) return 1;
    return -1;
}

int carregarRanking(Registro registros[], int max_registros) {
    if (!registros || max_registros <= 0) return 0;

    FILE *file = fopen("ranking.txt", "r");
    if (file == NULL) {
        return 0;
    }

    int count = 0;
    char temp_nome[20];
    int temp_pontos = 0;

    while (fscanf(file, "%19s %d", temp_nome, &temp_pontos) == 2) {
        /* Verifica se o jogador ja existe para manter apenas a maior pontuacao (evitar duplicatas) */
        int idx = -1;
        for (int i = 0; i < count; i++) {
            if (strcmp(registros[i].nome, temp_nome) == 0) {
                idx = i;
                break;
            }
        }

        if (idx >= 0) {
            if (temp_pontos > registros[idx].pontuacao) {
                registros[idx].pontuacao = temp_pontos;
            }
        } else if (count < max_registros) {
            strncpy(registros[count].nome, temp_nome, sizeof(registros[count].nome) - 1);
            registros[count].nome[sizeof(registros[count].nome) - 1] = '\0';
            registros[count].pontuacao = temp_pontos;
            count++;
        }
    }

    fclose(file);

    if (count > 1) {
        qsort(registros, count, sizeof(Registro), comparaRanking);
    }

    return count;
}

void salvarRanking(const char *nomeJogador, int pontuacao) {
    if (!nomeJogador || strlen(nomeJogador) == 0) return;

    Registro registros[100];
    int count = carregarRanking(registros, 100);

    /* Atualiza ou insere o jogador garantindo que nao haja duplicatas */
    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(registros[i].nome, nomeJogador) == 0) {
            idx = i;
            break;
        }
    }

    if (idx >= 0) {
        if (pontuacao > registros[idx].pontuacao) {
            registros[idx].pontuacao = pontuacao;
        }
    } else if (count < 100) {
        strncpy(registros[count].nome, nomeJogador, sizeof(registros[count].nome) - 1);
        registros[count].nome[sizeof(registros[count].nome) - 1] = '\0';
        registros[count].pontuacao = pontuacao;
        count++;
    }

    /* Reordena por pontuacao decrescente */
    if (count > 1) {
        qsort(registros, count, sizeof(Registro), comparaRanking);
    }

    /* Regrava o arquivo limpo, ordenado e sem duplicatas */
    FILE *file = fopen("ranking.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar o ranking.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", registros[i].nome, registros[i].pontuacao);
    }
    fclose(file);
}

void exibirRanking(void) {
    Registro registros[100];
    int count = carregarRanking(registros, 100);

    if (count == 0) {
        printf("\nNenhum registro encontrado no ranking.\n");
        return;
    }

    printf("\nRanking:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %d pontos\n", i + 1, registros[i].nome, registros[i].pontuacao);
    }
}
