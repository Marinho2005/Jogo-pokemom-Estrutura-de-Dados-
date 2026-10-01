#include "gui_audio.h"

#if defined(__has_include)
  #if __has_include(<SDL2/SDL.h>)
    #include <SDL2/SDL.h>
  #elif __has_include(<SDL.h>)
    #include <SDL.h>
  #else
    #include <SDL2/SDL.h>
  #endif
#else
  #include <SDL2/SDL.h>
#endif

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static SDL_AudioDeviceID g_audio_dev = 0;
static int g_master_volume = 80; // 0 a 100
static int g_prev_volume = 80;
static int g_is_muted = 0;

int audio_init(void) {
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
        return 0;
    }

    SDL_AudioSpec wanted;
    SDL_zero(wanted);
    wanted.freq = 44100;
    wanted.format = AUDIO_S16SYS;
    wanted.channels = 1;
    wanted.samples = 1024;

    g_audio_dev = SDL_OpenAudioDevice(NULL, 0, &wanted, NULL, 0);
    if (g_audio_dev == 0) {
        return 0;
    }

    SDL_PauseAudioDevice(g_audio_dev, 0);
    return 1;
}

void audio_cleanup(void) {
    if (g_audio_dev != 0) {
        SDL_CloseAudioDevice(g_audio_dev);
        g_audio_dev = 0;
    }
}

void audio_set_volume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;
    g_master_volume = volume;
    if (volume > 0) {
        g_is_muted = 0;
    }
}

int audio_get_volume(void) {
    return g_master_volume;
}

void audio_toggle_mute(void) {
    if (g_is_muted) {
        g_master_volume = (g_prev_volume > 0) ? g_prev_volume : 80;
        g_is_muted = 0;
    } else {
        g_prev_volume = g_master_volume;
        g_master_volume = 0;
        g_is_muted = 1;
    }
}

int audio_is_muted(void) {
    return g_is_muted || (g_master_volume == 0);
}

void audio_play(SoundType sound) {
    if (g_audio_dev == 0 || g_master_volume <= 0) {
        return;
    }

    float vol_scale = (float)g_master_volume / 100.0f;
    int sample_rate = 44100;
    int num_samples = 0;
    int16_t buffer[44100]; // Até 1 segundo de áudio mono

    switch (sound) {
        case SOUND_SELECT: {
            /* Beep agudo curto */
            num_samples = (int)(sample_rate * 0.07f);
            for (int i = 0; i < num_samples; i++) {
                float t = (float)i / (float)sample_rate;
                float freq = 800.0f + (t / 0.07f) * 600.0f;
                float s = sinf(2.0f * (float)M_PI * freq * t);
                float env = 1.0f - (float)i / (float)num_samples;
                buffer[i] = (int16_t)(s * 7000.0f * env * vol_scale);
            }
            break;
        }

        case SOUND_ATTACK: {
            /* Swoosh com queda de frequência */
            num_samples = (int)(sample_rate * 0.15f);
            for (int i = 0; i < num_samples; i++) {
                float t = (float)i / (float)sample_rate;
                float freq = 600.0f - (t / 0.15f) * 400.0f;
                float s = (sinf(2.0f * (float)M_PI * freq * t) > 0.0f) ? 1.0f : -1.0f; // Onda quadrada retrô
                float env = 1.0f - (float)i / (float)num_samples;
                buffer[i] = (int16_t)(s * 6000.0f * env * vol_scale);
            }
            break;
        }

        case SOUND_DAMAGE: {
            /* Impacto / ruído ruidoso */
            num_samples = (int)(sample_rate * 0.18f);
            for (int i = 0; i < num_samples; i++) {
                float noise = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
                float env = 1.0f - (float)i / (float)num_samples;
                buffer[i] = (int16_t)(noise * 9000.0f * env * env * vol_scale);
            }
            break;
        }

        case SOUND_VICTORY: {
            /* Fanfarra de vitória (arpejo C5 -> E5 -> G5 -> C6) */
            num_samples = (int)(sample_rate * 0.45f);
            float notes[] = {523.25f, 659.25f, 783.99f, 1046.50f};
            int sub_len = num_samples / 4;
            for (int i = 0; i < num_samples; i++) {
                int note_idx = i / sub_len;
                if (note_idx > 3) note_idx = 3;
                float t = (float)i / (float)sample_rate;
                float s = sinf(2.0f * (float)M_PI * notes[note_idx] * t);
                buffer[i] = (int16_t)(s * 7500.0f * vol_scale);
            }
            break;
        }

        case SOUND_CAPTURE: {
            /* Jingle de captura bem-sucedida (D5 -> G5) */
            num_samples = (int)(sample_rate * 0.35f);
            float n1 = 587.33f;
            float n2 = 783.99f;
            int half = num_samples / 2;
            for (int i = 0; i < num_samples; i++) {
                float freq = (i < half) ? n1 : n2;
                float t = (float)i / (float)sample_rate;
                float s = (sinf(2.0f * (float)M_PI * freq * t) > 0.0f) ? 0.8f : -0.8f;
                buffer[i] = (int16_t)(s * 7000.0f * vol_scale);
            }
            break;
        }

        case SOUND_FAINT: {
            /* Som descendente de Pokémon derrotado */
            num_samples = (int)(sample_rate * 0.28f);
            for (int i = 0; i < num_samples; i++) {
                float t = (float)i / (float)sample_rate;
                float freq = 450.0f - (t / 0.28f) * 350.0f;
                float s = sinf(2.0f * (float)M_PI * freq * t);
                float env = 1.0f - (float)i / (float)num_samples;
                buffer[i] = (int16_t)(s * 7000.0f * env * vol_scale);
            }
            break;
        }

        case SOUND_BUY: {
            /* Caixa registradora da loja (B5 -> E6) */
            num_samples = (int)(sample_rate * 0.20f);
            int half = num_samples / 2;
            for (int i = 0; i < num_samples; i++) {
                float freq = (i < half) ? 987.77f : 1318.51f;
                float t = (float)i / (float)sample_rate;
                float s = sinf(2.0f * (float)M_PI * freq * t);
                buffer[i] = (int16_t)(s * 7500.0f * vol_scale);
            }
            break;
        }
    }

    if (num_samples > 0) {
        SDL_ClearQueuedAudio(g_audio_dev);
        SDL_QueueAudio(g_audio_dev, buffer, num_samples * sizeof(int16_t));
    }
}
