#include <time.h>
#include <stdio.h>
#include <string.h>
#include "jogopoke.h"
#include <unistd.h> 
#include <locale.h>
#include <stdlib.h>

int main(){
    setlocale(LC_ALL, "Portuguese");
    char nomeJogador[20];
    Pokemon pokemons[17];
    Pokemon time[3];
    inicioDoJogo();
    printf("Digite o nome do jogador: ");
    scanf("%19[^\n]s", nomeJogador);
    Pokemon pokemonsrest[14];
    int cont = 0;


    // criação de 15 pokémons

    pokemons[0] = criarPokemon("Pikachu", 90); // inicializei com a lista de habilidade
    pokemons[1] = criarPokemon("Charmander", 70);
    pokemons[2] = criarPokemon("Bulbasaur", 75);
    pokemons[3] = criarPokemon("Squirtle", 70);
    pokemons[4] = criarPokemon("Jeryes", 95);
    pokemons[5] = criarPokemon("Uaireless", 75);
    pokemons[6] = criarPokemon("Solidariedade", 70);
    pokemons[7] = criarPokemon("Atilario", 120);
    pokemons[8] = criarPokemon("Lalai", 110);
    pokemons[9] = criarPokemon("Sfoggui", 115);
    pokemons[10] = criarPokemon("Marmarinho",130);
    pokemons[11] = criarPokemon("Mederios",  70);
    pokemons[12] = criarPokemon("Aedus", 180);
    pokemons[13] = criarPokemon("Marcius",  130);
    pokemons[14] = criarPokemon("Senayus",  140);
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

    // escolher 3 pokemons para o time do jogador
    printf("\nEscolha 3 Pokemons para o seu time:\n");
    for (int i = 0; i < 15; i++) {
      printf("%d - %s\n", i + 1, pokemons[i].nome);
    }


  int escolhas[3];
    printf("\nDigite os numeros dos Pokemons escolhidos:\n");
    scanf("%d %d %d", &escolhas[0], &escolhas[1], &escolhas[2]);

    Pokemon timeJogador[3];
    for (int i = 0; i < 3; i++) {
        timeJogador[i] = pokemons[escolhas[i] - 1];
        strcpy(pokemons[escolhas[i]-1].criterio, "lixo");
    }

    for(int i = 0; i < 15; i++){
      if(strcmp(pokemons[i].criterio, "lixo") != 0){
        pokemonsrest[cont] = pokemons[i];
        cont++;
      }
    }

    // imprimir o time do jogador
    printf("\nTime do jogador %s:\n", nomeJogador);
    for (int i = 0; i < 3; i++) {
        printf("%s\n", timeJogador[i].nome);
      }
     printf("\n");

     embaralharPokemons(pokemonsrest,12);

    printf("Pokemons restantes:\n");

  	
    // teste de embaralhamento
    for (int i = 0; i < 12; i++) {
      printf("%d - %s\n", i + 1 , pokemonsrest[i].nome);
    }
    // criar a pilha de pokemons restantes
    printf("pokemons restantes embaralhados na pilha:\n\n");
    //-------------------------------------------------------//
    Pilha pilhapok;
    
    criarPilha(&pilhapok, 12);
    pushPilha(&pilhapok,pokemonsrest[0]);
    pushPilha(&pilhapok,pokemonsrest[1]);
    pushPilha(&pilhapok,pokemonsrest[2]);
    pushPilha(&pilhapok,pokemonsrest[3]);
    pushPilha(&pilhapok,pokemonsrest[4]);
    pushPilha(&pilhapok,pokemonsrest[5]);
    pushPilha(&pilhapok,pokemonsrest[6]);
    pushPilha(&pilhapok,pokemonsrest[7]);
    pushPilha(&pilhapok,pokemonsrest[8]);
    pushPilha(&pilhapok,pokemonsrest[9]);
    pushPilha(&pilhapok,pokemonsrest[10]);
    pushPilha(&pilhapok,pokemonsrest[11]);
   
   	imprimaPilha(pilhapok);
    //-----------------------------------------------------------//
 	
    printf("\n\n");
    
    exibeHabilidades(&pokemons[escolhas[0]-1].filadeatk, pokemons[escolhas[0]- 1]);
    exibeHabilidades(&pokemons[escolhas[1]-1].filadeatk, pokemons[escolhas[1] - 1 ]);
    exibeHabilidades(&pokemons[escolhas[2]-1].filadeatk, pokemons[escolhas[2] - 1]);

	printf("\n\n");
	
    Jogador player;
    player.moedas = 1000;
    player.pokebolas = 5;
    player.pokemonslista = inicializaListase();
   	ListaLoja * listaLoja;
    inicializaListaLoja(&listaLoja);
    insereItemNaLoja(&listaLoja, "Pocao", 500);
    insereItemNaLoja(&listaLoja, "Pokebola", 200);
    insereItemNaLoja(&listaLoja, "Reviver Pokemon", 1000);
    
    int contador = 0;
    for(int i = 0; i  < 15; i++){
    	 if(strcmp(pokemons[i].criterio, "lixo") == 0 ){
    	 	insereListaNoFim(&player.pokemonslista, pokemons[i]);
    		contador++;
		 }
	}
	

	printf("Vc tem 1000 moedas, 5 pokebolas e 3 pokemons de inicio. Se todos os seus pokemons morrerem o jogo termina.");
	player.pontuacao = 0;
	strcpy(player.nome, nomeJogador );
	int pontuacao  = 0;
	char lojaduelo = '0';
	tp_listase * mortos = inicializaListase();
	while (lojaduelo == '0') {
		printf("\n----------------------------LOBBY-------------------------------------------\n");

		printf("seus pokemons:\n");
		
		imprime_listasevivos(player.pokemonslista);
		printf("%s\t\t\t\t\t Pontos: %d\n", bold_red, pontuacao );
		
        printf("%sdigite L se deseja ir para a loja.\ndigite B se deseja entrar na batalha\n", reset);
        printf("digite R se deseja visitar  o ranking\n");
        printf("pokemons mortos\n");
        imprime_listase(mortos);
        	
        printf("\n----------------------------------------------------------------------------\n");
        scanf(" %c", &lojaduelo);
        if (lojaduelo == 'L' || lojaduelo == 'l') {
        system("cls");
        setColor2(14);
		setColor2(14);
		printf("L         OOOOO     JJJJJJJ    AAAAA\n");
		printf("L        O     O        J      A   A\n");
		printf("L        O     O        J      AAAAA\n");
		printf("L        O     O   J    J      A   A\n");
		printf("LLLLLL    OOOOO     JJJJJ      A   A\n\n");
		setColor2(15);

            printf("Bem-vindo a loja!\n");
            lojaduelo = exibirLoja(listaLoja, &player, &mortos, &pontuacao);
            
        }
    
        if (lojaduelo == 'B' || lojaduelo == 'b') {
            printf("entrando na batalha...\n");
             sleep(2);
            system("cls");
             setColor2(14);
            printf("BBBBB     A     TTTTT   A     L      H   H    A\n");
    		printf("B    B   A A      T    A A    L      H   H   A A\n");
    		printf("BBBBB   AAAAA     T   AAAAA   L      HHHHH  AAAAA\n");
    		printf("B    B  A   A     T   A   A   L      H   H  A   A\n");
    		printf("BBBBB   A   A     T   A   A   LLLLL  H   H  A   A\n\n");
            setColor2(15);
          	lojaduelo =  realizarBatalha(&player, &pilhapok, &mortos, &pontuacao, &pilhapok, pokemons );
          	if(lojaduelo == 'f'){
          		char m;
          		printf("vc fez %d ponto(s)\n", pontuacao);
          		printf("Jogo terminou!");
          		salvarRanking(player.nome, player.pontuacao);
          		exibirRanking();
          		return 0;
			  }
			  
			  
		}
		if (lojaduelo == 'R' || lojaduelo == 'r') {
			printf("espere um pouco...");
			sleep(1);
			system("cls");
    		setColor(14); 
    		printf("RRRR    A   N   N  K   K  III  N   N   GGG\n");
   			printf("R   R  A A  NN  N  K  K    I   NN  N  G   \n");
    		printf("RRRR   AAA  N N N  KKK     I   N N N  G  GG\n");
    		printf("R  R   A A  N  NN  K  K    I   N  NN  G   G\n");
    		printf("R   R  A A  N   N  K   K  III  N   N   GGG\n\n");
    		setColor(15);
    		exibirRanking();
    		printf("Pressione qualquer tecla para voltar ao lobby.\n");
    		char p;
    		p = getch();
    		system("cls");
    		lojaduelo = '0';
    		}
}
   
    return 0;                                        
}
