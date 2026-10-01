#include "gui.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void add_battle_log(GuiApp *app, const char *msg) {
    if (app->battle_log_count < 4) {
        strncpy(app->battle_log[app->battle_log_count], msg, sizeof(app->battle_log[0]) - 1);
        app->battle_log[app->battle_log_count][sizeof(app->battle_log[0]) - 1] = '\0';
        app->battle_log_count++;
    } else {
        for (int i = 0; i < 3; i++) {
            strncpy(app->battle_log[i], app->battle_log[i + 1], sizeof(app->battle_log[0]));
        }
        strncpy(app->battle_log[3], msg, sizeof(app->battle_log[0]) - 1);
        app->battle_log[3][sizeof(app->battle_log[0]) - 1] = '\0';
    }
}

static void init_game_pokemons(GuiApp *app) {
    app->all_pokemons[0] = criarPokemon("Pikachu", 90);
    app->all_pokemons[1] = criarPokemon("Charmander", 70);
    app->all_pokemons[2] = criarPokemon("Bulbasaur", 75);
    app->all_pokemons[3] = criarPokemon("Squirtle", 70);
    app->all_pokemons[4] = criarPokemon("Jeryes", 95);
    app->all_pokemons[5] = criarPokemon("Uaireless", 75);
    app->all_pokemons[6] = criarPokemon("Solidariedade", 70);
    app->all_pokemons[7] = criarPokemon("Atilario", 120);
    app->all_pokemons[8] = criarPokemon("Lalai", 110);
    app->all_pokemons[9] = criarPokemon("Sfoggui", 115);
    app->all_pokemons[10] = criarPokemon("Marmarinho", 130);
    app->all_pokemons[11] = criarPokemon("Mederios", 70);
    app->all_pokemons[12] = criarPokemon("Aedus", 180);
    app->all_pokemons[13] = criarPokemon("Marcius", 130);
    app->all_pokemons[14] = criarPokemon("Senayus", 140);

    inserirFila(&app->all_pokemons[0].filadeatk, "Super Raio", 35);
    inserirFila(&app->all_pokemons[0].filadeatk, "Zap!", 25);

    inserirFila(&app->all_pokemons[1].filadeatk, "Chamas", 30);
    inserirFila(&app->all_pokemons[1].filadeatk, "Calor", 15);

    inserirFila(&app->all_pokemons[2].filadeatk, "Verdejante", 20);
    inserirFila(&app->all_pokemons[2].filadeatk, "Cipo", 25);

    inserirFila(&app->all_pokemons[3].filadeatk, "Mare", 25);
    inserirFila(&app->all_pokemons[3].filadeatk, "Onda", 20);

    inserirFila(&app->all_pokemons[4].filadeatk, "Admin", 40);
    inserirFila(&app->all_pokemons[4].filadeatk, "MaxMiauno", 25);

    inserirFila(&app->all_pokemons[5].filadeatk, "Circuitos", 35);
    inserirFila(&app->all_pokemons[5].filadeatk, "Protobordus", 30);

    inserirFila(&app->all_pokemons[6].filadeatk, "Calculus I", 25);
    inserirFila(&app->all_pokemons[6].filadeatk, "Calculus II", 25);

    inserirFila(&app->all_pokemons[7].filadeatk, "Quimicas", 40);
    inserirFila(&app->all_pokemons[7].filadeatk, "Musicas", 35);

    inserirFila(&app->all_pokemons[8].filadeatk, "Corrida", 35);
    inserirFila(&app->all_pokemons[8].filadeatk, "Viagem", 30);

    inserirFila(&app->all_pokemons[9].filadeatk, "Paixao", 30);
    inserirFila(&app->all_pokemons[9].filadeatk, "Risadas", 25);

    inserirFila(&app->all_pokemons[10].filadeatk, "Programmus", 30);
    inserirFila(&app->all_pokemons[10].filadeatk, "Estudus", 30);

    inserirFila(&app->all_pokemons[11].filadeatk, "Grupus", 20);
    inserirFila(&app->all_pokemons[11].filadeatk, "Tentus", 20);

    inserirFila(&app->all_pokemons[12].filadeatk, "Medus", 45);
    inserirFila(&app->all_pokemons[12].filadeatk, "Medius", 70);

    inserirFila(&app->all_pokemons[13].filadeatk, "Soussum", 30);
    inserirFila(&app->all_pokemons[13].filadeatk, "AED", 40);

    inserirFila(&app->all_pokemons[14].filadeatk, "Facul", 30);
    inserirFila(&app->all_pokemons[14].filadeatk, "Periculums", 50);
}

static void finalize_team_selection(GuiApp *app) {
    app->player.moedas = 1000;
    app->player.pokebolas = 5;
    app->player.pontuacao = 0;
    strncpy(app->player.nome, app->input_name, sizeof(app->player.nome) - 1);
    app->player.nome[sizeof(app->player.nome) - 1] = '\0';
    app->player.pokemonslista = inicializaListase();

    for (int i = 0; i < 3; i++) {
        int idx = app->selected_team[i];
        insereListaNoFim(&app->player.pokemonslista, app->all_pokemons[idx]);
        strncpy(app->all_pokemons[idx].criterio, "time", sizeof(app->all_pokemons[idx].criterio) - 1);
    }

    int contRest = 0;
    for (int i = 0; i < 15; i++) {
        if (strcmp(app->all_pokemons[i].criterio, "time") != 0 && contRest < 12) {
            app->pokemonsrest[contRest] = app->all_pokemons[i];
            contRest++;
        }
    }

    embaralharPokemons(app->pokemonsrest, 12);

    criarPilha(&app->pilhapok, 12);
    for (int i = 0; i < 12; i++) {
        pushPilha(&app->pilhapok, app->pokemonsrest[i]);
    }

    app->loja = inicializaListaLoja();
    insereItemNaLoja(&app->loja, "Pocao", 500);
    insereItemNaLoja(&app->loja, "Pokebola", 200);
    insereItemNaLoja(&app->loja, "Reviver Pokemon", 1000);

    app->mortos = inicializaListase();
    app->pontuacao = 0;
}

