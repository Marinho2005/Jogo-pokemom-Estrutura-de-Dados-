#include "utils.h"
#include <ctype.h>

const char *bold_red = "\033[1;31m";
const char *reset_color = "\033[0m";

void setColor(int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
    switch (color) {
        case 12:
            printf("\033[1;31m"); // Vermelho brilhante
            break;
        case 14:
            printf("\033[1;33m"); // Amarelo brilhante
            break;
        case 15:
            printf("\033[1;37m"); // Branco brilhante
            break;
        default:
            printf("\033[0m");    // Padrão / Reset
            break;
    }
    fflush(stdout);
#endif
}

void setColor2(int color) {
    setColor(color);
}

void limparTela(void) {
#ifdef _WIN32
    if (system("cls") == -1) {}
#else
    if (system("clear") == -1) {}
#endif
}

#ifndef _WIN32
int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
#endif

void pausarSegundos(int segundos) {
#ifdef _WIN32
    Sleep(segundos * 1000);
#else
    sleep(segundos);
#endif
}

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int lerInteiro(int min, int max, const char *mensagem) {
    char buffer[128];
    int valor;

    while (1) {
        if (mensagem != NULL && mensagem[0] != '\0') {
            printf("%s", mensagem);
        }
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            continue;
        }

        /* Tenta converter string lida para número inteiro */
        if (sscanf(buffer, "%d", &valor) == 1) {
            if (valor >= min && valor <= max) {
                return valor;
            }
            printf("Valor fora do intervalo permitido (%d a %d). Tente novamente.\n", min, max);
        } else {
            printf("Entrada invalida! Por favor, digite um numero valido (%d a %d).\n", min, max);
        }
    }
}

char lerCaractereOpcao(const char *opcoesValidas, const char *mensagem) {
    char buffer[128];
    char opcao;

    while (1) {
        if (mensagem != NULL && mensagem[0] != '\0') {
            printf("%s", mensagem);
        }
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            continue;
        }

        if (sscanf(buffer, " %c", &opcao) == 1) {
            char opcMaiuscula = (char)toupper((unsigned char)opcao);
            for (int i = 0; opcoesValidas[i] != '\0'; i++) {
                if (opcMaiuscula == (char)toupper((unsigned char)opcoesValidas[i])) {
                    return opcMaiuscula;
                }
            }
        }
        printf("Opcao invalida! Digite uma das opcoes validas (%s).\n", opcoesValidas);
    }
}

void lerString(char *destino, int tamanhoMaximo, const char *mensagem) {
    char buffer[256];

    while (1) {
        if (mensagem != NULL && mensagem[0] != '\0') {
            printf("%s", mensagem);
        }
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            /* Remove a quebra de linha ao final, se presente */
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
                len--;
            }
            if (len > 0) {
                strncpy(destino, buffer, tamanhoMaximo - 1);
                destino[tamanhoMaximo - 1] = '\0';
                return;
            }
        }
        printf("Entrada vazia! Por favor, digite um texto valido.\n");
    }
}

void inicioDoJogo(void) {
    char y;

    // Linha branca
    setColor(15);
    printf(" ######    #####   ###  ##  #######  ######    #####     ####   ##   ##  #######\n");

    // Linha vermelha
    setColor(12);
    printf("  ##  ##  ##   ##   ##  ##   ##   #   ##  ##  ##   ##   ##  ##  ##   ##   ##   #\n");

    // Linha branca
    setColor(15);
    printf("  ##  ##  ##   ##   ## ##    ## #     ##  ##  ##   ##  ##       ##   ##   ## #\n");

    // Linha vermelha
    setColor(12);
    printf("  #####   ##   ##   ####     ####     #####   ##   ##  ##       ##   ##   ####\n");

    // Linha branca
    setColor(15);
    printf("  ##      ##   ##   ## ##    ## #     ## ##   ##   ##  ##  ###  ##   ##   ## # \n");

    // Linha vermelha
    setColor(12);
    printf("  ##      ##   ##   ##  ##   ##   #   ##  ##  ##   ##   ##  ##  ##   ##   ##   #\n");

    // Linha branca
    setColor(15);
    printf(" ####      #####   ###  ##  #######  #### ##   #####     #####   #####   #######\n\n");

    // Reset para a cor padrão e mensagem de início
    setColor(15);
    printf("-------------------------Pressione [ESPACO] para iniciar------------------------\n");

    do {
        y = (char)getch();
    } while (y != 32);

    limparTela();
}
