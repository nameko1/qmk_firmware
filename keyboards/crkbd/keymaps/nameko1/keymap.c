#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _NORMAL 4
#define _VISUAL 5
#define _DELETE 6

leader_start()
LEADER_EXTERNS()
LEADER_DICTIONARY()

/* #define LOWER MO(_LOWER) */
/* #define RAISE MO(_RAISE) */
/* #define NORMAL TD(ETNTER_NORMAL_MODE) */
#define VISUAL TO(_VISUAL)
#define DELETE OSL(_DELETE)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  EX_NOML,
  LOWER,
  RAISE,
  ADJUST,
  PASTE,
  VI_UP,
  VI_DOWN,
  VI_LEFT,
  VI_RGHT,
  VI_YANK,
  WORD,
  EORD,
  BORD,
  UNDO,
  VI_WORD,
  VI_EORD,
  VI_BORD,
  BACKLIT,
  VI_DEL,
  NOTHING,
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
  JP_KANA,
  VI_REDO
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
      _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS,  KC_GRV,                      KC_MINS, KC_LBRC, KC_RBRC,  KC_EQL, KC_SCLN, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,  _______, _______ \
                                      //`--------------------------'  `--------------------------'
    ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, KC_TILD,                      KC_UNDS, KC_LCBR, KC_RCBR, KC_PLUS, KC_COLN, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       NORMAL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,  _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,  _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  // vi normal mode
  [_NORMAL] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX,    WORD,    EORD, XXXXXXX, XXXXXXX,                      XXXXXXX,    UNDO, EX_NOML, XXXXXXX,   PASTE, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX,  DELETE, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX,  KC_DEL, XXXXXXX,  VISUAL,    BORD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,  _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  // vi visual mode
  [_VISUAL] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, VI_WORD, VI_EORD, XXXXXXX, XXXXXXX,                      VI_YANK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  NORMAL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      VI_LEFT, VI_DOWN,   VI_UP, VI_RGHT, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  NORMAL, VI_BORD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,  _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  // vi delete layer
  [_DELETE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NOTHING,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX,  VI_DEL, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
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
const uint16_t PROGMEM jp_kana_combo[] = {KC_LCTL, KC_SCLN, COMBO_END};
/* const uint16_t PROGMEM vi_redo_combo[] = {KC_LCTL, KC_R, COMBO_END}; */

combo_t key_combos[COMBO_COUNT] = {
  [VI_ESC] = COMBO_ACTION(vi_esc_combo),
  [JP_KANA] = COMBO_ACTION(jp_kana_combo),
  /* [VI_REDO] = COMBO_ACTION(vi_redo_combo), */
};

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case VI_ESC:
      if (pressed) {
        tap_code16(LCTL(KC_LBRC));
      }
      break;
    case JP_KANA:
      if (pressed) {
        tap_code16(KC_LANG1);
      }
      break;
  /*   case VI_REDO: */
  /*     #<{(| if (pressed && IS_LAYER_ON(_NORMAL)) { |)}># */
  /*     if (pressed) { */
  /*       tap_code16(LSFT(LGUI(KC_Z))); */
  /*     } */
  /*     break; */
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

void matrix_scan_user(void) {
   iota_gfx_task();
}

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
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
      if (record->event.pressed) {
        tap_code16(LGUI(KC_C));
        tap_code16(KC_LEFT);
        layer_off(_VISUAL);
        layer_on(_NORMAL);
      }
      break;
    case UNDO:
      if (record->event.pressed) {
        tap_code16(LGUI(KC_Z));
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
    case EX_NOML:
        if (!record->event.pressed) {
          layer_off(_NORMAL);
        }
        return false;
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
          tap_code16(LGUI(KC_V));
      }
      break;
    case WORD:
    case EORD:
    case VI_WORD:
    case VI_EORD:
      if (record->event.pressed) {
        tap_code16(LALT(KC_RGHT));
        if (keycode == WORD) {
          tap_code16(KC_RGHT);
        }
      }
      break;
    case VI_BORD:
    case BORD:
      if (record->event.pressed) {
          tap_code16(LALT(KC_LEFT));
      }
      break;
    case VI_DEL:
      if (record->event.pressed) {
        tap_code16(LCTL(KC_A));
        tap_code16(LGUI(LSFT(KC_RGHT)));
        tap_code16(LCTL(KC_D));
        tap_code16(LCTL(KC_D));
      }
      break;
    case NOTHING:
      break;
  }
  return true;
}
