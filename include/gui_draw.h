#ifndef GUI_DRAW_H
#define GUI_DRAW_H

#include <SDL2/SDL.h>
#include <stdint.h>

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 640

/* Paleta de Cores Temática */
extern const SDL_Color C_BG_DARK;
extern const SDL_Color C_BG_LIGHT;
extern const SDL_Color C_PANEL_BG;
extern const SDL_Color C_PANEL_BORDER;
extern const SDL_Color C_WHITE;
extern const SDL_Color C_BLACK;
extern const SDL_Color C_GRAY;
extern const SDL_Color C_DARK_GRAY;
extern const SDL_Color C_RED;
extern const SDL_Color C_GREEN;
extern const SDL_Color C_BLUE;
extern const SDL_Color C_YELLOW;
extern const SDL_Color C_GOLD;
extern const SDL_Color C_BTN_NORMAL;
extern const SDL_Color C_BTN_HOVER;
extern const SDL_Color C_BTN_ACTIVE;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *font_texture;
    SDL_Texture *sprite_textures[15];
    int mouse_x;
    int mouse_y;
    int mouse_down;
    int mouse_clicked; // 1 se foi liberado o clique neste frame
    int key_pressed;   // SDL_Keycode da tecla pressionada neste frame
    char text_input[32]; // Caractere digitado neste frame
} UIContext;

/* Inicialização e finalização */
int ui_init(UIContext *ctx, int width, int height, const char *title);
void ui_cleanup(UIContext *ctx);

/* Controle de frame */
void ui_begin_frame(UIContext *ctx);
void ui_end_frame(UIContext *ctx);
void ui_clear(UIContext *ctx, SDL_Color color);

/* Primitivas de renderização */
void ui_draw_rect(UIContext *ctx, int x, int y, int w, int h, SDL_Color color);
void ui_draw_rect_outline(UIContext *ctx, int x, int y, int w, int h, SDL_Color color, int border);
void ui_draw_panel(UIContext *ctx, int x, int y, int w, int h, SDL_Color bg, SDL_Color border);
void ui_draw_pokeball(UIContext *ctx, int x, int y, int radius);

/* Texto e Fontes */
int ui_text_width(const char *text, int scale);
void ui_draw_text(UIContext *ctx, const char *text, int x, int y, int scale, SDL_Color color);
void ui_draw_text_centered(UIContext *ctx, const char *text, int cx, int y, int scale, SDL_Color color);

/* Componentes Interativos */
int ui_is_hovered(UIContext *ctx, int x, int y, int w, int h);
int ui_draw_button(UIContext *ctx, int x, int y, int w, int h, const char *text, int scale,
                  SDL_Color normal_bg, SDL_Color hover_bg, SDL_Color text_color);
int ui_draw_button_disabled(UIContext *ctx, int x, int y, int w, int h, const char *text, int scale);

/* Barra de Vida */
void ui_draw_health_bar(UIContext *ctx, int x, int y, int w, int h, int current_hp, int max_hp);

/* Sprites de Pokémons */
int ui_get_pokemon_sprite_idx(const char *name);
void ui_draw_sprite(UIContext *ctx, int sprite_idx, int x, int y, int scale);

#endif /* GUI_DRAW_H */