static void start_battle(GuiApp *app) {
    if (listaVazia(app->player.pokemonslista)) {
        app->current_scene = SCENE_GAME_OVER;
        return;
    }

    if (!vaziaPilha(&app->pilhapok)) {
        popPilha(&app->pilhapok, &app->current_adversario);
    } else {
        for (int i = 0; i < 12; i++) {
            pushPilha(&app->pilhapok, app->pokemonsrest[i]);
        }
        popPilha(&app->pilhapok, &app->current_adversario);
    }

    /* Define o primeiro Pokémon vivo como ativo */
    tp_listase *atu = app->player.pokemonslista;
    app->active_pokemon = &atu->info;

    app->battle_phase = BATTLE_PHASE_MENU;
    app->battle_log_count = 0;
    char intro[80];
    snprintf(intro, sizeof(intro), "Um %s selvagem apareceu!", app->current_adversario.nome);
    add_battle_log(app, intro);
    snprintf(intro, sizeof(intro), "Vai, %s!", app->active_pokemon->nome);
    add_battle_log(app, intro);

    app->current_scene = SCENE_BATTLE;
}

int gui_app_init(GuiApp *app) {
    memset(app, 0, sizeof(GuiApp));

    if (!ui_init(&app->ui, WINDOW_WIDTH, WINDOW_HEIGHT, "Pokemon - Estrutura de Dados (AED)")) {
        return 0;
    }

    srand((unsigned int)time(NULL));
    init_game_pokemons(app);

    app->current_scene = SCENE_TITLE;
    strncpy(app->input_name, "Ash", sizeof(app->input_name) - 1);
    app->running = 1;

    SDL_StartTextInput();
    return 1;
}

void gui_app_cleanup(GuiApp *app) {
    SDL_StopTextInput();
    destroi_listase(&app->player.pokemonslista);
    destroi_listase(&app->mortos);
    destroiListaLoja(&app->loja);
    destroiPilha(&app->pilhapok);
    ui_cleanup(&app->ui);
}

/* ========================================================================= */
/*                                CENAS                                      */
/* ========================================================================= */

static void render_scene_title(GuiApp *app) {
    ui_clear(&app->ui, C_BG_DARK);

    /* Pokebola decorativa gigante */
    ui_draw_pokeball(&app->ui, WINDOW_WIDTH / 2, 170, 70);

    /* Banner de Título */
    ui_draw_text_centered(&app->ui, "POKEMON", WINDOW_WIDTH / 2, 260, 4, C_YELLOW);
    ui_draw_text_centered(&app->ui, "ESTRUTURA DE DADOS (AED)", WINDOW_WIDTH / 2, 335, 2, C_WHITE);
    ui_draw_text_centered(&app->ui, "Fila circular * Pilha dinamica * Listas encadeadas", WINDOW_WIDTH / 2, 380, 1, C_GRAY);

    /* Botão de Iniciar */
    if (ui_draw_button(&app->ui, WINDOW_WIDTH / 2 - 140, 460, 280, 50, "INICIAR AVENTURA", 2,
                       C_BTN_NORMAL, C_BTN_HOVER, C_WHITE) ||
        (app->ui.key_pressed == SDLK_SPACE || app->ui.key_pressed == SDLK_RETURN)) {
        app->current_scene = SCENE_NAME_INPUT;
    }

    ui_draw_text_centered(&app->ui, "Pressione ESPACO ou clique para comecar", WINDOW_WIDTH / 2, 530, 1, C_GRAY);
}

static void render_scene_name_input(GuiApp *app) {
    ui_clear(&app->ui, C_BG_DARK);

    ui_draw_panel(&app->ui, WINDOW_WIDTH / 2 - 250, 160, 500, 320, C_PANEL_BG, C_PANEL_BORDER);

    ui_draw_text_centered(&app->ui, "IDENTIFICACAO DO TREINADOR", WINDOW_WIDTH / 2, 200, 2, C_BLACK);
    ui_draw_text_centered(&app->ui, "Digite o seu nome de treinador:", WINDOW_WIDTH / 2, 245, 1, C_DARK_GRAY);

    /* Caixa de Entrada de Texto */
    int box_x = WINDOW_WIDTH / 2 - 180;
    int box_y = 280;
    ui_draw_rect(&app->ui, box_x, box_y, 360, 48, C_WHITE);
    ui_draw_rect_outline(&app->ui, box_x, box_y, 360, 48, C_BLUE, 2);

    /* Manipulação de digitação */
    if (strlen(app->ui.text_input) > 0) {
        size_t cur_len = strlen(app->input_name);
        if (cur_len + strlen(app->ui.text_input) < sizeof(app->input_name) - 1) {
            strcat(app->input_name, app->ui.text_input);
        }
    }
    if (app->ui.key_pressed == SDLK_BACKSPACE) {
        size_t len = strlen(app->input_name);
        if (len > 0) {
            app->input_name[len - 1] = '\0';
        }
    }

    /* Desenha o nome com cursor piscante */
    char display_str[32];
    snprintf(display_str, sizeof(display_str), "%s%s", app->input_name, ((SDL_GetTicks() / 500) % 2 == 0) ? "_" : " ");
    ui_draw_text(&app->ui, display_str, box_x + 15, box_y + 16, 2, C_BLACK);

    /* Botão de Confirmação */
    int can_confirm = strlen(app->input_name) > 0;
    if (can_confirm) {
        if (ui_draw_button(&app->ui, WINDOW_WIDTH / 2 - 120, 365, 240, 45, "CONFIRMAR", 2,
                           C_GREEN, C_BTN_HOVER, C_WHITE) ||
            app->ui.key_pressed == SDLK_RETURN) {
            app->current_scene = SCENE_SELECT_TEAM;
        }
    } else {
        ui_draw_button_disabled(&app->ui, WINDOW_WIDTH / 2 - 120, 365, 240, 45, "DIGITE UM NOME", 1);
    }
}

