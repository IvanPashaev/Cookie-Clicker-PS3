#include "textures_load.h"
#include "pngdec/pngdec.h"
#include <stdint.h>

extern const uint8_t cookie_bin[];
extern const uint32_t cookie_bin_size;

extern const uint8_t bg_bin[];
extern const uint32_t bg_bin_size;

extern const uint8_t small_cookie_bin[];
extern const uint32_t small_cookie_bin_size;

extern const uint8_t shine_bin[];
extern const uint32_t shine_bin_size;

extern const uint8_t store_button_bin[];
extern const uint32_t store_button_bin_size;

extern const uint8_t cursor_store_bin[];
extern const uint32_t cursor_store_bin_size;

extern const uint8_t grandma_store_bin[];
extern const uint32_t grandma_store_bin_size;

extern const uint8_t gray_bin[];
extern const uint32_t gray_bin_size;

extern const uint8_t farm_store_bin[];
extern const uint32_t farm_store_bin_size;

extern const uint8_t mine_store_bin[];
extern const uint32_t mine_store_bin_size;

pngData cookie_texture;
u32 cookie_texture_offset;

pngData bg_texture;
u32 bg_texture_offset;

pngData small_cookie_texture;
u32 small_cookie_texture_offset;

pngData shine_texture;
u32 shine_texture_offset;

pngData store_button_texture;
u32 store_button_texture_offset;

pngData cursor_store_texture;
u32 cursor_store_texture_offset;

pngData grandma_store_texture;
u32 grandma_store_texture_offset;

pngData gray_texture;
u32 gray_texture_offset;

pngData farm_store_texture;
u32 farm_store_texture_offset;

pngData mine_store_texture;
u32 mine_store_texture_offset;

int loadTextures(void) {

  int ret = pngLoadFromBuffer(cookie_bin, cookie_bin_size, &cookie_texture);
  if (ret != 0)
    return ret;
  pngLoadFromBuffer(small_cookie_bin, small_cookie_bin_size,
                    &small_cookie_texture);
  pngLoadFromBuffer(shine_bin, shine_bin_size, &shine_texture);
  pngLoadFromBuffer(store_button_bin, store_button_bin_size,
                    &store_button_texture);
  pngLoadFromBuffer(cursor_store_bin, cursor_store_bin_size,
                    &cursor_store_texture);
  pngLoadFromBuffer(grandma_store_bin, grandma_store_bin_size,
                    &grandma_store_texture);
  pngLoadFromBuffer(gray_bin, gray_bin_size, &gray_texture);
  pngLoadFromBuffer(farm_store_bin, farm_store_bin_size, &farm_store_texture);
  pngLoadFromBuffer(mine_store_bin, mine_store_bin_size, &mine_store_texture);
  return pngLoadFromBuffer(bg_bin, bg_bin_size, &bg_texture);
}
