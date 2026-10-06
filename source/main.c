#include "textures_load.h"

#include <io/pad.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sysmodule/sysmodule.h>
#include <tiny3d.h>

#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void loadTextuesToVram(void) {
  if (cookie_texture.bmp_out && cookie_texture.width > 0 &&
      cookie_texture.height > 0) {
    u32 cookie_texture_size =
        (cookie_texture.pitch * cookie_texture.height + 15) & ~15;
    u32 *cookie_texture_rsx_mem =
        (u32 *)tiny3d_AllocTexture(cookie_texture_size);

    memcpy(cookie_texture_rsx_mem, cookie_texture.bmp_out,
           cookie_texture.pitch * cookie_texture.height);

    cookie_texture_offset = tiny3d_TextureOffset(cookie_texture_rsx_mem);
  }
}

void drawCookie(void) {
  float x = 100.0f;
  float y = 100.0f;

  float width = (float)cookie_texture.width;
  float height = (float)cookie_texture.height;

  tiny3d_SetPolygon(TINY3D_QUADS);

  tiny3d_VertexPos(x, y, 0);
  tiny3d_VertexColor(0xffffffff);   // Белый цвет, чтобы не искажать текстуру
  tiny3d_VertexTexture(0.0f, 0.0f); // UV: левый верх

  // Вершина 2: Правый Верхний
  tiny3d_VertexPos(x + width, y, 0);
  tiny3d_VertexColor(0xffffffff);
  tiny3d_VertexTexture(1.0f, 0.0f); // UV: правый верх

  // Вершина 3: Правый Нижний
  tiny3d_VertexPos(x + width, y + height, 0);
  tiny3d_VertexColor(0xffffffff);
  tiny3d_VertexTexture(1.0f, 1.0f); // UV: правый низ

  // Вершина 4: Левый Нижний
  tiny3d_VertexPos(x, y + height, 0);
  tiny3d_VertexColor(0xffffffff);
  tiny3d_VertexTexture(0.0f, 1.0f); // UV: левый низ

  // Заканчиваем описание полигона
  tiny3d_End();

  tiny3d_SetTexture(0, cookie_texture_offset, cookie_texture.width,
                    cookie_texture.height, cookie_texture.pitch,
                    TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);
}

int main(void) {
  tiny3d_Init(1280 * 720);
  ioPadInit(7);
  loadTextures();
  loadTextuesToVram();

  padInfo padinfo;
  padData paddata;

  sysModuleLoad(SYSMODULE_PNGDEC);

  while (1) {
    tiny3d_Clear(0xff000000, TINY3D_CLEAR_ALL);
    tiny3d_Project2D();

    // Enable alpha Test
    tiny3d_AlphaTest(1, 0x10, TINY3D_ALPHA_FUNC_GEQUAL);

    // Enable alpha blending.
    tiny3d_BlendFunc(1,
                     TINY3D_BLEND_FUNC_SRC_RGB_SRC_ALPHA |
                         TINY3D_BLEND_FUNC_SRC_ALPHA_SRC_ALPHA,
                     TINY3D_BLEND_FUNC_DST_RGB_ONE_MINUS_SRC_ALPHA |
                         TINY3D_BLEND_FUNC_DST_ALPHA_ZERO,
                     TINY3D_BLEND_RGB_FUNC_ADD | TINY3D_BLEND_ALPHA_FUNC_ADD);

    drawCookie();

    ioPadGetInfo(&padinfo);
    tiny3d_Flip();
  }
}
