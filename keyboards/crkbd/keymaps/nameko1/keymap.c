#include QMK_KEYBOARD_H
#ifdef LEADER_ENABLE
  #include "leader.c"
#endif


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

bool shift_pressed;
bool control_pressed;
bool c_mode = false;
extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _NORMAL 4
#define _LOOP 5
#define _VISUAL 6
#define _DELETE 7
#define _YANK 8
#define _LOWER 14
#define _RAISE 15
#define _ADJUST 16

#define VISUAL TO(_VISUAL)
#define ALFRED register_code16(LCTL(KC_QUOT));unregister_code16(LCTL(KC_QUOT));

enum custom_keycodes {
  //layers
  QWERTY = SAFE_RANGE,
  INSERT,
  LOWER,
  RAISE,
  ADJUST,
  #ifndef TAP_DANCE_ENABLE
  L_NOML,
  #endif
  L_YANK,
  L_LOOP,
  //commands
  COPY,
  PASTE,
  CUT,
  VI_UP,
  VI_DOWN,
  VI_LEFT,
  VI_RGHT,
  VI_YANK,
  VI_SFT,
  VI_CTL,
  IN_LINE,
  WORD,
  EORD,
  BORD,
  VI_WORD,
  VI_EORD,
  VI_BORD,
  BACKLIT,
  NOTHING,
  ALF,
  /* RGBRST */
};

#ifdef TAP_DANCE_ENABLE
enum tap_dance_events {
  ETNTER_NORMAL_MODE
};
#endif

#ifdef COMBO_ENABLE
enum combo_events {
  VI_ESC,
  JP_KANA
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,  KC_ENT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          /* KC_LGUI,   LOWER,   MT_SS,     KC_ENT,  RAISE,  KC_RGUI \ */
                                          KC_LGUI,   LOWER,  MT_SS,      MT_SS,  RAISE,  KC_RGUI \
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS,  KC_GRV,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_SCLN, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,  _______, _______ \
                                      //`--------------------------'  `--------------------------'
    ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, KC_TILD,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_COLN, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX,     CUT,    COPY,   PASTE, XXXXXXX,                       L_NOML, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,  _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     ALF,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX,  L_NOML, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,  _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  // vi normal mode
  [_NORMAL] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX,    WORD,    EORD, XXXXXXX, XXXXXXX,                       L_YANK, _______, _______, _______,   PASTE, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       VI_CTL, _______, XXXXXXX, _______, _______, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, IN_LINE,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX,  KC_DEL, _______,  VISUAL,    BORD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  VI_SFT,     VI_SFT,  L_LOOP, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOOP] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX,    KC_W, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_Y, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX,    KC_D, XXXXXXX,    KC_G,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_B,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, XXXXXXX, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_YANK] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX,    KC_W, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_Y, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_G,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX,  KC_DEL, XXXXXXX, XXXXXXX,    KC_B,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,  _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  // vi visual mode
  [_VISUAL] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, VI_WORD, VI_EORD, XXXXXXX, XXXXXXX,                      VI_YANK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  L_NOML,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      VI_LEFT, VI_DOWN,   VI_UP, VI_RGHT, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX,  KC_DEL, XXXXXXX,  L_NOML, VI_BORD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,  _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  // vi delete layer
  [_DELETE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX,    KC_W, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX,    KC_I, XXXXXXX, XXXXXXX,  L_NOML,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX,    KC_D, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,  _______, _______ \
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef TAP_DANCE_ENABLE
//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
 [ETNTER_NORMAL_MODE]  = ACTION_TAP_DANCE_LAYER_MOVE(KC_N, _NORMAL)
};
#endif

#ifdef COMBO_ENABLE
typedef const uint16_t comb_keys_t[];
const uint16_t PROGMEM vi_esc_combo[] = {KC_LCTL, KC_BSPC, COMBO_END};
const uint16_t PROGMEM jp_kana_combo[] = {KC_LCTL, KC_ENT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [VI_ESC] = COMBO_ACTION(vi_esc_combo),
  [JP_KANA] = COMBO_ACTION(jp_kana_combo),
};

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case VI_ESC:
      if (pressed) {
        TAP_KEY(LCTL(KC_LBRC));
      }
      break;
    case JP_KANA:
      if (pressed) {
        TAP_KEY(KC_LANG1);
      }
      break;
  }
}
#endif


int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
  layer_on(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}


void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
      iota_gfx_init(!has_usb());   // turns on the display
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

#ifdef LEADER_ENABLE

void leader_end() {
  if (IS_LAYER_ON(_YANK)) {
    layer_off(_YANK);
  }
  if (IS_LAYER_ON(_DELETE)) {
    layer_off(_DELETE);
    if (c_mode) {
      c_mode = false;
      layer_off(_NORMAL);
    }
  }
  if (IS_LAYER_ON(_LOOP)) {
    layer_off(_LOOP);
  }
}

