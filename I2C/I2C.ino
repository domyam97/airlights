#include <Wire.h>

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Wire.begin(0x69);
  delay(1000);
  Serial.println("I2C Slave: "+ 0x69);
  
  Wire.onReceive(handler);
  
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}
  

void handler(int numBytes){
  int numByte = 0;
  int* packet = new int[numBytes];
  while(Wire.available())
  {
    int i = Wire.read();
    if (numByte > 1){packet[numByte-1] = i;}
    numByte ++;  
  }
  for (int i = 0; i < numBytes-1; i++){
      Serial.print(i);
      Serial.print("  ");
      Serial.println(packet[i]); 
  }
  
  analogWrite(3, packet[3]);
  analogWrite(5, packet[4]);
  analogWrite(6, packet[5]);
  
  delete[] packet;
}

void loop() {
  // put your main code here, to run repeatedly:
}

