#include <Servo.h>

int ledPin=8;
int inputPin=2;
int pirState=LOW;
int val=0;


Servo servo1;
int pos1=0;

void setup() {
  // put your setup code here, to run once:
pinMode(ledPin,OUTPUT);
pinMode(inputPin,INPUT);

Serial.begin(9600);

servo1.attach(9);//pin at which servo is plugged in
 servo1.write(180);//degrees 180 or 0
}

void loop() {
  // put your main code here, to run repeatedly:
val=digitalRead(inputPin);

if(val == HIGH){
  digitalWrite(ledPin,HIGH);
  if(pirState == LOW){
     
    Serial.println("Motion Detected");
    
   
   pirState=HIGH; 
servo();
   
  }
} 

else {
  digitalWrite(ledPin,LOW);
  if(pirState == HIGH){

    Serial.println("Motion ended");

    pirState=LOW;
  }
}


}

void servo()
{
  Serial.println("Servo start");
  for(pos1 = 0; pos1 < 180; pos1 += 1)
  {
    servo1.write(pos1);
    delay(1);
  }
  for(pos1 = 180; pos1 >= 1;pos1-=1)
  {
    servo1.write(pos1);
    delay(1);
  }
}