static void render_scene_select_team(GuiApp *app) {
    ui_clear(&app->ui, C_BG_DARK);

    /* Cabeçalho */
    ui_draw_text_centered(&app->ui, "ESCOLHA 3 POKEMONS PARA O SEU TIME", WINDOW_WIDTH / 2, 20, 2, C_YELLOW);
    char status[64];
    snprintf(status, sizeof(status), "Pokemons selecionados: %d / 3", app->num_selected);
    ui_draw_text_centered(&app->ui, status, WINDOW_WIDTH / 2, 50, 1, C_WHITE);

    /* Grid de 15 Pokémons: 5 colunas x 3 linhas */
    int start_x = 40;
    int start_y = 80;
    int card_w = 168;
    int card_h = 135;
    int gap_x = 10;
    int gap_y = 10;

    for (int i = 0; i < 15; i++) {
        int col = i % 5;
        int row = i / 5;
        int x = start_x + col * (card_w + gap_x);
        int y = start_y + row * (card_h + gap_y);

        /* Checa se este Pokémon já está selecionado */
        int selected_rank = 0;
        for (int s = 0; s < app->num_selected; s++) {
            if (app->selected_team[s] == i) {
                selected_rank = s + 1;
                break;
            }
        }

        SDL_Color bg = selected_rank ? C_WHITE : C_PANEL_BG;
        SDL_Color border = selected_rank ? C_GREEN : (ui_is_hovered(&app->ui, x, y, card_w, card_h) ? C_YELLOW : C_PANEL_BORDER);
        ui_draw_panel(&app->ui, x, y, card_w, card_h, bg, border);

        /* Sprite */
        ui_draw_sprite(&app->ui, i, x + 8, y + 8, 2);

        /* Nome e HP */
        ui_draw_text(&app->ui, app->all_pokemons[i].nome, x + 76, y + 12, 1, C_BLACK);
        char hp_buf[20];
        snprintf(hp_buf, sizeof(hp_buf), "HP:%d", app->all_pokemons[i].vida);
        ui_draw_text(&app->ui, hp_buf, x + 76, y + 32, 1, C_RED);

        /* Habilidades */
        int idx = app->all_pokemons[i].filadeatk.inicial;
        for (int h = 0; h < app->all_pokemons[i].filadeatk.quantidade && h < 2; h++) {
            char atk_buf[32];
            snprintf(atk_buf, sizeof(atk_buf), "-%s (%d)",
                     app->all_pokemons[i].filadeatk.valores[idx].name,
                     app->all_pokemons[i].filadeatk.valores[idx].dano);
            ui_draw_text(&app->ui, atk_buf, x + 8, y + 78 + h * 16, 1, C_DARK_GRAY);
            idx = (idx + 1) % MAX_HABILIDADES;
        }

        /* Se selecionado, desenha badge # */
        if (selected_rank > 0) {
            ui_draw_rect(&app->ui, x + card_w - 30, y + 6, 24, 24, C_GREEN);
            char badge[8];
            snprintf(badge, sizeof(badge), "#%d", selected_rank);
            ui_draw_text(&app->ui, badge, x + card_w - 28, y + 10, 1, C_WHITE);
        }

        /* Clique para alternar seleção */
        if (ui_is_hovered(&app->ui, x, y, card_w, card_h) && app->ui.mouse_clicked) {
            if (selected_rank > 0) {
                /* Remove da seleção */
                int remove_pos = selected_rank - 1;
                for (int s = remove_pos; s < app->num_selected - 1; s++) {
                    app->selected_team[s] = app->selected_team[s + 1];
                }
                app->num_selected--;
            } else if (app->num_selected < 3) {
                /* Adiciona */
                app->selected_team[app->num_selected] = i;
                app->num_selected++;
            }
        }
    }

    /* Botão de confirmação */
    if (app->num_selected == 3) {
        if (ui_draw_button(&app->ui, WINDOW_WIDTH / 2 - 160, 560, 320, 50, "CONFIRMAR E AVANCAR", 2,
                           C_GREEN, C_BTN_HOVER, C_WHITE) ||
            app->ui.key_pressed == SDLK_RETURN) {
            finalize_team_selection(app);
            app->current_scene = SCENE_LOBBY;
        }
    } else {
        char wait_msg[64];
        snprintf(wait_msg, sizeof(wait_msg), "SELECIONE MAIS %d POKEMON(S)", 3 - app->num_selected);
        ui_draw_button_disabled(&app->ui, WINDOW_WIDTH / 2 - 160, 560, 320, 50, wait_msg, 1);
    }
}

