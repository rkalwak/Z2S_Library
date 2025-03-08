/*
 Copyright (C) AC SOFTWARE SP. Z O.O.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef Z2S_VIRTUAL_BINARY_H_
#define Z2S_VIRTUAL_BINARY_H_

#include <supla/sensor/virtual_binary.h>

#define MSINHOUR 60*60*1000

namespace Supla {
namespace Sensor {
class Z2S_VirtualBinary : public Supla::Sensor::VirtualBinary {
  
public:
    
  Z2S_VirtualBinary(bool keepStateInStorage = false, uint8_t timeout = 0) : VirtualBinary(keepStateInStorage), _timeout(timeout) {}

  void setTimeout(uint8_t timeout) {
    
    _timeout = timeout;
  }

  void Refresh() {
    _timeout_ms = millis();
    channel.setStateOnline();
  }

  void iterateAlways() override {
    if (millis() - lastReadTime > readIntervalMs) {
      lastReadTime = millis();
      channel.setNewValue(getValue());
    }
    if ((_timeout > 0) && (millis() - _timeout_ms > _timeout * MSINHOUR)) {
      _timeout_ms = millis();
      channel.setStateOffline();
    }
  }


    
 protected:
   uint8_t  _timeout = 0;
   uint32_t _timeout_ms = 0;
};
};  // namespace Sensor
};  // namespace Supla

#endif  // Z2S_VIRTUAL_BINARY_H_
