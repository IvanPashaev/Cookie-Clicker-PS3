#include "textures_load.h"
#include "pngdec/pngdec.h"
#include <stdlib.h>

extern const uint8_t cookie_bin[];
extern const uint32_t cookie_bin_size;

pngData cookie_texture;
u32 cookie_texture_offset;
pngData bg_texture;

int loadTextures(void) {
  pngLoadFromBuffer(cookie_bin, cookie_bin_size, &cookie_texture);
}
