#ifndef FONTS_H
#define FONTS_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <libfont.h>
#include <stdint.h>

extern int ttf_inited;

extern FT_Library freetype;
extern FT_Face face;

int TTFLoadFont(char *path, void *from_memory, int size_from_memory);
void TTFUnloadFont();
void TTF_to_Bitmap(u8 chr, u8 *bitmap, short *w, short *h, short *y_correction);
int loadFonts(void);
#endif
