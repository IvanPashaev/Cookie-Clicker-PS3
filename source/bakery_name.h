#ifndef BAKERY_NAME_H
#define BAKERY_NAME_H

#include <ppu-types.h>
#include <sysutil/osk.h>
#include <sysutil/sysutil.h>

extern volatile int osk_done;
extern u16 osk_input_text[256];
extern char osk_input_text_utf8[256];

void show_keyboard(void);

#endif
