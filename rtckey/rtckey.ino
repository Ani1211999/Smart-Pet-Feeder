#include <Key.h>
#include <Keypad.h>

#include <DS3231.h>
#include "PiezoSpeaker.h"
#include "Speaker.h"
#include "Keypad.h"

#include <Servo.h>

#define echo 2

//int Relay = 4;
unsigned int thinSpeakerHoorayLength          = 6;                                                      // amount of notes in melody
unsigned int thinSpeakerHoorayMelody[]        = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5}; // list of notes. List length must match HoorayLength!
unsigned int thinSpeakerHoorayNoteDurations[] = {8      , 8      , 8      , 4      , 8      , 4      }; // note durations; 4 = quarter note, 8 = eighth note, etc. List length must match HoorayLength!
#define KEYPADMEM3X4_PIN_COL1 4
#define KEYPADMEM3X4_PIN_COL2 5
#define KEYPADMEM3X4_PIN_COL3 6
#define KEYPADMEM3X4_PIN_ROW1 7
#define KEYPADMEM3X4_PIN_ROW2 8
#define KEYPADMEM3X4_PIN_ROW3 9
#define KEYPADMEM3X4_PIN_ROW4 10
#define THINSPEAKER_PIN_POS  12
DS3231  rtc(SDA, SCL);
int t1, t2, t3, t4, t5, t6;
int timer[4];
Time t;
char keypadmem3x4keys[ROWS][COLS] = {
      {'1','2','3'},
      {'4','5','6'},
      {'7','8','9'},
      {'*','0','#'}
    };
PiezoSpeaker thinSpeaker(THINSPEAKER_PIN_POS);
Keypad keypadmem3x4(KEYPADMEM3X4_PIN_COL1,KEYPADMEM3X4_PIN_COL2,KEYPADMEM3X4_PIN_COL3,KEYPADMEM3X4_PIN_ROW1,KEYPADMEM3X4_PIN_ROW2,KEYPADMEM3X4_PIN_ROW3,KEYPADMEM3X4_PIN_ROW4);
/*const int OnHour = 13;
const int OnMin = 40;*/
const int OffHour = 12;
const int OffMin = 25;

char OnHour;
char OnMin;
char c;
int k=2,i=0;
  int j=0;




int max = 200, min =0;
long distance, pulseTime;


Servo servo1;
int pos1=0;
  
void setup() {
  Serial.begin(115200);
  //OnHour=Serial.read();
  keypadmem3x4.begin(keypadmem3x4keys);
  rtc.begin();
  Serial.println("Enter feeding time (HH MM)");
  
   // getKeypad();
  //pinMode(Relay, OUTPUT);
  //digitalWrite(Relay, LOW);

  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);

  int trig=3;

  servo1.attach(11);//pin at which servo is plugged in
  servo1.write(180);//degrees 180 or 0
}


void speaker(){

  thinSpeaker.playMelody(thinSpeakerHoorayLength, thinSpeakerHoorayMelody, thinSpeakerHoorayNoteDurations); 
    delay(500);   
}
/*char getKeypad()
{
    Serial.println("getKeypad loop start");
    delay(1000);
    char keypadmem3x4Key = keypadmem3x4.getKey();
    delay(1000);
    if (isDigit(keypadmem3x4Key) ||  keypadmem3x4Key == '*' ||  keypadmem3x4Key == '#')
    {
      OnHour=keypadmem3x4Key;
      
      return OnHour;
    }
}*/

  
void loop() {

  String t="";
  t = rtc.getTimeStr();
  t1 = t.charAt(0)-48;
  t2 = t.charAt(1)-48;
  t3 = t.charAt(3)-48;
  t4 = t.charAt(4)-48;
  char k=0;
  
  /*Serial.print(t.hour);
  Serial.print(" hour(s), ");
  Serial.print(t.min);
  Serial.print(" minute(s)");
  Serial.println(" ");*/
  
  if(timer[0]==t1 && timer[1]==t2 && timer[2]==t3 && timer[3]==t4)
  {
     speaker();
     ultrasonic();
  }
  
  if(i==0)
  {
      Serial.println("Feed Start");
      while(j<=3)
      {
         
        char k=  keypadmem3x4.getKey();
         if(k!=NO_KEY)
         {
           timer[j] = k-48;
           Serial.println(timer[j]);
           delay(1000);
           j++;
         }
         else
         {
           char k=  keypadmem3x4.getKey();
           delay(100);
         }
         
      }
       
  }
 
  i++;

  
  /*if(t.hour == OnHour && t.min == OnMin){
    Serial.println("Motion Started");
    //digitalWrite(Relay,HIGH);
    Serial.println("LIGHT ON");
    speaker();
    }
    
    else if(t.hour == OffHour && t.min == OffMin){
      Serial.println("Motion Stopped");
      //digitalWrite(Relay,LOW);
      Serial.println("LIGHT OFF");
      
    }
    
    */
    
    
}
/*void stopspeaker()
{
   thinSpeaker.stopMelody(thinSpeakerHoorayLength, thinSpeakerHoorayMelody, thinSpeakerHoorayNoteDurations);
}*/

void ultrasonic() {
  digitalWrite(3, LOW);
  delayMicroseconds(2);

  digitalWrite(3, HIGH);
  delayMicroseconds(10);

  digitalWrite(3, LOW);
  pulseTime = pulseIn(2, HIGH);

  distance = pulseTime/58.2;
  if(distance >= max || distance <= min ){
    digitalWrite(13, HIGH);
    Serial.println("oops");
  }else if(distance<=75){
    
    servo();
    //stopspeaker();
    digitalWrite(13, LOW);
    Serial.println(distance);
    
  }
  
}

void servo() {
  // put your main code here, to run repeatedly:
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
