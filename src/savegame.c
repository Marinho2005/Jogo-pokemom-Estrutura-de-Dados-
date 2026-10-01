#include "savegame.h"
#include "gui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SAVEGAME_FILE "savegame.dat"
#define SAVE_MAGIC 0x504B4D4E /* "PKMN" */
#define SAVE_VERSION 1

int savegame_exists(void) {
    FILE *f = fopen(SAVEGAME_FILE, "rb");
    if (!f) return 0;

    uint32_t magic = 0;
    uint32_t ver = 0;
    if (fread(&magic, sizeof(uint32_t), 1, f) != 1 ||
        fread(&ver, sizeof(uint32_t), 1, f) != 1) {
        fclose(f);
        return 0;
    }

    fclose(f);
    return (magic == SAVE_MAGIC && ver == SAVE_VERSION);
}

void savegame_delete(void) {
    remove(SAVEGAME_FILE);
}

int savegame_save(const GuiApp *app) {
    if (!app) return 0;

    FILE *f = fopen(SAVEGAME_FILE, "wb");
    if (!f) return 0;

    uint32_t magic = SAVE_MAGIC;
    uint32_t ver = SAVE_VERSION;
    fwrite(&magic, sizeof(uint32_t), 1, f);
    fwrite(&ver, sizeof(uint32_t), 1, f);

    /* Dados gerais e Treinador */
    fwrite(&app->pontuacao, sizeof(int), 1, f);
    fwrite(&app->player.moedas, sizeof(int), 1, f);
    fwrite(&app->player.pokebolas, sizeof(int), 1, f);
    fwrite(&app->player.pontuacao, sizeof(int), 1, f);
    fwrite(app->player.nome, sizeof(char), sizeof(app->player.nome), f);
    fwrite(app->input_name, sizeof(char), sizeof(app->input_name), f);

    /* Time do Jogador */
    int team_count = tamanho_listase(app->player.pokemonslista);
    fwrite(&team_count, sizeof(int), 1, f);
    tp_listase *atu = app->player.pokemonslista;
    while (atu != NULL) {
        fwrite(&atu->info, sizeof(Pokemon), 1, f);
        atu = atu->prox;
    }

    /* Cemitério (Mortos) */
    int mortos_count = tamanho_listase(app->mortos);
    fwrite(&mortos_count, sizeof(int), 1, f);
    tp_listase *cem = app->mortos;
    while (cem != NULL) {
        fwrite(&cem->info, sizeof(Pokemon), 1, f);
        cem = cem->prox;
    }

    /* Pilha de Adversários */
    fwrite(&app->pilhapok.capacidade, sizeof(int), 1, f);
    fwrite(&app->pilhapok.topo, sizeof(int), 1, f);
    for (int i = 0; i <= app->pilhapok.topo; i++) {
        fwrite(&app->pilhapok.pokemons[i], sizeof(Pokemon), 1, f);
    }

    /* Pokemons restantes */
    fwrite(app->pokemonsrest, sizeof(Pokemon), 12, f);

    /* Seleção */
    fwrite(app->selected_team, sizeof(int), 3, f);
    fwrite(&app->num_selected, sizeof(int), 1, f);

    fclose(f);
    return 1;
}

int savegame_load(GuiApp *app) {
    if (!app) return 0;

    FILE *f = fopen(SAVEGAME_FILE, "rb");
    if (!f) return 0;

    uint32_t magic = 0;
    uint32_t ver = 0;
    if (fread(&magic, sizeof(uint32_t), 1, f) != 1 ||
        fread(&ver, sizeof(uint32_t), 1, f) != 1 ||
        magic != SAVE_MAGIC || ver != SAVE_VERSION) {
        fclose(f);
        return 0;
    }

    /* Limpa listas e pilha anteriores se existirem */
    destroi_listase(&app->player.pokemonslista);
    destroi_listase(&app->mortos);
    destroiPilha(&app->pilhapok);

    app->player.pokemonslista = inicializaListase();
    app->mortos = inicializaListase();

    /* Dados gerais e Treinador */
    if (fread(&app->pontuacao, sizeof(int), 1, f) != 1 ||
        fread(&app->player.moedas, sizeof(int), 1, f) != 1 ||
        fread(&app->player.pokebolas, sizeof(int), 1, f) != 1 ||
        fread(&app->player.pontuacao, sizeof(int), 1, f) != 1 ||
        fread(app->player.nome, sizeof(char), sizeof(app->player.nome), f) != sizeof(app->player.nome) ||
        fread(app->input_name, sizeof(char), sizeof(app->input_name), f) != sizeof(app->input_name)) {
        fclose(f);
        return 0;
    }

    /* Time do Jogador */
    int team_count = 0;
    if (fread(&team_count, sizeof(int), 1, f) != 1) {
        fclose(f);
        return 0;
    }
    for (int i = 0; i < team_count; i++) {
        Pokemon p;
        if (fread(&p, sizeof(Pokemon), 1, f) != 1) {
            fclose(f);
            return 0;
        }
        insereListaNoFim(&app->player.pokemonslista, p);
    }

    /* Cemitério (Mortos) */
    int mortos_count = 0;
    if (fread(&mortos_count, sizeof(int), 1, f) != 1) {
        fclose(f);
        return 0;
    }
    for (int i = 0; i < mortos_count; i++) {
        Pokemon p;
        if (fread(&p, sizeof(Pokemon), 1, f) != 1) {
            fclose(f);
            return 0;
        }
        insereListaNoFim(&app->mortos, p);
    }

    /* Pilha de Adversários */
    int capacidade = 0;
    int topo = -1;
    if (fread(&capacidade, sizeof(int), 1, f) != 1 ||
        fread(&topo, sizeof(int), 1, f) != 1) {
        fclose(f);
        return 0;
    }
    criarPilha(&app->pilhapok, capacidade);
    app->pilhapok.topo = topo;
    for (int i = 0; i <= topo; i++) {
        if (fread(&app->pilhapok.pokemons[i], sizeof(Pokemon), 1, f) != 1) {
            fclose(f);
            return 0;
        }
    }

    /* Pokemons restantes */
    if (fread(app->pokemonsrest, sizeof(Pokemon), 12, f) != 12) {
        fclose(f);
        return 0;
    }

    /* Seleção */
    if (fread(app->selected_team, sizeof(int), 3, f) != 3 ||
        fread(&app->num_selected, sizeof(int), 1, f) != 1) {
        fclose(f);
        return 0;
    }

    fclose(f);

    /* Inicializa a loja se necessário */
    if (app->loja == NULL) {
        app->loja = inicializaListaLoja();
        insereItemNaLoja(&app->loja, "Pocao", 500);
        insereItemNaLoja(&app->loja, "Pokebola", 200);
        insereItemNaLoja(&app->loja, "Reviver Pokemon", 1000);
    }

    return 1;
}
