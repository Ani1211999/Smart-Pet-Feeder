#include <LiquidCrystal.h>
#include <String.h>
#define C1 9
#define C2 10
#define C3 11
LiquidCrystal lod (13,12,8,7,4,3);
char a; 
void setup() {
  // put your setup code here, to run once:
lod.begin (16,2);

pinMode(C1,INPUT);

pinMode(C2,INPUT);
pinMode(C3,INPUT);

pinMode(A0,OUTPUT);

pinMode(A1,OUTPUT);

pinMode(A2,OUTPUT);

pinMode(A3,OUTPUT);

lod.setCursor(0,0);
lod.print("KEYPAD WORKING");
delay(5000);
lod.clear
}

void loop() {
  // put your main code here, to run repeatedly:

}
