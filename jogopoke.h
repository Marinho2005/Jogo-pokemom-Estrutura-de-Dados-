#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#define MAX 10
#include <unistd.h> 
#include <windows.h>









char *bold_red = "\033[1;31m"; // para pintar o texto de vermelho
char *reset = "\033[0m"; // volta a ser texto padrao
typedef struct {
  char name[20];
  int dano;
} Habilidade;

typedef struct {
  int inicial, final, quantidade;
  Habilidade valores[MAX];
} Fila;
int criarFila(Fila *p1);
typedef struct {
  char nome[20];
  Fila filadeatk;
  int vida;
  char criterio[10];
  int vidamax;
} Pokemon;

void setColor2(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}


typedef struct tp_no {
    Pokemon info;
    struct tp_no *prox;
} tp_listase;

  typedef struct {
        char nome[20];
        int pontuacao;
    } Registro;



typedef struct {
	int moedas;
	tp_listase *pokemonslista;// struct q tem fila de hab
	int pokebolas;
	int pontuacao;
	char nome[20];
}Jogador;




Habilidade criarHabilidade(char *pont, int damage) {
  Habilidade ability;
  strcpy(ability.name, pont);
  ability.dano = damage;
  return ability;
}

Pokemon criarPokemon(char *nome, int vida) {
  Pokemon pokemon;
  strcpy(pokemon.nome, nome);
  criarFila(&pokemon.filadeatk);
  pokemon.vida = vida;
  strcpy(pokemon.criterio, "criterio");
  pokemon.vidamax = vida;
  return pokemon;
}
void embaralharPokemons(Pokemon *pokemons, int n) {
  srand(time(NULL));
  for (int i = n - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    Pokemon temp = pokemons[i];
    pokemons[i] = pokemons[j];
    pokemons[j] = temp;
  }
}






void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void inicioDoJogo() {
    char y;

    // Linha branca
    setColor(15); // Branco
    printf(" ######    #####   ###  ##  #######  ######    #####     ####   ##   ##  #######\n");

    // Linha vermelha
    setColor(12); // Vermelho
    printf("  ##  ##  ##   ##   ##  ##   ##   #   ##  ##  ##   ##   ##  ##  ##   ##   ##   #\n");

    // Linha branca
    setColor(15); // Branco
    printf("  ##  ##  ##   ##   ## ##    ## #     ##  ##  ##   ##  ##       ##   ##   ## #\n");

    // Linha vermelha
    setColor(12); // Vermelho
    printf("  #####   ##   ##   ####     ####     #####   ##   ##  ##       ##   ##   ####\n");

    // Linha branca
    setColor(15); // Branco
    printf("  ##      ##   ##   ## ##    ## #     ## ##   ##   ##  ##  ###  ##   ##   ## # \n");

    // Linha vermelha
    setColor(12); // Vermelho
    printf("  ##      ##   ##   ##  ##   ##   #   ##  ##  ##   ##   ##  ##  ##   ##   ##   #\n");

    // Linha branca
    setColor(15); // Branco
    printf(" ####      #####   ###  ##  #######  #### ##   #####     #####   #####   #######\n\n");

    // Reset para a cor padrão (branco) e mensagem de início
    printf("-------------------------Pressione [ESPACO] para iniciar------------------------\n");
    
    do {
        y = getch();
    } while (y != 32);

    system("cls");
}
//-----------------------------------PILHA------------------------------------------//
typedef struct {
  Pokemon *pokemons;
  int topo;
  int capacidade;
} Pilha;
// Função para criar uma nova pilha
void criarPilha(Pilha *pilha, int capacidade) {
    pilha->topo = -1;
    pilha->capacidade = capacidade;
    pilha->pokemons = (Pokemon *)malloc(capacidade * sizeof(Pokemon)); // Alocação de memória
    if (pilha->pokemons == NULL) {
        printf("Erro ao alocar memoria para a pilha.\n");
        exit(1);  // Termina o programa se a alocação falhar
    }
}
// Função para empilhar um Pokémon
int pushPilha(Pilha *pilha, Pokemon pokemon) {
    if (pilha->topo == pilha->capacidade - 1) {
        printf("Pilha cheia.\n");
        return 0;
    }
    pilha->topo++;
    pilha->pokemons[pilha->topo] = pokemon;
    return 1;
}

