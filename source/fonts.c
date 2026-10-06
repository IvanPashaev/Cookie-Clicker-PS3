#include "fonts.h"

#include <stdint.h>

int ttf_inited = 0;

FT_Library freetype;
FT_Face face;

extern const uint8_t merriweather_bold_ttf_bin[];
extern const uint32_t merriweather_bold_ttf_bin_size;

int TTFLoadFont(char *path, void *from_memory, int size_from_memory) {
  if (!ttf_inited)
    FT_Init_FreeType(&freetype);
  ttf_inited = 1;

  if (path) {
    if (FT_New_Face(freetype, path, 0, &face))
      return -1;
  } else {
    if (FT_New_Memory_Face(freetype, from_memory, size_from_memory, 0, &face))
      return -1;
  }

  return 0;
}