// peace for our time

#include "fonts.h"
#include "textures_load.h"
#include "values.h"

#include <io/pad.h>
#include <libfont.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sysmodule/sysmodule.h>
#include <time.h>
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
    u32 *cookie_texture_rsx_mem = (u32 *)tiny3d_AllocTexture(
        cookie_texture_size); // alloc memory in rsx for texture

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
  if (small_cookie_texture.bmp_out && small_cookie_texture.width > 0 &&
      small_cookie_texture.height > 0) {
    u32 small_cookie_texture_size =
        (small_cookie_texture.pitch * small_cookie_texture.height + 15) & ~15;
    u32 *small_cookie_texture_rsx_mem =
        (u32 *)tiny3d_AllocTexture(small_cookie_texture_size);

    if (small_cookie_texture_rsx_mem) {
      memcpy(small_cookie_texture_rsx_mem, small_cookie_texture.bmp_out,
             small_cookie_texture.pitch * small_cookie_texture.height);

      small_cookie_texture_offset =
          tiny3d_TextureOffset(small_cookie_texture_rsx_mem);
    }
  }
}

void drawCookie(void) {
  float x = 15.0f;
  float y = 180.0f;

  float width = (float)cookie_texture.width / 2.5;
  float height = (float)cookie_texture.height / 2.5;

  tiny3d_SetTexture(0, cookie_texture_offset, cookie_texture.width,
                    cookie_texture.height, cookie_texture.pitch,
                    TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);

  tiny3d_SetPolygon(TINY3D_QUADS);

  tiny3d_VertexPos(x, y, 0);
  tiny3d_VertexColor(0xffffffff);   // white color standart
  tiny3d_VertexTexture(0.0f, 0.0f); // uv: left up

  tiny3d_VertexPos(x + width, y, 0);
  tiny3d_VertexColor(0xffffffff);
  tiny3d_VertexTexture(1.0f, 0.0f); // uv: right up

  tiny3d_VertexPos(x + width, y + height, 0);
  tiny3d_VertexColor(0xffffffff);
  tiny3d_VertexTexture(1.0f, 1.0f); // uv: right down

  tiny3d_VertexPos(x, y + height, 0);
  tiny3d_VertexColor(0xffffffff);
  tiny3d_VertexTexture(0.0f, 1.0f); // uv: left down

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
      tiny3d_VertexColor(0xffffffff);
      tiny3d_VertexTexture(0.0f, 0.0f);

      tiny3d_VertexPos(x + width, y, 0);
      tiny3d_VertexColor(0xffffffff);
      tiny3d_VertexTexture(1.0f, 0.0f);

      tiny3d_VertexPos(x + width, y + height, 0);
      tiny3d_VertexColor(0xffffffff);
      tiny3d_VertexTexture(1.0f, 1.0f);

      tiny3d_VertexPos(x, y + height, 0);
      tiny3d_VertexColor(0xffffffff);
      tiny3d_VertexTexture(0.0f, 1.0f);

      tiny3d_End();
    }
  }
}

void drawValue(void) {
  SetCurrentFont(0);
  SetFontSize(18, 32);
  SetFontColor(0xffffffff, 0x0);
  DrawFormatString(70.0f, 100.0f, "cookies: %lld", cookies);
}

void spawnFloatCookie(float cx, float cy) {
  for (int i = 0; i < MAX_FLOAT_COOKIES; i++) {
    if (!float_cookies[i].active) {
      float_cookies[i].active = 1;
      float_cookies[i].x = cx;
      float_cookies[i].y = cy;
      float_cookies[i].w = (float)small_cookie_texture.width / 10.0f;
      float_cookies[i].h = (float)small_cookie_texture.height / 10.0f;
      float_cookies[i].life = 45; // 0.75 at 60 fps
      float_cookies[i].max_life = 45;
      break;
    }
  }
}

void updateFloatCookies(void) {
  for (int i = 0; i < MAX_FLOAT_COOKIES; i++) {
    if (float_cookies[i].active) {
      float_cookies[i].y -= 1.5f; // swim to up
      if (--float_cookies[i].life <= 0)
        float_cookies[i].active = 0;
    }
  }
}

void drawFloatCookies(void) {
  for (int i = 0; i < MAX_FLOAT_COOKIES; i++) {
    FloatCookie *c = &float_cookies[i];
    if (!c->active)
      continue;

    float t = (float)c->life / (float)c->max_life; // 1 → 0
    float scale = 1.0f + 0.5f * (1.0f - t);        // 1.5 → 1.0

    float w = c->w * scale;
    float h = c->h * scale;

    tiny3d_SetTexture(0, small_cookie_texture_offset,
                      small_cookie_texture.width, small_cookie_texture.height,
                      small_cookie_texture.pitch, TINY3D_TEX_FORMAT_A8R8G8B8,
                      TEXTURE_LINEAR);
    tiny3d_SetPolygon(TINY3D_QUADS);

    tiny3d_VertexPos(c->x, c->y, 0);
    tiny3d_VertexFcolor(1.0f, 1.0f, 1.0f, t);
    tiny3d_VertexTexture(0.0f, 0.0f);

    tiny3d_VertexPos(c->x + w, c->y, 0);
    tiny3d_VertexFcolor(1.0f, 1.0f, 1.0f, t);
    tiny3d_VertexTexture(1.0f, 0.0f);

    tiny3d_VertexPos(c->x + w, c->y + h, 0);
    tiny3d_VertexFcolor(1.0f, 1.0f, 1.0f, t);
    tiny3d_VertexTexture(1.0f, 1.0f);

    tiny3d_VertexPos(c->x, c->y + h, 0);
    tiny3d_VertexFcolor(1.0f, 1.0f, 1.0f, t);
    tiny3d_VertexTexture(0.0f, 1.0f);

    tiny3d_End();
  }
}

int main(void) {
  srand(time(NULL));
  printf("init tiny3d...\n");
  int r = tiny3d_Init(1024 * 1024);
  printf("tiny3d_Init ret=%d\n", r);

  ioPadInit(7);

  sysModuleLoad(SYSMODULE_PNGDEC);
  loadTextures();

  loadTextuesToVram();
  loadFonts();

  padInfo padinfo;
  padData paddata;
  int frame = 0;

  while (1) {
    if ((frame++ % 60) == 0)
      printf("frame %d\n", frame);

    if ((frame % 60) == 0) {
      cookies += (long long)cookies_per_second;
    }

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
    drawValue();
    drawFloatCookies();
    ioPadGetInfo(&padinfo);
    static u16 prev_cross = 0;
    for (int i = 0; i < MAX_PADS; i++) {
      if (padinfo.status[i]) {
        ioPadGetData(i, &paddata);

        if (paddata.len > 0) {
          u16 cur_cross = paddata.BTN_CROSS != 0;
          if (cur_cross && !prev_cross) {
            cookies++;
            float x =
                0.0f + ((float)rand() / (float)RAND_MAX) * (150.0f - 0.0f);
            float y =
                140.0f + ((float)rand() / (float)RAND_MAX) * (300.0f - 140.0f);
            spawnFloatCookie(x, y);
          }
          prev_cross = cur_cross;
        }
      }
    }
    updateFloatCookies();
    tiny3d_Flip();
  }
}
