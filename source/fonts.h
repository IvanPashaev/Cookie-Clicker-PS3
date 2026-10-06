#ifndef FONTS_H
#define FONTS_H

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>

extern int ttf_inited;

extern FT_Library freetype;
extern FT_Face face;

int TTFLoadFont(char *path, void *from_memory, int size_from_memory);

#endif