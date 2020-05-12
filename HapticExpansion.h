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

#pragma once

#include <Kaleidoscope.h>

namespace kaleidoscope {

class HapticExpansion : public kaleidoscope::Plugin {
 public:
  HapticExpansion(void) {}

  void on(uint32_t duration);
  void off(void);

  EventHandlerResult onSetup(void);
  EventHandlerResult beforeEachCycle(void);
  // EventHandlerResult onKeyswitchEvent(Key &mapped_key, byte row, byte col, uint8_t key_state);

 private:
  uint32_t start_time_;
  uint32_t end_time_;
  uint32_t next_time_;
  int pin_;
};

}

extern kaleidoscope::HapticExpansion HapticExpansion;