static void render_scene_lobby(GuiApp *app) {
    ui_clear(&app->ui, C_BG_DARK);

    /* Barra Superior do Treinador */
    ui_draw_panel(&app->ui, 20, 15, WINDOW_WIDTH - 40, 60, C_PANEL_BG, C_PANEL_BORDER);

    char trainer_text[64];
    snprintf(trainer_text, sizeof(trainer_text), "Treinador: %s", app->player.nome);
    ui_draw_text(&app->ui, trainer_text, 35, 34, 2, C_BLACK);

    /* Moedas, Pokebolas e Pontos */
    ui_draw_pokeball(&app->ui, 500, 45, 12);
    char pb_text[32];
    snprintf(pb_text, sizeof(pb_text), "Pokebolas: %d", app->player.pokebolas);
    ui_draw_text(&app->ui, pb_text, 520, 36, 1, C_BLACK);

    char coins_text[32];
    snprintf(coins_text, sizeof(coins_text), "Moedas: %d", app->player.moedas);
    ui_draw_text(&app->ui, coins_text, 680, 36, 1, C_GOLD);

    char pts_text[32];
    snprintf(pts_text, sizeof(pts_text), "Pontos: %d", app->pontuacao);
    ui_draw_text(&app->ui, pts_text, 820, 36, 1, C_BLUE);

    /* Painel Esquerdo: Pokémons do Time Ativo */
    ui_draw_panel(&app->ui, 20, 90, 580, 440, C_PANEL_BG, C_PANEL_BORDER);
    ui_draw_text(&app->ui, "SEUS POKEMONS VIVOS", 35, 105, 2, C_BLACK);

    tp_listase *atu = app->player.pokemonslista;
    int poke_idx = 0;
    while (atu != NULL && poke_idx < 4) {
        int card_x = 35;
        int card_y = 145 + poke_idx * 90;
        ui_draw_rect(&app->ui, card_x, card_y, 550, 80, C_WHITE);
        ui_draw_rect_outline(&app->ui, card_x, card_y, 550, 80, C_PANEL_BORDER, 1);

        int sprite_id = ui_get_pokemon_sprite_idx(atu->info.nome);
        ui_draw_sprite(&app->ui, sprite_id, card_x + 8, card_y + 8, 2);

        ui_draw_text(&app->ui, atu->info.nome, card_x + 80, card_y + 12, 2, C_BLACK);

        /* Barra de Vida */
        ui_draw_health_bar(&app->ui, card_x + 220, card_y + 14, 200, 20, atu->info.vida, atu->info.vidamax);

        /* Habilidades */
        int hab_idx = atu->info.filadeatk.inicial;
        char hab_line[80] = "Golpes: ";
        for (int h = 0; h < atu->info.filadeatk.quantidade; h++) {
            char part[40];
            snprintf(part, sizeof(part), "%s (%d)  ",
                     atu->info.filadeatk.valores[hab_idx].name,
                     atu->info.filadeatk.valores[hab_idx].dano);
            strcat(hab_line, part);
            hab_idx = (hab_idx + 1) % MAX_HABILIDADES;
        }
        ui_draw_text(&app->ui, hab_line, card_x + 80, card_y + 48, 1, C_DARK_GRAY);

        atu = atu->prox;
        poke_idx++;
    }

    if (poke_idx == 0) {
        ui_draw_text_centered(&app->ui, "Nenhum Pokemon vivo! Va a loja reviver um!", 310, 280, 1, C_RED);
    }

    /* Painel Direito: Pokémons Derrotados (Cemitério) */
    ui_draw_panel(&app->ui, 615, 90, 325, 440, C_PANEL_BG, C_PANEL_BORDER);
    ui_draw_text(&app->ui, "POKEMONS DERROTADOS", 630, 105, 2, C_RED);

    tp_listase *cem = app->mortos;
    int mort_count = 0;
    while (cem != NULL && mort_count < 6) {
        int my = 150 + mort_count * 45;
        ui_draw_rect(&app->ui, 630, my, 295, 38, C_WHITE);
        ui_draw_rect_outline(&app->ui, 630, my, 295, 38, C_PANEL_BORDER, 1);

        int sid = ui_get_pokemon_sprite_idx(cem->info.nome);
        ui_draw_sprite(&app->ui, sid, 634, my + 3, 1);

        ui_draw_text(&app->ui, cem->info.nome, 675, my + 11, 1, C_DARK_GRAY);
        ui_draw_text(&app->ui, "[Derrotado]", 810, my + 11, 1, C_RED);

        cem = cem->prox;
        mort_count++;
    }
    if (mort_count == 0) {
        ui_draw_text_centered(&app->ui, "Nenhum no momento", 777, 260, 1, C_GRAY);
    }

    /* Barra Inferior de Ações */
    if (ui_draw_button(&app->ui, 20, 550, 215, 60, "BATALHAR", 2, C_RED, C_BTN_HOVER, C_WHITE)) {
        start_battle(app);
    }

    if (ui_draw_button(&app->ui, 255, 550, 215, 60, "LOJA", 2, C_BLUE, C_BTN_HOVER, C_WHITE)) {
        app->shop_mode = SHOP_MODE_NORMAL;
        app->shop_status[0] = '\0';
        app->current_scene = SCENE_SHOP;
    }

    if (ui_draw_button(&app->ui, 490, 550, 215, 60, "RANKING", 2, C_GOLD, C_BTN_HOVER, C_WHITE)) {
        app->current_scene = SCENE_RANKING;
    }

    if (ui_draw_button(&app->ui, 725, 550, 215, 60, "SALVAR E SAIR", 2, C_DARK_GRAY, C_BTN_HOVER, C_WHITE)) {
        if (app->player.pontuacao > 0) {
            salvarRanking(app->player.nome, app->player.pontuacao);
        }
        app->running = 0;
    }
}

