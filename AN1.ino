#include "U8g2lib.h"
#include "TimerOne.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,SCL,SDA,U8X8_PIN_NONE);
int Minute = 48;
int Second = 0;
int Hour = 11;
void timerIsr(){
  Second++;
  if (Second > 59)
  {
    Second = 0;
    Minute++;   
    if (Minute > 59)
      {Minute = 0;
        Hour++;
    if(Hour > 24)
      Hour=0;
      }
  } 
}

void setup() {
// initialize the serial communication:
  int state = 1;
  Serial.begin(9600);
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -

  u8g2.begin();
  Timer1.initialize(1000000);
  Timer1.attachInterrupt( timerIsr );
  u8g2.setFont(u8g2_font_ncenB14_tr); 
  
  if(state==1)
 {
  u8g2.clearBuffer();
  u8g2.drawStr(0,17,"BT online");
  u8g2.drawLine(0,20, 128, 20);
  u8g2.drawLine(0,50, 128, 50);
  u8g2.drawLine(0,51, 128, 51);
  u8g2.sendBuffer();
 }
else
  {
  u8g2.clearBuffer();
  u8g2.drawStr(0,17,"BT offline"); 
  u8g2.drawLine(0,20, 128, 20);
  u8g2.drawLine(0,50, 128, 50);
  u8g2.sendBuffer();
  }
}

int j = 0;
void loop() {
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    Serial.println('!');
  }
  else{
// send the value of analog input 0:
    int amp = analogRead(A0);
    //Serial.println(amp);
    if(amp<700){
      Serial.println(4);
    }
    else{
      Serial.println((amp-700)/4);
    }
  }
  char Hou[3];
  char Min[3];
  char Sec[3];
  itoa(Hour,Hou,10); 
  itoa(Minute,Min,10);
  itoa(Second,Sec,10);
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(45,45,Hou);
  u8g2.drawStr(65,45,":");
  u8g2.drawStr(75,45,Min);
  u8g2.drawStr(95,45,":");
  u8g2.drawStr(105,45,Sec);
  u8g2.setFont(u8g2_font_fur11_tr);
  u8g2.drawStr(30,64,"BPM=110");
  u8g2.drawStr(0,43,"Time");
  u8g2.sendBuffer();
//Wait for a bit to keep serial data from saturating
}
