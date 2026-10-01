#include "pokemon.h"
#include <time.h>

Habilidade criarHabilidade(const char *pont, int damage) {
    Habilidade ability;
    strncpy(ability.name, pont, sizeof(ability.name) - 1);
    ability.name[sizeof(ability.name) - 1] = '\0';
    ability.dano = damage;
    return ability;
}

Pokemon criarPokemon(const char *nome, int vida) {
    Pokemon pokemon;
    strncpy(pokemon.nome, nome, sizeof(pokemon.nome) - 1);
    pokemon.nome[sizeof(pokemon.nome) - 1] = '\0';
    criarFila(&pokemon.filadeatk);
    pokemon.vida = vida;
    strncpy(pokemon.criterio, "criterio", sizeof(pokemon.criterio) - 1);
    pokemon.criterio[sizeof(pokemon.criterio) - 1] = '\0';
    pokemon.vidamax = vida;
    return pokemon;
}

void embaralharPokemons(Pokemon *pokemons, int n) {
    srand((unsigned int)time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Pokemon temp = pokemons[i];
        pokemons[i] = pokemons[j];
        pokemons[j] = temp;
    }
}

void aplicarDano(Pokemon *alvo, int danoBase) {
    alvo->vida -= danoBase;
    if (alvo->vida < 0) {
        alvo->vida = 0;
    }
}

void aplicarDanoAdversario(Pokemon *alvo, int danoBase, int pontos) {
    int danoFinal = danoBase + (pontos * 2);
    alvo->vida -= danoFinal;
    if (alvo->vida < 0) {
        alvo->vida = 0;
    }
}

/*----------------- FILA CIRCULAR -----------------*/

int criarFila(Fila *p1) {
    p1->inicial = 0;
    p1->final = 0;
    p1->quantidade = 0;
    return 1;
}

int vaziaFila(const Fila *p1) {
    return p1->quantidade == 0;
}

int cheiaFila(const Fila *p1) {
    return p1->quantidade == MAX_HABILIDADES;
}

int retirarFila(Fila *p1, Habilidade *e) {
    if (vaziaFila(p1)) return 0;
    p1->quantidade--;
    *e = p1->valores[p1->inicial];
    p1->inicial = (p1->inicial + 1) % MAX_HABILIDADES;
    return 1;
}

int inserirFila(Fila *p1, const char *nome, int dano) {
    if (cheiaFila(p1)) return 0;
    strncpy(p1->valores[p1->final].name, nome, sizeof(p1->valores[p1->final].name) - 1);
    p1->valores[p1->final].name[sizeof(p1->valores[p1->final].name) - 1] = '\0';
    p1->valores[p1->final].dano = dano;
    p1->final = (p1->final + 1) % MAX_HABILIDADES;
    p1->quantidade++;
    return 1;
}

void imprimaFila(Fila m) {
    Habilidade z;
    while (!vaziaFila(&m)) {
        retirarFila(&m, &z);
        printf("%s\n", z.name);
    }
}

int quantidadeFila(const Fila *f1) {
    return f1->quantidade;
}

void exibeHabilidades(const Fila *fila, Pokemon p1) {
    if (vaziaFila(fila)) {
        printf("Nenhuma habilidade na fila.\n");
        return;
    }

    int indice = fila->inicial;
    printf("as habilidades do %s\n", p1.nome);
    for (int i = 0; i < fila->quantidade; i++) {
        printf("Habilidade %d: %s (Dano: %d)\n", i + 1, fila->valores[indice].name, fila->valores[indice].dano);
        indice = (indice + 1) % MAX_HABILIDADES;
    }
}

Habilidade* escolherHabilidadePorIndice(Fila *fila, int indice) {
    if (vaziaFila(fila) || indice < 0 || indice >= fila->quantidade) {
        printf("Escolha invalida.\n");
        return NULL;
    }
    int posicao = (fila->inicial + indice) % MAX_HABILIDADES;
    return &(fila->valores[posicao]);
}

