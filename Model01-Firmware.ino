// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#define DEBUG_SERIAL false

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "flynn-0.1"
#endif


#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"
//#include "Kaleidoscope-Numlock.h"
#include "Kaleidoscope.h"
#include "key_defs.h"

#include "LED-Off.h"
#include "Kaleidoscope-LEDEffect-SolidColor.h"
#include "Kaleidoscope-LEDEffect-Breathe.h"
#include "Kaleidoscope-LEDEffect-Chase.h"
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LED-Stalker.h"
#include "Kaleidoscope-LED-AlphaSquare.h"
#include "Kaleidoscope-Model01-TestMode.h"

#define MACRO_VERSION_INFO 1
#define Macro_VersionInfo M(MACRO_VERSION_INFO)
#define MACRO_ANY 2
#define Macro_Any M(MACRO_ANY)

#define FLYNN KEYMAP_STACKED ( \
    ___,                  Key_1,                       Key_2,                   Key_3,                 Key_4,             Key_5,              Key_Tab,           \
    Key_Escape,           Key_Q,                       Key_W,                   Key_E,                 Key_R,             Key_T,              Key_RightBracket,  \
    Key_PageUp,           Key_A,                       Key_S,                   Key_D,                 Key_F,             Key_G,                                 \
    Key_PageDown,         Key_Z,                       Key_X,                   Key_C,                 Key_V,             Key_B,              Key_Backtick,      \
        Key_LeftGui, Key_Backspace, Key_LeftControl, Key_LeftShift,     \
            Key_KeymapNext_Momentary,     \
\
    Macro_Any,            Key_6,                       Key_7,                   Key_8,                 Key_9,             Key_0,              Key_Quote,        \
    Key_Enter,            Key_Y,                       Key_U,                   Key_I,                 Key_O,             Key_P,              Key_LeftBracket,  \
                          Key_H,                       Key_J,                   Key_K,                 Key_L,             Key_Semicolon,      Key_Backslash,    \
    Key_RightAlt,         Key_N,                       Key_M,                   Key_Comma,             Key_Period,        Key_Slash,          Key_RightShift,   \
        Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightGui,                        \
            Key_KeymapNext_Momentary      \
)

#define GENERIC_FN2  KEYMAP_STACKED ( \
Macro_VersionInfo,        Key_F1,                     Key_F2,                  Key_F3,                 Key_F4,            Key_F5,             Key_LEDEffectNext, \
Key_Tab,                  ___,                        Key_mouseUp,             ___,                    Key_mouseBtnR,     Key_mouseWarpEnd,   Key_mouseWarpNE,   \
Key_Home,                 Key_mouseL,                 Key_mouseDn,             Key_mouseR,             Key_mouseBtnL,     Key_mouseWarpNW,                       \
Key_End,                  Key_PrintScreen,            Key_Insert,              ___,                    Key_mouseBtnM,     Key_mouseWarpSW,    Key_mouseWarpSE,   \
    Key_LeftControl, Key_Delete, Key_LeftGui, Key_LeftShift,  \
        ___,   \
\
Consumer_VolumeIncrement, Key_F6,                     Key_F7,                  Key_F8,                 Key_F9,            Key_F10,            Key_F11,           \
Consumer_VolumeDecrement, ___,                        Key_UpArrow,             ___,                    Key_Minus,         Key_Equals,         Key_F12,           \
                          Key_LeftArrow,              Key_DownArrow,           Key_RightArrow,         LSHIFT(Key_Minus), LSHIFT(Key_Equals), ___,               \
Key_Menu,                 Consumer_ScanPreviousTrack, Consumer_PlaySlashPause, Consumer_ScanNextTrack, ___,               Key_Backslash,      Key_Pipe,          \
    Key_RightShift, Key_RightAlt, Key_Enter, Key_RightControl, \
        ___ \
)

const Key keymaps[][ROWS][COLS] PROGMEM = {
  FLYNN,
  GENERIC_FN2
};

static LEDSolidColor solidRed(160, 0, 0);
static LEDSolidColor solidOrange(140, 70, 0);
static LEDSolidColor solidYellow(130, 100, 0);
static LEDSolidColor solidGreen(0, 160, 0);
static LEDSolidColor solidBlue(0, 70, 130);
static LEDSolidColor solidIndigo(0, 0, 170);
static LEDSolidColor solidViolet(130, 0, 120);

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
//  if (macroIndex == TOGGLENUMLOCK && keyToggledOn(keyState)) {
//    return NumLock.toggle();
//  } else 
  if (macroIndex == 1 && keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  } else if (macroIndex == MACRO_ANY) {
    static Key lastKey;
    if (keyToggledOn(keyState))
      lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

    if (keyIsPressed(keyState))
      kaleidoscope::hid::pressKey(lastKey);
  }
  return MACRO_NONE;
}

void setup() {
  Kaleidoscope.setup(KEYMAP_SIZE);
  BootKeyboard.begin();
  Kaleidoscope.use(&TestMode,
                   &LEDControl, &LEDOff,
                   &LEDRainbowEffect, &LEDRainbowWaveEffect, &LEDChaseEffect,
                   &solidRed, &solidOrange, &solidYellow, &solidGreen, &solidBlue, &solidIndigo, &solidViolet,
                   &LEDBreatheEffect,
                   &AlphaSquareEffect,
                   &StalkerEffect,
//                   &NumLock,

                   &Macros,
                   &MouseKeys,
                   NULL);

//  NumLock.numPadLayer = NUMPAD_KEYMAP;
  AlphaSquare.color = { 255, 0, 0 };
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);
  StalkerEffect.variant = STALKER(BlazingTrail);
  LEDOff.activate();
}


void loop() {
  Kaleidoscope.loop();
}
