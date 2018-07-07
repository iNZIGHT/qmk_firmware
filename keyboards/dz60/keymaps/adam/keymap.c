#include "dz60.h"
#include "action_layer.h"
#define _______ KC_TRNS //readability

#define _DL 0 //default
#define _F1 1 //function 1
#define _F2 2 //function 2

#define RGB_STA RGB_M_P //rgb static
#define RGB_BRE RGB_M_B //rgb breathe
#define RGB_RAI RGB_M_R //rgb rainbow
#define RGB_SWI RGB_M_SW //rgb swirl
#define RGB_SNA RGB_M_SN //rgb snake
#define RGB_KNI RGB_M_K //rgb knight
#define RGB_GRA RGB_M_G //rgb gradient
#define RGB_XMA RGB_M_X //xmas mode


// How long (in ms) to wait between animation steps for the swirl mode
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {100, 50, 20};

// #define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_DL] = LAYOUT(
		KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_NO, KC_BSPC,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
		MO(_F1), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_NO,
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_RALT, MO(_F1), KC_NO, MO(_F2), KC_RCTL),

	[_F1] = LAYOUT( // function layer1
		KC_GRAVE,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12, _______, KC_DEL,
		_______, KC_MPLY, KC_MPRV, KC_MNXT  ,_______, _______, _______, KC_PGUP, KC_UP,   KC_PGDN, _______, _______, _______, _______,
		_______, MAGIC_SWAP_LALT_LGUI,      KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______,
		_______, _______, _______           ,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______           ,_______, KC_BTN1, KC_BTN1, KC_BTN2, KC_MS_L, _______, _______, _______),

	[_F2] = LAYOUT( // function layer 1
		_______, RGB_STA, RGB_BRE, RGB_RAI, RGB_SWI, RGB_SNA, RGB_GRA, RGB_M_X, _______, _______, _______, _______, _______, _______, KC_DEL,
		_______, RGB_TOG, RGB_SMOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, RESET,
		KC_CAPS, AG_NORM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, BL_DEC, BL_TOGG, BL_INC, BL_STEP, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
};



enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    
    switch(keycode){
        case MAGIC_SWAP_LALT_LGUI:
           if (record->event.pressed){
                if(!checkrgb()){
                
                    rgblight_toggle();
                    rgblight_setrgb(0xFF,0x00,0x00);
                    rgblight_toggle();
                    return true;
                }
               
                rgblight_setrgb(0xFF,0x00,0x00);
           }
            return true;
        case AG_NORM: 
           if (record->event.pressed){
                if(!checkrgb()){
                
                    rgblight_toggle();
                    rgblight_setrgb(0xFF,0x00,0x00);
                    rgblight_toggle();
                    return true;
                }
               
                rgblight_setrgb(0x00,0xFF,0x00);
           }
            return true; 
        default:
            return true;
    }
}
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
