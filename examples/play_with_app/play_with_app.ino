#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include "EEPROM.h"
#include "detect_color.h"
#include "action.h"
#include "line_follower.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

//========================= control ================================
#define BLE_SERVICE1_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define BLE_CHARACTERISTIC1_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

//========================= calib ==================================
#define BLE_SERVICE2_UUID "4fafc201-2fb5-459e-8fcc-c5c9c331914b"
#define BLE_CHARACTERISTIC2_UUID "beb5483e-37e1-4688-b7f5-ea07361b26a8"
#define UUID_CHARACTERISTIC_LINE_COLOR  "beb5483e-54e1-4688-b7f5-ea07361b26a8"
#define UUID_CHARACTERISTIC_BG_COLOR  "beb5483e-55e1-4688-b7f5-ea07361b26a8"

//========================= game mode ==============================
#define BLE_SERVICE3_UUID  "4fafc201-9fb5-459e-8fcc-c5c9c331914b"
#define BLE_CHARACTERISTIC3_UUID  "beb5483e-50e1-4688-b7f5-ea07361b26a8"
#define UUID_CHARACTERISTIC_WINNER  "beb5483e-51e1-4688-b7f5-ea07361b26a8"

//=========================== motor ==============================
#define BLE_SERVICE4_UUID "4fafc201-3fb5-459e-8fcc-c5c9c331914b"
#define BLE_CHARACTERISTIC4_UUID  "beb5483e-39e1-4688-b7f5-ea07361b26a8"

//========================== monitor =============================
#define UUID_SERVICE_MONI  "4fafc201-8fb5-459e-8fcc-c5c9c331914b"
#define UUID_CHARACTERISTIC_MONI  "beb5483e-55e1-4688-b7f5-ea07361b26a8"


BLEServer* pServer = NULL;
BLECharacteristic *pCharacteristic1 = NULL;
BLECharacteristic *pCharacteristic2 = NULL;
BLECharacteristic *pCharacteristic3 = NULL;
BLECharacteristic *pCharacteristic31 = NULL;
BLECharacteristic *pCharacteristic4 = NULL;
BLECharacteristic *pCharacteristic_line = NULL;
BLECharacteristic *pCharacteristic_bg = NULL;
BLECharacteristic *pCharacteristic_moni = NULL;

#define EEPROM_SIZE 64

#define BUTTON 7

#define PWM1_A 2
#define PWM1_B 10

#define PWM2_A 5
#define PWM2_B 6

#define IR_LED_ON 20
#define W_LED_ON  21

#define threshold 1000

#define den 1    
#define lam 2
#define luc 3
#define do 4   

uint32_t chipId = 0;

int color[5];
int mode,mode2;
int setc;
int st;
uint8_t data[3]; 
//extern int speed;
extern int zigac_check;
int speed1=120, speed2=120;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

int rc,gc,bc;
int oke;
void read_color(){
   uint16_t clear, red, green, blue;
  tcs.getRawData(&red, &green, &blue, &clear);
  float r, g, b;
  r = red;
  g = green;
  b = blue;
  
  r /= clear;
  g /= clear;
  b /= clear;

  r *= 255;
  g *= 255;
  b *= 255;
  data[0]=r;
  data[1]=g;
  data[2]=b;
  data[3]=detectColor(2,r, g, b);
   detectColor(2,r, g, b);
  Serial.print(rc);
  Serial.print("    ");
  Serial.print(gc);
  Serial.print("    ");
  Serial.println(bc);
  Serial.print("mau co:  " );
  Serial.println(detectColor(2,r, g, b));
  oke=detectColor(2,r, g, b);
  rc=r;
  gc=g;
  bc=b;
}

extern int rp1,gp1,bp1,rp2,gp2,bp2,rp3,gp3,bp3,rp4,gp4,bp4;
void EEPROMValues() {

 rp1=EEPROM.read(0);
 gp1=EEPROM.read(1);
 bp1=EEPROM.read(2);

 rp2=EEPROM.read(3);
 gp2=EEPROM.read(4);
 bp2=EEPROM.read(5);

 rp3=EEPROM.read(6);
 gp3=EEPROM.read(7);
 bp3=EEPROM.read(8);

 rp4=EEPROM.read(9);
 gp4=EEPROM.read(10);
 bp4=EEPROM.read(11);


  Serial.print(EEPROM.read(0));
  Serial.print("    ");
  Serial.print(EEPROM.read(1));
  Serial.print("    ");
  Serial.print(EEPROM.read(2));
  Serial.println("black");

   
   Serial.print(EEPROM.read(3));
  Serial.print("    ");
  Serial.print(EEPROM.read(4));
  Serial.print("    ");
  Serial.print(EEPROM.read(5));
  Serial.println("blue");


   Serial.print(EEPROM.read(6));
  Serial.print("    ");
  Serial.print(EEPROM.read(7));
  Serial.print("    ");
  Serial.print(EEPROM.read(8));
  Serial.println("green");

    Serial.print(EEPROM.read(9));
  Serial.print("    ");
  Serial.print(EEPROM.read(10));
  Serial.print("    ");
  Serial.print(EEPROM.read(11));
  Serial.println("red");


}


