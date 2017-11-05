#include <Wire.h>
long gap = 0;
int totBytes = 0;
void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
Wire.begin(0x69);
delay(1000);
Serial.println("I2C Slave: "+ 0x69);

Wire.onReceive(handler);
}

void handler(int numBytes){
  long start = micros();
  int numByte = 0;
  while(Wire.available())
  {
    int i = Wire.read();
    numByte ++;  
  }
  long stp = micros();
  totBytes += numByte;
  gap += (stp-start);
  Serial.println(gap);
  Serial.println(totBytes);
}

void loop() {
  // put your main code here, to run repeatedly:
}
