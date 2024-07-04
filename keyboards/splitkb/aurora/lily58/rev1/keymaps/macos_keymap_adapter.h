// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/*******************************************************************************
  88888888888 888      d8b                .d888 d8b 888               d8b
      888     888      Y8P               d88P"  Y8P 888               Y8P
      888     888                        888        888
      888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
      888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
      888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
      888     888  888 888      X88      888    888 888 Y8b.          888      X88
      888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
                                                        888                 888
                                                        888                 888
                                                        888                 888
     .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
    d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
    888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
    Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
     "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
         888
    Y8b d88P
     "Y88P"
*******************************************************************************/

#pragma once
#include "keycodes.h"
// clang-format off

// Aliases
#define MSE_SECT KC_GRV  // §
#define MSE_1    KC_1    // 1
#define MSE_2    KC_2    // 2
#define MSE_3    KC_3    // 3
#define MSE_4    KC_4    // 4
#define MSE_5    KC_5    // 5
#define MSE_6    KC_6    // 6
#define MSE_7    KC_7    // 7
#define MSE_8    KC_8    // 8
#define MSE_9    KC_9    // 9
#define MSE_0    KC_0    // 0
#define MSE_PLUS KC_MINS // +
#define MSE_ACUT KC_EQL  // ´ (dead)
#define MSE_Q    KC_Q    // Q
#define MSE_W    KC_W    // W
#define MSE_E    KC_E    // E
#define MSE_R    KC_R    // R
#define MSE_T    KC_T    // T
#define MSE_Y    KC_Y    // Y
#define MSE_U    KC_U    // U
#define MSE_I    KC_I    // I
#define MSE_O    KC_O    // O
#define MSE_P    KC_P    // P
#define MSE_ARNG KC_LBRC // Å
#define MSE_DIAE KC_RBRC // ¨ (dead)
#define MSE_A    KC_A    // A
#define MSE_S    KC_S    // S
#define MSE_D    KC_D    // D
#define MSE_F    KC_F    // F
#define MSE_G    KC_G    // G
#define MSE_H    KC_H    // H
#define MSE_J    KC_J    // J
#define MSE_K    KC_K    // K
#define MSE_L    KC_L    // L
#define MSE_ODIA KC_SCLN // Ö
#define MSE_ADIA KC_QUOT // Ä
#define MSE_QUOT KC_NUHS // '
#define MSE_LABK KC_NUBS // <
#define MSE_Z    KC_Z    // Z
#define MSE_X    KC_X    // X
#define MSE_C    KC_C    // C
#define MSE_V    KC_V    // V
#define MSE_B    KC_B    // B
#define MSE_N    KC_N    // N
#define MSE_M    KC_M    // M
#define MSE_COMM KC_COMM // ,
#define MSE_DOT  KC_DOT  // .
#define MSE_MINS KC_SLSH // -
#define MSE_DEG  S(MSE_SECT) // °
#define MSE_EXLM S(MSE_1)    // !
#define MSE_DQUO S(MSE_2)    // "
#define MSE_HASH S(MSE_3)    // #
#define MSE_EURO S(MSE_4)    // €
#define MSE_PERC S(MSE_5)    // %
#define MSE_AMPR S(MSE_6)    // &
#define MSE_SLSH S(MSE_7)    // /
#define MSE_LPRN S(MSE_8)    // (
#define MSE_RPRN S(MSE_9)    // )
#define MSE_EQL  S(MSE_0)    // =
#define MSE_QUES S(MSE_PLUS) // ?
#define MSE_GRV  S(MSE_ACUT) // `
#define MSE_CIRC S(MSE_DIAE) // ^ (dead)
#define MSE_ASTR S(MSE_QUOT) // *
#define MSE_RABK S(MSE_LABK) // >
#define MSE_SCLN S(MSE_COMM) // ;
#define MSE_COLN S(MSE_DOT)  // :
#define MSE_UNDS S(MSE_MINS) // _
#define MSE_PILC A(MSE_SECT) // ¶
#define MSE_COPY A(MSE_1)    // ©
#define MSE_TM   A(MSE_2)    // ™
#define MSE_PND  A(MSE_3)    // £
#define MSE_DLR  A(MSE_4)    // $
#define MSE_INFN A(MSE_5)    // ∞
#define MSE_PIPE A(MSE_7)    // |
#define MSE_LBRC A(MSE_8)    // [
#define MSE_RBRC A(MSE_9)    // ]
#define MSE_AEQL A(MSE_0)    // ≈
#define MSE_PLMN A(MSE_PLUS) // ±
#define MSE_BULT A(MSE_Q)    // •
#define MSE_OMEG A(MSE_W)    // Ω
#define MSE_EACU A(MSE_E)    // É
#define MSE_REGD A(MSE_R)    // ®
#define MSE_DAGG A(MSE_T)    // †
#define MSE_MICR A(MSE_Y)    // µ
#define MSE_UDIA A(MSE_U)    // Ü
#define MSE_DLSI A(MSE_I)    // ı
#define MSE_OE   A(MSE_O)    // Œ
#define MSE_PI   A(MSE_P)    // π
#define MSE_DOTA A(MSE_ARNG) // ˙
#define MSE_TILD A(MSE_DIAE) // ~ (dead)
#define MSE_APPL A(MSE_A)    //  (Apple logo)
#define MSE_SS   A(MSE_S)    // ß
#define MSE_PDIF A(MSE_D)    // ∂
#define MSE_FHK  A(MSE_F)    // ƒ
#define MSE_CEDL A(MSE_G)    // ¸
#define MSE_OGON A(MSE_H)    // ˛
#define MSE_SQRT A(MSE_J)    // √
#define MSE_FORD A(MSE_K)    // ª
#define MSE_FI   A(MSE_L)    // ﬁ
#define MSE_OSTR A(MSE_ODIA) // Ø
#define MSE_AE   A(MSE_ADIA) // Æ
#define MSE_AT   A(MSE_QUOT) // @
#define MSE_LTEQ A(MSE_LABK) // ≤
#define MSE_DIV  A(MSE_Z)    // ÷
#define MSE_CCED A(MSE_C)    // Ç
#define MSE_LSAQ A(MSE_V)    // ‹
#define MSE_RSAQ A(MSE_B)    // ›
#define MSE_LSQU A(MSE_N)    // ‘
#define MSE_RSQU A(MSE_M)    // ’
#define MSE_SLQU A(MSE_COMM) // ‚
#define MSE_ELLP A(MSE_DOT)  // …
#define MSE_NDSH A(MSE_MINS) // –
#define MSE_IEXL S(A(MSE_1))    // ¡
#define MSE_YEN  S(A(MSE_3))    // ¥
#define MSE_CENT S(A(MSE_4))    // ¢
#define MSE_PERM S(A(MSE_5))    // ‰
#define MSE_BSLS S(A(MSE_7))    // (backslash)
#define MSE_LCBR S(A(MSE_8))    // {
#define MSE_RCBR S(A(MSE_9))    // }
#define MSE_NEQL S(A(MSE_0))    // ≠
#define MSE_IQUE S(A(MSE_PLUS)) // ¿
#define MSE_DACU S(A(MSE_W))    // ˝
#define MSE_DDAG S(A(MSE_T))    // ‡
#define MSE_STIL S(A(MSE_Y))    // ˜
#define MSE_DCIR S(A(MSE_I))    // ˆ
#define MSE_NARP S(A(MSE_P))    // ∏
#define MSE_RNGA S(A(MSE_ARNG)) // ˚
#define MSE_LOZN S(A(MSE_A))    // ◊
#define MSE_NARS S(A(MSE_S))    // ∑
#define MSE_INCR S(A(MSE_D))    // ∆
#define MSE_INTG S(A(MSE_F))    // ∫
#define MSE_MACR S(A(MSE_G))    // ¯
#define MSE_BREV S(A(MSE_H))    // ˘
#define MSE_NOT  S(A(MSE_J))    // ¬
#define MSE_MORD S(A(MSE_K))    // º
#define MSE_FL   S(A(MSE_L))    // ﬂ
#define MSE_GTEQ S(A(MSE_LABK)) // ≥
#define MSE_FRSL S(A(MSE_Z))    // ⁄
#define MSE_CARN S(A(MSE_X))    // ˇ
#define MSE_LDAQ S(A(MSE_V))    // «
#define MSE_RDAQ S(A(MSE_B))    // »
#define MSE_LDQU S(A(MSE_N))    // “
#define MSE_RDQU S(A(MSE_M))    // ”
#define MSE_DLQU S(A(MSE_COMM)) // „
#define MSE_MDDT S(A(MSE_DOT))  // ·
#define MSE_MDSH S(A(MSE_MINS)) // —

