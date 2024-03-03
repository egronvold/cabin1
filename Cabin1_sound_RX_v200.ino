/* Sketch for "Cabin in the forest".
Based on the library DFPlayerMini_Fast by PowerBroker2:
https://github.com/PowerBroker2/DFPlayerMini_Fast/blob/master/src/DFPlayerMini_Fast.h

Simulating a cabin without electricity; candle lights, oven and outside chandelier.
Using LEDs made for simulating flames
Version 2 is including playing music from a "bluetooth speaker" in the cabin.
Version RX has added functionality to control sound and light using a R/C radio.

Created for and used on an Arduino Nano Every.

Written by Emil Grønvold
Version RX 2.00: 24 February 2024
*/

// Library related data
#include <DFPlayerMini_Fast.h>   // Library for controlling the DFPlayerMini

#if !defined(UBRR1H)             // From the example from PowerBroker2
#include <SoftwareSerial.h>      // Library for creating software serial ports for communications 
SoftwareSerial mySerial(10, 11); // Seet up pins to act as RX and TX pins for serial communications
#endif

DFPlayerMini_Fast myMP3;        // Declaring name for the MP3-player object

// Declare constant variables
const int insidePin1 =    2;      // Pin for LED 1 inside the cabin
const int insidePin2 =    3;      // Pin for LED 2 inside the cabin
const int outsidePin =    4;      // Pin for the LED in the outside chandelier
const int ovenPin =       5;      // Pin for the LED in the oven
const int busyPin =       9;      // Busy pin on DFMiniPlayer
// Pin 10 and 11 are used by the SoftwareSerial
const int pwmInputPinA =  A0;     // A0 on Arduino Nano Every reading PWM input A
const int pwmInputPinB =  A1;     // A1 on Arduino Nano Every reading PWM input B
const int yourCountInterval = 500;// Used for determin how long signal A must meet a criteria over threshold
const int numModes = 4;           // Number of modes managed by signal A
const int volumeMax = 30;         // The maximum the volume can be adjusted to. DFPlayerMini volum range is 0-30

// Declare variables
int i;                          // Variable used in for-functions
int songNumber = 1;             // Variable telling which song the player shall play
int lastSequentialTrack = 2;    // Variable for number of tracks before and including to be played sequentially
int lowRandomTrack = 3;         // Variable for setting the lowest number of the randomized tracks
int highRandomTrack = 7;        // Variable for setting the highest number of the randomized tracks
int counter = 0;                // Variable for counting number of times all songs in a folder has been played
int volume = 15;                // Variable for controlling the volume from 0-30
int busyStatus;                 // Variable for the status of the busyPin
int aboveThresholdCount = 0;    // Counter for how manytimes signal A has met a critera
int belowThresholdCount = 0;    // Used for executing toggle switch for signal A
int lowCountB = 0;              // Counter for how many times signal B has met a criteria

// Declare large variables
unsigned long currentMillis = 0;        // Variable to store the current time at an event
unsigned long lastCheck = 0;            // Variable used to check if it's time to change the track (song)
unsigned long playTime = 4000;          // Variable to set minimum playtime before the sketch shall check to see if it's time to change the track (song)
unsigned long fireLit = 0;              // Variable to store the time the oven fire was lit
unsigned long fireWait = 20;            // Variable to set the time needed for the MP3.player to react to start playing the sound of fire
unsigned long functionCheckTime = 100;  // Variable to set the time between running certain functions in the void loop() 
unsigned long lastFunctionCheck = 0;    // Variable used to check if it's time to change run the functions
unsigned long lastCountTime = 0;        // Used for timing for counter in signal A

// Declare conditions
bool lightsOn = false;        // Condition used to check if the lights are on or off
bool playMusic = false;       // Condition used to check if the music shall be turned on or off
bool isPlaying = false;       // Condition used to check if the music is playing
bool firstSong = true;        // Condition used to check if it's the first song after music has started playing
bool stop = false;            // Condition used to check if the music shall be stopped
bool fire = false;            // Condition used to check if the fire is burning
bool lightFire = false;       // Condition used to check if it's time to light the fire
bool extinguishFire = false;  // Condition used to check if it's time to extinguish the fire

// Signal range parameters
int calibratedMinStartA = 1000;  // Initial value, adjust as needed
int calibratedMaxStartA = 1800;  // Initial value, adjust as needed
int calibratedMinStartB = 1000;  // Initial value, adjust as needed
int calibratedMaxStartB = 1800;  // Initial value, adjust as needed
int calibratedMinA = 1000;       // Initial value, adjust as needed
int calibratedMaxA = 1800;       // Initial value, adjust as needed
int calibratedMinB = 1000;       // Initial value, adjust as needed
int calibratedMaxB = 1800;       // Initial value, adjust as needed
int calDelay = 10;               // Value to make sure calibration is not flooding
int setupBlink = 80;             // Value to blink the headlights during calibration setup
int signalRangeMax = 255;        // Adjust this value based on your requirements
int signalRangeA;                // Variable to be used for input pin A
int signalRangeB;                // Variable to be used for input pin B

