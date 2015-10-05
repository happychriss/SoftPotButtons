/*
  SoftPotButton library for the Arduino.

  GNU GPLv3 license:

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef PLAY_ARDUINO_SOFTPOT_H
#define PLAY_ARDUINO_SOFTPOT_H

#include <inttypes.h>
#include <ctype.h>
#include "Arduino.h"
#include "pins_arduino.h"
#include "limits.h"

// number of values that are read from ths SP and checked for noise (old value - new value), if noise is below
// MAX_NOISE a button was clicked. These numbers must be adjusted, when the scan frequency SCAN_FREQUENCY_MS is changed.


#define FS 15
#define MAX_NOISE 20
#define SCAN_FREQUENCY_MS 5 //every Xms a new value form analog pin is read and processed

#define MIN_VALUE_SP 300 // ignore all values below to get rid of noise


//Return values for GetTouchedButton function
#define NO_BUTTON 99  //no button was pressed after timeout
#define NOT_IN_SAVE_AREA_BUTTON 98  //wrong button was pressed



class SoftPot {

    int *touchpoints;   //center points of you touch-area (e.g. touch in the middle of the field)
    uint8_t save_area;      //width of the touchpoint, if user touches not in the eare no-tp is returned


    uint8_t GetButton(int val);
    uint8_t sp_pin;
    int filter[FS] = {0};

public:

    SoftPot(int *set_touchpoints, uint8_t tp_save_area, uint8_t SoftPot_Pin);

    uint8_t GetTouchedButton(unsigned long max_button_wait_time);

};


#endif //PLAY_ARDUINO_SOFTPOT_H
