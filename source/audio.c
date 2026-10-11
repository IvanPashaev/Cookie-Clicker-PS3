#include <soundlib/audioplayer.h>
#include <soundlib/spu_soundlib.h>
#include <stdint.h>
#include <stdlib.h>

#include "audio.h"

#define MAX_CACHED_SOUNDS 16

typedef struct {
  const uint8_t *src;
  uint32_t src_size;
  short *samples;
  int size_samples;
  int freq;
  int is_stereo;
} CachedSound;

static CachedSound sound_cache[MAX_CACHED_SOUNDS];
static int num_cached_sounds = 0;

int initAudioSystem(void) {
  u32 spu;
  sysSpuImage spu_image;
  sysSpuInitialize(6, 5);
  sysSpuRawCreate(&spu, NULL);
  sysSpuImageImport(&spu_image, spu_soundmodule_bin, 0);
  sysSpuRawImageLoad(spu, &spu_image);
  if (SND_Init(spu))
    return 0;
}

static CachedSound *decodeSound(const uint8_t *sound, uint32_t sound_size) {
  for (int i = 0; i < num_cached_sounds; i++) {
    if (sound_cache[i].src == sound)
      return &sound_cache[i];
  }

  if (num_cached_sounds >= MAX_CACHED_SOUNDS)
    return NULL;

  int size_samples = 48000 * 2 * 2 * 2;
  short *samples = malloc(size_samples);

  if (!samples)
    return NULL;

  CachedSound *c = &sound_cache[num_cached_sounds];
  c->size_samples = size_samples;
  if (DecodeAudio((void *)sound, sound_size, samples, &c->size_samples,
                  &c->freq, &c->is_stereo) != 0) {
    free(samples);
    return NULL;
  }

  c->src = sound;
  c->src_size = sound_size;
  c->samples = samples;
  num_cached_sounds++;
  return c;
}

int playSound(const uint8_t *sound, uint32_t sound_size) {
  CachedSound *c = decodeSound(sound, sound_size);

  if (!c)
    return -1;

  SND_Pause(0);
  SND_SetVoice(2, c->is_stereo ? VOICE_STEREO_16BIT : VOICE_MONO_16BIT, c->freq,
               0, c->samples, c->size_samples, 255, 255, NULL);
  return 0;
}
