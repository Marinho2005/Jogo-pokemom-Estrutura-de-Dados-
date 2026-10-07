#ifndef GUI_H
#define GUI_H

#include "gui_draw.h"
#include "gui_audio.h"
#include "pokemon.h"
#include "jogador.h"
#include "loja.h"
#include "ranking.h"
#include "savegame.h"

typedef enum {
    SCENE_TITLE,
    SCENE_NAME_INPUT,
    SCENE_SELECT_TEAM,
    SCENE_LOBBY,
    SCENE_BATTLE,
    SCENE_SHOP,
    SCENE_RANKING,
    SCENE_SETTINGS,
    SCENE_GAME_OVER
} GameScene;

typedef enum {
    BATTLE_PHASE_MENU,
    BATTLE_PHASE_ATTACK,
    BATTLE_PHASE_SWAP,
    BATTLE_PHASE_VICTORY,
    BATTLE_PHASE_DEFEAT_POKE,
    BATTLE_PHASE_CAPTURED
} BattlePhase;

typedef enum {
    SHOP_MODE_NORMAL,
    SHOP_MODE_HEAL_SELECT,
    SHOP_MODE_REVIVE_SELECT
} ShopMode;

struct GuiApp {
    UIContext ui;
    GameScene current_scene;
    GameScene previous_scene;

    /* Controle de Save e Notificações */
    char title_notification[80];
    int show_confirm_overwrite;

    /* Dados do Jogo */
    Jogador player;
    Pokemon all_pokemons[15];
    Pokemon pokemonsrest[12];
    Pilha pilhapok;
    tp_listase *mortos;
    ListaLoja *loja;
    int pontuacao;

    /* Entrada de Nome */
    char input_name[24];

    /* Seleção de Time */
    int selected_team[3];
    int num_selected;

    /* Batalha */
    BattlePhase battle_phase;
    Pokemon current_adversario;
    Pokemon *active_pokemon;
    char battle_log[4][96];
    int battle_log_count;
    char battle_message[96];

    /* Loja */
    ShopMode shop_mode;
    char shop_status[96];

    /* Teste e Captura */
    char screenshot_path[128];
    int capture_and_exit;

    int running;
};

int gui_app_init(GuiApp *app);
void gui_app_set_scene(GuiApp *app, GameScene scene);
void gui_app_take_screenshot(GuiApp *app, const char *path);
void gui_app_run(GuiApp *app);
void gui_app_cleanup(GuiApp *app);

#endif /* GUI_H */
