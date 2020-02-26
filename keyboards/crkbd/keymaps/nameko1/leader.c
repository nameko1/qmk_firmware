LEADER_EXTERNS();

bool is_number(uint16_t keycode);
uint16_t keycode_to_number(uint16_t keycode);
void loop(uint16_t index, uint16_t keycode);

#define IS_NUM(kc) is_number(kc)
#define KC_TO_NUM(kc) keycode_to_number(kc)
#define SEQ_DIGIT_ONE_KEY(key1) if (IS_NUM(leader_sequence[0]) && leader_sequence[1] == (key1) && leader_sequence[2] == 0 && leader_sequence[3] == 0 && leader_sequence[4] == 0)
#define SEQ_TWO_DIGITS_ONE_KEY(key1) if (IS_NUM(leader_sequence[0]) && IS_NUM(leader_sequence[1]) && leader_sequence[2] == (key1) && leader_sequence[3] == 0 && leader_sequence[4] == 0)
#define SEQ_DIGIT_TWO_KEYS(key1, key2) if (IS_NUM(leader_sequence[0]) && leader_sequence[1] == (key1) && leader_sequence[2] == (key2) && leader_sequence[3] == 0 && leader_sequence[4] == 0)
#define SEQ_TWO_DIGITS_TWO_KEYS(key1, key2) if (IS_NUM(leader_sequence[0]) && IS_NUM(leader_sequence[1]) && leader_sequence[2] == (key1) && leader_sequence[3] == (key2) && leader_sequence[4] == 0)

bool is_number(uint16_t keycode) {
    if ((keycode >> 1 ^ 0x0F) == 0) {
      return true;
    }
    if ((keycode >> 3 ^ 0x04) == 0) {
      return true;
    }
      return false;
}

uint16_t keycode_to_number(uint16_t keycode) {
  if (!is_number(keycode)) {
    return -1;
  }
  uint16_t num;

  num = keycode - 0x1D;
  if (num == 0x0A) {
    return 0;
  }
  return num;
}

void yank_some_lines(uint16_t num) {
  TAP_HOME
  TAP_KEY(LALT(LSFT(KC_DOWN)))
  for (int i = 1; i < num; i++) {
    TAP_KEY(LSFT(KC_DOWN))
  }
  TAP_COPY
  TAP_KEY(KC_LEFT)
}

void delete_some_lines(uint16_t num) {
  TAP_HOME
  TAP_KEY(LALT(LSFT(KC_DOWN)))
  for (int i = 1; i < num; i++) {
    TAP_KEY(LSFT(KC_DOWN))
  }
  TAP_CUT
}
