#include "keycodes.h"
#include "wpm.h"
#include QMK_KEYBOARD_H
#include "os_detection.h"

#include "../macos_keymap_adapter.h"
#include "../qwerty_keymap_adapter.h"

enum CustomKeycodes { QSE_LUT = QK_KB_0, QSE_RUT, MSE_LUT, MSE_RUT };

bool is_shift_active(uint8_t mods) {
    return (mods & MOD_MASK_SHIFT) != 0;
};

bool is_alt_active(uint8_t mods) {
    return (mods & MOD_MASK_ALT) != 0;
};

bool handle_custom_keycode(uint16_t kc, uint16_t kc_on_shift, uint16_t kc_on_alt) {
    uint8_t mods     = get_mods();
    bool    is_shift = is_shift_active(mods);
    bool    is_alt   = is_alt_active(mods);

    clear_mods();

    if (is_shift && is_alt) {
        set_mods(mods);
        return true;
    } else if (is_shift) {
        tap_code16(kc_on_shift);
    } else if (is_alt) {
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
                return handle_custom_keycode(QSE_LPRN, QSE_LBRC, QSE_LCBR);
            }
            return false;
        case QSE_RUT:
            if (record->event.pressed) {
                return handle_custom_keycode(QSE_RPRN, QSE_RBRC, QSE_RCBR);
            }
            return false;
        case MSE_LUT:
            if (record->event.pressed) {
                return handle_custom_keycode(MSE_LPRN, MSE_LBRC, MSE_LCBR);
            }
            return false;
        case MSE_RUT:
            if (record->event.pressed) {
                return handle_custom_keycode(MSE_RPRN, MSE_RBRC, MSE_RCBR);
            }
            return false;
    }
    return true;
};

enum Layers {
    QWERTY_BASE = 0,
    MACOS_BASE  = 1,
    QWERTY_1    = 2,
    MACOS_1     = 3,
    QWERTY_2    = 4,
    MACOS_2     = 5,
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

// clang-format off
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
// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [QWERTY_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)}, [QWERTY_1] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [QWERTY_2] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [QWERTY_3] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [MACOS_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)}, [MACOS_1] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [MACOS_2] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)}, [MACOS_3] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
};
#endif

// BONGO --------------------------
// Rotate OLED display
//

#ifdef OLED_ENABLE

// OLED setup
#    define IDLE_FRAMES 5
#    define IDLE_SPEED 10
#    define TAP_FRAMES 2
#    define TAP_SPEED 40
#    define ANIM_FRAME_DURATION 200
#    define ANIM_SIZE 512

bool     gui_on = true;
char     wpm_str[10];
uint32_t anim_timer         = 0;
uint32_t anim_sleep         = 0;
uint8_t  current_idle_frame = 0;
uint8_t  current_tap_frame  = 0;

static long int oled_timeout = 600000; // 10 minutes
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master())
        return OLED_ROTATION_180;
    else
        return rotation;
}

