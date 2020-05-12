/* -*- mode: c++ -*-
 * Kaleidoscope-HapticExpansion -- Haptic feedback
 * Copyright (C) 2019 Kodachi 6 14, LLC
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "HapticExpansion.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

namespace kaleidoscope {

// uint32_t HapticExpansion::start_time_;
// uint32_t HapticExpansion::end_time_;
// int HapticExpansion::pin_;

// duration is in ms
void HapticExpansion::on(uint32_t duration) {
  if (start_time_ == 0) {
    next_time_ = 0;
    start_time_ = millis();
    end_time_ = start_time_ + duration;
    digitalWrite(pin_, HIGH);

    // Macros.type(PSTR("Jar1 "));
  }
}

void HapticExpansion::off(void) {
  start_time_ = 0;
  end_time_ = 0;
  digitalWrite(pin_, LOW);

  next_time_ = millis() + 600000;

  // Macros.type(PSTR("Jar0 ")); 
}

EventHandlerResult HapticExpansion::onSetup(void) {
  pin_ = 21;
  pinMode(pin_, OUTPUT);
  off();

  return EventHandlerResult::OK;
}

EventHandlerResult HapticExpansion::beforeEachCycle(void) {
  if (end_time_ > 0) {
    if (millis() > end_time_) {
      off();
    }
  }
  else if (next_time_ > 0) {
    if (millis() > next_time_) {
      on(250);
    }
  }

  return EventHandlerResult::OK;
}

// EventHandlerResult HapticExpansion::onKeyswitchEvent(Key &mapped_key, byte row, byte col, uint8_t key_state) {

// }
}

kaleidoscope::HapticExpansion HapticExpansion;

