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

#define IR_LED_ON 21
#define W_LED_ON 20


#define vspeed 35
#define tspeed 45
#define threshold 1900

void forward();
void backward();
void left(uint8_t speed);
void stop(uint8_t speed);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


void setup() {
  Serial.begin(115200);

  pinMode(W_LED_ON, OUTPUT);
  pinMode(IR_LED_ON, OUTPUT);
  digitalWrite(W_LED_ON, 1);
  digitalWrite(IR_LED_ON, 1);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    // while (1)
    //   ;
  }

  ledcSetup(0, 500, 8);
  ledcSetup(1, 500, 8);
  ledcSetup(2, 500, 8);
  ledcSetup(3, 500, 8);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(PWM1_B, 0);

  ledcAttachPin(PWM2_B, 1);

  ledcAttachPin(PWM2_A, 2);
  ledcAttachPin(PWM1_A, 3);
  // while (1)
    stop();
}

void stop() {
  for (int i = 0; i < 4; i++)
    ledcWrite(i, 0);
}
void backward() {
  ledcWrite(0, vspeed+8);
  ledcWrite(1, 0);
  ledcWrite(2, vspeed);
  ledcWrite(3, 0);
}

void forward()

{
  ledcWrite(0, 0);
  ledcWrite(1, vspeed);
  ledcWrite(2, 0);
  ledcWrite(3, vspeed+8);
  Serial.println("forward");
}

void left(uint8_t speed) {
  ledcWrite(0, speed+8);
  ledcWrite(1, speed);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
  Serial.println("left");
}
void right(uint8_t speed) {
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, speed);
  ledcWrite(3, speed+8);
  Serial.println("right");
}
void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  // float red, green, blue;

  // tcs.getRGB(&red, &green, &blue);

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
  // Serial.print(red);
  // Serial.print("\t");
  // Serial.print(green);
  // Serial.print("\t");
  // Serial.println(blue);
  // if (b > 500) {
  //   stop();
  // } else {
    // if (analogRead(SENSOR_2_PIN) < threshold && analogRead(SENSOR_3_PIN) = < threshold) stop();
  uint8_t sensor_array = 0;
  sensor_array += (analogRead(SENSOR_1_PIN) <= threshold);
  sensor_array<<=1;
  sensor_array += (analogRead(SENSOR_2_PIN) <= threshold);
  sensor_array<<=1;
  sensor_array += (b <= 350);
  sensor_array<<=1;
  sensor_array += (analogRead(SENSOR_3_PIN) <= threshold);
  sensor_array<<=1;
  sensor_array += (analogRead(SENSOR_4_PIN) <= threshold);

  switch(sensor_array) 
  {
    case 0b10000:
    case 0b11100:
    case 0b10100:
      left(tspeed+1);
      break;
    case 0b01100:
    case 0b11000:
      left(tspeed);
      break;
    case 0b00001:
    case 0b00111:
      right(tspeed+1);
      break;
    case 0b00101:
    case 0b00110:
    case 0b00011:
      right(tspeed);
      break;
    // case 100:
    default:
      forward();
      break;
  }

  Serial.println(sensor_array,BIN);


  //   if (analogRead(SENSOR_2_PIN) > threshold && analogRead(SENSOR_3_PIN) <= threshold) right();
  //   if (analogRead(SENSOR_4_PIN) <= threshold) right();
  //   if (analogRead(SENSOR_2_PIN) <= threshold && analogRead(SENSOR_3_PIN) > threshold) left();

  //   if (analogRead(SENSOR_1_PIN) <= threshold) left();

  //   if (analogRead(SENSOR_2_PIN) > threshold && analogRead(SENSOR_3_PIN) > threshold) forward();
  // // }

  // wait 10 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(10);
}