int d;
int dem;
void button(){
  if(digitalRead(BUTTON)==1) d=1; 
  if(digitalRead(BUTTON)==0&& d==1){
     dem++;
     d=0;
    
  }
  if(dem>1) dem=0;
}

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        Serial.println("Đã kết nối đến thiết bị BLE");
         mode2=1;
    }

    void onDisconnect(BLEServer* pServer) {
        mode=0;
        mode2=0;
        Serial.println("Thiết bị BLE đã ngắt kết nối");
        
    }
};

int st21, st22;
class MyCallbacks1 : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        Serial.print("Nhận được dữ liệu BLE từ Service 1: ");
        mode2=1;
       // game=1;
        for (int i = 0; i < value.length(); i++) {
            Serial.print(int (value[0])); // action
            Serial.print("   --  "); // speed
            Serial.print(int (value[1])); // action
            Serial.print("   --  "); // speed
            Serial.print(int (value[2])); // action
            Serial.print("   --  "); // speed
            Serial.print(int (value[3])); // action
            Serial.print("   --  "); // speed
            Serial.println(st); // action



          if(int (value[0])==1) st=1;
          if(int (value[0])==2) st=2;
          if(int (value[0])==3) st=3;
          if(int (value[0])==4) st=4;
          if(int (value[0])==5) st=5;
          if(int (value[0])==6) st=6;
          if(int (value[0])==7) st=7;
          if(int (value[0])==8) st=8;
          if(int (value[0])==9) st=9;

          if(int (value[0])==16) st=10;
          if(int (value[0])==17) st=11;
          if(int (value[0])==18) st=12;
          if(int (value[0])==19) st=13;
          if(int (value[0])==20) st=14;
          if(int (value[0])==21) st=15;
          if(int (value[0])==22) st=16;
          if(int (value[0])==23) st=17;
          if(int (value[0])==24) st=18;
          if(int (value[0])==25) st=31;
// ======================= mode 1============================
          if(int (value[0])==34) st=34;
          if(int (value[0])==32) st=32;
          if(int (value[0])==35) st=35;
          if(int (value[0])==33) st=33;

//======================== mode 2===========================          
          if(int (value[0])==36) st21=36;
          if(int (value[0])==37) st21=37;
          if(int (value[0])==38) st21=38;

          if(int (value[2])==39) st22=39;
          if(int (value[2])==40) st22=40;
          if(int (value[2])==41) st22=41;


           speed1=int (value[1]);
          if(speed1>70)speed1=70;

          speed2=int (value[3]);
          if(speed2>70)speed2=70;

          if(int (value[0])==0) {
            st=0;
            st22=0;
            st21=0;

          }

        }
    }
};

class MyCallbacks2 : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        Serial.print("Nhận được dữ liệu BLE từ Service 2: ");
        mode=1;
        for (int i = 0; i < value.length(); i++) {
            Serial.println(int (value[i]));
            if(int (value[i])==1) setc=1; //black
            if(int (value[i])==2) setc=2;// blue
            if(int (value[i])==3) setc=3;// green
            if(int (value[i])==4) setc=4;// red
        }
    }
};

int cuop_co, game;
class MyCallbacks3 : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        game=2;// game
        Serial.print("Nhận được dữ liệu BLE từ Service 3: ");
        for (int i = 0; i < value.length(); i++) {
            Serial.println(int (value[i]));
          if(int (value[0])==1) cuop_co=1;
          if(int (value[0])==2) cuop_co=2;
          if(int (value[0])==3) cuop_co=3;
          if(int (value[0])==4) cuop_co=4;

        }
    }
};


class MyCallbacks4 : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        Serial.print("Nhận được dữ liệu BLE từ Service 4: ");
        for (int i = 0; i < value.length(); i++) {
            Serial.println(int (value[i]));
  

        }
    }
};

class MyCallbacks_line : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        Serial.print("Nhận được dữ liệu BLE từ Service line: ");
        for (int i = 0; i < value.length(); i++) {
            Serial.println(int (value[i]));
  

        }
    }
};


class MyCallbacks_bg : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        Serial.print("Nhận được dữ liệu BLE từ Service bg: ");
        for (int i = 0; i < value.length(); i++) {
            Serial.println(int (value[i]));
  

        }
    }
};

