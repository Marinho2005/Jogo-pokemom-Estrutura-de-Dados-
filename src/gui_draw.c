#include "gui_draw.h"
#include "font_data.h"
#include "sprite_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const SDL_Color C_BG_DARK     = {24, 30, 42, 255};
const SDL_Color C_BG_LIGHT    = {235, 240, 245, 255};
const SDL_Color C_PANEL_BG    = {248, 249, 250, 255};
const SDL_Color C_PANEL_BORDER= {170, 185, 200, 255};
const SDL_Color C_WHITE       = {255, 255, 255, 255};
const SDL_Color C_BLACK       = {25, 25, 30, 255};
const SDL_Color C_GRAY        = {140, 150, 160, 255};
const SDL_Color C_DARK_GRAY   = {50, 55, 65, 255};
const SDL_Color C_RED         = {220, 55, 55, 255};
const SDL_Color C_GREEN       = {45, 170, 85, 255};
const SDL_Color C_BLUE        = {45, 125, 220, 255};
const SDL_Color C_YELLOW      = {250, 195, 30, 255};
const SDL_Color C_GOLD        = {225, 165, 25, 255};
const SDL_Color C_BTN_NORMAL  = {45, 65, 90, 255};
const SDL_Color C_BTN_HOVER   = {60, 110, 180, 255};
const SDL_Color C_BTN_ACTIVE  = {30, 85, 150, 255};

static const char *pokemon_names_table[15] = {
    "Pikachu", "Charmander", "Bulbasaur", "Squirtle", "Jeryes",
    "Uaireless", "Solidariedade", "Atilario", "Lalai", "Sfoggui",
    "Marmarinho", "Mederios", "Aedus", "Marcius", "Senayus"
};

int ui_get_pokemon_sprite_idx(const char *name) {
    if (!name) return 0;
    for (int i = 0; i < 15; i++) {
        if (strcmp(pokemon_names_table[i], name) == 0) {
            return i;
        }
    }
    return 0;
}

int ui_init(UIContext *ctx, int width, int height, const char *title) {
    memset(ctx, 0, sizeof(UIContext));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 0;
    }

    ctx->window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );
    if (!ctx->window) {
        fprintf(stderr, "Erro ao criar janela: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    ctx->renderer = SDL_CreateRenderer(ctx->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ctx->renderer) {
        ctx->renderer = SDL_CreateRenderer(ctx->window, -1, 0);
    }
    if (!ctx->renderer) {
        fprintf(stderr, "Erro ao criar renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(ctx->window);
        SDL_Quit();
        return 0;
    }

    SDL_SetRenderDrawBlendMode(ctx->renderer, SDL_BLENDMODE_BLEND);

    /* Cria textura de fonte a partir dos dados embutidos (128 x 256 pixels) */
    SDL_Surface *font_surf = SDL_CreateRGBSurfaceWithFormat(0, 128, 256, 32, SDL_PIXELFORMAT_RGBA32);
    if (font_surf) {
        uint32_t *pixels = (uint32_t *)font_surf->pixels;
        for (int ch = 0; ch < 256; ch++) {
            int cx = (ch % 16) * 8;
            int cy = (ch / 16) * 16;
            for (int y = 0; y < 16; y++) {
                uint8_t row = font8x16_data[ch][y];
                for (int x = 0; x < 8; x++) {
                    int px = cx + x;
                    int py = cy + y;
                    if (row & (1 << (7 - x))) {
                        pixels[py * 128 + px] = 0xFFFFFFFF; // Branco opaco
                    } else {
                        pixels[py * 128 + px] = 0x00000000; // Transparente
                    }
                }
            }
        }
        ctx->font_texture = SDL_CreateTextureFromSurface(ctx->renderer, font_surf);
        SDL_FreeSurface(font_surf);
        if (ctx->font_texture) {
            SDL_SetTextureBlendMode(ctx->font_texture, SDL_BLENDMODE_BLEND);
        }
    }

    /* Cria texturas dos 15 sprites */
    for (int i = 0; i < 15; i++) {
        SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0, SPRITE_WIDTH, SPRITE_HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);
        if (surf) {
            memcpy(surf->pixels, pokemon_sprites[i], SPRITE_WIDTH * SPRITE_HEIGHT * 4);
            ctx->sprite_textures[i] = SDL_CreateTextureFromSurface(ctx->renderer, surf);
            SDL_FreeSurface(surf);
            if (ctx->sprite_textures[i]) {
                SDL_SetTextureBlendMode(ctx->sprite_textures[i], SDL_BLENDMODE_BLEND);
            }
        }
    }

    return 1;
}

