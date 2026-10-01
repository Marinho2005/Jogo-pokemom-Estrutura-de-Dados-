#include "ranking.h"
#include <stdlib.h>
#include <string.h>

void salvarRanking(const char *nomeJogador, int pontuacao) {
    FILE *file = fopen("ranking.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar o ranking.\n");
        return;
    }
    fprintf(file, "%s %d\n", nomeJogador, pontuacao);
    fclose(file);
}

int comparaRanking(const void *n1, const void *n2) {
    const Registro *a = (const Registro *)n1;
    const Registro *b = (const Registro *)n2;
    if (a->pontuacao == b->pontuacao) return 0;
    else if (a->pontuacao < b->pontuacao) return 1;
    return -1;
}

void exibirRanking(void) {
    FILE *file = fopen("ranking.txt", "r");
    if (file == NULL) {
        printf("\nNenhum ranking registrado ainda.\n");
        return;
    }

    Registro registros[100];
    int count = 0;

    while (count < 100 && fscanf(file, "%19s %d", registros[count].nome, &registros[count].pontuacao) == 2) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("\nNenhum registro encontrado no ranking.\n");
        return;
    }

    /* Ordenação decrescente por pontuação */
    qsort(registros, count, sizeof(Registro), comparaRanking);

    printf("\nRanking:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %d pontos\n", i + 1, registros[i].nome, registros[i].pontuacao);
    }
}
