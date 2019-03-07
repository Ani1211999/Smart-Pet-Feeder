#include <Servo.h>
Servo servo1;
int pos1=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  servo1.attach(11);//pin at which servo is plugged in
  servo1.write(180);//degrees 180 or 0
}

void loop() {
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