class MyCallbacks_moni : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        Serial.print("Nhận được dữ liệu BLE từ Service moni: ");
        for (int i = 0; i < value.length(); i++) {
            Serial.println(int (value[i]));
  

        }
    }
};

void send_winner(){
    pCharacteristic31->setValue("01");
    pCharacteristic31->notify("01");
}


void monitor(){
    pCharacteristic_moni->setValue(data, 4);
    pCharacteristic_moni->notify();
}

void setup_ble(){
  chipId = (uint32_t)ESP.getEfuseMac();  
  // Lấy 4 ký tự cuối của chipId
  char chipIdStr[9];
  sprintf(chipIdStr, "%08X", chipId);
  char bleName[14]; // "Cobot" + 4 ký tự hex + null kết thúc chuỗi
  sprintf(bleName, "Cobot%s", chipIdStr + 4); // Bắt đầu từ ký tự thứ 5 của chipIdStr

  // Khởi tạo BLE
    BLEDevice::init(bleName);
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

//========================================= Control =================================================
    BLEService *pService1 = pServer->createService(BLEUUID(BLE_SERVICE1_UUID));
    pCharacteristic1 = pService1->createCharacteristic(
        BLEUUID(BLE_CHARACTERISTIC1_UUID),
        BLECharacteristic::PROPERTY_WRITE
    );
    pCharacteristic1->setCallbacks(new MyCallbacks1());
    pService1->start();
//====================================== calib ====================================================
    BLEService *pService2 = pServer->createService(BLEUUID(BLE_SERVICE2_UUID));
    pCharacteristic2 = pService2->createCharacteristic(
        BLEUUID(BLE_CHARACTERISTIC2_UUID),
        BLECharacteristic::PROPERTY_WRITE
    );

    pCharacteristic2->setCallbacks(new MyCallbacks2());

    pCharacteristic_line = pService2->createCharacteristic(
        BLEUUID(UUID_CHARACTERISTIC_LINE_COLOR),
        BLECharacteristic::PROPERTY_WRITE
    );
    pCharacteristic_line->setCallbacks(new MyCallbacks_line());

    pCharacteristic_bg = pService2->createCharacteristic(
        BLEUUID(UUID_CHARACTERISTIC_BG_COLOR),
        BLECharacteristic::PROPERTY_WRITE
    );
    pCharacteristic_bg->setCallbacks(new MyCallbacks_bg());

    pService2->start();

//===================== service game=========================================
    BLEService *pService3 = pServer->createService(BLEUUID(BLE_SERVICE3_UUID));
    pCharacteristic3 = pService3->createCharacteristic(
        BLEUUID(BLE_CHARACTERISTIC3_UUID),
        BLECharacteristic::PROPERTY_NOTIFY| BLECharacteristic::PROPERTY_WRITE 
    );
    pCharacteristic3->setCallbacks(new MyCallbacks3());

    pCharacteristic31 = pService3->createCharacteristic(
        BLEUUID(UUID_CHARACTERISTIC_WINNER),
         BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    pCharacteristic31->setCallbacks(new MyCallbacks3());

    pService3->start();
//=================================== motor ========================================================
    BLEService *pService4 = pServer->createService(BLEUUID(BLE_SERVICE4_UUID));
    pCharacteristic4 = pService4->createCharacteristic(
        BLEUUID(BLE_CHARACTERISTIC4_UUID),
        BLECharacteristic::PROPERTY_WRITE
    );
    pCharacteristic4->setCallbacks(new MyCallbacks4());
    pService4->start();

//=================================== monitor ========================================================
    BLEService *pService_moni = pServer->createService(BLEUUID(UUID_SERVICE_MONI));
    pCharacteristic_moni = pService_moni->createCharacteristic(
        BLEUUID(UUID_CHARACTERISTIC_MONI),
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
    );
    pCharacteristic_moni->setCallbacks(new MyCallbacks_moni());
    pService_moni->start();
//=====================================================================================================================


    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
}


int state(){
     if(color[0]==do && color[1]==lam && color[2]==luc) st=1;//
else if(color[0]==do && color[1]==den && color[2]==luc) st=2;//
else if(color[0]==do && color[1]==lam && color[2]==den) st=3;//
else if(color[0]==do && color[1]==luc && color[2]==lam) st=4;//
else if(color[0]==do && color[1]==den && color[2]==lam) st=5;//
else if(color[0]==do && color[1]==luc && color[2]==den) st=6;//
else if(color[0]==lam && color[1]==do && color[2]==luc) st=7;//
else if(color[0]==lam && color[1]==den && color[2]==luc) st=8;//
else if(color[0]==lam && color[1]==do && color[2]==den) st=9;//
else if(color[0]==lam && color[1]==luc && color[2]==do) st=10;//
else if(color[0]==lam && color[1]==den && color[2]==do) st=11;//
else if(color[0]==lam && color[1]==luc && color[2]==den) st=12;//
else if(color[0]==luc && color[1]==do && color[2]==lam) st=13;//
else if(color[0]==luc && color[1]==den && color[2]==lam) st=14;//
else if(color[0]==luc && color[1]==do && color[2]==den) st=15;//
else if(color[0]==luc && color[1]==lam && color[2]==do) st=16;
else if(color[0]==luc && color[1]==den && color[2]==do) st=17;
else if(color[0]==luc && color[1]==lam && color[2]==den) st=18;

 return st;
}


void mode2_run(){

  if(st21==36){
left_wheel(speed1*2.55,1);
  }
 if(st21==37){
left_wheel(0,1);
  }
 if(st21==38){
left_wheel(speed1*2.55,0);
  }


  if(st22==39){
  right_wheel(speed2*2.55,1);  
  }
  if(st22==40){
  right_wheel(0,1);  
  }
  if(st22==41){
  right_wheel(speed2*2.55,0);  
  }
 
}


void setup() {
    Serial.begin(115200);
 if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }
  Serial.println(" bytes read from Flash . Values are:");
  for (int i = 0; i < EEPROM_SIZE; i++)
  {
    Serial.print(byte(EEPROM.read(i))); Serial.print(" ");
  }

  setup_ble();
  pinMode(BUTTON,INPUT_PULLUP);
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

  setup_follow();
  stop();


}