int vaziaPilha(Pilha *pilha) {
  if (pilha->topo == -1)
    return 1;
  return 0;
}
Pokemon popPilha(Pilha *pilha, Pokemon *resto) {
  if (vaziaPilha(pilha) == 1) {
    printf("Pilha vazia.\n");
  }
  *resto = pilha->pokemons[pilha->topo];
  pilha->topo--;
  return *resto;
}
int cheiaPilha(Pilha *pilha) {
  if (pilha->topo == pilha->capacidade - 1)
    return 1;
  return 0;
}
void imprimaPilha(Pilha p) {

  Pokemon e;
  while(!vaziaPilha(&p)) {
    popPilha(&p, &e);
    printf("%s\n", e.nome);
  }
}
//---------------------------------------------FILA-------------------------------------------------------------//

int  criarFila(Fila *p1) {
  p1->inicial = p1->final = p1->quantidade = 0;
  return 1;
}
int vaziaFila(Fila *p1) {
  if (p1->quantidade == 0)
    return 1;
  return 0;
}
int cheiaFila(Fila *p1) {
  if (p1->quantidade == MAX)
    return 1;
  return 0;
}
int retirarFila(Fila *p1, Habilidade *e) {
  if (vaziaFila(p1))
    return 0;
  p1->quantidade--;
  *e = p1->valores[p1->inicial];
  p1->inicial = (p1->inicial + 1) % MAX;
  return 1;
}
int inserirFila(Fila *p1, char *nome, int dano) {
  if (cheiaFila(p1))
    return 0;
    
  strcpy(p1->valores[p1->final].name, nome);
  p1->valores[p1->final].dano = dano;
  p1->final = (p1->final + 1) % MAX;
  p1->quantidade++;
  return 1;
}
void imprimaFila(Fila m) {
  Habilidade z;
  while (vaziaFila(&m) == 0) {
    retirarFila(&m, &z);
    printf("%s", z.name);
  }
}
int quantidadeFila(Fila *f1) { return f1->quantidade; }

void exibeHabilidades(Fila *fila, Pokemon p1) {
    if (vaziaFila(fila)) {
        printf("Nenhuma habilidade na fila.\n");
        return;
    }

    int i;
    int indice = fila->inicial;
    printf("as habilidades do %s\n", p1.nome);
    for (i = 0; i < fila->quantidade; i++) {
        printf("Habilidade %d: %s (Dano: %d)\n", i + 1, fila->valores[indice].name, fila->valores[indice].dano);
        indice = (indice + 1) % MAX;  // Incrementa circularmente
        
    }
}

Habilidade* escolherHabilidadePorIndice(Fila *fila, int indice) {
    if (vaziaFila(fila) || indice < 0 || indice >= fila->quantidade) {
        printf("Escolha invalida.\n");
        return NULL;
    }

    int posicao = (fila->inicial + indice) % MAX;  // Calcula a posição real na fila circular
    return &(fila->valores[posicao]);
}


///---------------------------------------------------FLISTASE----------------------------------------------------//


// Inicializa a lista
tp_listase *inicializaListase() {
    return NULL;
}

// Verifica se a lista está vazia
int listaVazia(tp_listase *lista) {
    return lista == NULL;
}

// Aloca um novo nó na lista
tp_listase *alocaListase() {
    tp_listase *novo_no = (tp_listase *)malloc(sizeof(tp_listase));
    if (novo_no != NULL) {
        novo_no->prox = NULL;
    }
    return novo_no;
}

// Insere um Pokémon no fim da lista
int insereListaNoFim(tp_listase **l, Pokemon e) {
    tp_listase *novo_no = alocaListase();
    if (novo_no == NULL) return 0;

    novo_no->info = e;
    novo_no->prox = NULL;

    if (listaVazia(*l)) {
        *l = novo_no;
    } else {
        tp_listase *atu = *l;
        while (atu->prox != NULL) {
            atu = atu->prox;
        }
        atu->prox = novo_no;
    }
    return 1;
}

// Imprime os nomes dos Pokémon na lista
void imprime_listase(tp_listase *lista) {
    tp_listase *atu = lista;
    if(atu == NULL){
    	printf("(null)");
	}
    while (atu != NULL) {
        printf("%s\n", atu->info.nome);  // Corrigido para %s
        atu = atu->prox;
    }
}
void imprime_listasevivos(tp_listase *lista) {
    tp_listase *atu = lista;
    if(atu == NULL){
    	printf(" ");
	}
    while (atu != NULL) {
        printf("%s (vida: %d)\n", atu->info.nome, atu->info.vida);  // Corrigido para %s
        atu = atu->prox;
    }
}



