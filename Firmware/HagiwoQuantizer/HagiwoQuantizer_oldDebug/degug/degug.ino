#define  ENCODER_OPTIMIZE_INTERRUPTS //
#include <Wire.h>
#include <Encoder.h>
#include "MCP_DAC.h"

MCP4821 MCP(11,13);  

// Trigger 

byte triggerPin = 2;

//CV
int cvPin = A0;
float CV_IN = 512;//CV_IN*60/1024
float old_CV_IN = 512;//
int CV_INr = 512;//CV_IN
int CV_INh = 10;//
int i = 0; //
long old_CV_OUT = 0;

//slide
byte slidePin = 6;
byte slideSWPin = 7;
byte slidePotPin = A1; // unconnected on PCB (error)

int slide_CV = 0 ; 
int slide_time = 1 ; //slide time。
int scale = 1;
byte slide = 0;//0=OFF,1=ON
byte slide_sw = 0;//0=EXT,1=ON
int j = 0;

//illumination mode
byte slide_IN = 0;//
int k = 0;//illumination
int illR = 0;
int illG = 100;
int illB = 200;

//LED
byte now_R = 0;
byte now_G = 0;
byte now_B = 0;

byte ledPin1 = 3;
byte ledPin2 = 5;
byte ledPin3 = 4;

//ロータリーエンコーダ設定
Encoder myEnc(9, 12);//ロータリーエンコーダライブラリ用
float oldPosition  = -999;//ロータリーエンコーダライブラリ用
float newPosition = -999;









/////////////////////////////////////////////////////////////////////////
/////////////////////////////// SETUP ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////




void setup() {
 pinMode(ledPin1, OUTPUT); //Color_LED_R
 pinMode(ledPin2, OUTPUT); //Color_LED_G
 pinMode(ledPin3, OUTPUT); //Color_LED_B
 pinMode(triggerPin, OUTPUT); //trigger out
 pinMode(slidePin, INPUT); //slide_in
 pinMode(slideSWPin, INPUT_PULLUP); //slide_sw

 //dev
 Serial.begin(9600);

 //DAC I2C通信
 //SPI.begin();
 MCP.begin(10);
}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////// LOOP ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////




void loop() {
  CV_IN = analogRead(cvPin);
  Serial.println(CV_IN);
  DACWrite(CV_IN);
}







void DACWrite(int CVoutput){
  MCP.write(CVoutput);
}

void Gate(){
  digitalWrite(triggerPin, LOW) ;//gate
}

void LED(byte R, byte G, byte B) {
 analogWrite(ledPin1, 255-R);
 analogWrite(ledPin2, 255-G);
 analogWrite(ledPin3, 255-B);
}
