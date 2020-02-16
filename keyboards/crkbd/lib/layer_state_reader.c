
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "crkbd.h"

// in the future, should use (1U<<_LAYER_NAME) instead, but needs to be moved to keymap,c
#define L_BASE 0x0
#define L_LOWER 0x4000
#define L_RAISE 0x8000
#define L_ADJUST 0x1C000
#define L_VI_NORMAL 0x10
#define L_VI_NORMAL_LOWER 0x4010
#define L_VI_NORMAL_RAISE 0x8010
#define L_VI_LOOP 0x30
#define L_VI_LOOP_RAISE 0x8030
#define L_VI_VISUAL 0x40
#define L_VI_DELETE 0x90
#define L_VI_YANK 0x110

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
    break;
  case L_RAISE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise");
    break;
  case L_LOWER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower");
    break;
  case L_VI_NORMAL:
  case L_VI_NORMAL_LOWER:
  case L_VI_NORMAL_RAISE:
  case L_VI_LOOP:
  case L_VI_LOOP_RAISE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Normal");
    break;
  case L_VI_VISUAL:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Visual");
    break;
  case L_VI_DELETE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Delete");
    break;
  case L_VI_YANK:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Yank");
    break;
  case L_ADJUST:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}
