#ifndef GUI_AUDIO_H
#define GUI_AUDIO_H

typedef enum {
    SOUND_SELECT,
    SOUND_ATTACK,
    SOUND_DAMAGE,
    SOUND_VICTORY,
    SOUND_CAPTURE,
    SOUND_FAINT,
    SOUND_BUY
} SoundType;

int audio_init(void);
void audio_cleanup(void);
void audio_set_volume(int volume);
int audio_get_volume(void);
void audio_toggle_mute(void);
int audio_is_muted(void);
void audio_play(SoundType sound);

#endif /* GUI_AUDIO_H */
