
/*
  SoftPot library for the Arduino.
  This library implements the following features:

  The SoftPot can be seperated in several areas (e.g. to assign buttons). The library filters out
  noise, identifies when the softpot is pressed with a finger and returns the relevant button. By this a single
  SoftPot can replaca a lot of buttons (Ribbon = 12 Buttons).

  The center a "soft button" is defined as touchpoints, each touchpoint has the same size. The library supports as many
  touchpoints as you want. A touchpoint is surrounded by a save area, so the finger must not exactly hit the point.
  You must read the outpuot value of the SoftPot to define the touchpoints.

   Author:          Christian Neuhaus pmsfriend@googlemail.com
  Available from:  https://github.com/rodan/ds3231

  SoftPots are very thin variable potentiometers. By pressing down on various parts of the strip, the resistance
  linearly changes from 100Ohms to 10,000Ohms allowing the user to very accurately calculate the relative position
  on the strip.

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
#include <SoftPot.h>


SoftPot::SoftPot(int set_touchpoints[], uint8_t tp_save_area, uint8_t SoftPot_Pin) {
    int i;
    touchpoints = set_touchpoints;
    sp_pin = SoftPot_Pin;
    save_area = tp_save_area;
    for (i = 0; i < 10; i++) { Serial.println(touchpoints[i]); };
};

uint8_t SoftPot::GetTouchedButton(unsigned long max_button_wait_time) {


    int i = 0;
    int val, val_old = 0; // values read from SoftPot
    int curr_noise=0, noise=0;
    int count = 0;
    boolean filter_ready=false;


    uint8_t button = NO_BUTTON;


    unsigned long t_start, t_end, t_button_start;

    long stage_time, button_stage_time,frequency=SCAN_FREQUENCY_MS;

    t_button_start = millis();

    memset(filter, 0, sizeof(filter));

    do {

        t_start = millis();

        val = analogRead(sp_pin);
        curr_noise = abs(val_old - val);
        val_old = val;
        noise = noise + curr_noise;
        noise = noise - filter[i];
        filter[i] = curr_noise;
        i++;

        if (i == FS) { i = 0; filter_ready=true;};

        if (noise < MAX_NOISE and val > MIN_VALUE_SP and filter_ready) {

            if (count == 1) {
                button = GetButton(val);
                delay(100);
            }
            count++;
        } else { count = 0; }


//        Serial.print(val);Serial.print("-");Serial.print(noise);Serial.print("-");Serial.println(millis());

        t_end = millis();
        stage_time = t_end - t_start;
        button_stage_time= t_end - t_button_start;

        if (stage_time<frequency) {
            delay((unsigned long)(frequency - stage_time));
        }

        // stay in loop until wait time is over or button is pressed
    } while ((button == NO_BUTTON) && (button_stage_time < max_button_wait_time));

    return button;
}

uint8_t SoftPot::GetButton(int val) {

    uint8_t i = 0;
    uint8_t button = NOT_IN_SAVE_AREA_BUTTON;

    while (touchpoints[i] != NO_BUTTON) {
        if ((val > (touchpoints[i] - save_area)) and (val < (touchpoints[i] + save_area))){
            button = i;
            break;
        }
        i++;
    }

    return button;
}