#define SELECT_WORD TAP_KEY(LALT(LSFT(KC_RGHT)))
#endif
void matrix_scan_user(void) {
  iota_gfx_task();

  #ifdef LEADER_ENABLE
  if (IS_LAYER_ON(_YANK)) {
    LEADER_DICTIONARY() {
      leading = false;
      leader_end();
      SEQ_ONE_KEY(KC_W) {
        TAP_KEY(LALT(LSFT(KC_RGHT)))
        TAP_COPY
        TAP_KEY(KC_LEFT)
      }
      SEQ_ONE_KEY(KC_Y) {
        yank_some_lines(1);
      }
      SEQ_ONE_KEY(LSFT(KC_G)) {
        TAP_HOME
        TAP_KEY(LSFT(LGUI(KC_DOWN)))
        TAP_COPY
        TAP_KEY(KC_LEFT)
      }
      SEQ_TWO_KEYS(KC_G, KC_G) {
        TAP_END
        TAP_KEY(LSFT(LGUI(KC_UP)))
        TAP_COPY
        TAP_KEY(KC_RGHT)
      }
      SEQ_ONE_KEY(KC_B) {
        TAP_KEY(LALT(LSFT(KC_LEFT)))
        TAP_COPY
        TAP_KEY(KC_RGHT)
      }
    }
  }
  if (IS_LAYER_ON(_DELETE)) {
    LEADER_DICTIONARY() {
      leading = false;
      leader_end();
      SEQ_ONE_KEY(KC_D) {
        if (!c_mode) {
          delete_some_lines(1);
        }
      }
      SEQ_ONE_KEY(KC_W) {
        TAP_KEY(LSFT(LALT(KC_RGHT)))
        TAP_KEY(KC_DEL)
      }
      SEQ_TWO_KEYS(KC_I, KC_W) {
        TAP_KEY(LALT(KC_LEFT))
        TAP_KEY(LSFT(LALT(KC_RGHT)))
        TAP_KEY(KC_DEL)
      }
    }
  }
  if (IS_LAYER_ON(_LOOP)) {
    LEADER_DICTIONARY() {
      leading = false;
      leader_end();
      SEQ_ONE_KEY(KC_0) {
        TAP_HOME
      }
      SEQ_DIGIT_TWO_KEYS(KC_Y, KC_Y) {
        yank_some_lines(KC_TO_NUM(leader_sequence[0]));
      }
      SEQ_DIGIT_TWO_KEYS(KC_D, KC_D) {
        delete_some_lines(KC_TO_NUM(leader_sequence[0]));
      }
    }
  }
  #endif  //LEADER_ENABLE
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  if (IS_LAYER_ON(_NORMAL)) {
    switch (keycode) {
      case KC_I:
        if (record->event.pressed) {
          if (shift_pressed) { TAP_KEY(LGUI(KC_RGHT)) }
          if (IS_LAYER_ON(_DELETE)) { return true;}
          layer_off(_NORMAL);
        }
        return false;
      case KC_U:
        if (record->event.pressed) {
          if (control_pressed) {
            TAP_KEY(KC_PGUP)
          } else {
            TAP_KEY(LGUI(KC_Z))
          }
        }
        return false;
      case KC_O:
        if (record->event.pressed) {
          if (shift_pressed) {
            TAP_KEY(KC_UP)
            TAP_KEY(LGUI(KC_RGHT))
            TAP_KEY(KC_ENT)
          } else {
            TAP_KEY(KC_DOWN)
            TAP_KEY(LGUI(KC_LEFT))
            TAP_KEY(KC_ENT)
            TAP_KEY(KC_UP)
          }
          layer_off(_NORMAL);
        }
        return false;
      case KC_A:
        if (record->event.pressed) {
          if (shift_pressed) {
            TAP_KEY(LGUI(KC_LEFT))
          } else {
            TAP_KEY(KC_RIGHT)
          }
          layer_off(_NORMAL);
        }
        return false;
      case KC_D:
      case KC_C:
        if (IS_LAYER_ON(_DELETE) || IS_LAYER_ON(_LOOP)) {
          return true;
        }
        if (record->event.pressed) {
          if (control_pressed) {
            TAP_KEY(KC_PGDN)
          } else {
            if (keycode == KC_C) {c_mode = true;}
            layer_on(_DELETE);
            qk_leader_start();
            return false;
          }
        }
        break;
      case KC_F:
        if (record->event.pressed) {
          if (control_pressed) {
            TAP_KEY(KC_PGDN)
          }
        }
        return false;
      case KC_DOWN:
        if (record->event.pressed) {
          if (shift_pressed) {
            TAP_END
            TAP_KEY(KC_SPC)
            TAP_KEY(KC_DEL)
            return false;
          }
        }
        return true;
      case KC_DLR:
        if (record->event.pressed) {
          TAP_KEY(LGUI(KC_RGHT))
        }
        return false;
    }
  }
  if (IS_LAYER_ON(_VISUAL)) {
    switch (keycode) {
      case KC_0:
        if (record->event.pressed) {
          TAP_KEY(SGUI(KC_LEFT))
        }
        return false;
      case KC_DLR:
        if (record->event.pressed) {
          TAP_KEY(SGUI(KC_RGHT))
        }
        return false;
    }
  }

  switch (keycode) {
    case ALF:
      if (record->event.pressed) {
        ALFRED
        TAP_KEY(KC_T)
        TAP_KEY(KC_I)
        TAP_KEY(KC_ENT)
      }
        break;
    case VI_UP:
      if (record->event.pressed) {
        register_code16(LSFT(KC_UP));
      } else {
        unregister_code16(LSFT(KC_UP));
      }
        break;
    case VI_DOWN:
      if (record->event.pressed) {
        register_code16(LSFT(KC_DOWN));
      } else {
        unregister_code16(LSFT(KC_DOWN));
      }
      break;
    case VI_LEFT:
      if (record->event.pressed) {
        register_code16(LSFT(KC_LEFT));
      } else {
        unregister_code16(LSFT(KC_LEFT));
      }
      break;
    case VI_RGHT:
      if (record->event.pressed) {
        register_code16(LSFT(KC_RGHT));
      } else {
        unregister_code16(LSFT(KC_RGHT));
      }
      break;
    case VI_YANK:
    case COPY:
      if (record->event.pressed) {
        tap_code16(LGUI(KC_C));
        if (keycode == VI_YANK) {
          tap_code16(KC_LEFT);
          layer_off(_VISUAL);
          layer_on(_NORMAL);
        }
      }
      break;
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    #ifndef TAP_DANCE_ENABLE
    case L_NOML:
      if (record->event.pressed) {
        layer_on(_NORMAL);
        if (IS_LAYER_ON(_VISUAL)) {
          layer_off(_VISUAL);
        }
        if (IS_LAYER_ON(_DELETE)) {
          layer_off(_DELETE);
        }
      }
      return false;
    #endif
    case L_LOOP:
      if (record->event.pressed) {
        layer_on(_RAISE);
        layer_on(_LOOP);
        qk_leader_start();
      }
      if (!record->event.pressed) {
        layer_off(_RAISE);
      }
      return false;
    case L_YANK:
      if (record->event.pressed) {
        layer_on(_YANK);
        qk_leader_start();
      }
      return false;
    case INSERT:
      if (record->event.pressed) {
        layer_off(_NORMAL);
      }
      return false;
    case IN_LINE:
      if (record->event.pressed) {
        TAP_KEY(LGUI(KC_RGHT))
        TAP_KEY(KC_ENT)
      }
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    /* case RGBRST: */
    /*   #ifdef RGBLIGHT_ENABLE */
    /*     if (record->event.pressed) { */
    /*       eeconfig_update_rgblight_default(); */
    /*       rgblight_enable(); */
    /*       RGB_current_mode = rgblight_config.mode; */
    /*     } */
    /*   #endif */
    /*   break; */
    case PASTE:
      if (record->event.pressed) {
          TAP_KEY(LGUI(KC_V));
      }
      break;
    case CUT:
      if (record->event.pressed) {
          TAP_KEY(LGUI(KC_X));
      }
      break;
    case VI_WORD:
    case VI_EORD:
      if (record->event.pressed) {
        TAP_KEY(LALT(LSFT(KC_RGHT)));
        if (keycode == VI_WORD) {
          TAP_KEY(LALT(LSFT(KC_RGHT)));
          TAP_KEY(LALT(LSFT(KC_LEFT)));
          TAP_KEY(LSFT(KC_LEFT));
        }
      }
      break;
    case WORD:
    case EORD:
      if (record->event.pressed) {
        TAP_KEY(LALT(KC_RGHT));
        if (keycode == WORD) {
          TAP_KEY(LALT(KC_RGHT));
          TAP_KEY(LALT(KC_LEFT));
        }
      }
      break;
    case VI_BORD:
    case BORD:
      if (record->event.pressed) {
          TAP_KEY(LALT(KC_LEFT));
      }
      break;
    case VI_SFT:
      if (record->event.pressed) {
        shift_pressed=true;
      } else {
        shift_pressed=false;
      }
      break;
    case VI_CTL:
      if (record->event.pressed) {
        control_pressed=true;
      } else {
        control_pressed=false;
      }
      break;
    case NOTHING:
      break;
  }
  return true;
}