static void render_scene_battle(GuiApp *app) {
    ui_clear(&app->ui, C_BG_DARK);

    /* Painel do Adversário (Topo Direito) */
    ui_draw_panel(&app->ui, 500, 30, 420, 150, C_PANEL_BG, C_PANEL_BORDER);
    int opp_sid = ui_get_pokemon_sprite_idx(app->current_adversario.nome);
    ui_draw_sprite(&app->ui, opp_sid, 520, 45, 3);
    ui_draw_text(&app->ui, app->current_adversario.nome, 630, 55, 2, C_BLACK);
    ui_draw_text(&app->ui, "HP:", 630, 90, 1, C_DARK_GRAY);
    ui_draw_health_bar(&app->ui, 665, 87, 230, 22, app->current_adversario.vida, app->current_adversario.vidamax);

    /* Painel do Jogador (Esquerda / Centro) */
    ui_draw_panel(&app->ui, 40, 190, 440, 150, C_PANEL_BG, C_PANEL_BORDER);
    int pl_sid = ui_get_pokemon_sprite_idx(app->active_pokemon->nome);
    ui_draw_sprite(&app->ui, pl_sid, 60, 205, 3);
    ui_draw_text(&app->ui, app->active_pokemon->nome, 175, 215, 2, C_BLACK);
    ui_draw_text(&app->ui, "HP:", 175, 250, 1, C_DARK_GRAY);
    ui_draw_health_bar(&app->ui, 210, 247, 245, 22, app->active_pokemon->vida, app->active_pokemon->vidamax);

    char pb_info[32];
    snprintf(pb_info, sizeof(pb_info), "Pokebolas: %d", app->player.pokebolas);
    ui_draw_text(&app->ui, pb_info, 175, 290, 1, C_BLUE);

    /* Caixa de Diálogo / Log de Batalha (Inferior Esquerda) */
    ui_draw_panel(&app->ui, 40, 360, 480, 250, C_PANEL_BG, C_PANEL_BORDER);
    ui_draw_text(&app->ui, "EVENTOS DO COMBATE:", 55, 375, 1, C_DARK_GRAY);
    for (int i = 0; i < app->battle_log_count; i++) {
        ui_draw_text(&app->ui, app->battle_log[i], 55, 410 + i * 36, 1, C_BLACK);
    }

    /* Painel de Ações do Jogador (Inferior Direita) */
    ui_draw_panel(&app->ui, 540, 360, 380, 250, C_PANEL_BG, C_PANEL_BORDER);

    if (app->battle_phase == BATTLE_PHASE_MENU) {
        if (ui_draw_button(&app->ui, 560, 380, 340, 50, "ATACAR", 2, C_RED, C_BTN_HOVER, C_WHITE)) {
            app->battle_phase = BATTLE_PHASE_ATTACK;
        }

        char cap_btn[40];
        snprintf(cap_btn, sizeof(cap_btn), "POKEBOLA (%d)", app->player.pokebolas);
        if (ui_draw_button(&app->ui, 560, 440, 340, 50, cap_btn, 2, C_BLUE, C_BTN_HOVER, C_WHITE)) {
            if (app->player.pokebolas <= 0) {
                add_battle_log(app, "Voce nao tem nenhuma Pokebola!");
            } else {
                app->player.pokebolas--;
                float taxa = (1.0f - ((float)app->current_adversario.vida / (float)app->current_adversario.vidamax)) * 100.0f;
                int chance = rand() % 100;
                if (chance < (int)taxa) {
                    /* Captura bem-sucedida */
                    adicionarPokemonCapturado(&app->player, &app->current_adversario);
                    app->player.moedas += 100;
                    app->pontuacao++;
                    app->player.pontuacao++;
                    char msg[80];
                    snprintf(msg, sizeof(msg), "Capturado! %s foi adicionado ao time!", app->current_adversario.nome);
                    add_battle_log(app, msg);
                    add_battle_log(app, "+100 Moedas e +1 Ponto obtidos!");
                    app->battle_phase = BATTLE_PHASE_CAPTURED;
                } else {
                    add_battle_log(app, "A captura falhou! O Pokemon escapou!");
                    /* Turno do Adversário */
                    if (app->current_adversario.filadeatk.quantidade > 0) {
                        int h_idx = rand() % app->current_adversario.filadeatk.quantidade;
                        Habilidade *hab = escolherHabilidadePorIndice(&app->current_adversario.filadeatk, h_idx);
                        if (hab) {
                            aplicarDanoAdversario(app->active_pokemon, hab->dano, app->pontuacao);
                            char emsg[80];
                            snprintf(emsg, sizeof(emsg), "%s usou %s e deu dano!", app->current_adversario.nome, hab->name);
                            add_battle_log(app, emsg);
                        }
                    }
                    if (app->active_pokemon->vida <= 0) {
                        app->active_pokemon->vida = app->active_pokemon->vidamax;
                        pushPilha(&app->pilhapok, app->current_adversario);
                        insereListaNoFim(&app->mortos, *app->active_pokemon);
                        remove_listase(&app->player.pokemonslista, *app->active_pokemon);
                        if (listaVazia(app->player.pokemonslista)) {
                            salvarRanking(app->player.nome, app->player.pontuacao);
                            app->current_scene = SCENE_GAME_OVER;
                        } else {
                            app->battle_phase = BATTLE_PHASE_DEFEAT_POKE;
                        }
                    }
                }
            }
        }

        if (ui_draw_button(&app->ui, 560, 500, 340, 45, "TROCAR POKEMON", 1, C_DARK_GRAY, C_BTN_HOVER, C_WHITE)) {
            app->battle_phase = BATTLE_PHASE_SWAP;
        }

        if (ui_draw_button(&app->ui, 560, 555, 340, 40, "FUGIR PARA LOBBY", 1, C_GRAY, C_BTN_HOVER, C_WHITE)) {
            pushPilha(&app->pilhapok, app->current_adversario);
            app->current_scene = SCENE_LOBBY;
        }
    } else if (app->battle_phase == BATTLE_PHASE_ATTACK) {
        ui_draw_text(&app->ui, "ESCOLHA O ATAQUE:", 560, 375, 1, C_BLACK);

        int q = app->active_pokemon->filadeatk.quantidade;
        int idx = app->active_pokemon->filadeatk.inicial;

        for (int i = 0; i < q && i < 3; i++) {
            Habilidade *hab = &app->active_pokemon->filadeatk.valores[idx];
            char btn_text[64];
            snprintf(btn_text, sizeof(btn_text), "%s (Dano %d)", hab->name, hab->dano);

            if (ui_draw_button(&app->ui, 560, 405 + i * 48, 340, 42, btn_text, 1,
                               C_BTN_NORMAL, C_BTN_HOVER, C_WHITE)) {
                /* Executa ataque do jogador */
                aplicarDano(&app->current_adversario, hab->dano);
                char log_buf[80];
                snprintf(log_buf, sizeof(log_buf), "%s usou %s! Causou %d de dano!",
                         app->active_pokemon->nome, hab->name, hab->dano);
                add_battle_log(app, log_buf);

                if (app->current_adversario.vida <= 0) {
                    /* Vitória! */
                    app->player.moedas += 250;
                    app->pontuacao++;
                    app->player.pontuacao++;
                    snprintf(log_buf, sizeof(log_buf), "Vitoria! %s foi derrotado!", app->current_adversario.nome);
                    add_battle_log(app, log_buf);
                    add_battle_log(app, "Voce ganhou 250 moedas e 1 ponto!");
                    app->battle_phase = BATTLE_PHASE_VICTORY;
                } else {
                    /* Turno do Adversário */
                    if (app->current_adversario.filadeatk.quantidade > 0) {
                        int h_idx = rand() % app->current_adversario.filadeatk.quantidade;
                        Habilidade *hab_adv = escolherHabilidadePorIndice(&app->current_adversario.filadeatk, h_idx);
                        if (hab_adv) {
                            aplicarDanoAdversario(app->active_pokemon, hab_adv->dano, app->pontuacao);
                            snprintf(log_buf, sizeof(log_buf), "%s usou %s e causou dano!",
                                     app->current_adversario.nome, hab_adv->name);
                            add_battle_log(app, log_buf);
                        }
                    }

                    if (app->active_pokemon->vida <= 0) {
                        snprintf(log_buf, sizeof(log_buf), "Seu %s foi derrotado!", app->active_pokemon->nome);
                        add_battle_log(app, log_buf);
                        app->active_pokemon->vida = app->active_pokemon->vidamax;
                        pushPilha(&app->pilhapok, app->current_adversario);
                        insereListaNoFim(&app->mortos, *app->active_pokemon);
                        remove_listase(&app->player.pokemonslista, *app->active_pokemon);

                        if (listaVazia(app->player.pokemonslista)) {
                            salvarRanking(app->player.nome, app->player.pontuacao);
                            app->current_scene = SCENE_GAME_OVER;
                        } else {
                            app->battle_phase = BATTLE_PHASE_DEFEAT_POKE;
                        }
                    } else {
                        app->battle_phase = BATTLE_PHASE_MENU;
                    }
                }
            }
            idx = (idx + 1) % MAX_HABILIDADES;
        }

        if (ui_draw_button(&app->ui, 560, 560, 340, 38, "VOLTAR", 1, C_GRAY, C_BTN_HOVER, C_WHITE)) {
            app->battle_phase = BATTLE_PHASE_MENU;
        }
    } else if (app->battle_phase == BATTLE_PHASE_SWAP || app->battle_phase == BATTLE_PHASE_DEFEAT_POKE) {
        ui_draw_text(&app->ui, "ESCOLHA O POKEMON:", 560, 375, 1, C_BLACK);
        tp_listase *atu = app->player.pokemonslista;
        int opt = 0;
        while (atu != NULL && opt < 3) {
            char swap_buf[64];
            snprintf(swap_buf, sizeof(swap_buf), "%s (HP %d/%d)", atu->info.nome, atu->info.vida, atu->info.vidamax);
            if (ui_draw_button(&app->ui, 560, 405 + opt * 48, 340, 42, swap_buf, 1,
                               C_BLUE, C_BTN_HOVER, C_WHITE)) {
                app->active_pokemon = &atu->info;
                char swap_msg[80];
                snprintf(swap_msg, sizeof(swap_msg), "Vai, %s! Eu escolho voce!", app->active_pokemon->nome);
                add_battle_log(app, swap_msg);
                app->battle_phase = BATTLE_PHASE_MENU;
                break;
            }
            atu = atu->prox;
            opt++;
        }
        if (app->battle_phase == BATTLE_PHASE_SWAP) {
            if (ui_draw_button(&app->ui, 560, 560, 340, 38, "CANCELAR", 1, C_GRAY, C_BTN_HOVER, C_WHITE)) {
                app->battle_phase = BATTLE_PHASE_MENU;
            }
        }
    } else if (app->battle_phase == BATTLE_PHASE_VICTORY || app->battle_phase == BATTLE_PHASE_CAPTURED) {
        ui_draw_text_centered(&app->ui, "VITORIA!", 730, 410, 3, C_GREEN);
        if (ui_draw_button(&app->ui, 580, 490, 300, 55, "VOLTAR AO LOBBY", 2, C_GREEN, C_BTN_HOVER, C_WHITE)) {
            app->current_scene = SCENE_LOBBY;
        }
    }
}

