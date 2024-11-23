#include "keycodes.h"
#include QMK_KEYBOARD_H
#include "os_detection.h"

#include "../macos_keymap_adapter.h"
#include "../qwerty_keymap_adapter.h"

enum CustomKeycodes {
    QSE_LUT = QK_KB_0,
    QSE_RUT,
	MSE_LUT,
	MSE_RUT
};

bool is_shift_active(uint8_t mods) {
	return (mods & MOD_MASK_SHIFT) != 0;
};

bool is_alt_active(uint8_t mods) {
	return (mods & MOD_MASK_ALT) != 0;
};

bool handle_custom_keycode(uint16_t kc, uint16_t kc_on_shift, uint16_t kc_on_alt){
	uint8_t mods = get_mods();
	bool is_shift = is_shift_active(mods);
	bool is_alt = is_alt_active(mods);

	clear_mods();

	if (is_shift && is_alt) {
		set_mods(mods);
		return true;
	} else if(is_shift) {
		tap_code16(kc_on_shift);
	} else if(is_alt) {
		tap_code16(kc_on_alt);
	} else {
		tap_code16(kc);
	}
	set_mods(mods);
	return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case QSE_LUT:
            if (record->event.pressed) {
				return handle_custom_keycode(
					QSE_LPRN,
					QSE_LBRC,
					QSE_LCBR
				);
			 }
            return false;
        case QSE_RUT:
            if (record->event.pressed) {
				return handle_custom_keycode(
					QSE_RPRN,
					QSE_RBRC,
					QSE_RCBR
				);
			 }
            return false;
		case MSE_LUT:
            if (record->event.pressed) {
				return handle_custom_keycode(
					MSE_LPRN,
					MSE_LBRC,
					MSE_LCBR
				);
			 }
            return false;
        case MSE_RUT:
            if (record->event.pressed) {
				return handle_custom_keycode(
					MSE_RPRN,
					MSE_RBRC,
					MSE_RCBR
				);
			 }
            return false;
	}
	return true;
};

enum Layers {
	QWERTY_BASE = 0,
	MACOS_BASE = 1,
	QWERTY_1 = 2,
	MACOS_1 = 3,
	QWERTY_2 = 4,
	MACOS_2 = 5,
};

bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            set_single_persistent_default_layer(MACOS_BASE);
            break;
        case OS_WINDOWS:
        case OS_LINUX:
        case OS_UNSURE:
		default:
            set_single_persistent_default_layer(QWERTY_BASE);
            break;
    }

    return false;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [QWERTY_BASE] = LAYOUT(
	KC_ESC,  QSE_1, QSE_2, QSE_3,    QSE_4,    QSE_5,                 	  		 QSE_6,  QSE_7,    QSE_8,    QSE_9,  QSE_0,     QSE_GRV,
	KC_TAB,  QSE_Q, QSE_W, QSE_E,    QSE_R,    QSE_T,                  	 		 QSE_Y,  QSE_U,    QSE_I,    QSE_O,  QSE_P,     QSE_ARNG,
	KC_LSFT, QSE_A, QSE_S, QSE_D,    QSE_F,    QSE_G,                   	  	 QSE_H,  QSE_J,    QSE_K,    QSE_L,  QSE_ODIA,  QSE_ADIA,
	KC_LCTL, QSE_Z, QSE_X, QSE_C,    QSE_V,    QSE_B,  QSE_LUT, QSE_RUT, QSE_N,  QSE_M,    QSE_COMM, QSE_DOT, QSE_MINS, XXXXXXX,
	                     		KC_LGUI, KC_LALT, KC_BSPC, KC_SPC,	KC_ENT,  MO(QWERTY_1), KC_RALT, KC_RGUI
      ),
      [QWERTY_1] = LAYOUT(
	KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	_______,  XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
    _______,   QSE_LABK,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  _______, _______, QSE_PLUS, QSE_MINS, QSE_EQL,  QSE_QUOT, QSE_DIAE, KC_BACKSLASH,
	                           _______, _______, MO(QWERTY_2),   _______, _______, _______, _______, _______
      ),
      [QWERTY_2] = LAYOUT(
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
	                           _______, _______, _______, _______, _______, _______, _______, _______
      ),
	  [MACOS_BASE] = LAYOUT(
	KC_ESC,  MSE_1, MSE_2, MSE_3,    MSE_4,    MSE_5,                 	  MSE_6,  MSE_7,    MSE_8,    MSE_9,  MSE_0,     MSE_GRV,
	KC_TAB,  MSE_Q, MSE_W, MSE_E,    MSE_R,    MSE_T,                  	  MSE_Y,  MSE_U,    MSE_I,    MSE_O,  MSE_P,     MSE_ARNG,
	KC_LSFT, MSE_A, MSE_S, MSE_D,    MSE_F,    MSE_G,                   	  MSE_H,  MSE_J,    MSE_K,    MSE_L,  MSE_ODIA,  MSE_ADIA,
	KC_LCTL, MSE_Z, MSE_X, MSE_C,    MSE_V,    MSE_B,   MSE_LUT, 	MSE_RUT, MSE_N,  MSE_M,    MSE_COMM, MSE_DOT, MSE_MINS, KC_RSFT,
	                     			KC_LGUI, KC_LALT, KC_BSPC, KC_SPC,	KC_ENT,  MO(MACOS_1), KC_RALT, KC_RGUI
      ),
      [MACOS_1] = LAYOUT(
	KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	_______,  XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
	_______,   QSE_LABK,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  _______, _______, MSE_PLUS, MSE_MINS, MSE_EQL,  MSE_QUOT, MSE_DIAE, KC_BACKSLASH,
	                           _______, _______, MO(MACOS_2),   _______, _______, _______, _______, _______
      ),
      [MACOS_2] = LAYOUT(
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
	                           _______, _______, _______, _______, _______, _______, _______, _______
      )
};



#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [QWERTY_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [QWERTY_1] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [QWERTY_2] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [QWERTY_3] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
	[MACOS_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [MACOS_1] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [MACOS_2] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [MACOS_3] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#endif

//TODO OS SPECIFIC KEYMAPS: https://qmk.github.io/qmk_docs_devel/#/feature_os_detection
//Swedish layout https://docs.qmk.fm/reference_keymap_extras
