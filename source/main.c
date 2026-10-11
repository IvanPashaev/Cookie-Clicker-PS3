// peace for our time

#include "audio.h"
#include "bakery_name.h"
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
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

float shine_angle = 0.0f;

#define STORE_THINGS 1
int store_select = 0;

enum store_stats { CURSORS };

enum store_stats STORE_STATS = {CURSORS};

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

  if (shine_texture.bmp_out && shine_texture.width > 0 &&
      shine_texture.height > 0) {
    u32 shine_texture_size =
        (shine_texture.pitch * shine_texture.height + 15) & ~15;
    u32 *shine_texture_rsx_mem = (u32 *)tiny3d_AllocTexture(shine_texture_size);

    if (shine_texture_rsx_mem) {
      memcpy(shine_texture_rsx_mem, shine_texture.bmp_out,
             shine_texture.pitch * shine_texture.height);

      shine_texture_offset = tiny3d_TextureOffset(shine_texture_rsx_mem);
    }
  }

  if (store_button_texture.bmp_out && store_button_texture.width > 0 &&
      store_button_texture.height > 0) {
    u32 store_button_texture_size =
        (store_button_texture.pitch * store_button_texture.height + 15) & ~15;
    u32 *store_button_texture_rsx_mem =
        (u32 *)tiny3d_AllocTexture(store_button_texture_size);

    if (store_button_texture_rsx_mem) {
      memcpy(store_button_texture_rsx_mem, store_button_texture.bmp_out,
             store_button_texture.pitch * store_button_texture.height);

      store_button_texture_offset =
          tiny3d_TextureOffset(store_button_texture_rsx_mem);
    }
  }

  if (cursor_store_texture.bmp_out && cursor_store_texture.width > 0 &&
      cursor_store_texture.height > 0) {
    u32 cursor_store_texture_size =
        (cursor_store_texture.pitch * cursor_store_texture.height + 15) & ~15;
    u32 *cursor_store_texture_rsx_mem =
        (u32 *)tiny3d_AllocTexture(cursor_store_texture_size);

    if (cursor_store_texture_rsx_mem) {
      memcpy(cursor_store_texture_rsx_mem, cursor_store_texture.bmp_out,
             cursor_store_texture.pitch * cursor_store_texture.height);

      cursor_store_texture_offset =
          tiny3d_TextureOffset(cursor_store_texture_rsx_mem);
    }
  }

  if (grandma_store_texture.bmp_out && grandma_store_texture.width > 0 &&
      grandma_store_texture.height > 0) {
    u32 grandma_store_texture_size =
        (grandma_store_texture.pitch * grandma_store_texture.height + 15) & ~15;
    u32 *grandma_store_texture_rsx_mem =
        (u32 *)tiny3d_AllocTexture(grandma_store_texture_size);

    if (grandma_store_texture_rsx_mem) {
      memcpy(grandma_store_texture_rsx_mem, grandma_store_texture.bmp_out,
             grandma_store_texture.pitch * grandma_store_texture.height);

      grandma_store_texture_offset =
          tiny3d_TextureOffset(grandma_store_texture_rsx_mem);
    }
  }
}