// Remove um Pokémon da lista, procurando pelo nome
int remove_listase(tp_listase **lista, Pokemon p) {
    tp_listase *ant = NULL, *atu = *lista;

    // Procura o Pokémon com o nome especificado
    while (atu != NULL && strcmp(atu->info.nome, p.nome) != 0 ) {
        ant = atu;
        atu = atu->prox;
    }

    if (atu == NULL) return 0;  // Pokémon não encontrado

    if (ant == NULL) {
        *lista = atu->prox;
    } else {
        ant->prox = atu->prox;
    }

    free(atu);
    return 1;
}

// Busca um Pokémon na lista pelo nome
tp_listase *busca_listase(tp_listase *lista, Pokemon p ) {
    tp_listase *atu = lista;
    while (atu != NULL && strcmp(atu->info.nome, p.nome) != 0) {
        atu = atu->prox;
    }
    return atu;
}

// Retorna o tamanho da lista
int tamanho_listase(tp_listase *lista) {
    int cont = 0;
    tp_listase *atu = lista;
    while (atu != NULL) {
        cont++;
        atu = atu->prox;
    }
    return cont;
}

// Destroi a lista e libera a memória
void destroi_listase(tp_listase **l) {
    tp_listase *atu = *l;
    while (atu != NULL) {
        tp_listase *temp = atu;
        atu = atu->prox;
        free(temp);
    }
    *l = NULL;
}
int usarPokebola(Jogador *player) {
    if (player->pokebolas > 0) {
        player->pokebolas--;
        printf("Você usou uma Pokebola. Restantes: %d\n", player->pokebolas);
        return 1;  // Sucesso
    } else {
        printf("Você não possui Pokebolas suficientes!\n");
        return 0;  // Falha
    }
}
int tentarCapturarPokemon(Jogador *player, Pokemon *adversario) {
    if (!usarPokebola(player)) {
        return 0;  // Falha ao tentar capturar, pois não tem Pokébolas
    }

    // Taxa de captura: quanto menor a vida do adversário, maior a chance de captura
    float taxaCaptura = (1.0f - ((float)adversario->vida / adversario->vidamax)) * 100;
    int chance = rand() % 100;

    if (chance < taxaCaptura) {
        printf("Parabens! Voce capturou %s!\n", adversario->nome);
        return 1;  // Captura bem-sucedida
    } else {
        printf("O %s escapou da Pokebola!\n", adversario->nome);
        return 0;  // Captura falhou
    }
}
void adicionarPokemonCapturado(Jogador *player, Pokemon *capturado) {
    insereListaNoFim(&player->pokemonslista, *capturado);
    printf("%s foi adicionado ao seu time!\n", capturado->nome);
}

//--------------------------------------------------------------------------------------------------------------//
typedef struct No {
    char nome[50];
    int preco;
    struct No* proximo;  // Corrigido para apontar para a struct No
} ListaLoja;


ListaLoja* inicializaListaLoja() {
    return NULL;
}

void insereItemNaLoja(ListaLoja** lista, const char* nome, int preco) {
    ListaLoja* novoItem = (ListaLoja*)malloc(sizeof(ListaLoja));
    if (novoItem == NULL) {
        printf("Erro de alocaçao de memoria!\n");
        exit(1);
    }
    strcpy(novoItem->nome, nome);
    novoItem->preco = preco;
    novoItem->proximo = *lista;
    *lista = novoItem;
}

void exibeLoja(ListaLoja* lista, Jogador* jogador) {
    ListaLoja* atu = lista;  // Corrigido para ListaLoja*
    printf("Suas moedas: %d\n", jogador->moedas);
    printf("Itens a venda:\n");
    while (atu != NULL) {
        printf("%s - %d moedas\n", atu->nome, atu->preco);
        atu = atu->proximo;
    }
}




