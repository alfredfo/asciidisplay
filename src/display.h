#pragma once

#include <stdint.h>

#include "gpio.h"
#include "systick.h"

enum { B_RS = 1, B_RW = 2, B_SELECT = 4, B_E = 0x40 };

void ascii_clear_display(struct gpio *, struct systick *);
void ascii_function_set(struct gpio *, struct systick *, int, int);
void ascii_display_control(struct gpio *, struct systick *, int, int, int);
void ascii_entry_mode(struct gpio *, struct systick *, int, int);
void ascii_write_char(struct gpio *, struct systick *, char);
