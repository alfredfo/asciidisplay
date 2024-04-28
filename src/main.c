#include "board-constants.h"
#include "display.h"
#include "gpio.h"
#include "systick.h"

int main() {
  struct gpio *gpio_e = (struct gpio *)GPIO_E_ADDR;
  struct systick *stk = (struct systick *)SYSTICK_ADDR;

  gpio_e->moders.l = 0x5555;
  // gpio_e->odr.l = 0x00;
  delay_250ns(stk);
  // delay_micro(stk, 10);
  gpio_e->odr.l = 0xFF;
  //  func set
  //  ascii_function_set(gpio_e, stk, 2, 1);
  //  display control
  //  ascii_display_control(gpio_e, stk, 1, 1, 1);
  //  clear display
  //  ascii_clear_display(gpio_e, stk);
  //  entry mode
  //  ascii_entry_mode(gpio_e, stk, 1, 0);

  // ascii_write_char(gpio_e, stk, 'a');
  delay_milli(stk, 1);
  gpio_e->odr.l = 0x00;
  delay_milli(stk, 10);
  gpio_e->odr.l = 0xF0;
  return 0;
}