void ui_cleanup(UIContext *ctx) {
    if (!ctx) return;
    if (ctx->font_texture) {
        SDL_DestroyTexture(ctx->font_texture);
        ctx->font_texture = NULL;
    }
    for (int i = 0; i < 15; i++) {
        if (ctx->sprite_textures[i]) {
            SDL_DestroyTexture(ctx->sprite_textures[i]);
            ctx->sprite_textures[i] = NULL;
        }
    }
    if (ctx->renderer) {
        SDL_DestroyRenderer(ctx->renderer);
        ctx->renderer = NULL;
    }
    if (ctx->window) {
        SDL_DestroyWindow(ctx->window);
        ctx->window = NULL;
    }
    SDL_Quit();
}

void ui_begin_frame(UIContext *ctx) {
    ctx->mouse_clicked = 0;
    ctx->key_pressed = 0;
    ctx->text_input[0] = '\0';
}

void ui_end_frame(UIContext *ctx) {
    SDL_RenderPresent(ctx->renderer);
}

void ui_clear(UIContext *ctx, SDL_Color color) {
    SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(ctx->renderer);
}

void ui_draw_rect(UIContext *ctx, int x, int y, int w, int h, SDL_Color color) {
    SDL_Rect r = {x, y, w, h};
    SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(ctx->renderer, &r);
}

void ui_draw_rect_outline(UIContext *ctx, int x, int y, int w, int h, SDL_Color color, int border) {
    SDL_SetRenderDrawColor(ctx->renderer, color.r, color.g, color.b, color.a);
    for (int i = 0; i < border; i++) {
        SDL_Rect r = {x + i, y + i, w - 2 * i, h - 2 * i};
        SDL_RenderDrawRect(ctx->renderer, &r);
    }
}

void ui_draw_panel(UIContext *ctx, int x, int y, int w, int h, SDL_Color bg, SDL_Color border) {
    /* Fundo suave com sombra leve */
    SDL_Rect shadow = {x + 3, y + 3, w, h};
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 40);
    SDL_RenderFillRect(ctx->renderer, &shadow);

    ui_draw_rect(ctx, x, y, w, h, bg);
    ui_draw_rect_outline(ctx, x, y, w, h, border, 2);
}

static uint8_t decode_utf8_char(const char **str) {
    unsigned char c = (unsigned char)**str;
    if (c < 128) {
        (*str)++;
        return c;
    }
    if (c == 0xC3 && *(*str + 1) != '\0') {
        unsigned char c2 = (unsigned char)*(*str + 1);
        *str += 2;
        /* UTF-8 0xC3 0x80..0xBF mapeia para 0xC0..0xFF em Latin-1 */
        return c2 + 64;
    }
    (*str)++;
    return '?';
}

int ui_text_width(const char *text, int scale) {
    if (!text) return 0;
    int len = 0;
    const char *p = text;
    while (*p != '\0') {
        decode_utf8_char(&p);
        len++;
    }
    return len * 8 * scale;
}

void ui_draw_text(UIContext *ctx, const char *text, int x, int y, int scale, SDL_Color color) {
    if (!ctx || !ctx->font_texture || !text) return;

    SDL_SetTextureColorMod(ctx->font_texture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(ctx->font_texture, color.a);

    int cur_x = x;
    int cur_y = y;
    const char *p = text;

    while (*p != '\0') {
        if (*p == '\n') {
            cur_y += 18 * scale;
            cur_x = x;
            p++;
            continue;
        }

        uint8_t ch = decode_utf8_char(&p);

        int cx = (ch % 16) * 8;
        int cy = (ch / 16) * 16;
        SDL_Rect src = {cx, cy, 8, 16};
        SDL_Rect dst = {cur_x, cur_y, 8 * scale, 16 * scale};

        SDL_RenderCopy(ctx->renderer, ctx->font_texture, &src, &dst);
        cur_x += 8 * scale;
    }
}

void ui_draw_text_centered(UIContext *ctx, const char *text, int cx, int y, int scale, SDL_Color color) {
    int w = ui_text_width(text, scale);
    ui_draw_text(ctx, text, cx - w / 2, y, scale, color);
}

int ui_is_hovered(UIContext *ctx, int x, int y, int w, int h) {
    return (ctx->mouse_x >= x && ctx->mouse_x < x + w &&
            ctx->mouse_y >= y && ctx->mouse_y < y + h);
}

int ui_draw_button(UIContext *ctx, int x, int y, int w, int h, const char *text, int scale,
                  SDL_Color normal_bg, SDL_Color hover_bg, SDL_Color text_color) {
    int hovered = ui_is_hovered(ctx, x, y, w, h);
    SDL_Color bg = hovered ? hover_bg : normal_bg;

    /* Sombra do botão */
    SDL_Rect shadow = {x + 2, y + 2, w, h};
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 60);
    SDL_RenderFillRect(ctx->renderer, &shadow);

    ui_draw_rect(ctx, x, y, w, h, bg);
    SDL_Color border = hovered ? C_WHITE : C_PANEL_BORDER;
    ui_draw_rect_outline(ctx, x, y, w, h, border, hovered ? 2 : 1);

    int tw = ui_text_width(text, scale);
    int th = 16 * scale;
    int tx = x + (w - tw) / 2;
    int ty = y + (h - th) / 2;
    ui_draw_text(ctx, text, tx, ty, scale, text_color);

    return (hovered && ctx->mouse_clicked);
}

