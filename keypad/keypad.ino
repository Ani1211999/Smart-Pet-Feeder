

void setup() {
  // put your setup code here, to run once:
  pinMode(8,INPUT);
  Serial.begin(9600);
  pinMode(7,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = digitalRead(8);

  if(sensorValue == HIGH) {
    delay(120);
    Serial.print(sensorValue);
    digitalWrite(7, HIGH);
  }
}
