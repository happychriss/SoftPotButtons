/*
  Demo Program for the SoftPotButton library for the Arduino.

  The example program will print buttons pressed on a ribbon softpot, divided in 12 equal areas.
  The center of an areas can be defined as touchpoints, each touchpoint has the same size (e.g. +- 10).


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

#include "Arduino.h"
#include "pins_arduino.h"
#include "limits.h"
#include "SoftPot.h"


int potPin = A5;    // select the input pin for the potentiometer
int touchpoints[13] = {337, 364, 390, 414, 438, 466, 485, 518, 546, 571, 600, 625, NO_BUTTON};//must end with no_BUTTON


// Init Softpot: touchpoints,save area for the button,potPin for reading analog value

SoftPot CirclePot(touchpoints, 10 ,potPin);

void setup() {
    Serial.begin(9600);
    Serial.println("Init Program");
}

void loop() {

    Serial.println("** Press return in terminal to start reading buttons from SoftPot **");
    Serial.flush(); while(!Serial.available()) ;//flush all previous received and transmitted data

    uint8_t button;


    while (true) {


        button = CirclePot.GetTouchedButton(5000); // wait 2 seconds if a button is pressed

        switch (button) {
            case NO_BUTTON:
              Serial.println("No button pressed within timeout!");
                break;
            case NOT_IN_SAVE_AREA_BUTTON:
                Serial.println("Hmm..not sure if the correct button was pressed!");
                break;
            default:
                Serial.print("Button pressed: ");
                Serial.println(button);
                break;
        }


    }

}