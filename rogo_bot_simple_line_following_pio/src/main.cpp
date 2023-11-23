#include <Arduino.h>

#define PWM_PIN_L_A 2
#define PWM_PIN_L_B 10
#define PWM_PIN_R_A 6
#define PWM_PIN_R_B 5

#define left_motor_chanel_a 0
#define left_motor_chanel_b 1
#define right_motor_chanel_a 2
#define right_motor_chanel_b 3

#define SENSOR_1_PIN 4
#define SENSOR_2_PIN 3
#define SENSOR_3_PIN 1
#define SENSOR_4_PIN 0

#define IR_LED_ON 20
#define W_LED_ON  21

#define threshold 2000

uint8_t vspeed = 70; //50    
uint8_t tspeed = 70; //70

uint8_t vspeed_l = vspeed;
uint8_t tspeed_l = tspeed;
uint8_t vspeed_r = vspeed * 1.5;
uint8_t tspeed_r = tspeed * 1.5;

void stop()
{
    ledcWrite(left_motor_chanel_a, 0);
    ledcWrite(left_motor_chanel_b, 0);
    ledcWrite(right_motor_chanel_a, 0);
    ledcWrite(right_motor_chanel_b, 0);    
    Serial.println("stop");
}

void forward()
{
    ledcWrite(left_motor_chanel_a, vspeed_l);
    ledcWrite(left_motor_chanel_b, 0);
    ledcWrite(right_motor_chanel_a, vspeed_r);
    ledcWrite(right_motor_chanel_b, 0);    
    Serial.println("forward");
} 

void backward()
  {
    ledcWrite(left_motor_chanel_a, 0);
    ledcWrite(left_motor_chanel_b, vspeed_l);
    ledcWrite(right_motor_chanel_a, 0);
    ledcWrite(right_motor_chanel_b, vspeed_r);    
    Serial.println("backward");
  } 

void left()
{
    ledcWrite(left_motor_chanel_a, 0);
    ledcWrite(left_motor_chanel_b, tspeed_l);
    ledcWrite(right_motor_chanel_a, tspeed_r);
    ledcWrite(right_motor_chanel_b, 0);      
    Serial.println("left");
}

void right()
{
    ledcWrite(left_motor_chanel_a, tspeed_l);
    ledcWrite(left_motor_chanel_b, 0);
    ledcWrite(right_motor_chanel_a, 0);
    ledcWrite(right_motor_chanel_b, tspeed_r);  
    Serial.println("right");
}

void setup() {
  Serial.begin(115200);

  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  ledcSetup(3, 5000, 8);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(PWM_PIN_L_A, left_motor_chanel_a);
  ledcAttachPin(PWM_PIN_L_B, left_motor_chanel_b);
  ledcAttachPin(PWM_PIN_R_A, right_motor_chanel_a);
  ledcAttachPin(PWM_PIN_R_B, right_motor_chanel_b);

  pinMode(W_LED_ON,OUTPUT);
  pinMode(IR_LED_ON,OUTPUT);
  digitalWrite(W_LED_ON,1);
  digitalWrite(IR_LED_ON,1);
}

void loop() {
  Serial.print("sensor = \t");
  Serial.print(analogRead(SENSOR_1_PIN));
  Serial.print("\t");
  Serial.print(analogRead(SENSOR_2_PIN));
  Serial.print("\t");
  Serial.print(analogRead(SENSOR_3_PIN));
  Serial.print("\t");
  Serial.println(analogRead(SENSOR_4_PIN));


  // Serial.println(vspeed_l);
  // Serial.print(" ");
  // Serial.print(vspeed_r);

  if ((analogRead(SENSOR_1_PIN) > threshold  && analogRead(SENSOR_2_PIN) < threshold && analogRead(SENSOR_3_PIN) > threshold && analogRead(SENSOR_4_PIN) > threshold)
      || (analogRead(SENSOR_1_PIN) > threshold  && analogRead(SENSOR_2_PIN) > threshold && analogRead(SENSOR_3_PIN) < threshold && analogRead(SENSOR_4_PIN) > threshold)
      || (analogRead(SENSOR_1_PIN) > threshold  && analogRead(SENSOR_2_PIN) < threshold && analogRead(SENSOR_3_PIN) < threshold && analogRead(SENSOR_4_PIN) > threshold))
    forward();
  else
    stop();

  // if (analogRead(SENSOR_2_PIN) > threshold && analogRead(SENSOR_3_PIN) < threshold)
  //   right();

  // if (analogRead(SENSOR_2_PIN) < threshold && analogRead(SENSOR_3_PIN) > threshold)
  //   left();

  // if (analogRead(SENSOR_2_PIN) > threshold && analogRead(SENSOR_3_PIN) > threshold)
  //   forward();

  delay(10);
}