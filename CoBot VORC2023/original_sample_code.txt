#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define SENSOR_1_PIN 4
#define SENSOR_2_PIN 3
#define SENSOR_3_PIN 1
#define SENSOR_4_PIN 0

#define PWM1_A 2
#define PWM1_B 10

#define PWM2_A 5
#define PWM2_B 6

#define IR_LED_ON 20
#define W_LED_ON  21

#define vspeed 70 //50    
#define tspeed 100 //70
#define threshold 2000

void forward();
void backward();
void left();
void stop();
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


void setup() {
  Serial.begin(115200);
  
  pinMode(W_LED_ON,OUTPUT);
  pinMode(IR_LED_ON,OUTPUT);
  digitalWrite(W_LED_ON,1);
  digitalWrite(IR_LED_ON,1);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  ledcSetup(3, 5000, 8);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(PWM1_B, 0);
  ledcAttachPin(PWM2_B, 1);

  ledcAttachPin(PWM2_A, 2);
  ledcAttachPin(PWM1_A, 3);
  stop();


}

void stop()
{
    for(int i =0; i<4;i++)
    ledcWrite(i, 0);
}
void backward()
 {
    ledcWrite(0, vspeed);
    ledcWrite(1, 0);
    ledcWrite(2, vspeed);
    ledcWrite(3, 0);

 } 

 void forward()

 {
    ledcWrite(0, 0);
    ledcWrite(1, vspeed);
    ledcWrite(2, 0);
    ledcWrite(3, vspeed);
  Serial.println("forward");

 } 

void left()
{
    ledcWrite(0, tspeed);
    ledcWrite(1, tspeed);
    ledcWrite(2, 0);
    ledcWrite(3, 0);
  Serial.println("left");
}
void right()
{
    ledcWrite(0, 0);
    ledcWrite(1, 0);
    ledcWrite(2, tspeed);
    ledcWrite(3, tspeed);
    Serial.println("right");

}
void loop() {
uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  Serial.print("sensor = \t");
  Serial.print(analogRead(SENSOR_1_PIN));
  Serial.print("\t");
  Serial.print(analogRead(SENSOR_2_PIN));
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(analogRead(SENSOR_3_PIN));
  Serial.print("\t");
  Serial.println(analogRead(SENSOR_4_PIN));

  if(analogRead(SENSOR_2_PIN) < threshold  && analogRead(SENSOR_3_PIN) < threshold ) 
    forward();
  if(analogRead(SENSOR_2_PIN) > threshold && analogRead(SENSOR_3_PIN) < threshold ) 
    right();
  if(analogRead(SENSOR_2_PIN) < threshold && analogRead(SENSOR_3_PIN) > threshold ) 
    left();
  if(analogRead(SENSOR_2_PIN) > threshold && analogRead(SENSOR_3_PIN) > threshold ) 
    forward();


  // wait 10 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(10);
}
