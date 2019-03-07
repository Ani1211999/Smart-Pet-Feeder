#include <Servo.h>

#define echo 2

int max = 200, min =0;
long distance, pulseTime;


Servo servo1;
int pos1=0;

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);

  int trig=3;

  servo1.attach(11);//pin at which servo is plugged in
  servo1.write(180);//degrees 180 or 0
}

void loop() {
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