static void render_scene_shop(GuiApp *app) {
    ui_clear(&app->ui, C_BG_DARK);

    /* Cabeçalho */
    ui_draw_panel(&app->ui, 20, 20, WINDOW_WIDTH - 40, 70, C_PANEL_BG, C_PANEL_BORDER);
    ui_draw_text(&app->ui, "POKEMART - LOJA POKEMON", 40, 38, 3, C_BLUE);
    char coin_buf[32];
    snprintf(coin_buf, sizeof(coin_buf), "Suas Moedas: %d", app->player.moedas);
    ui_draw_text(&app->ui, coin_buf, 650, 44, 2, C_GOLD);

    /* Mensagem de Feedback da loja */
    if (strlen(app->shop_status) > 0) {
        ui_draw_text_centered(&app->ui, app->shop_status, WINDOW_WIDTH / 2, 105, 1, C_YELLOW);
    }

    if (app->shop_mode == SHOP_MODE_NORMAL) {
        /* Vitrine de 3 Itens */
        int item_y = 135;

        /* Item 1: Pocao */
        ui_draw_panel(&app->ui, 40, item_y, 880, 110, C_PANEL_BG, C_PANEL_BORDER);
        ui_draw_text(&app->ui, "POCAO DE CURA", 65, item_y + 20, 2, C_BLACK);
        ui_draw_text(&app->ui, "Restaura 30 (+ bonus) de HP para um Pokemon vivo do seu time.", 65, item_y + 55, 1, C_DARK_GRAY);
        ui_draw_text(&app->ui, "Preco: 500 Moedas", 65, item_y + 75, 1, C_GOLD);
        if (ui_draw_button(&app->ui, 720, item_y + 30, 180, 50, "COMPRAR", 2, C_GREEN, C_BTN_HOVER, C_WHITE)) {
            if (app->player.moedas < 500) {
                strncpy(app->shop_status, "Moedas insuficientes para comprar Pocao!", sizeof(app->shop_status));
            } else if (listaVazia(app->player.pokemonslista)) {
                strncpy(app->shop_status, "Voce nao tem nenhum Pokemon no time!", sizeof(app->shop_status));
            } else {
                app->shop_mode = SHOP_MODE_HEAL_SELECT;
                app->shop_status[0] = '\0';
            }
        }

        /* Item 2: Pokebola */
        item_y += 125;
        ui_draw_panel(&app->ui, 40, item_y, 880, 110, C_PANEL_BG, C_PANEL_BORDER);
        ui_draw_pokeball(&app->ui, 75, item_y + 55, 18);
        ui_draw_text(&app->ui, "POKEBOLA", 115, item_y + 20, 2, C_BLACK);
        ui_draw_text(&app->ui, "Usada durante a batalha para capturar Pokemons adversarios.", 115, item_y + 55, 1, C_DARK_GRAY);
        ui_draw_text(&app->ui, "Preco: 200 Moedas", 115, item_y + 75, 1, C_GOLD);
        if (ui_draw_button(&app->ui, 720, item_y + 30, 180, 50, "COMPRAR", 2, C_GREEN, C_BTN_HOVER, C_WHITE)) {
            if (app->player.moedas >= 200) {
                app->player.moedas -= 200;
                app->player.pokebolas++;
                strncpy(app->shop_status, "Pokebola comprada com sucesso!", sizeof(app->shop_status));
            } else {
                strncpy(app->shop_status, "Moedas insuficientes para comprar Pokebola!", sizeof(app->shop_status));
            }
        }

        /* Item 3: Reviver */
        item_y += 125;
        ui_draw_panel(&app->ui, 40, item_y, 880, 110, C_PANEL_BG, C_PANEL_BORDER);
        ui_draw_text(&app->ui, "REVIVER POKEMON", 65, item_y + 20, 2, C_BLACK);
        ui_draw_text(&app->ui, "Restaura um Pokemon derrotado com vida maxima e devolve ao time.", 65, item_y + 55, 1, C_DARK_GRAY);
        ui_draw_text(&app->ui, "Preco: 1000 Moedas", 65, item_y + 75, 1, C_GOLD);
        if (ui_draw_button(&app->ui, 720, item_y + 30, 180, 50, "REVIVER", 2, C_GREEN, C_BTN_HOVER, C_WHITE)) {
            if (app->player.moedas < 1000) {
                strncpy(app->shop_status, "Moedas insuficientes! Reviver custa 1000 moedas.", sizeof(app->shop_status));
            } else if (listaVazia(app->mortos)) {
                strncpy(app->shop_status, "Nenhum Pokemon no cemiterio para reviver!", sizeof(app->shop_status));
            } else {
                app->shop_mode = SHOP_MODE_REVIVE_SELECT;
                app->shop_status[0] = '\0';
            }
        }

        /* Botão Voltar ao Lobby */
        if (ui_draw_button(&app->ui, WINDOW_WIDTH / 2 - 120, 530, 240, 50, "VOLTAR AO LOBBY", 2,
                           C_BTN_NORMAL, C_BTN_HOVER, C_WHITE)) {
            app->current_scene = SCENE_LOBBY;
        }

    } else if (app->shop_mode == SHOP_MODE_HEAL_SELECT) {
        ui_draw_panel(&app->ui, 120, 130, 720, 380, C_PANEL_BG, C_PANEL_BORDER);
        ui_draw_text_centered(&app->ui, "ESCOLHA O POKEMON PARA CURAR", WINDOW_WIDTH / 2, 150, 2, C_BLACK);

        tp_listase *atu = app->player.pokemonslista;
        int p = 0;
        while (atu != NULL && p < 4) {
            int by = 200 + p * 60;
            char info[64];
            snprintf(info, sizeof(info), "%s (HP %d/%d)", atu->info.nome, atu->info.vida, atu->info.vidamax);
            if (ui_draw_button(&app->ui, 160, by, 640, 48, info, 2, C_GREEN, C_BTN_HOVER, C_WHITE)) {
                app->player.moedas -= 500;
                int cura_base = 30;
                int cura_total = cura_base + (app->pontuacao / 10) * 5;
                atu->info.vida += cura_total;
                if (atu->info.vida > atu->info.vidamax) {
                    atu->info.vida = atu->info.vidamax;
                }
                snprintf(app->shop_status, sizeof(app->shop_status), "Cura aplicada! %s recuperou HP!", atu->info.nome);
                app->shop_mode = SHOP_MODE_NORMAL;
                break;
            }
            atu = atu->prox;
            p++;
        }

        if (ui_draw_button(&app->ui, WINDOW_WIDTH / 2 - 100, 450, 200, 40, "CANCELAR", 1, C_GRAY, C_BTN_HOVER, C_WHITE)) {
            app->shop_mode = SHOP_MODE_NORMAL;
        }

    } else if (app->shop_mode == SHOP_MODE_REVIVE_SELECT) {
        ui_draw_panel(&app->ui, 120, 130, 720, 380, C_PANEL_BG, C_PANEL_BORDER);
        ui_draw_text_centered(&app->ui, "ESCOLHA O POKEMON PARA REVIVER", WINDOW_WIDTH / 2, 150, 2, C_RED);

        tp_listase *cem = app->mortos;
        int m = 0;
        while (cem != NULL && m < 4) {
            int by = 200 + m * 60;
            char minfo[64];
            snprintf(minfo, sizeof(minfo), "Reviver %s (HP Max %d)", cem->info.nome, cem->info.vidamax);
            if (ui_draw_button(&app->ui, 160, by, 640, 48, minfo, 2, C_RED, C_BTN_HOVER, C_WHITE)) {
                app->player.moedas -= 1000;
                cem->info.vida = cem->info.vidamax;
                insereListaNoFim(&app->player.pokemonslista, cem->info);
                remove_listase(&app->mortos, cem->info);
                snprintf(app->shop_status, sizeof(app->shop_status), "%s foi revivido e voltou ao seu time!", cem->info.nome);
                app->shop_mode = SHOP_MODE_NORMAL;
                break;
            }
            cem = cem->prox;
            m++;
        }

        if (ui_draw_button(&app->ui, WINDOW_WIDTH / 2 - 100, 450, 200, 40, "CANCELAR", 1, C_GRAY, C_BTN_HOVER, C_WHITE)) {
            app->shop_mode = SHOP_MODE_NORMAL;
        }
    }
}

