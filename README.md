# Softpot  Buttons

## Using a SoftPot Ribbon as flexible button array / switches
SoftPots are very thin variable potentiometers. By pressing down on various parts of the strip, the resistance linearly changes from 100Ohms to 10,000Ohms allowing the user to very accurately calculate the relative position on the strip.
The SoftPot can be easily connected to Arduino via 2 10KOhm resistors to VCC and ground (two external connectors). The middle connector part is connected to analogue in. The voltage measured is related to the position touched at the softpot.

The SoftPot library enables you to use the SoftPot as a a set of several buttons. For example the Circular Soft Potentiometer can be divided into 12 segments, where each segment can be touched and defined as one button:
1. Very robust (Operating Temperature: 	-40°C to +50°C / Humidity: 	No affect  / IP Rating 	IP65)
2. Only will need one Analog - Input from Arduino (+GND and VCC)
3. The buttons are defined via Software, size of the button & position can be changed via SourceCode
4. Looks cool

The main problem when usin the SoftPot as a "Buttons" is to exactly identify when an area (touchpoint) is pressed down by the finger, as a lot of noisy signals are created during this time.
The library implements a filter that removes the noise and identifies the right moment when to measuer the touched position.


## The SoftPot Library
On initialisation of the library the touchpoints are defined, this are the virtual buttons.- you need to read the data from anlogue in while you press down in the button area for long time, so the SoftPot is stable. In addition you define a save-area - so the button is defined as touchpoint -"save-area" to touchpoint + "save area". Last parameter is the analogue pin to read the voltage:

```c_cpp
int potPin = A5;    // select the input pin for the potentiometer
int touchpoints[13] = {337, 364,........ NO_BUTTON};//must end with no_BUTTON
int save_area = 10
// Init Softpot: touchpoints,save area for the button,potPin for reading analog value

SoftPot CirclePot(touchpoints, save_area ,potPin);
```

When reading, you define a time-out to determine how long the library is waiting for a button to be pressed.

```c_cpp
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

```

# Inportant
The library is tested with the circular Softpot, Arduino 3V.

# Background Noise Filter
The library is reading every 5ms analog in and caclulating the noise of the last 30 values. If the noise is below threshold the button is identifed as pressed.


 ![alt text](https://github.com/happychriss/SoftPotButtons/softpot_noise_filter.jpg "Voltage and Noise read from a Circular Ribbon SoftPot")
