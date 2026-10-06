#include "textures_load.h"
#include "values.h"

#include <io/pad.h>
#include <libfont.h>
#include <stdint.h>
#include <string.h>
#include <sysmodule/sysmodule.h>
#include <tiny3d.h>

#include <assert.h>
#include <malloc.h>
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

    if (cookie_texture_rsx_mem) {
      memcpy(cookie_texture_rsx_mem, cookie_texture.bmp_out,
             cookie_texture.pitch * cookie_texture.height);

      cookie_texture_offset = tiny3d_TextureOffset(cookie_texture_rsx_mem);
    }
  }

  if (bg_texture.bmp_out && bg_texture.width > 0 && bg_texture.height > 0) {
    u32 bg_texture_size = (bg_texture.pitch * bg_texture.height + 15) & ~15;
    u32 *bg_texture_rsx_mem = (u32 *)tiny3d_AllocTexture(bg_texture_size);

    if (bg_texture_rsx_mem) {
      memcpy(bg_texture_rsx_mem, bg_texture.bmp_out,
             bg_texture.pitch * bg_texture.height);

      bg_texture_offset = tiny3d_TextureOffset(bg_texture_rsx_mem);
    }
  }
}

void drawCookie(void) {
  float x = 15.0f;
  float y = 100.0f;

  float width = (float)cookie_texture.width / 2.5;
  float height = (float)cookie_texture.height / 2.5;

  tiny3d_SetTexture(0, cookie_texture_offset, cookie_texture.width,
                    cookie_texture.height, cookie_texture.pitch,
                    TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);

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
}

void drawBackgroundTiled(void) {
  float width = (float)bg_texture.width;
  float height = (float)bg_texture.height;

  if (width <= 0.0f || height <= 0.0f)
    return;

  for (float y = 0.0f; y < 720.0f; y += height) {
    for (float x = 0.0f; x < 1280.0f; x += width) {
      tiny3d_SetTexture(0, bg_texture_offset, bg_texture.width,
                        bg_texture.height, bg_texture.pitch,
                        TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);

      tiny3d_SetPolygon(TINY3D_QUADS);

      tiny3d_VertexPos(x, y, 0);
      tiny3d_VertexColor(0xffffffff); // Белый цвет, чтобы не искажать текстуру
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
    }
  }
}

void drawValue(void) { DrawFormatString(15.0f, 120.0f, "%lld", clicks); }

int main(void) {
  printf("init tiny3d...\n");
  int r = tiny3d_Init(1024 * 1024);
  printf("tiny3d_Init ret=%d\n", r);

  ioPadInit(7);

  sysModuleLoad(SYSMODULE_PNGDEC);
  loadTextures();

  loadTextuesToVram();

  padInfo padinfo;
  padData paddata;
  int frame = 0;

  while (1) {
    if ((frame++ % 60) == 0)
      printf("frame %d\n", frame);
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
    drawBackgroundTiled();
    drawCookie();

    ioPadGetInfo(&padinfo);

    for (int i = 0; i < MAX_PADS; i++) {
      if (padinfo.status[i]) {
        ioPadGetData(i, &paddata);

        if (paddata.BTN_CROSS) {
        }
      }
    }
    tiny3d_Flip();
  }
}
