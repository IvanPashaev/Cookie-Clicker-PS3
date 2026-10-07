#include "textures_load.h"
#include "pngdec/pngdec.h"
#include <stdint.h>

extern const uint8_t cookie_bin[];
extern const uint32_t cookie_bin_size;

extern const uint8_t bg_bin[];
extern const uint32_t bg_bin_size;

extern const uint8_t small_cookie_bin[];
extern const uint32_t small_cookie_bin_size;

extern const uint8_t light_bin[];
extern const uint32_t light_bin_size;

pngData cookie_texture;
u32 cookie_texture_offset;

pngData bg_texture;
u32 bg_texture_offset;

pngData small_cookie_texture;
u32 small_cookie_texture_offset;

pngData light_texture;
u32 light_texture_offset;

int loadTextures(void) {

  int ret = pngLoadFromBuffer(cookie_bin, cookie_bin_size, &cookie_texture);
  if (ret != 0)
    return ret;
  pngLoadFromBuffer(small_cookie_bin, small_cookie_bin_size,
                    &small_cookie_texture);
  pngLoadFromBuffer(light_bin, light_bin_size, &light_texture);
  return pngLoadFromBuffer(bg_bin, bg_bin_size, &bg_texture);
}
