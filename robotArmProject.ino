#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>
Servo wristServo;
Servo verticalServo;
Servo horizontalServo;
Servo spinServo;
Adafruit_TCS34725 color_sensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  color_sensor.begin();
  Serial.begin(9600);
  wristServo.attach(10);  
  verticalServo.attach(6);
  horizontalServo.attach(11);
  spinServo.attach(3);
}

void loop() {
  float red_float, green_float, blue_float;
  delay(10); 
  color_sensor.getRGB(&red_float, &green_float, &blue_float); 
  int red, green, blue;
  red = (int)(red_float);
  green = (int)(green_float);
  blue = (int)(blue_float);
  if(red > 100){
    grab();
    retract();
    releaseRed();
  }
  if(blue > 100){
    grab();
    retract();
    releaseBlue();
  }
  else{
    retract();
    spinServo.write(100);
  }
  delay(10);
}

void retract(){
  //wristServo.write(35);
  horizontalServo.write(50);
  verticalServo.write(140);
  delay(1000);
}

void grab(){
  //wristServo.write(100);
  horizontalServo.write(130);
  verticalServo.write(120);
  delay(1000);
  //wristServo.write(35);
  delay(1000);
}

void releaseBlue(){
  spinServo.write(160);
  horizontalServo.write(120);
  verticalServo.write(120);
  //wristServo.write(140);
  delay(1000);
}

void releaseRed(){
  spinServo.write(80);
  horizontalServo.write(120);
  verticalServo.write(120);
  //wristServo.write(140);
  delay(1000);
}