void loop() {
  read_color();
  button();
  if(dem==0) stop();

while(dem==1){
  read_color();  
  Serial.print("trang thai: ");
  Serial.println(state());
  button();
  EEPROMValues();
  nhan_vach_ngang();
monitor();
  switch(state()){
  case 0:  // bt
     if(mode2==0) run_follow(zigac_check);
     else stop();
     break;  

  case 1: // 30%
     speed1=thirty();
     st=0;
     reset();
     break;
  case 2: // 45%
     speed1=forty_five(); 
     st=0;
     reset();
     break;
  case 3: // 60%
     speed1=sixty();
     st=0;
     reset();
     break;
  case 4: // 70%
    speed1=seventy();
     st=0;
     reset();
     break;
  case 5: // 85%
     speed1=eighty_five();
     st=0;
     reset();
     break;               
  case 6: // 100%
     speed1=one_hundred();
     st=0;
     reset();
     break;
  case 7: // re trai
     //if(nhan_vach_ngang()==1) 
     turn_left();
     st=0;
     reset();
     break;
  case 8: // re phai
     //if(nhan_vach_ngang()==1) 
     turn_right();
     st=0;
     reset();
     break;               
  case 9: // 180 do
     half_rotate();
     st=0;
     reset();
     break;
  case 10: // cong trai
    left_circle();
     st=0;
     reset();
     break;
  case 11: // cong phải
     right_circle();
     st=0;
     reset();
     break;
  case 13: // rotate
    rotate();
     st=0;
     reset();
     break;
  case 14: // zigzac
    //run_zigzac();
    zigac_mode();
     st=0;
     reset();
     break;
  case 15: // square
     square();
     st=0;
     reset();
     break;
  case 16: // quay tròn
     round();
     st=0;
     reset();
     break;
   case 17: // lùi
     backward(150);
     delay(500);
     st=0;
     reset();
     break;    
   case 18: // dung
    mode2=1;
    dem=0;
     reset();
     break;   
  

  case 34: // tien
     forward(speed1*2.55);
     break;
  case 33: // trai
     left(speed1*1.55); 
     break;
  case 35: // phai
     right(speed1*1.55);
     break;
  case 32: // lui
     backward(speed1*2.55); 
     break;


}


 mode2_run();

if(game==2){
 if(oke==cuop_co)  send_winner();

}


  delay(10);
  }


while(mode==1){
  read_color();
  stop();
if(setc==1){
              EEPROM.write(0, rc);
              EEPROM.write(1, gc);
              EEPROM.write(2, bc);
              EEPROM.commit();
              delay(500);
              setc=0;
              Serial.println("ok");

}

if(setc==2){
              EEPROM.write(3, rc);
              EEPROM.write(4, gc);
              EEPROM.write(5, bc);
              EEPROM.commit();
              delay(500);
              setc=0;
              Serial.println("ok");

}



if(setc==3){
              EEPROM.write(6, rc);
              EEPROM.write(7, gc);
              EEPROM.write(8, bc);
              EEPROM.commit();
              delay(500);
              setc=0;
              Serial.println("ok");

}


if(setc==4){
              EEPROM.write(9, rc);
              EEPROM.write(10, gc);
              EEPROM.write(11, bc);
              EEPROM.commit();
              delay(500);
              setc=0;
              Serial.println("ok");

}


}

}
