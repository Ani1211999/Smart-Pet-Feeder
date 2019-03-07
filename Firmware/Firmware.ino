
// Include Libraries
#include "Arduino.h"
#include "NewPing.h"
#include "KeyPad.h"
#include "Wire.h"
#include "RTClib.h"
#include "Servo.h"
#include "PiezoSpeaker.h"


#include <DS3231.h>

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

#include <Servo.h>
Servo servo1;
int pos1=0;

// Pin Definitions
#define HCSR04_PIN_TRIG	3
#define HCSR04_PIN_ECHO	2
#define KEYPADMEM3X4_PIN_COL1	4
#define KEYPADMEM3X4_PIN_COL2	5
#define KEYPADMEM3X4_PIN_COL3	6
#define KEYPADMEM3X4_PIN_ROW1	7
#define KEYPADMEM3X4_PIN_ROW2	8
#define KEYPADMEM3X4_PIN_ROW3	9
#define KEYPADMEM3X4_PIN_ROW4	10
#define SERVOSM_PIN_SIG	11
#define THINSPEAKER_PIN_POS	12

int max = 200, min =0;
long distance, pulseTime;


// Global variables and defines
//Use this 2D array to map the keys as you desire
char keypadmem3x4keys[ROWS][COLS] = {
      {'1','2','3'},
      {'4','5','6'},
      {'7','8','9'},
      {'*','0','#'}
    };
const int servoSMRestPosition   = 20;  //Starting position
const int servoSMTargetPosition = 150; //Position when event is detected
unsigned int thinSpeakerHoorayLength          = 6;                                                      // amount of notes in melody
unsigned int thinSpeakerHoorayMelody[]        = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5}; // list of notes. List length must match HoorayLength!
unsigned int thinSpeakerHoorayNoteDurations[] = {8      , 8      , 8      , 4      , 8      , 4      }; // note durations; 4 = quarter note, 8 = eighth note, etc. List length must match HoorayLength!
// object initialization

Keypad keypadmem3x4(KEYPADMEM3X4_PIN_COL1,KEYPADMEM3X4_PIN_COL2,KEYPADMEM3X4_PIN_COL3,KEYPADMEM3X4_PIN_ROW1,KEYPADMEM3X4_PIN_ROW2,KEYPADMEM3X4_PIN_ROW3,KEYPADMEM3X4_PIN_ROW4);
Servo servoSM;
NewPing hcsr04(HCSR04_PIN_TRIG,HCSR04_PIN_ECHO);
RTC_DS3231 rtcDS;
PiezoSpeaker thinSpeaker(THINSPEAKER_PIN_POS);



// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    //Initialize the keypad with selected key map
    keypadmem3x4.begin(keypadmem3x4keys);
    if (! rtcDS.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
      }

    Serial.begin(115200);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}
  
  // Initialize the rtc object
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time
  rtc.setDOW(THURSDAY);     // Set Day-of-Week to SUNDAY
  rtc.getTime();     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(25, 10, 2018);   // Set the date to January 1st, 2014

      //if (rtcDS.lostPower()) {
        //Serial.println("RTC lost power, lets set the time!");
        // following line sets the RTC to the date & time this sketch was compiled
        //rtcDS.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtcDS.adjust(DateTime(2014, 1, 21, 3, 0, 0));

    pinMode(HCSR04_PIN_ECHO, INPUT);
    pinMode(HCSR04_PIN_TRIG, OUTPUT);
    pinMode(13, OUTPUT);
    
    /*servoSM.attach(SERVOSM_PIN_SIG);
    servoSM.write(servoSMRestPosition);
    delay(100);
    servoSM.detach();*/

    Serial.begin(115200);
    servo1.attach(SERVOSM_PIN_SIG);//pin at which servo is plugged in
    servo1.write(180);//degrees 180 or 0
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // Ultrasonic Sensor - HC-SR04 - Test Code
    // Read distance measurment from UltraSonic sensor           
    /*int hcsr04Dist = hcsr04.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04Dist); Serial.println(F("[cm]"));*/

    digitalWrite(HCSR04_PIN_TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(HCSR04_PIN_TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(HCSR04_PIN_TRIG, LOW);
  pulseTime = pulseIn(HCSR04_PIN_ECHO, HIGH);

  distance = pulseTime/58.2;
  if(distance >= max || distance <= min ){
    digitalWrite(13, HIGH);
    Serial.println("oops");
  }else if(distance<=75){
    
    digitalWrite(13, LOW);
    Serial.println(distance);
  }

    }
    else if(menuOption == '2') {
    // Membrane 3x4 Matrix Keypad - Test Code
    //Read keypad
    char keypadmem3x4Key = keypadmem3x4.getKey();
    if (isDigit(keypadmem3x4Key) ||  keypadmem3x4Key == '*' ||  keypadmem3x4Key == '#')
    {
    Serial.print(keypadmem3x4Key);
    }
    }
    else if(menuOption == '3') {
    // DS3231 Precision RTC Breakout - Test Code
    //This will display the time and date of the RTC. see RTC.h for more functions such as rtcDS.hour(), rtcDS.month() etc.
    /*DateTime now = rtcDS.now();
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print("  ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    delay(1000);*/
    // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());
  
  // Wait one second before repeating :)
  delay (1000);
    }
    else if(menuOption == '4') {
    // Servo - Generic Metal Gear (Micro Size) - Test Code
    // The servo will rotate to target position and back to resting position with an interval of 500 milliseconds (0.5 seconds) 
    /*servoSM.attach(SERVOSM_PIN_SIG);         // 1. attach the servo to correct pin to control it.
    servoSM.write(servoSMTargetPosition);  // 2. turns servo to target position. Modify target position by modifying the 'ServoTargetPosition' definition above.
    delay(500);                              // 3. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servoSM.write(servoSMRestPosition);    // 4. turns servo back to rest position. Modify initial position by modifying the 'ServoRestPosition' definition above.
    delay(500);                              // 5. waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servoSM.detach();                   //6. release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
  */

  Serial.println("Servo Start");
  for(pos1 = 0; pos1 < 180; pos1 += 1)
  {
    servo1.write(pos1);
    //Serial.println("ghuma");
    delay(1);
  }
  for(pos1 = 180; pos1 >= 1;pos1-=1)
  {
    servo1.write(pos1);
    //Serial.println("ghuma");
    delay(1);
  }
    
    }
    else if(menuOption == '5') {
    // Thin Speaker - Test Code
    // The Speaker will play the Hooray tune
    thinSpeaker.playMelody(thinSpeakerHoorayLength, thinSpeakerHoorayMelody, thinSpeakerHoorayNoteDurations); 
    delay(500);   
    }
    
    
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Ultrasonic Sensor - HC-SR04"));
    Serial.println(F("(2) Membrane 3x4 Matrix Keypad"));
    Serial.println(F("(3) DS3231 Precision RTC Breakout"));
    Serial.println(F("(4) Servo - Generic Metal Gear (Micro Size)"));
    Serial.println(F("(5) Thin Speaker"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {
            if(c == '1') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Membrane 3x4 Matrix Keypad"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing DS3231 Precision RTC Breakout"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Servo - Generic Metal Gear (Micro Size)"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing Thin Speaker"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/
