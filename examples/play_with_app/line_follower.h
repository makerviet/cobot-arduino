#define PWM_PIN_L_A 2
#define PWM_PIN_L_B 10
#define PWM_PIN_R_A 6
#define PWM_PIN_R_B 5

#define left_motor_channel_a 0
#define left_motor_channel_b 1
#define right_motor_channel_a 2
#define right_motor_channel_b 3

#define SENSOR_1_PIN 4
#define SENSOR_2_PIN 3
#define SENSOR_3_PIN 1
#define SENSOR_4_PIN 0


#define threshold 2000

uint8_t vspeed = 100; //50    
uint8_t tspeed = 95; //70

uint8_t vspeed_l = vspeed;
uint8_t tspeed_l = tspeed;
uint8_t vspeed_r = vspeed * 1.1;
uint8_t tspeed_r = tspeed * 1.1;

extern int speed1;

void stop1()
{
    ledcWrite(left_motor_channel_a, 0);
    ledcWrite(left_motor_channel_b, 0);
    ledcWrite(right_motor_channel_a, 0);
    ledcWrite(right_motor_channel_b, 0); 
  //  Serial.println("stop");
}

void forward1()
{
    ledcWrite(left_motor_channel_a, speed1);
    ledcWrite(left_motor_channel_b, 0);
    ledcWrite(right_motor_channel_a, speed1);
    ledcWrite(right_motor_channel_b, 0);    
  //  Serial.println("forward");
} 

void backward1()
  {
    ledcWrite(left_motor_channel_a, 0);
    ledcWrite(left_motor_channel_b, speed1);
    ledcWrite(right_motor_channel_a, 0);
    ledcWrite(right_motor_channel_b, speed1);
  // Serial.println("backward");
  } 

void left1()
{
    ledcWrite(left_motor_channel_a, 0);
    ledcWrite(left_motor_channel_b, tspeed_l);
    ledcWrite(right_motor_channel_a, tspeed_r);
    ledcWrite(right_motor_channel_b, 0);      
  //  Serial.println("left");
}

void right1()
{
    ledcWrite(left_motor_channel_a, tspeed_l);
    ledcWrite(left_motor_channel_b, 0);
    ledcWrite(right_motor_channel_a, 0);
    ledcWrite(right_motor_channel_b, tspeed_r);  
  //  Serial.println("right");
}


void left2()
{
    ledcWrite(left_motor_channel_a, tspeed_l-20);
    ledcWrite(left_motor_channel_b, 0);
    ledcWrite(right_motor_channel_a, tspeed_r);
    ledcWrite(right_motor_channel_b, 0);   
   
 //   Serial.println("left");
}

void right2()
{
    ledcWrite(left_motor_channel_a, tspeed_l);
    ledcWrite(left_motor_channel_b, 0);
    ledcWrite(right_motor_channel_a, tspeed_r-20);
    ledcWrite(right_motor_channel_b, 0);  
 //   Serial.println("right");
}

void left3()
{
    ledcWrite(left_motor_channel_a, 0);
    ledcWrite(left_motor_channel_b, tspeed_l-15);
    ledcWrite(right_motor_channel_a, tspeed_r-15);
    ledcWrite(right_motor_channel_b, 0);      
 //   Serial.println("left");
}

void right3()
{
    ledcWrite(left_motor_channel_a, tspeed_l-15);
    ledcWrite(left_motor_channel_b, 0);
    ledcWrite(right_motor_channel_a, 0);
    ledcWrite(right_motor_channel_b, tspeed_r-15);  
 //   Serial.println("right");
}


void setup_follow() {
  
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  ledcSetup(3, 5000, 8);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(PWM_PIN_L_A, left_motor_channel_a);
  ledcAttachPin(PWM_PIN_L_B, left_motor_channel_b);
  ledcAttachPin(PWM_PIN_R_A, right_motor_channel_a);
  ledcAttachPin(PWM_PIN_R_B, right_motor_channel_b);

  // pinMode(W_LED_ON,OUTPUT);
  // pinMode(IR_LED_ON,OUTPUT);
  // digitalWrite(W_LED_ON, 0);
  // digitalWrite(IR_LED_ON, 1);

}
int nhan_vach_ngang(){
  int sensor_1_state = analogRead(SENSOR_1_PIN);
  int sensor_2_state = analogRead(SENSOR_2_PIN);
  int sensor_3_state = analogRead(SENSOR_3_PIN);
  int sensor_4_state = analogRead(SENSOR_4_PIN);

  uint8_t sensor_array = 0;
  int aa;

  sensor_array += (sensor_1_state <= threshold);
  sensor_array<<=1;
  sensor_array += (sensor_2_state <= threshold);
  sensor_array<<=1;
  sensor_array += (sensor_3_state <= threshold);
  sensor_array<<=1;
  sensor_array += (sensor_4_state <= threshold);

  switch(sensor_array) 
  {
    case 0b1111:
      aa=1;
      break;
    default:
      aa=0;
      break;
  }
   Serial.println(aa);
  return aa;
}



void run_follow(int sw_mode){
  int sensor_1_state = analogRead(SENSOR_1_PIN);
  int sensor_2_state = analogRead(SENSOR_2_PIN);
  int sensor_3_state = analogRead(SENSOR_3_PIN);
  int sensor_4_state = analogRead(SENSOR_4_PIN);
  // Serial.print("ir = \t");
  // Serial.print(sensor_1_state);
  // Serial.print("\t");
  // Serial.print(sensor_2_state);
  // Serial.print("\t");
  // Serial.print(sensor_3_state);
  // Serial.print("\t");
  // Serial.println(sensor_4_state);


  uint8_t sensor_array = 0;
  
  sensor_array += (sensor_1_state <= threshold);
  sensor_array<<=1;
  sensor_array += (sensor_2_state <= threshold);
  sensor_array<<=1;
  sensor_array += (sensor_3_state <= threshold);
  sensor_array<<=1;
  sensor_array += (sensor_4_state <= threshold);


if(sw_mode==0){

  switch(sensor_array) 
  {
    case 0b1000:
      left1();
      break;
    case 0b1100:
      left2();
      break;

    case 0b0001:
      right1();
      break;
    case 0b0011:
      right2();
      break; 
      
    // case 0b0001:
    //   right1();
    //   break;
    // case 0b0011:
    //   right2();
    //   break; 

    case 0b0110:
    case 0b0100:
    case 0b0010:
    case 0b1110:
    case 0b0111:
    case 0b1111:
      forward1();
      break;

    default:
      forward1();
      break;
  }

}


else{
    switch(sensor_array) 
  {
    case 0b1000:
    case 0b1100:
      left1();
      break;

    case 0b0001:
    case 0b0011:
      right1();
      break;

    case 0b0110:
    case 0b0100:
    case 0b0010:
    case 0b1110:
    case 0b0111:
    case 0b1111:
      forward1();
      break;

    default:
      forward1();
      break;
  }
}


    // Serial.println(sensor_array, BIN);
  delay(10);

}