static void render_scene_ranking(GuiApp *app) {
    ui_clear(&app->ui, C_BG_DARK);

    ui_draw_panel(&app->ui, 100, 40, WINDOW_WIDTH - 200, 540, C_PANEL_BG, C_PANEL_BORDER);
    ui_draw_text_centered(&app->ui, "HALL DA FAMA - RANKING", WINDOW_WIDTH / 2, 60, 3, C_GOLD);

    /* Leitura do arquivo ranking.txt */
    Registro registros[100];
    int count = 0;
    FILE *file = fopen("ranking.txt", "r");
    if (file) {
        while (count < 100 && fscanf(file, "%19s %d", registros[count].nome, &registros[count].pontuacao) == 2) {
            count++;
        }
        fclose(file);
    }

    if (count > 0) {
        qsort(registros, count, sizeof(Registro), comparaRanking);

        int max_show = count < 8 ? count : 8;
        for (int i = 0; i < max_show; i++) {
            int ry = 130 + i * 45;
            SDL_Color bar_bg = (i % 2 == 0) ? C_WHITE : C_PANEL_BG;
            ui_draw_rect(&app->ui, 130, ry, WINDOW_WIDTH - 260, 40, bar_bg);
            ui_draw_rect_outline(&app->ui, 130, ry, WINDOW_WIDTH - 260, 40, C_PANEL_BORDER, 1);

            char rank_str[16];
            snprintf(rank_str, sizeof(rank_str), "%d.", i + 1);
            SDL_Color rank_color = (i == 0) ? C_GOLD : ((i == 1) ? C_GRAY : ((i == 2) ? C_RED : C_BLACK));
            ui_draw_text(&app->ui, rank_str, 150, ry + 12, 1, rank_color);

            ui_draw_text(&app->ui, registros[i].nome, 210, ry + 12, 1, C_BLACK);

            char pts[32];
            snprintf(pts, sizeof(pts), "%d pontos", registros[i].pontuacao);
            ui_draw_text(&app->ui, pts, 650, ry + 12, 1, C_BLUE);
        }
    } else {
        ui_draw_text_centered(&app->ui, "Nenhum recorde registrado ainda.", WINDOW_WIDTH / 2, 260, 2, C_GRAY);
    }

    if (ui_draw_button(&app->ui, WINDOW_WIDTH / 2 - 120, 510, 240, 45, "VOLTAR AO LOBBY", 2,
                       C_BTN_NORMAL, C_BTN_HOVER, C_WHITE)) {
        app->current_scene = SCENE_LOBBY;
    }
}

