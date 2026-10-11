#include <stdint.h>

typedef struct sound {
  uint8_t sound;
  uint32_t sound_size;
} Sound;

typedef struct sound_group {
  Sound sounds[6];
} SoundGroup;

extern const uint8_t spu_soundmodule_bin[0x0000d471];

extern const uint8_t audio_click1_bin[];
extern const uint32_t audio_click1_bin_size;

extern const uint8_t audio_click2_bin[];
extern const uint32_t audio_click2_bin_size;

extern const uint8_t audio_click3_bin[];
extern const uint32_t audio_click3_bin_size;

extern const uint8_t audio_click4_bin[];
extern const uint32_t audio_click4_bin_size;

extern const uint8_t audio_buy1_bin[];
extern const uint32_t audio_buy1_bin_size;

extern const uint8_t audio_buy2_bin[];
extern const uint32_t audio_buy2_bin_size;

extern const uint8_t audio_buy3_bin[];
extern const uint32_t audio_buy3_bin_size;

extern const uint8_t audio_buy4_bin[];
extern const uint32_t audio_buy4_bin_size;

extern const uint8_t audio_click5_bin[];
extern const uint32_t audio_click5_bin_size;

extern const uint8_t audio_click6_bin[];
extern const uint32_t audio_click6_bin_size;

extern const uint8_t audio_click7_bin[];
extern const uint32_t audio_click7_bin_size;

int initAudioSystem(void);
int playSound(const uint8_t *sound, uint32_t sound_size);