char exibirLoja(ListaLoja* lista, Jogador* jogador, tp_listase **mortos, int *pontos) {
    char escolha;
    do {
        ListaLoja *atu = lista;
        int opcao;
        printf("Voce tem %d moedas\n", jogador->moedas);
        printf("0. Sair da loja\n");

        int i = 1;
        while(atu != NULL) {
            printf("%d. %s (%d moedas)\n", i, atu->nome, atu->preco);
            atu = atu->proximo;
            i++;
        }

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 0) {
        	system("cls");
            return '0';  // Sai da loja e retorna ao combate
        }
		if(opcao == 3) {
            atu = lista;
            for (int j = 1; j < opcao && atu != NULL; j++) {
                atu = atu->proximo; // ele encontra o no 
            }

            if (atu != NULL && jogador->moedas >= atu->preco) {
    	printf("%s comprado!\n", atu->nome);
    	jogador->moedas -= atu->preco;

    // Exibe os Pokémon do jogador
    int count = 1;
    tp_listase *atu33 = jogador->pokemonslista;
    while (atu33 != NULL) {
        printf("%d. %s (Vida: %d)\n", count, atu33->info.nome, atu33->info.vida);
        atu33 = atu33->prox;
        count++;
    }

    // Escolha do Pokémon para aplicar a poção
    int escolha;
    printf("Escolha o Pokémon para aplicar a poção de cura:\n");
    scanf("%d", &escolha);

    // Achar o Pokémon escolhido
    atu33 = jogador->pokemonslista;
    int contc = 1;
    while(atu33 != NULL && contc != escolha) {
        atu33 = atu33->prox;
        contc++;
    }

    // Cálculo da cura baseada nos pontos do jogador
    	int cura_base = 30; // Cura padrão
    	int aumento_por_pontos = *pontos / 10; // A cada 10 pontos, a cura aumenta em 5
    	int cura_total = cura_base + (aumento_por_pontos * 5);

    // Aumenta a vida do Pokémon escolhido
    	atu33->info.vida += cura_total;
    	printf("Vida aumentada em %d pontos! (Total de %d de cura)\n", cura_total, cura_total);
}

        } 
		else if(opcao == 1) {
            int contador = 1;
            tp_listase *cemiterio = *mortos;
            if(cemiterio == NULL) {
                printf("Nenhum morto\n");
                printf("Voltando ao lobby...");
                sleep(3);
                return '0';
            }

            while (cemiterio != NULL) {
                printf("%d. %s (Vida: %d)\n", contador, cemiterio->info.nome, cemiterio->info.vida);
                cemiterio = cemiterio->prox;
                contador++;
            }

            int decida;
            printf("Escolha o pokemon para reviver\n");
            scanf("%d", &decida);
            cemiterio = *mortos;
            int contadormorto = 1;
            while(cemiterio != NULL && contadormorto != decida) {
                cemiterio = cemiterio->prox;
                contadormorto++;
            }

            insereListaNoFim(&jogador->pokemonslista, cemiterio->info);
            remove_listase(mortos, cemiterio->info);
            printf("Pokemon revivido\n");
            sleep(1);
        }
		//else if(opcao == 2)pokebola
		else if(opcao == 2) {
            // Lógica de compra de Pokébola
            atu = lista;
            for (int j = 1; j < opcao && atu != NULL; j++) {
                atu = atu->proximo;
            }

            if (atu != NULL && jogador->moedas >= atu->preco) {
                printf("Pokebola comprada!\n");
                jogador->moedas -= atu->preco;
                jogador->pokebolas++;  // Incrementa a quantidade de Pokébolas do jogador
                printf("Você agora tem %d Pokebolas.\n", jogador->pokebolas);
            }
		}
		
		//else if(opcao == 2)pokebola
		 else {
            printf("Moedas insuficientes ou opçao invalida!\n");
        }

        printf("Deseja continuar comprando? (S/N): ");
        scanf(" %c", &escolha);
        
        if(escolha == 'N' || escolha == 'n') {
        	system("cls");
            return '0';
        }

    } while (escolha == 'S' || escolha == 's');
}

void salvarRanking(const char *nomeJogador, int pontuacao) {
    FILE *file = fopen("ranking.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar o ranking.\n");
        return;
    }
    fprintf(file, "%s %d\n", nomeJogador, pontuacao);
    fclose(file);
}

  int compara(const void * n1, const void * n2){
  		const Registro *a = (Registro *)n1;
  		const Registro *b = (Registro * )n2 ;
  		if(a->pontuacao == b->pontuacao) return 0;
  		else if(a->pontuacao < b->pontuacao) return 1;
  		return -1;
  }

