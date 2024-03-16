// #define vspeed 90    
// #define tspeed 150
#define left_motor_channel_a1 0
#define left_motor_channel_b1 1
#define right_motor_channel_a1 2
#define right_motor_channel_b1 3
int speed=100;
int zigac_check=0;
void stop()
{
    for(int i =0; i<4;i++)
    ledcWrite(i, 0);
}

void left_wheel(int sp, int dir)
 {
if(dir==0){
    ledcWrite(left_motor_channel_a1, 0);
    ledcWrite(left_motor_channel_b1, sp);
}
else{
    ledcWrite(left_motor_channel_a1, sp);
    ledcWrite(left_motor_channel_b1, 0);
}
    Serial.println("left");
 } 

void right_wheel(int sp, int dir)
 {
if(dir==0){
    ledcWrite(right_motor_channel_a1, 0);
    ledcWrite(right_motor_channel_b1, sp);
}
else{
    ledcWrite(right_motor_channel_a1, sp);
    ledcWrite(right_motor_channel_b1, 0);
}
    Serial.println("right");
 }

void backward(int sp)
 {
    // ledcWrite(0, sp);
    // ledcWrite(1, 0);
    // ledcWrite(2, sp);
    // ledcWrite(3, 0);
    ledcWrite(left_motor_channel_a1, 0);
    ledcWrite(left_motor_channel_b1, sp);
    ledcWrite(right_motor_channel_a1, 0);
    ledcWrite(right_motor_channel_b1, sp);
    Serial.println("backward");

 } 

 void forward(int sp)

 {
  //   ledcWrite(0, 0);
  //   ledcWrite(1, sp);
  //   ledcWrite(2, 0);
  //   ledcWrite(3, sp);
  // Serial.println("forward");
    ledcWrite(left_motor_channel_a1, sp);
    ledcWrite(left_motor_channel_b1, 0);
    ledcWrite(right_motor_channel_a1, sp);
    ledcWrite(right_motor_channel_b1, 0);    
    Serial.println("forward");

 } 

void left(int sp)
{
  //   ledcWrite(0, sp);
  //   ledcWrite(1, sp);
  //   ledcWrite(2, 0);
  //   ledcWrite(3, 0);
  // Serial.println("left");
    ledcWrite(left_motor_channel_a1, 0);
    ledcWrite(left_motor_channel_b1, sp);
    ledcWrite(right_motor_channel_a1, sp);
    ledcWrite(right_motor_channel_b1, 0);      
    Serial.println("left");
}

void right(int sp)
{
    // ledcWrite(0, 0);
    // ledcWrite(1, 0);
    // ledcWrite(2, sp+15);
    // ledcWrite(3, sp+15);
    // Serial.println("right");
    ledcWrite(left_motor_channel_a1, sp);
    ledcWrite(left_motor_channel_b1, 0);
    ledcWrite(right_motor_channel_a1, 0);
    ledcWrite(right_motor_channel_b1, sp);  
    Serial.println("right");

}
 void zigzac(int sp1,int sp2)

 {
    ledcWrite(left_motor_channel_a1, sp1);
    ledcWrite(left_motor_channel_b1, 0);
    ledcWrite(right_motor_channel_a1, sp2);
    ledcWrite(right_motor_channel_b1, 0);    
  Serial.println("zigzac");

 } 

int thirty(){
 speed=30*2.55;
 return speed;
}

int forty_five(){
  speed=45*2.55;
  return speed;
}

int sixty(){
 speed=60*2.55;
 return speed;
}
int seventy(){
 speed=70*2.55;
 return speed;
}
int eighty_five(){
 speed=85*2.55;
 return speed;
}
int one_hundred(){
 speed=100*2.55;
 return speed;
}
void turn_left(){
     delay(300);
     left(130);
     delay(200);
 }
void turn_right(){
     delay(300);
     right(130);
     delay(200);
 }
void half_rotate(){
     delay(500);
     left(150);
     delay(350);
 }
void left_circle(){
   zigzac(100,200);
   delay(500);
 }
void right_circle(){
   zigzac(200,100);
   delay(500);
 }
void round(){
  zigzac(200,100);
  delay(5000);
 }
void square(){
  forward(100);
  delay(500);
   right(130);
   delay(250);

  forward(100);
  delay(500);
   right(130);
   delay(250);

  forward(100);
  delay(500);
   right(130);
   delay(250);

  forward(100);
  delay(500);
    right(130);
   delay(200);
 }
void rotate(){
     delay(500);
     left(150);
     delay(1000);
 }

void run_zigzac(){
     zigzac(250,100);
     delay(400);
     zigzac(100,250);
     delay(400);
     zigzac(250,100);
     delay(400);
     zigzac(100,250);  
     delay(400);
 }
void zigac_mode(){
  zigac_check=1;
}


