#include <stdint.h>

#include "display.h"

void ascii_ctrl_bit_set(struct gpio *gpio, uint8_t x) {
  gpio->odr.l |= (B_SELECT | x);
}

void ascii_ctrl_bit_clear(struct gpio *gpio, uint8_t x) {
  gpio->odr.l &= ~x;
  gpio->odr.l |= B_SELECT;
}

void ascii_write_controller(struct gpio *gpio, struct systick *stk, uint8_t x) {
  uint16_t old_moderh = gpio->moders.h;
  gpio->moders.h = 0x5555;
  ascii_ctrl_bit_clear(gpio, B_RW);
  ascii_ctrl_bit_set(gpio, B_E);
  gpio->odr.h = x;
  ascii_ctrl_bit_clear(gpio, B_E);
  delay_250ns(stk);
  gpio->moders.h = old_moderh;
}

void ascii_write_cmd(struct gpio *gpio, struct systick *stk, uint8_t cmd) {
  ascii_ctrl_bit_clear(gpio, B_RS);
  ascii_write_controller(gpio, stk, cmd);
}

void ascii_write_data(struct gpio *gpio, struct systick *stk, uint8_t data) {
  ascii_ctrl_bit_set(gpio, B_RS);
  ascii_write_controller(gpio, stk, data);
}

uint8_t ascii_read_controller(struct gpio *gpio, struct systick *stk) {
  uint16_t old_moderh = gpio->moders.h;
  gpio->moders.h = 0x0000;
  ascii_ctrl_bit_set(gpio, B_RW);
  ascii_ctrl_bit_set(gpio, B_E);
  delay_250ns(stk);
  delay_250ns(stk);
  uint8_t rv = gpio->odr.h;
  ascii_ctrl_bit_clear(gpio, B_E);
  gpio->moders.h = old_moderh;
  return rv;
}

uint8_t ascii_read_status(struct gpio *gpio, struct systick *stk) {
  ascii_ctrl_bit_clear(gpio, B_RS);
  uint8_t c = ascii_read_controller(gpio, stk);
  return c;
}

uint8_t ascii_read_data(struct gpio *gpio, struct systick *stk) {
  ascii_ctrl_bit_set(gpio, B_RS);
  uint8_t c = ascii_read_controller(gpio, stk);
  return c;
}

void ascii_clear_display(struct gpio *gpio, struct systick *stk) {
  while (ascii_read_status(gpio, stk) & 0x80) {
    delay_micro(stk, 8);
    ascii_write_cmd(gpio, stk, 1);
    delay_milli(stk, 2);
  }
}

void ascii_function_set(struct gpio *gpio, struct systick *stk, int rows,
                        int fontsize) {
  uint8_t cmd = 0x30;
  uint8_t N = 8 * (rows - 1);
  uint8_t F = 4 * fontsize;
  ascii_write_cmd(gpio, stk, cmd | N | F);
}

void ascii_display_control(struct gpio *gpio, struct systick *stk, int on,
                           int marker, int blinking_marker) {
  uint8_t cmd = 0x8;
  uint8_t D = 4 * on;
  uint8_t C = 2 * marker;
  uint8_t B = 1 * blinking_marker;
  ascii_write_cmd(gpio, stk, cmd | B | C | D);
}

void ascii_entry_mode(struct gpio *gpio, struct systick *stk, int mode,
                      int shift) {
  uint8_t cmd = 0x4;
  uint8_t ID = 2 * mode;
  uint8_t SH = shift;
  ascii_write_cmd(gpio, stk, cmd | ID | SH);
}

void ascii_write_char(struct gpio *gpio, struct systick *stk, char c) {
  ascii_write_data(gpio, stk, c);
}