void aplicarDano(Pokemon *alvo, int danoBase) {
    int danoFinal = danoBase;  // O dano aumenta em 2 a cada ponto
    alvo->vida -= danoFinal;
    if (alvo->vida < 0) {
        alvo->vida = 0;
    }
    // Exibe o dano aplicado
}
void aplicarDanoAdversario(Pokemon *alvo, int danoBase,  int pontos) {
    int danoFinal = danoBase +  ( pontos * 2) ;  // O dano aumenta em 2 a cada ponto
    alvo->vida -= danoFinal;
    if (alvo->vida < 0) {
        alvo->vida = 0;
    }
    // Exibe o dano aplicado
}


//Função para exibir o ranking em ordem decrescente
void exibirRanking() {
    FILE *file = fopen("ranking.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para exibir o ranking.\n");
        return;
    }

  
    Registro registros[100];
    int count = 0;

    while (fscanf(file, "%s %d", registros[count].nome, &registros[count].pontuacao) != EOF) {
        count++;
    }
    fclose(file);

	 for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (registros[i].pontuacao < registros[j].pontuacao) {
                Registro temp = registros[i];
                registros[i] = registros[j];
                registros[j] = temp;
            }
        }
    }
	
	
	
	
	
   
    printf("\nRanking:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %d pontos\n", i + 1, registros[i].nome, registros[i].pontuacao);
    }
}


