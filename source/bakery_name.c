#include "bakery_name.h"
#include <sys/memory.h>
#include <tiny3d.h>

volatile int osk_done;
u16 osk_input_text[256];
char osk_input_text_utf8[256] = "PS3 Bakery";

static void utf16_to_utf8(const u16 *src, char *dst) {
  int i;
  for (i = 0; src[i]; i++) {
    if ((src[i] & 0xFF80) == 0)
      *(dst++) = src[i] & 0xFF;
    else if ((src[i] & 0xF800) == 0) {
      *(dst++) = ((src[i] >> 6) & 0x1F) | 0xC0;
      *(dst++) = (src[i] & 0x3F) | 0x80;
    } else {
      *(dst++) = ((src[i] >> 12) & 0x0F) | 0xE0;
      *(dst++) = ((src[i] >> 6) & 0x3F) | 0x80;
      *(dst++) = (src[i] & 0x3F) | 0x80;
    }
  }
  *dst = 0;
}
static oskCallbackReturnParam osk_output;

static void osk_callback(u64 status, u64 param, void *userdata) {
  (void)param;
  (void)userdata;
  switch (status) {
  case SYSUTIL_OSK_INPUT_CANCELED:
    oskAbort();
    /* fall through */
  case SYSUTIL_OSK_DONE:
    oskUnloadAsync(&osk_output);
    break;
  case SYSUTIL_OSK_UNLOADED:
    osk_done = 1;
    break;
  }
}

void show_keyboard(void) {
  sys_mem_container_t container;
  sysMemContainerCreate(&container, 4 * 1024 * 1024);

  u16 title[] = {'B', 'a', 'k', 'e', 'r', 'y', ' ', 'n', 'a', 'm', 'e', 0};
  oskParam param = {0};
  oskInputFieldInfo info = {0};

  param.firstViewPanel = OSK_PANEL_TYPE_LATIN;
  param.allowedPanels = OSK_PANEL_TYPE_LATIN;
  param.prohibitFlags = OSK_PROHIBIT_RETURN | OSK_PROHIBIT_INPUT_ANALOG;

  info.message = title;
  info.startText = osk_input_text;
  info.maxLength = 255;

  osk_input_text[0] = 0;
  osk_output.res = OSK_OK;
  osk_output.len = 255;
  osk_output.str = osk_input_text;
  osk_done = 0;

  sysUtilRegisterCallback(0, osk_callback, NULL);
  oskSetInitialInputDevice(OSK_DEVICE_PAD);
  oskSetKeyLayoutOption(OSK_FULLKEY_PANEL);
  oskSetLayoutMode(OSK_LAYOUTMODE_HORIZONTAL_ALIGN_CENTER |
                   OSK_LAYOUTMODE_VERTICAL_ALIGN_CENTER);

  if (oskLoadAsync(container, &param, &info) != 0) {
    sysUtilUnregisterCallback(0);
    sysMemContainerDestroy(container);
    return;
  }

  while (!osk_done) {
    sysUtilCheckCallback();
    tiny3d_Flip();
  }

  utf16_to_utf8(osk_input_text, osk_input_text_utf8);

  sysUtilUnregisterCallback(0);
  sysMemContainerDestroy(container);
}
