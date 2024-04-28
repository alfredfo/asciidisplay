#pragma once

#include <stdint.h>

struct gpio {
  union {
    struct {
      uint16_t l;
      uint16_t h;
    } moders;
    uint32_t moder;
  };
  union {
    uint16_t otyper;
    uint32_t _otyper_full;
  };
  uint32_t ospeedr;
  uint32_t pupdr;
  union {
    uint16_t idr;
    uint32_t _idr_full;
  };
  union {
    struct {
      uint8_t l;
      uint8_t h;
    } odr;
    uint32_t _odr_full;
  };
  uint32_t bsrr;
  uint32_t lckr;
  uint32_t afrl;
  uint32_t afrh;
};