static void render_scene_game_over(GuiApp *app) {
    ui_clear(&app->ui, C_BG_DARK);

    ui_draw_panel(&app->ui, WINDOW_WIDTH / 2 - 250, 120, 500, 400, C_PANEL_BG, C_PANEL_BORDER);

    ui_draw_text_centered(&app->ui, "FIM DE JOGO!", WINDOW_WIDTH / 2, 160, 4, C_RED);
    ui_draw_text_centered(&app->ui, "Todos os seus Pokemons foram derrotados.", WINDOW_WIDTH / 2, 230, 1, C_BLACK);

    char score_text[64];
    snprintf(score_text, sizeof(score_text), "Pontuacao Final: %d ponto(s)", app->pontuacao);
    ui_draw_text_centered(&app->ui, score_text, WINDOW_WIDTH / 2, 270, 2, C_BLUE);

    if (ui_draw_button(&app->ui, WINDOW_WIDTH / 2 - 150, 330, 300, 50, "JOGAR NOVAMENTE", 2,
                       C_GREEN, C_BTN_HOVER, C_WHITE)) {
        /* Reinicia o jogo */
        destroi_listase(&app->player.pokemonslista);
        destroi_listase(&app->mortos);
        destroiListaLoja(&app->loja);
        destroiPilha(&app->pilhapok);

        init_game_pokemons(app);
        app->num_selected = 0;
        app->current_scene = SCENE_SELECT_TEAM;
    }

    if (ui_draw_button(&app->ui, WINDOW_WIDTH / 2 - 150, 400, 300, 45, "VER RANKING", 1,
                       C_GOLD, C_BTN_HOVER, C_WHITE)) {
        app->current_scene = SCENE_RANKING;
    }

    if (ui_draw_button(&app->ui, WINDOW_WIDTH / 2 - 150, 460, 300, 40, "SAIR DO JOGO", 1,
                       C_DARK_GRAY, C_BTN_HOVER, C_WHITE)) {
        app->running = 0;
    }
}

/* ========================================================================= */
/*                              LOOP PRINCIPAL                               */
/* ========================================================================= */

void gui_app_run(GuiApp *app) {
    SDL_Event e;

    while (app->running) {
        ui_begin_frame(&app->ui);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                if (app->player.pontuacao > 0) {
                    salvarRanking(app->player.nome, app->player.pontuacao);
                }
                app->running = 0;
            } else if (e.type == SDL_MOUSEMOTION) {
                app->ui.mouse_x = e.motion.x;
                app->ui.mouse_y = e.motion.y;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    app->ui.mouse_down = 1;
                }
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    app->ui.mouse_down = 0;
                    app->ui.mouse_clicked = 1;
                }
            } else if (e.type == SDL_KEYDOWN) {
                app->ui.key_pressed = e.key.keysym.sym;
            } else if (e.type == SDL_TEXTINPUT) {
                strncpy(app->ui.text_input, e.text.text, sizeof(app->ui.text_input) - 1);
                app->ui.text_input[sizeof(app->ui.text_input) - 1] = '\0';
            }
        }

        switch (app->current_scene) {
            case SCENE_TITLE:
                render_scene_title(app);
                break;
            case SCENE_NAME_INPUT:
                render_scene_name_input(app);
                break;
            case SCENE_SELECT_TEAM:
                render_scene_select_team(app);
                break;
            case SCENE_LOBBY:
                render_scene_lobby(app);
                break;
            case SCENE_BATTLE:
                render_scene_battle(app);
                break;
            case SCENE_SHOP:
                render_scene_shop(app);
                break;
            case SCENE_RANKING:
                render_scene_ranking(app);
                break;
            case SCENE_GAME_OVER:
                render_scene_game_over(app);
                break;
        }

        if (app->capture_and_exit) {
            gui_app_take_screenshot(app, app->screenshot_path);
            ui_end_frame(&app->ui);
            app->running = 0;
            break;
        }

        ui_end_frame(&app->ui);
        SDL_Delay(16); // ~60 FPS
    }
}

void gui_app_set_scene(GuiApp *app, GameScene scene) {
    if (scene == SCENE_LOBBY || scene == SCENE_BATTLE || scene == SCENE_SHOP || scene == SCENE_RANKING) {
        app->selected_team[0] = 0; // Pikachu
        app->selected_team[1] = 1; // Charmander
        app->selected_team[2] = 2; // Bulbasaur
        app->num_selected = 3;
        finalize_team_selection(app);
    }
    if (scene == SCENE_BATTLE) {
        start_battle(app);
    } else {
        app->current_scene = scene;
    }
}

void gui_app_take_screenshot(GuiApp *app, const char *path) {
    SDL_Surface *sshot = SDL_CreateRGBSurfaceWithFormat(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_PIXELFORMAT_ARGB8888);
    if (sshot) {
        SDL_RenderReadPixels(app->ui.renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
        SDL_SaveBMP(sshot, path);
        SDL_FreeSurface(sshot);
    }
}
