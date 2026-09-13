// Initializes and sets colors on the HC-SR04 module's built-in RGB LEDs and prepares the trigger/echo pins for distance measurement on an Arduino Uno.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-hcsr04-rgb-distance-leds
// Parts used: https://shillehtek.com/products/shillehtek-hc-sr04-with-rgb-light-distance
//             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
//             https://shillehtek.com/products/shillehtek-400-point-breadboard
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "RGBLed.h"
// Set the pin nr wired to the ultrasonic sensor's pin marked "RGB" or "RGB_IN":
const int RGBpin = 2;
const int trigPin = 9;
const int echoPin = 10;
const long RED    = 0xFF0000;
const long ORANGE = 0xFF8800;
const long YELLOW = 0xFFFF00;
const long GREEN  = 0x00FF00;
const long BLUE   = 0x0000FF;
const long PURPLE = 0xFF00FF;
// Put the colours in an array:
const long RAINBOW[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
int index = 0;
// The ultrasonic sensor has 6 built-in leds in total: 3 in each cylinder.
RGBLed ultrasonicRGB(RGBpin, 6);
// defines variables
long duration;
int distance;
void setup() {
// Set the 3 leds in the first cylinder to one colour,
// passing values from 0 to 255 for red, green, and blue.
for(int ledNr = 1; ledNr <= 3; ledNr++) {
ultrasonicRGB.setColor(ledNr, 200, 255, 0);  //yellow
}
// Set the leds in the other cylinder individually:
ultrasonicRGB.setColor(4, 255, 0, 0);  //red
ultrasonicRGB.setColor(5, 0, 255, 0);  //green
// Alternatively you can pass a hex colour value:
ultrasonicRGB.setColor(6, 0x0000FF);  //blue
// Apply the changes:
ultrasonicRGB.show();
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {
// // Shift the rainbow array's index across [0] to [5], red to purple:
// index += 1;
// if(index > 2) {index = 0;}
// // Set the colours for all leds, shifting at each loop:
// for(int ledNr = 1; ledNr <= 6; ledNr++) {
// int colourNr = (index + ledNr % 2) % 6;
// ultrasonicRGB.setColor(ledNr, RAINBOW[colourNr]);
// }
// ultrasonicRGB.show();
// // Change the colours with a certain interval.
// // The smaller the delay, the faster the animation.
// delay(150);
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance = duration * 0.0343 / 2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}