//
// Render left OLED display
//
static void render_status(void) {
    // WPM
    oled_write_P(PSTR("      "), false);
    sprintf(wpm_str, "%03d", get_current_wpm());
    oled_write(wpm_str, false);
    oled_write_P(PSTR("   WPM"), false);

    // GUI keys indicator
    if (gui_on)
        oled_write_P(PSTR("\n       "), false);
    else
        oled_write_P(PSTR("\n      GUI   OFF"), false);

    // Caps lock indicator
    led_t led_state = host_keyboard_led_state();

    // Layer indicator
    oled_write_P(PSTR("\nLAYER "), false);

    switch (get_highest_layer(layer_state)) {
        case QWERTY_BASE:
        case MACOS_BASE:
            oled_write_P(PSTR("\nBASE"), false);
            break;
        case QWERTY_1:
        case MACOS_1:
            oled_write_P(PSTR("\nUP"), false);
            break;
        case QWERTY_2:
        case MACOS_2:
            oled_write_P(PSTR("\nDOWN"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("\nN/A"), false);
    }

    // Host Keyboard LED Status
    oled_write_P(led_state.num_lock ? PSTR("\nNUM ") : PSTR("\n    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("\nCAP ") : PSTR("\n    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("\nSCR ") : PSTR("\n    "), false);
}

//
// Render right OLED display animation
//
static void render_anim(void) {
    // Idle animation
    static const char PROGMEM idle[IDLE_FRAMES][ANIM_SIZE] = {

        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,  0, 0, 0, 0, 0, 0, 0, 0, 128, 64, 64, 32, 32, 32, 32, 16, 16,  16, 16, 16, 8,  8,  4,  4, 4, 8, 48, 64, 128, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 100, 130, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 0, 48, 48, 0, 192, 193, 193, 194, 4, 8, 16, 32, 64, 128, 0, 0, 0, 128, 128, 128, 128, 64, 64, 64, 64, 32, 32, 32, 32, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 56, 4, 3, 0, 0, 0, 0, 0, 0, 0,   12, 12, 12, 13, 1,  0,  64, 160, 33, 34, 18, 17, 17, 17, 9, 8, 8, 8,  8,  4,   4, 8, 8, 16, 16, 16, 16, 16, 17, 15, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 128, 128, 64, 64, 64, 64, 64, 32, 32, 32, 32, 32, 16, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 3, 2,  2,   1,   1, 1, 1, 1, 1, 2, 2, 4, 4, 8, 8,   8,   8, 8, 7, 0, 0, 0, 0, 0, 0, 0,   0, 0,  0,  0, 0,   0,   0,   0,   0, 0, 0,  0,  0,  0,   0, 0, 0, 0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,  0, 0, 0, 0, 0, 0, 0, 0, 128, 64, 64, 32, 32, 32, 32, 16, 16,  16, 16, 16, 8,  8,  4,  4, 4, 8, 48, 64, 128, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 100, 130, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 0, 48, 48, 0, 192, 193, 193, 194, 4, 8, 16, 32, 64, 128, 0, 0, 0, 128, 128, 128, 128, 64, 64, 64, 64, 32, 32, 32, 32, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 56, 4, 3, 0, 0, 0, 0, 0, 0, 0,   12, 12, 12, 13, 1,  0,  64, 160, 33, 34, 18, 17, 17, 17, 9, 8, 8, 8,  8,  4,   4, 8, 8, 16, 16, 16, 16, 16, 17, 15, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 128, 128, 64, 64, 64, 64, 64, 32, 32, 32, 32, 32, 16, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 3, 2,  2,   1,   1, 1, 1, 1, 1, 2, 2, 4, 4, 8, 8,   8,   8, 8, 7, 0, 0, 0, 0, 0, 0, 0,   0, 0,  0,  0, 0,   0,   0,   0,   0, 0, 0,  0,  0,  0,   0, 0, 0, 0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,  0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 64, 64, 64, 64, 32, 32,  32, 32, 16, 8,  4,  2,  2,  4, 24, 96, 128, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 194, 1, 1, 2, 2, 4, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 96, 96, 0, 129, 130, 130, 132, 8, 16, 32, 64, 128, 0, 0, 0, 0, 128, 128, 128, 128, 64, 64, 64, 64, 32, 32, 32, 32, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 112, 25, 6, 0, 0, 0, 0, 0, 0, 0, 24,  24,  24, 27, 3,  0,  64, 160, 34, 36, 20, 18, 18, 18, 11, 8, 8,  8,  8,   5, 5, 9, 9, 16, 16, 16, 16, 16, 17, 15, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 128, 128, 64, 64, 64, 64, 64, 32, 32, 32, 32, 32, 16, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 3, 2,  2,   1, 1, 1, 1, 1, 1, 2, 2, 4, 4, 8, 8, 8, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0, 0,   0,   0,   0,   0, 0,  0,  0,  0,   0, 0, 0, 0, 0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,  128, 128, 0, 0, 0, 0, 0, 128, 64, 64, 32, 32, 32, 32, 16, 16,  16, 16, 8,  4,  2,  1,  1, 2, 12, 48, 64, 128, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 225, 0, 0, 1, 1, 2, 2, 1, 0, 0, 0, 0, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 0, 48, 48, 0, 192, 193, 193, 194, 4, 8, 16, 32, 64, 128, 0, 0, 0, 128, 128, 128, 128, 64, 64, 64, 64, 32, 32, 32, 32, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 112, 12, 3,   0,   0, 0, 0, 0, 0, 0,   12, 12, 12, 13, 1,  0,  64, 160, 33, 34, 18, 17, 17, 17, 9, 8, 8,  8,  8,  4,   4, 8, 8, 16, 16, 16, 16, 16, 17, 15, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 128, 128, 64, 64, 64, 64, 64, 32, 32, 32, 32, 32, 16, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 3, 2,  2,   1, 1, 1, 1, 1, 1, 2, 2, 4, 4, 8, 8,   8,   8, 8, 7, 0, 0, 0, 0, 0, 0, 0,   0, 0,  0,  0, 0,   0,   0,   0,   0, 0, 0,  0,  0,  0,   0, 0, 0, 0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,  0, 0, 0, 0, 0, 0, 0, 128, 64, 64, 32, 32, 32, 32, 16, 16,  16, 16, 8,  8,  4,  2,  2, 2, 4, 56, 64, 128, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 226, 1, 1, 2, 2, 2, 2, 1, 0, 0, 0, 0, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 0, 48, 48, 0, 192, 193, 193, 194, 4, 8, 16, 32, 64, 128, 0, 0, 0, 128, 128, 128, 128, 64, 64, 64, 64, 32, 32, 32, 32, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 112, 12, 3, 0, 0, 0, 0, 0, 0, 0,   12, 12, 12, 13, 1,  0,  64, 160, 33, 34, 18, 17, 17, 17, 9, 8, 8, 8,  8,  4,   4, 8, 8, 16, 16, 16, 16, 16, 17, 15, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 128, 128, 64, 64, 64, 64, 64, 32, 32, 32, 32, 32, 16, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 3, 2,  2,   1, 1, 1, 1, 1, 1, 2, 2, 4, 4, 8, 8,   8,   8, 8, 7, 0, 0, 0, 0, 0, 0, 0,   0, 0,  0,  0, 0,   0,   0,   0,   0, 0, 0,  0,  0,  0,   0, 0, 0, 0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

    };

    // Prep animation
    static const char PROGMEM prep[][ANIM_SIZE] = {

        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,  128, 128, 0, 0,  0, 0, 0,   128, 64,  64,  32,  32, 32, 32, 16, 16, 16, 16, 8,  4,  2,  1,  1, 2, 12, 48, 64, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 225, 0, 0, 1, 1, 2, 2, 129, 128, 128, 0, 0, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 0, 48, 48, 0, 0, 1, 225, 26, 6, 9, 49, 53, 1, 138, 124, 0, 0, 128, 128, 128, 128, 64, 64, 64, 64, 32, 32, 32, 32, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 112, 12, 3,   0,   0, 24, 6, 5, 152, 153, 132, 195, 124, 65, 65, 64, 64, 32, 33, 34, 18, 17, 17, 17, 9, 8, 8,  8,  8,  4,   4, 4, 4, 4, 4, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 128, 128, 64, 64, 64, 64, 64, 32, 32, 32, 32, 32, 16, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 3, 2,  2,   1, 1, 1, 1, 1, 1, 0,   0,   0,   0, 0, 0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0,  0,  0, 0, 0, 0,   0,  0, 0, 0,  0,  0, 0,   0,   0, 0, 0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

    };

    // Typing animation
    static const char PROGMEM tap[TAP_FRAMES][ANIM_SIZE] = {

        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,  128, 128, 0, 0,  0, 0, 0,   128, 64,  64, 32,  32, 32, 32, 16, 16, 16, 16, 8,  4,  2,  1,  1, 2, 12, 48, 64, 128, 0, 0, 0, 0,  0,  0,  0,  248, 248, 248, 248, 0,  0,   0,   0,   0,   128, 128, 0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 225, 0, 0, 1, 1, 2, 2, 129, 128, 128, 0, 0, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 0, 48, 48, 0, 0, 1, 1, 2, 4, 8, 16, 32, 67, 135, 7, 1, 0, 184, 188, 190, 159, 95, 95, 79, 76, 32, 32, 32, 32, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 112, 12, 3,   0,   0, 24, 6, 5, 152, 153, 132, 67, 124, 65, 65, 64, 64, 32, 33, 34, 18, 17, 17, 17, 9, 8, 8,  8,  8,  4,   4, 8, 8, 16, 16, 16, 16, 16,  17,  15,  1,   61, 124, 252, 252, 252, 252, 252, 60, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 128, 128, 64, 64, 64, 64, 64, 32, 32, 32, 32, 32, 16, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 3, 2,  2,   1, 1, 1, 1, 1, 1, 0,   0,   0,   0, 0, 0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0,  0,  0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,   0, 0, 0, 0,   0,   1,   3,   3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,  128, 128, 0, 0, 0, 0, 0, 128, 64, 64, 32, 32, 32, 32, 16, 16,  16, 16, 8,  4,  2,  1,  1, 2, 12, 48, 64, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30,  225, 0,   0,   1,   1,   2,  2,  1, 0, 0, 0, 0, 128, 128, 0,   0,   0,   0,   0, 0, 0, 0, 0, 128, 0, 48, 48, 0, 0, 1, 225, 26, 6, 9, 49, 53, 1, 138, 124, 0, 0, 128, 128, 128, 128, 64, 64, 64, 64, 32, 32, 32, 32, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 112, 12, 3,   0,   0, 0, 0, 0, 0, 0,   0,  0,  0,  1,  1,  0,  64, 160, 33, 34, 18, 17, 17, 17, 9, 8, 8,  8,  8,  4,   4, 4, 4, 4, 4, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 128, 128, 64, 64, 64, 64, 64, 32, 32, 32, 32, 32, 16, 16, 16, 16, 16, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 2, 3, 122, 122, 121, 121, 121, 121, 57, 49, 2, 2, 4, 4, 8, 8,   8,   136, 136, 135, 128, 0, 0, 0, 0, 0, 0,   0, 0,  0,  0, 0, 0, 0,   0,  0, 0, 0,  0,  0, 0,   0,   0, 0, 0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

    };

    void animation_phase(void) {
        if (get_current_wpm() <= IDLE_SPEED) {
            current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
            oled_write_raw_P(idle[abs((IDLE_FRAMES - 1) - current_idle_frame)], ANIM_SIZE);
        }

        if (get_current_wpm() > IDLE_SPEED && get_current_wpm() < TAP_SPEED) {
            oled_write_raw_P(prep[0], ANIM_SIZE);
        }

        if (get_current_wpm() >= TAP_SPEED) {
            current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
            oled_write_raw_P(tap[abs((TAP_FRAMES - 1) - current_tap_frame)], ANIM_SIZE);
        }
    }

    if (get_current_wpm() != 000) {
        oled_on();

        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }

        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > oled_timeout) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}

//
// OLED display rendering
//
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Left side
        render_status();
    } else {
        // Right side
        render_anim();
    }

    return 0;
}
void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 16; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
        } else {
            oled_write_P(PSTR("Rebooting "), false);
        }
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return false;
}
#endif

// TODO OS SPECIFIC KEYMAPS: https://qmk.github.io/qmk_docs_devel/#/feature_os_detection
// Swedish layout https://docs.qmk.fm/reference_keymap_extras
