#define PWM_PIN_L_A 2
#define PWM_PIN_L_B 10
#define PWM_PIN_R_A 6
#define PWM_PIN_R_B 5

#define left_motor_channel_a 0
#define left_motor_channel_b 1
#define right_motor_channel_a 2
#define right_motor_channel_b 3

uint8_t vspeed = 255;
uint8_t tspeed = 255;

uint8_t vspeed_l = vspeed;
uint8_t tspeed_l = tspeed;
uint8_t vspeed_r = vspeed * 1.0;
uint8_t tspeed_r = tspeed * 1.0;

void forward();
void backward();
void left();
void stop();

void setup() {
  Serial.begin(115200);

  // attach the channel to the GPIO to be controlled
  
  // for esp32 arduino core 2.0.15
  // ledcSetup(0, 5000, 8);
  // ledcSetup(1, 5000, 8);
  // ledcSetup(2, 5000, 8);
  // ledcSetup(3, 5000, 8);
  // ledcAttachPin(PWM_PIN_L_A, left_motor_channel_a);
  // ledcAttachPin(PWM_PIN_L_B, left_motor_channel_b);
  // ledcAttachPin(PWM_PIN_R_A, right_motor_channel_a);
  // ledcAttachPin(PWM_PIN_R_B, right_motor_channel_b);

  // for esp32 arduino core 3.2.0
  ledcAttachChannel(PWM_PIN_L_A, 5000, 8, left_motor_channel_a);
  ledcAttachChannel(PWM_PIN_L_B, 5000, 8, left_motor_channel_b);
  ledcAttachChannel(PWM_PIN_R_A, 5000, 8, right_motor_channel_a);
  ledcAttachChannel(PWM_PIN_R_B, 5000, 8, right_motor_channel_b);

  stop();
}

void stop()
{
  ledcWriteChannel(left_motor_channel_a, 0);
  ledcWriteChannel(left_motor_channel_b, 0);
  ledcWriteChannel(right_motor_channel_a, 0);
  ledcWriteChannel(right_motor_channel_b, 0);
}

void forward()
{
  ledcWriteChannel(left_motor_channel_a, vspeed_l);
  ledcWriteChannel(left_motor_channel_b, 0);
  ledcWriteChannel(right_motor_channel_a, vspeed_r);
  ledcWriteChannel(right_motor_channel_b, 0);    
} 

void backward()
{
  ledcWriteChannel(left_motor_channel_a, 0);
  ledcWriteChannel(left_motor_channel_b, vspeed_l);
  ledcWriteChannel(right_motor_channel_a, 0);
  ledcWriteChannel(right_motor_channel_b, vspeed_r);    
} 

void left()
{
  ledcWriteChannel(left_motor_channel_a, 0);
  ledcWriteChannel(left_motor_channel_b, tspeed_l);
  ledcWriteChannel(right_motor_channel_a, tspeed_r);
  ledcWriteChannel(right_motor_channel_b, 0);      
}

void right()
{
  ledcWriteChannel(left_motor_channel_a, tspeed_l);
  ledcWriteChannel(left_motor_channel_b, 0);
  ledcWriteChannel(right_motor_channel_a, 0);
  ledcWriteChannel(right_motor_channel_b, tspeed_r);  
}

void loop() {
  forward();

  Serial.print("Forward: ");
  Serial.print(vspeed_l);
  Serial.print(" - ");
  Serial.print(vspeed_r);
  Serial.println("\n");

  delay(3000);

  backward();

  Serial.print("Backward: ");
  Serial.print(vspeed_l);
  Serial.print(" - ");
  Serial.print(vspeed_r);
  Serial.println("\n");

  delay(3000);

  left();

  Serial.print("Left: ");
  Serial.print(vspeed_l);
  Serial.print(" - ");
  Serial.print(vspeed_r);
  Serial.println("\n");

  delay(3000);

  right();

  Serial.print("Right: ");
  Serial.print(vspeed_l);
  Serial.print(" - ");
  Serial.print(vspeed_r);
  Serial.println("\n");

  delay(3000);
}
