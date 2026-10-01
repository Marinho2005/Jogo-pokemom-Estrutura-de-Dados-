#include "gui.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    GuiApp app;
    if (!gui_app_init(&app)) {
        fprintf(stderr, "Falha ao inicializar aplicacao grafica PokeRogue.\n");
        return 1;
    }

    /* Processamento de argumentos opcionais de cena e captura de tela */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--scene") == 0 && i + 1 < argc) {
            const char *sc = argv[++i];
            if (strcmp(sc, "title") == 0) gui_app_set_scene(&app, SCENE_TITLE);
            else if (strcmp(sc, "name") == 0) gui_app_set_scene(&app, SCENE_NAME_INPUT);
            else if (strcmp(sc, "select") == 0) gui_app_set_scene(&app, SCENE_SELECT_TEAM);
            else if (strcmp(sc, "lobby") == 0) gui_app_set_scene(&app, SCENE_LOBBY);
            else if (strcmp(sc, "battle") == 0) gui_app_set_scene(&app, SCENE_BATTLE);
            else if (strcmp(sc, "shop") == 0) gui_app_set_scene(&app, SCENE_SHOP);
            else if (strcmp(sc, "ranking") == 0) gui_app_set_scene(&app, SCENE_RANKING);
            else if (strcmp(sc, "settings") == 0) gui_app_set_scene(&app, SCENE_SETTINGS);
            else if (strcmp(sc, "gameover") == 0) gui_app_set_scene(&app, SCENE_GAME_OVER);
        } else if (strcmp(argv[i], "--screenshot") == 0 && i + 1 < argc) {
            strncpy(app.screenshot_path, argv[++i], sizeof(app.screenshot_path) - 1);
            app.capture_and_exit = 1;
        }
    }

    gui_app_run(&app);
    gui_app_cleanup(&app);

    return 0;
}
