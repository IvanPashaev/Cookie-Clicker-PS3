#include "fonts.h"
#include "libfont.h"

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

void TTFUnloadFont() {
  FT_Done_FreeType(freetype);
  ttf_inited = 0;
}

void TTF_to_Bitmap(u8 chr, u8 *bitmap, short *w, short *h,
                   short *y_correction) {
  FT_Set_Pixel_Sizes(face, (*w), (*h));

  FT_GlyphSlot slot = face->glyph;

  memset(bitmap, 0, (*w) * (*h));

  if (FT_Load_Char(face, (char)chr, FT_LOAD_RENDER)) {
    (*w) = 0;
    return;
  }

  int n, m, ww;

  *y_correction = (*h) - 1 - slot->bitmap_top;

  ww = 0;

  for (n = 0; n < slot->bitmap.rows; n++) {
    for (m = 0; m < slot->bitmap.width; m++) {

      if (m >= (*w) || n >= (*h))
        continue;

      bitmap[m] = (u8)slot->bitmap.buffer[ww + m];
    }

    bitmap += *w;

    ww += slot->bitmap.width;
  }

  *w = ((slot->advance.x + 31) >> 6) +
       ((slot->bitmap_left < 0) ? -slot->bitmap_left : 0);
  *h = slot->bitmap.rows;
}

int loadFonts(void) {
  ResetFont();
  TTFLoadFont(NULL, (void *)merriweather_bold_ttf_bin,
              merriweather_bold_ttf_bin_size);
  u8 *texture_pointer = (u8 *)tiny3d_AllocTexture(1024 * 1024);
  AddFontFromTTF(texture_pointer, 32, 255, 32, 32, TTF_to_Bitmap);
  TTFUnloadFont();
  return 0;
}