char realizarBatalha(Jogador *player, Pilha *pilhaPokAdversario, tp_listase ** mortos, int * pontos, Pilha * pilha, Pokemon *pokemonsrest) {
    Pokemon adversario;
    if (!vaziaPilha(pilhaPokAdversario)) {
        popPilha(pilhaPokAdversario, &adversario);
    }
    else{
    pushPilha(pilhaPokAdversario,pokemonsrest[0]);
    pushPilha(pilhaPokAdversario,pokemonsrest[1]);
    pushPilha(pilhaPokAdversario,pokemonsrest[2]);
    pushPilha(pilhaPokAdversario,pokemonsrest[3]);
    pushPilha(pilhaPokAdversario,pokemonsrest[4]);
    pushPilha(pilhaPokAdversario,pokemonsrest[5]);
    pushPilha(pilhaPokAdversario,pokemonsrest[6]);
    pushPilha(pilhaPokAdversario,pokemonsrest[7]);
    pushPilha(pilhaPokAdversario,pokemonsrest[8]);
    pushPilha(pilhaPokAdversario,pokemonsrest[9]);
    pushPilha(pilhaPokAdversario,pokemonsrest[10]);
    pushPilha(pilhaPokAdversario,pokemonsrest[11]);
   	popPilha(pilhaPokAdversario, &adversario);
	}
    
    
    
    
    
    
  

    printf("Voce esta enfrentando %s!\n", adversario.nome);

    // Seleção do Pokémon do jogador
    printf("Escolha um Pokemon para o combate:\n");
    tp_listase *atu = player->pokemonslista;
    int escolha, count = 1;
    while (atu != NULL) {
        printf("%d. %s (Vida: %d)\n", count, atu->info.nome, atu->info.vida);
        atu = atu->prox;
        count++;
    }
    printf("Digite o número do seu Pokemon: ");
    scanf("%d", &escolha);

    // Seleciona o Pokémon escolhido
    atu = player->pokemonslista;
    for (int i = 1; i < escolha && atu != NULL; i++) {
        atu = atu->prox;
    }
    if (atu == NULL) {
        printf("Escolha invalida. Batalha cancelada.\n");
        return '0';
    }

    Pokemon *jogadorPokemon = &atu->info;

// Loop de combate

    // Loop de combate
    while (adversario.vida > 0 && jogadorPokemon->vida > 0) {
        printf("\nEscolha sua acao:\n");
        printf("pokebolas: %d\n", player->pokebolas);
        printf("1. Atacar\n");
        printf("2. Usar Pokebola\n");
    	
        printf("Escolha: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            // Exibe as habilidades do jogador para ele escolher
            printf("Escolha uma habilidade para atacar:\n");
            int indice = jogadorPokemon->filadeatk.inicial;
            for (int i = 0; i < jogadorPokemon->filadeatk.quantidade; i++) {
                printf("%d. %s (Dano: %d)\n", i + 1, jogadorPokemon->filadeatk.valores[indice].name, jogadorPokemon->filadeatk.valores[indice].dano);
                indice = (indice + 1) % MAX;
            }

            // Lê a escolha de habilidade do jogador
            int escolha_hab;
            scanf("%d", &escolha_hab);

            // Verifica se a escolha é válida
            if (escolha_hab < 1 || escolha_hab > jogadorPokemon->filadeatk.quantidade) {
                printf("Habilidade invalida!\n");
                continue;  // Volta ao início do loop para uma nova tentativa
            }

            // Seleciona a habilidade e aplica o dano ao adversário
            Habilidade *hab_jogador = escolherHabilidadePorIndice(&jogadorPokemon->filadeatk, escolha_hab - 1);
            aplicarDano(&adversario, hab_jogador->dano);
            printf("Voce usou %s e causou %d de dano!\n", hab_jogador->name, hab_jogador->dano);

            // Verifica se o adversário foi derrotado
            if (adversario.vida <= 0) {
                printf(" %s foi derrotado!\n", adversario.nome);
                player->moedas += 250;
               (*pontos)++;
               player->pontuacao++;
                return '0';  // Retorna para o lobby
            }

        } else if (escolha == 2) {
        	if(player->pokebolas == 0 ){
        		printf("vc tem 0 pokebolas");
        		sleep(1);
        		continue;
			}
            // Tentativa de captura usando uma Pokébola
            if (tentarCapturarPokemon(player, &adversario)) {
                // Captura bem-sucedida
                adicionarPokemonCapturado(player, &adversario);
                printf("Batalha terminada! Voce capturou %s.\n", adversario.nome);
                player->moedas += 100;
                (*pontos)++;
                player->pontuacao++;
                return '0';  // Retorna para o lobby após a captura bem-sucedida
            } else {
                printf("A captura falhou! A batalha continua...\n");
            }

        } else {
            printf("Opcao invalida! Tente novamente.\n");
            continue;  // Volta ao início do loop
        }

        // Turno do adversário: seleciona uma habilidade aleatória
        if (adversario.vida > 0) {  // Verifica novamente se adversário está vivo
            // Seleciona uma habilidade aleatória do adversário
            if (adversario.filadeatk.quantidade > 0) {
                int hab_index = rand() % adversario.filadeatk.quantidade;
                Habilidade *hab_adversario = escolherHabilidadePorIndice(&adversario.filadeatk, hab_index);
                aplicarDanoAdversario(jogadorPokemon, hab_adversario->dano, *pontos );
                printf("%s usou %s e causou %d de dano!\n", adversario.nome, hab_adversario->name, hab_adversario->dano);
            } 
        }

        // Verifica se o Pokémon do jogador foi derrotado
        if (jogadorPokemon->vida <= 0) {
            printf("Seu Pokemon foi derrotado!\n");
            printf("Pressione qualquer tecla para voltar ao lobby.\n");
    		char p;
    		p = getch();
    		system("cls");
            jogadorPokemon->vida = jogadorPokemon->vidamax;
            pushPilha(pilha,adversario);
            // Move o Pokémon do jogador para a lista de mortos e remove-o do time ativo
            insereListaNoFim(mortos, *jogadorPokemon);
            remove_listase(&player->pokemonslista, *jogadorPokemon);

            if (listaVazia(player->pokemonslista)) {
                printf("Todos os seus Pokemons foram derrotados! \n");
                sleep(3);
                return 'f';  // Termina o jogo se o jogador perdeu todos os Pokémon
            }
            return '0';  // Retorna para o lobby
        }
    }
    return '0';  // Sai da função de combate caso o loop termine
}









/* pushPilha(pilhaPokAdversario,pokemonsrest[0]);
    pushPilha(pilhaPokAdversario,pokemonsrest[1]);
    pushPilha(pilhaPokAdversario,pokemonsrest[2]);
    pushPilha(pilhaPokAdversario,pokemonsrest[3]);
    pushPilha(pilhaPokAdversario,pokemonsrest[4]);
    pushPilha(pilhaPokAdversario,pokemonsrest[5]);
    pushPilha(pilhaPokAdversario,pokemonsrest[6]);
    pushPilha(pilhaPokAdversario,pokemonsrest[7]);
    pushPilha(pilhaPokAdversario,pokemonsrest[8]);
    pushPilha(pilhaPokAdversario,pokemonsrest[9]);
    pushPilha(pilhaPokAdversario,pokemonsrest[10]);
    pushPilha(pilhaPokAdversario,pokemonsrest[11]);
   */







