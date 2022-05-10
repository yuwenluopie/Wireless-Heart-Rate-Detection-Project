#include<U8g2lib.h>
#include <SoftwareSerial.h>

SoftwareSerial serial(2, 3);
U8G2_MAX7219_32X8_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 9, /* data=*/ 7, /* cs=*/ 8, /* dc=*/ U8X8_PIN_NONE, /* reset=*/ U8X8_PIN_NONE);
void setup() {
  // put your setup code here, to run once:
  serial.begin(9600);
  u8g2.begin();
  u8g2.setContrast(1); 
  Serial.begin(9600);
}
int amp[32] = {0};
void loop() {
  // put your main code here, to run repeatedly:
  if(serial.available()){
    for(int i=0;i<31;i++){
      amp[i] = amp[i+1];
    }
    amp[31] = serial.parseInt();
    u8g2.clearBuffer();
    for(int i = 1;i<=32;i++){
      u8g2.drawLine(i,amp[i-1],i+1,amp[i]);
    }
    u8g2.sendBuffer();
  }  
}