void drawCookie(void) {

  float base_width = cookie_texture.width / 2.5;
  float base_height = cookie_texture.height / 2.5;

  float center_x = 15.0f + base_width / 2;
  float center_y = 180.0f + base_height / 2;

  float width = (float)cookie_texture.width / cookie_width;
  float height = (float)cookie_texture.height / cookie_height;

  float x = center_x - width / 2.0f;
  float y = center_y - height / 2.0f;

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

void drawShine(float angle) {
  float x = 120.0f;
  float y = 280.0f;

  float fullW = (float)shine_texture.width * 2.0f;
  float fullH = (float)shine_texture.height * 2.0f;
  float hw = fullW * 0.5f;
  float hh = fullH * 0.5f;

  float rad = angle;
  float c = cosf(rad);
  float s = sinf(rad);

  // local corners, rotated manually
  float x0 = (-hw * c) - (-hh * s);
  float y0 = (-hw * s) + (-hh * c);
  float x1 = (hw * c) - (-hh * s);
  float y1 = (hw * s) + (-hh * c);
  float x2 = (hw * c) - (hh * s);
  float y2 = (hw * s) + (hh * c);
  float x3 = (-hw * c) - (hh * s);
  float y3 = (-hw * s) + (hh * c);

  tiny3d_SetTexture(0, shine_texture_offset, shine_texture.width,
                    shine_texture.height, shine_texture.pitch,
                    TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);

  tiny3d_SetPolygon(TINY3D_QUADS);

  tiny3d_VertexPos(x + x0, y + y0, 0.0f);
  tiny3d_VertexColor(0xffffffff);
  tiny3d_VertexTexture(0.0f, 0.0f);

  tiny3d_VertexPos(x + x1, y + y1, 0.0f);
  tiny3d_VertexColor(0xffffffff);
  tiny3d_VertexTexture(0.99f, 0.0f);

  tiny3d_VertexPos(x + x2, y + y2, 0.0f);
  tiny3d_VertexColor(0xffffffff);
  tiny3d_VertexTexture(0.99f, 0.99f);

  tiny3d_VertexPos(x + x3, y + y3, 0.0f);
  tiny3d_VertexColor(0xffffffff);
  tiny3d_VertexTexture(0.0f, 0.99f);

  tiny3d_End();
}

void drawCursorButton() {
  u32 color;
  if (store_select == 0) {
    color = 0xffffffff;
  } else {
    color = 0x808080FF;
  }

  float x = 700.0f;
  float y = 80.0f;

  float width = (float)store_button_texture.width / 1.2;
  float height = (float)store_button_texture.height / 1.2;

  tiny3d_SetTexture(0, store_button_texture_offset, store_button_texture.width,
                    store_button_texture.height, store_button_texture.pitch,
                    TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);

  tiny3d_SetPolygon(TINY3D_QUADS);

  tiny3d_VertexPos(x, y, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(0.0f, 0.0f);

  tiny3d_VertexPos(x + width, y, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(1.0f, 0.0f);

  tiny3d_VertexPos(x + width, y + height, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(1.0f, 1.0f);

  tiny3d_VertexPos(x, y + height, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(0.0f, 1.0f);

  tiny3d_End();
  SetCurrentFont(0);
  SetFontSize(24, 28);
  if (store_select == 0) {
    SetFontColor(0xffffffff, 0x0);
  } else {
    SetFontColor(0xff000000, 0x0);
  }
  DrawString(753.0f, 81.0f, "Cursor");
  SetFontColor(0x34B233FF, 0x0);
  SetFontSize(12, 16);

  float price_icon_x = 753.0f;
  float price_icon_y = 112.0f;
  float price_icon_width = (float)small_cookie_texture.width / 22.0f;
  float price_icon_height = (float)small_cookie_texture.height / 22.0f;

  tiny3d_SetTexture(0, small_cookie_texture_offset, small_cookie_texture.width,
                    small_cookie_texture.height, small_cookie_texture.pitch,
                    TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);

  tiny3d_SetPolygon(TINY3D_QUADS);

  tiny3d_VertexPos(price_icon_x, price_icon_y, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(0.0f, 0.0f);

  tiny3d_VertexPos(price_icon_x + price_icon_width, price_icon_y, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(1.0f, 0.0f);

  tiny3d_VertexPos(price_icon_x + price_icon_width,
                   price_icon_y + price_icon_height, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(1.0f, 1.0f);

  tiny3d_VertexPos(price_icon_x, price_icon_y + price_icon_height, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(0.0f, 1.0f);

  tiny3d_End();

  if (cookies >= (long long)cursors_price) {
    SetFontColor(0x34B233FF, 0x0);
  } else {
    SetFontColor(0xff0000ff, 0x0);
  }
  DrawFormatString(price_icon_x + price_icon_width + 2.0f, 108.5f, "%lld",
                   (long long)cursors_price);

  SetFontColor(0x777777ff, 0x0);
  DrawFormatString(x + width - 30.0f, y + height - 20.0f, "%lld", cursors);

  float icon_x = 700.0f;
  float icon_y = 78.0f;

  float icon_width = (float)cursor_store_texture.width / 1.1;
  float icon_height = (float)cursor_store_texture.height / 1.1;

  tiny3d_SetTexture(0, cursor_store_texture_offset, cursor_store_texture.width,
                    cursor_store_texture.height, cursor_store_texture.pitch,
                    TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);

  tiny3d_SetPolygon(TINY3D_QUADS);

  tiny3d_VertexPos(icon_x, icon_y, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(0.0f, 0.0f);

  tiny3d_VertexPos(icon_x + icon_width, icon_y, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(1.0f, 0.0f);

  tiny3d_VertexPos(icon_x + icon_width, icon_y + icon_height, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(1.0f, 1.0f);

  tiny3d_VertexPos(icon_x, icon_y + icon_height, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(0.0f, 1.0f);

  tiny3d_End();
}

void drawGrandmaButton() {
  u32 color;
  if (store_select == 1) {
    color = 0xffffffff;
  } else {
    color = 0x808080FF;
  }

  float x = 700.0f;
  float y = 143.0f;

  float width = (float)store_button_texture.width / 1.2;
  float height = (float)store_button_texture.height / 1.2;

  tiny3d_SetTexture(0, store_button_texture_offset, store_button_texture.width,
                    store_button_texture.height, store_button_texture.pitch,
                    TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);

  tiny3d_SetPolygon(TINY3D_QUADS);

  tiny3d_VertexPos(x, y, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(0.0f, 0.0f);

  tiny3d_VertexPos(x + width, y, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(1.0f, 0.0f);

  tiny3d_VertexPos(x + width, y + height, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(1.0f, 1.0f);

  tiny3d_VertexPos(x, y + height, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(0.0f, 1.0f);

  tiny3d_End();
  SetCurrentFont(0);
  SetFontSize(24, 28);
  if (store_select == 1) {
    SetFontColor(0xffffffff, 0x0);
  } else {
    SetFontColor(0xff000000, 0x0);
  }
  DrawString(753.0f, 144.0f, "Grandma");
  SetFontColor(0x34B233FF, 0x0);
  SetFontSize(12, 16);

  float price_icon_x = 753.0f;
  float price_icon_y = 175.0f;
  float price_icon_width = (float)small_cookie_texture.width / 22.0f;
  float price_icon_height = (float)small_cookie_texture.height / 22.0f;

  tiny3d_SetTexture(0, small_cookie_texture_offset, small_cookie_texture.width,
                    small_cookie_texture.height, small_cookie_texture.pitch,
                    TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);

  tiny3d_SetPolygon(TINY3D_QUADS);

  tiny3d_VertexPos(price_icon_x, price_icon_y, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(0.0f, 0.0f);

  tiny3d_VertexPos(price_icon_x + price_icon_width, price_icon_y, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(1.0f, 0.0f);

  tiny3d_VertexPos(price_icon_x + price_icon_width,
                   price_icon_y + price_icon_height, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(1.0f, 1.0f);

  tiny3d_VertexPos(price_icon_x, price_icon_y + price_icon_height, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(0.0f, 1.0f);

  tiny3d_End();

  if (cookies >= (long long)grandmas_price) {
    SetFontColor(0x34B233FF, 0x0);
  } else {
    SetFontColor(0xff0000ff, 0x0);
  }
  DrawFormatString(price_icon_x + price_icon_width + 2.0f, 171.5f, "%lld",
                   (long long)grandmas_price);

  SetFontColor(0x777777ff, 0x0);
  DrawFormatString(x + width - 30.0f, y + height - 20.0f, "%lld", grandmas);

  float icon_x = 700.0f;
  float icon_y = 141.0f;

  float icon_width = (float)grandma_store_texture.width / 1.1;
  float icon_height = (float)grandma_store_texture.height / 1.1;

  tiny3d_SetTexture(0, grandma_store_texture_offset,
                    grandma_store_texture.width, grandma_store_texture.height,
                    grandma_store_texture.pitch, TINY3D_TEX_FORMAT_A8R8G8B8,
                    TEXTURE_LINEAR);

  tiny3d_SetPolygon(TINY3D_QUADS);

  tiny3d_VertexPos(icon_x, icon_y, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(0.0f, 0.0f);

  tiny3d_VertexPos(icon_x + icon_width, icon_y, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(1.0f, 0.0f);

  tiny3d_VertexPos(icon_x + icon_width, icon_y + icon_height, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(1.0f, 1.0f);

  tiny3d_VertexPos(icon_x, icon_y + icon_height, 0);
  tiny3d_VertexColor(color);
  tiny3d_VertexTexture(0.0f, 1.0f);

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

void drawBakeryName(void) {
  float text_y = 10.0f;
  float text_height = 30.0f;
  float screen_width = 1280.0f;
  float padding = 5.0f;

  float bg_x = 0.0f;
  float bg_y = text_y - padding + 8.0f;
  float bg_w = screen_width;
  float bg_h = text_height + (padding * 2) + 12.0f;

  tiny3d_SetPolygon(TINY3D_QUADS);

  tiny3d_SetTexture(0, gray_texture_offset, gray_texture.width,
                    gray_texture.height, gray_texture.pitch,
                    TINY3D_TEX_FORMAT_A8R8G8B8, TEXTURE_LINEAR);

  tiny3d_VertexPos(bg_x, bg_y, 0);
  tiny3d_VertexFcolor(0.5f, 0.5f, 0.5f, 0.5f);
  tiny3d_VertexTexture(0.0f, 0.0f);

  tiny3d_VertexPos(bg_x + bg_w, bg_y, 0);
  tiny3d_VertexFcolor(0.5f, 0.5f, 0.5f, 0.5f);
  tiny3d_VertexTexture(1.0f, 0.0f);

  tiny3d_VertexPos(bg_x + bg_w, bg_y + bg_h, 0);
  tiny3d_VertexFcolor(0.5f, 0.5f, 0.5f, 0.5f);
  tiny3d_VertexTexture(1.0f, 1.0f);

  tiny3d_VertexPos(bg_x, bg_y + bg_h, 0);
  tiny3d_VertexFcolor(0.5f, 0.5f, 0.5f, 0.5f);
  tiny3d_VertexTexture(0.0f, 1.0f);

  tiny3d_End();

  SetCurrentFont(0);
  SetFontSize(28, 42);
  SetFontColor(0xffffffff, 0x0);
  SetFontAutoCenter(1);
  DrawFormatString(70.0f, text_y, "%s", osk_input_text_utf8);
  SetFontAutoCenter(0);
}

void drawValue(void) {
  SetCurrentFont(0);
  SetFontSize(18, 32);
  SetFontColor(0xffffffff, 0x0);
  DrawFormatString(70.0f, 100.0f, "cookies: %lld", cookies);
  SetFontSize(10, 24);
  DrawFormatString(65.0f, 135.0f, "cookies per second: %.1f",
                   cookies_per_second);
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
  tiny3d_UserViewport(1, 0, 0, (float)(Video_Resolution.width / 916.0f),
                      (float)(Video_Resolution.height / 582.0f),
                      (float)(Video_Resolution.width / 1920.0f),
                      (float)(Video_Resolution.height / 1080.0f));
  initAudioSystem();
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

    cookies_per_second = (double)cursors * 0.1 + (double)grandmas * 1.0;
    static double cookies_fraction = 0.0;
    cookies_fraction += cookies_per_second / 60.0;
    if (cookies_fraction >= 1.0) {
      cookies += (long long)cookies_fraction;
      cookies_fraction -= (long long)cookies_fraction;
    }

    if (cookie_width > 2.5f && cookie_height > 2.5f) {
      cookie_height -= 0.05f;
      cookie_width -= 0.05f;
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
    drawShine(shine_angle);
    drawCookie();
    drawValue();
    drawBakeryName();
    drawCursorButton();
    drawGrandmaButton();
    drawFloatCookies();

    ioPadGetInfo(&padinfo);
    static u16 prev_cross = 0;
    static u16 prev_square = 0;
    static u16 prev_down = 0;
    static u16 prev_up = 0;
    for (int i = 0; i < MAX_PADS; i++) {
      if (padinfo.status[i]) {
        ioPadGetData(i, &paddata);

        if (paddata.len > 0) {
          u16 cur_cross = paddata.BTN_CROSS != 0;
          if (cur_cross && !prev_cross) {
            cookies++;
            switch (rand() % 7 + 1) {
            case 1:
              playSound(audio_click1_bin, audio_click1_bin_size);
              break;
            case 2:
              playSound(audio_click2_bin, audio_click2_bin_size);
              break;
            case 3:
              playSound(audio_click3_bin, audio_click3_bin_size);
              break;
            case 4:
              playSound(audio_click4_bin, audio_click4_bin_size);
              break;
            case 5:
              playSound(audio_click5_bin, audio_click5_bin_size);
              break;
            case 6:
              playSound(audio_click6_bin, audio_click6_bin_size);
              break;
            case 7:
              playSound(audio_click7_bin, audio_click7_bin_size);
              break;
            }
            cookie_width = 3.0f;
            cookie_height = 3.0f;
            float x =
                0.0f + ((float)rand() / (float)RAND_MAX) * (150.0f - 0.0f);
            float y =
                140.0f + ((float)rand() / (float)RAND_MAX) * (300.0f - 140.0f);
            spawnFloatCookie(x, y);
          }
          prev_cross = cur_cross;
          u16 cur_square = paddata.BTN_SQUARE != 0;
          if (cur_square && !prev_square) {
            switch (store_select) { // needs a sounds
            case 0: {
              if (cookies >= (long long)cursors_price) {
                cookies -= (long long)cursors_price;
                cursors++;
                cursors_price =
                    cursors_base_price * powf(1.15f, (float)cursors);

                switch (rand() % 4 + 1) {
                case 1:
                  playSound(audio_buy1_bin, audio_buy1_bin_size);
                  break;
                case 2:
                  playSound(audio_buy2_bin, audio_buy2_bin_size);
                  break;
                case 3:
                  playSound(audio_buy3_bin, audio_buy3_bin_size);
                  break;
                case 4:
                  playSound(audio_buy4_bin, audio_buy4_bin_size);
                  break;
                }
              }

            case 1: {
              if (cookies >= (long long)grandmas_price) {
                cookies -= (long long)grandmas_price;
                grandmas++;
                grandmas_price =
                    grandmas_base_price * powf(1.15f, (float)grandmas);

                switch (rand() % 4 + 1) {
                case 1:
                  playSound(audio_buy1_bin, audio_buy1_bin_size);
                  break;
                case 2:
                  playSound(audio_buy2_bin, audio_buy2_bin_size);
                  break;
                case 3:
                  playSound(audio_buy3_bin, audio_buy3_bin_size);
                  break;
                case 4:
                  playSound(audio_buy4_bin, audio_buy4_bin_size);
                  break;
                }
              }
            }

            break;
            }
            }
          }
          prev_square = cur_square;
          u16 cur_down = paddata.BTN_DOWN != 0;
          if (cur_down && !prev_down) {
            if (store_select < STORE_THINGS) {
              store_select++;
            }
          }
          prev_down = cur_down;
          u16 cur_up = paddata.BTN_UP != 0;
          if (cur_up && !prev_up) {
            if (store_select <= STORE_THINGS && store_select > 0) {
              store_select--;
            }
          }
          prev_up = cur_up;
        }
      }
    }
    updateFloatCookies();
    shine_angle += 0.009f;
    tiny3d_Flip();
  }
}