int ui_draw_button_disabled(UIContext *ctx, int x, int y, int w, int h, const char *text, int scale) {
    ui_draw_rect(ctx, x, y, w, h, C_GRAY);
    ui_draw_rect_outline(ctx, x, y, w, h, C_DARK_GRAY, 1);
    int tw = ui_text_width(text, scale);
    int th = 16 * scale;
    int tx = x + (w - tw) / 2;
    int ty = y + (h - th) / 2;
    ui_draw_text(ctx, text, tx, ty, scale, C_DARK_GRAY);
    return 0;
}

void ui_draw_health_bar(UIContext *ctx, int x, int y, int w, int h, int current_hp, int max_hp) {
    if (max_hp <= 0) max_hp = 1;
    if (current_hp < 0) current_hp = 0;
    if (current_hp > max_hp) current_hp = max_hp;

    float ratio = (float)current_hp / (float)max_hp;

    /* Fundo cinza escuro */
    ui_draw_rect(ctx, x, y, w, h, C_DARK_GRAY);

    /* Cor baseada no HP: Verde > 50%, Amarelo 20-50%, Vermelho <= 20% */
    SDL_Color bar_color = C_GREEN;
    if (ratio <= 0.20f) {
        bar_color = C_RED;
    } else if (ratio <= 0.50f) {
        bar_color = C_YELLOW;
    }

    int fill_w = (int)(ratio * (w - 4));
    if (fill_w > 0) {
        ui_draw_rect(ctx, x + 2, y + 2, fill_w, h - 4, bar_color);
    }

    ui_draw_rect_outline(ctx, x, y, w, h, C_BLACK, 1);

    /* Texto de HP */
    char buf[32];
    snprintf(buf, sizeof(buf), "%d/%d", current_hp, max_hp);
    int text_x = x + (w - ui_text_width(buf, 1)) / 2;
    int text_y = y + (h - 16) / 2;
    ui_draw_text(ctx, buf, text_x, text_y, 1, C_WHITE);
}

void ui_draw_sprite(UIContext *ctx, int sprite_idx, int x, int y, int scale) {
    if (!ctx || sprite_idx < 0 || sprite_idx >= 15 || !ctx->sprite_textures[sprite_idx]) return;

    SDL_Rect dst = {x, y, SPRITE_WIDTH * scale, SPRITE_HEIGHT * scale};
    SDL_RenderCopy(ctx->renderer, ctx->sprite_textures[sprite_idx], NULL, &dst);
}

void ui_draw_pokeball(UIContext *ctx, int x, int y, int r) {
    /* Desenha Pokebola estilizada */
    for (int dy = -r; dy <= r; dy++) {
        for (int dx = -r; dx <= r; dx++) {
            if (dx*dx + dy*dy <= r*r) {
                if (dy < -1) {
                    SDL_SetRenderDrawColor(ctx->renderer, 220, 40, 40, 255); // Metade superior vermelha
                } else if (dy > 1) {
                    SDL_SetRenderDrawColor(ctx->renderer, 245, 245, 245, 255); // Metade inferior branca
                } else {
                    SDL_SetRenderDrawColor(ctx->renderer, 40, 40, 40, 255); // Faixa preta central
                }
                SDL_RenderDrawPoint(ctx->renderer, x + dx, y + dy);
            }
        }
    }
    /* Botão central da pokebola */
    int r_inner = r / 3;
    for (int dy = -r_inner; dy <= r_inner; dy++) {
        for (int dx = -r_inner; dx <= r_inner; dx++) {
            if (dx*dx + dy*dy <= r_inner*r_inner) {
                SDL_SetRenderDrawColor(ctx->renderer, 255, 255, 255, 255);
                SDL_RenderDrawPoint(ctx->renderer, x + dx, y + dy);
            }
        }
    }
}
