#include <Adafruit_TCS34725.h>
#include <Wire.h>
 
/*
  SCL - SCL ( Analog 5 )
  SDA - SDA ( analog 4 )
  VDD - 3.3V DC
  GND - GND
*/
 
//  Sử dụng cảm biến ở giá trị mặc định (int time = 2.4ms, gain = 1x)
//Adafruit_TCS34725 tcs = Adafruit_TCS34725();
 
/* Sử dụng cảm với thời gian cụ thể và Gain cụ thể
 * integration time (Thời gian lấy mẫu màu của cảm biến): 2.4ms, 24ms, 50ms, 101ms, 154ms, 700ms
 * Gain (Độ lợi kiểm soát độ nhạy màu của biến): 1x, 4x, 16x, 60x
 */

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_4X);
 
void setup() 
{
  Serial.begin(9600);
 
  if (tcs.begin()) 
  {
    Serial.println("Cảm biến hoạt động");
  } 
  else 
  {
    Serial.println("Cảm biến không kết nối, hãy kiểm tra lại kết nối...");
    while (1);
  }
  
}
 
void loop() 

{
    uint16_t r, g, b, c, colorTemp, lux;
     
    tcs.getRawData(&r, &g, &b, &c);
    
    colorTemp = tcs.calculateColorTemperature(r, g, b); //Nhiệt độ màu theo thang đo Kelvin
    
    lux = tcs.calculateLux(r, g, b); //Độ rọi soi, cường độ sáng
     
    Serial.print("Color Temp: "); Serial.print(colorTemp); Serial.print(" K - ");
    Serial.print("Lux: "); Serial.print(lux); Serial.print(" - ");
    Serial.print("Red: "); Serial.print(r); Serial.print(" ");
    Serial.print("Green: "); Serial.print(g); Serial.print(" ");
    Serial.print("Blue: "); Serial.print(b); Serial.print(" ");
    Serial.print("Clear: "); Serial.print(c); Serial.print(" ");
    Serial.println(" ");

    if(c>r && c>g && c>b && lux>500) //Không có màu
    {
      Serial.println(" Màu sắc hiện tại là: KHÔNG CÓ MÀU");
      Serial.println(" ");
    }
    else if(r>g && r>b && r<c && lux>10 && lux<100) //Màu đỏ
    {
      Serial.println(" Màu sắc hiện tại là: MÀU ĐỎ");
      Serial.println(" ");  
    }
    else if(g>r && g>b && g<c && lux>200 && lux<300) //Màu lục
    {
      Serial.println(" Màu sắc hiện tại là: MÀU LỤC");
      Serial.println(" ");         
    }
    else if(b>r && b>g && b<c && lux>100 && lux<200) //Màu xanh biển
    {
      Serial.println(" Màu sắc hiện tại là: MÀU XANH BIỂN");
      Serial.println(" ");        
    }
}