/*----------------- PILHA DINÂMICA -----------------*/

void criarPilha(Pilha *pilha, int capacidade) {
    pilha->topo = -1;
    pilha->capacidade = capacidade;
    pilha->pokemons = (Pokemon *)malloc(capacidade * sizeof(Pokemon));
    if (pilha->pokemons == NULL) {
        printf("Erro ao alocar memoria para a pilha.\n");
        exit(1);
    }
}

int pushPilha(Pilha *pilha, Pokemon pokemon) {
    if (pilha->topo == pilha->capacidade - 1) {
        printf("Pilha cheia.\n");
        return 0;
    }
    pilha->topo++;
    pilha->pokemons[pilha->topo] = pokemon;
    return 1;
}

int vaziaPilha(const Pilha *pilha) {
    return pilha->topo == -1;
}

int cheiaPilha(const Pilha *pilha) {
    return pilha->topo == pilha->capacidade - 1;
}

Pokemon popPilha(Pilha *pilha, Pokemon *resto) {
    if (vaziaPilha(pilha)) {
        printf("Pilha vazia.\n");
    }
    *resto = pilha->pokemons[pilha->topo];
    pilha->topo--;
    return *resto;
}

void imprimaPilha(Pilha p) {
    Pokemon e;
    while (!vaziaPilha(&p)) {
        popPilha(&p, &e);
        printf("%s\n", e.nome);
    }
}

void destroiPilha(Pilha *pilha) {
    if (pilha->pokemons != NULL) {
        free(pilha->pokemons);
        pilha->pokemons = NULL;
    }
    pilha->topo = -1;
    pilha->capacidade = 0;
}

/*----------------- LISTA SIMPLESMENTE ENCADEADA -----------------*/

tp_listase *inicializaListase(void) {
    return NULL;
}

int listaVazia(const tp_listase *lista) {
    return lista == NULL;
}

tp_listase *alocaListase(void) {
    tp_listase *novo_no = (tp_listase *)malloc(sizeof(tp_listase));
    if (novo_no != NULL) {
        novo_no->prox = NULL;
    }
    return novo_no;
}

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

void imprime_listase(const tp_listase *lista) {
    const tp_listase *atu = lista;
    if (atu == NULL) {
        printf("(null)\n");
        return;
    }
    while (atu != NULL) {
        printf("%s\n", atu->info.nome);
        atu = atu->prox;
    }
}

void imprime_listasevivos(const tp_listase *lista) {
    const tp_listase *atu = lista;
    if (atu == NULL) {
        printf(" \n");
        return;
    }
    while (atu != NULL) {
        printf("%s (vida: %d)\n", atu->info.nome, atu->info.vida);
        atu = atu->prox;
    }
}

int remove_listase(tp_listase **lista, Pokemon p) {
    tp_listase *ant = NULL;
    tp_listase *atu = *lista;

    while (atu != NULL && strcmp(atu->info.nome, p.nome) != 0) {
        ant = atu;
        atu = atu->prox;
    }

    if (atu == NULL) return 0; // Não encontrado

    if (ant == NULL) {
        *lista = atu->prox;
    } else {
        ant->prox = atu->prox;
    }

    free(atu);
    return 1;
}

tp_listase *busca_listase(tp_listase *lista, Pokemon p) {
    tp_listase *atu = lista;
    while (atu != NULL && strcmp(atu->info.nome, p.nome) != 0) {
        atu = atu->prox;
    }
    return atu;
}

int tamanho_listase(const tp_listase *lista) {
    int cont = 0;
    const tp_listase *atu = lista;
    while (atu != NULL) {
        cont++;
        atu = atu->prox;
    }
    return cont;
}

void destroi_listase(tp_listase **l) {
    tp_listase *atu = *l;
    while (atu != NULL) {
        tp_listase *temp = atu;
        atu = atu->prox;
        free(temp);
    }
    *l = NULL;
}
