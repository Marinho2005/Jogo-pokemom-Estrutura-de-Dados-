#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "utils.h"
#include "pokemon.h"
#include "jogador.h"
#include "loja.h"
#include "ranking.h"
#include "batalha.h"

int main(void) {
#ifdef _WIN32
    setlocale(LC_ALL, "Portuguese");
#else
    if (setlocale(LC_ALL, "pt_BR.UTF-8") == NULL) {
        setlocale(LC_ALL, "");
    }
#endif

    char nomeJogador[20];
    Pokemon pokemons[15];
    Pokemon pokemonsrest[12];

    inicioDoJogo();

    lerString(nomeJogador, sizeof(nomeJogador), "Digite o nome do jogador: ");

    /* Criação dos 15 Pokémons e suas habilidades */
    pokemons[0] = criarPokemon("Pikachu", 90);
    pokemons[1] = criarPokemon("Charmander", 70);
    pokemons[2] = criarPokemon("Bulbasaur", 75);
    pokemons[3] = criarPokemon("Squirtle", 70);
    pokemons[4] = criarPokemon("Jeryes", 95);
    pokemons[5] = criarPokemon("Uaireless", 75);
    pokemons[6] = criarPokemon("Solidariedade", 70);
    pokemons[7] = criarPokemon("Atilario", 120);
    pokemons[8] = criarPokemon("Lalai", 110);
    pokemons[9] = criarPokemon("Sfoggui", 115);
    pokemons[10] = criarPokemon("Marmarinho", 130);
    pokemons[11] = criarPokemon("Mederios", 70);
    pokemons[12] = criarPokemon("Aedus", 180);
    pokemons[13] = criarPokemon("Marcius", 130);
    pokemons[14] = criarPokemon("Senayus", 140);

    inserirFila(&pokemons[0].filadeatk, "Super Raio", 35);
    inserirFila(&pokemons[0].filadeatk, "Zap!", 25);

    inserirFila(&pokemons[1].filadeatk, "Chamas", 30);
    inserirFila(&pokemons[1].filadeatk, "Calor", 15);

    inserirFila(&pokemons[2].filadeatk, "Verdejante", 20);
    inserirFila(&pokemons[2].filadeatk, "Cipo", 25);

    inserirFila(&pokemons[3].filadeatk, "Mare", 25);
    inserirFila(&pokemons[3].filadeatk, "Onda", 20);

    inserirFila(&pokemons[4].filadeatk, "Admin", 40);
    inserirFila(&pokemons[4].filadeatk, "MaxMiauno", 25);

    inserirFila(&pokemons[5].filadeatk, "Circuitos", 35);
    inserirFila(&pokemons[5].filadeatk, "Protobordus", 30);

    inserirFila(&pokemons[6].filadeatk, "Calculus I", 25);
    inserirFila(&pokemons[6].filadeatk, "Calculus II", 25);

    inserirFila(&pokemons[7].filadeatk, "Quimicas", 40);
    inserirFila(&pokemons[7].filadeatk, "Musicas", 35);

    inserirFila(&pokemons[8].filadeatk, "Corrida", 35);
    inserirFila(&pokemons[8].filadeatk, "Viagem", 30);

    inserirFila(&pokemons[9].filadeatk, "Paixao", 30);
    inserirFila(&pokemons[9].filadeatk, "Risadas", 25);

    inserirFila(&pokemons[10].filadeatk, "Programmus", 30);
    inserirFila(&pokemons[10].filadeatk, "Estudus", 30);

    inserirFila(&pokemons[11].filadeatk, "Grupus", 20);
    inserirFila(&pokemons[11].filadeatk, "Tentus", 20);

    inserirFila(&pokemons[12].filadeatk, "Medus", 45);
    inserirFila(&pokemons[12].filadeatk, "Medius", 70);

    inserirFila(&pokemons[13].filadeatk, "Soussum", 30);
    inserirFila(&pokemons[13].filadeatk, "AED", 40);

    inserirFila(&pokemons[14].filadeatk, "Facul", 30);
    inserirFila(&pokemons[14].filadeatk, "Periculums", 50);

    /* Escolha dos 3 Pokémons para o time */
    printf("\nEscolha 3 Pokemons para o seu time:\n");
    for (int i = 0; i < 15; i++) {
        printf("%2d - %s\n", i + 1, pokemons[i].nome);
    }

    int escolhas[3];
    escolhas[0] = lerInteiro(1, 15, "\nDigite o numero do 1o Pokemon: ");
    do {
        escolhas[1] = lerInteiro(1, 15, "Digite o numero do 2o Pokemon: ");
        if (escolhas[1] == escolhas[0]) {
            printf("Voce ja escolheu esse Pokemon! Escolha um diferente.\n");
        }
    } while (escolhas[1] == escolhas[0]);

    do {
        escolhas[2] = lerInteiro(1, 15, "Digite o numero do 3o Pokemon: ");
        if (escolhas[2] == escolhas[0] || escolhas[2] == escolhas[1]) {
            printf("Voce ja escolheu esse Pokemon! Escolha um diferente.\n");
        }
    } while (escolhas[2] == escolhas[0] || escolhas[2] == escolhas[1]);

    Jogador player;
    player.moedas = 1000;
    player.pokebolas = 5;
    player.pontuacao = 0;
    strncpy(player.nome, nomeJogador, sizeof(player.nome) - 1);
    player.nome[sizeof(player.nome) - 1] = '\0';
    player.pokemonslista = inicializaListase();

    for (int i = 0; i < 3; i++) {
        insereListaNoFim(&player.pokemonslista, pokemons[escolhas[i] - 1]);
        strncpy(pokemons[escolhas[i] - 1].criterio, "time", sizeof(pokemons[escolhas[i] - 1].criterio) - 1);
    }

    /* Separação dos 12 restantes para a pilha de adversários */
    int contRest = 0;
    for (int i = 0; i < 15; i++) {
        if (strcmp(pokemons[i].criterio, "time") != 0 && contRest < 12) {
            pokemonsrest[contRest] = pokemons[i];
            contRest++;
        }
    }

    printf("\nTime do jogador %s:\n", player.nome);
    imprime_listasevivos(player.pokemonslista);

    embaralharPokemons(pokemonsrest, 12);

    /* Criação da pilha de adversários */
    Pilha pilhapok;
    criarPilha(&pilhapok, 12);
    for (int i = 0; i < 12; i++) {
        pushPilha(&pilhapok, pokemonsrest[i]);
    }

    /* Inicialização da Loja */
    ListaLoja *listaLoja = inicializaListaLoja();
    insereItemNaLoja(&listaLoja, "Pocao", 500);
    insereItemNaLoja(&listaLoja, "Pokebola", 200);
    insereItemNaLoja(&listaLoja, "Reviver Pokemon", 1000);

    tp_listase *mortos = inicializaListase();
    int pontuacao = 0;

    printf("\nVoce tem 1000 moedas, 5 pokebolas e 3 pokemons de inicio.\nSe todos os seus pokemons morrerem, o jogo termina.\n");

    /* Loop Principal do Lobby */
    while (1) {
        printf("\n---------------------------- LOBBY -----------------------------\n");
        printf("Seus Pokemons:\n");
        imprime_listasevivos(player.pokemonslista);

        printf("%sMoedas: %d  |  Pokebolas: %d  |  Pontos: %d%s\n", bold_red, player.moedas, player.pokebolas, pontuacao, reset_color);

        printf("\nPokemons derrotados:\n");
        imprime_listase(mortos);

        printf("\nOpcoes disponiveis:\n");
        printf(" [L] Loja\n");
        printf(" [B] Batalha\n");
        printf(" [R] Ranking\n");
        printf(" [S] Sair do jogo\n");
        printf("----------------------------------------------------------------\n");

        char opcaoLobby = lerCaractereOpcao("LBRS", "Escolha uma opcao: ");

        if (opcaoLobby == 'L') {
            limparTela();
            setColor2(14);
            printf("L         OOOOO     JJJJJJJ    AAAAA\n");
            printf("L        O     O        J      A   A\n");
            printf("L        O     O        J      AAAAA\n");
            printf("L        O     O   J    J      A   A\n");
            printf("LLLLLL    OOOOO     JJJJJ      A   A\n\n");
            setColor2(15);
            printf("Bem-vindo a loja!\n");
            exibirLoja(listaLoja, &player, &mortos, &pontuacao);
        } else if (opcaoLobby == 'B') {
            printf("\nEntrando na batalha...\n");
            pausarSegundos(1);
            limparTela();
            setColor2(14);
            printf("BBBBB     A     TTTTT   A     L      H   H    A\n");
            printf("B    B   A A      T    A A    L      H   H   A A\n");
            printf("BBBBB   AAAAA     T   AAAAA   L      HHHHH  AAAAA\n");
            printf("B    B  A   A     T   A   A   L      H   H  A   A\n");
            printf("BBBBB   A   A     T   A   A   LLLLL  H   H  A   A\n\n");
            setColor2(15);

            char resultadoBatalha = realizarBatalha(&player, &pilhapok, &mortos, &pontuacao, &pilhapok, pokemonsrest);
            if (resultadoBatalha == 'f') {
                printf("\n=========================================\n");
                printf("Voce fez %d ponto(s)!\n", pontuacao);
                printf("Fim de Jogo! Todos os seus Pokemons foram derrotados.\n");
                printf("=========================================\n");
                salvarRanking(player.nome, player.pontuacao);
                exibirRanking();
                break;
            }
        } else if (opcaoLobby == 'R') {
            printf("Carregando ranking...\n");
            pausarSegundos(1);
            limparTela();
            setColor(14);
            printf("RRRR    A   N   N  K   K  III  N   N   GGG\n");
            printf("R   R  A A  NN  N  K  K    I   NN  N  G   \n");
            printf("RRRR   AAA  N N N  KKK     I   N N N  G  GG\n");
            printf("R  R   A A  N  NN  K  K    I   N  NN  G   G\n");
            printf("R   R  A A  N   N  K   K  III  N   N   GGG\n\n");
            setColor(15);
            exibirRanking();
            printf("\nPressione [ESPACO] ou [ENTER] para voltar ao lobby.\n");
            getch();
            limparTela();
        } else if (opcaoLobby == 'S') {
            char confirma = lerCaractereOpcao("SN", "Tem certeza que deseja sair do jogo? (S/N): ");
            if (confirma == 'S') {
                printf("\nSaindo...\n");
                printf("Obrigado por jogar, %s! Ate a proxima.\n", player.nome);
                break;
            }
            limparTela();
        }
    }

    /* Liberação de memória */
    destroi_listase(&player.pokemonslista);
    destroi_listase(&mortos);
    destroiListaLoja(&listaLoja);
    destroiPilha(&pilhapok);

    return 0;
}
