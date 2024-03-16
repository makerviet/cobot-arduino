int a,c,i,a_old;
int rp1,gp1,bp1,rp2,gp2,bp2,rp3,gp3,bp3,rp4,gp4,bp4;
boolean check1,check2,check3,check4,check5;
extern  int color[5];
unsigned long time1;


void m(){
  color[i]=c;
  i++;
}
void reset(){
  a=0;
  i=0;
 color[0]=0;
 color[1]=0;
 color[2]=0;
   check1=false;
   check2=false;
   check3=false;
   check4=false;
}

int detectColor(int mode, float red, float green, float blue) {
int range=6;
int r1=rp1, g1=gp1, b1=bp1; //black
int r2=rp2, g2=gp2, b2=bp2;// blue
int r3=rp3, g3=gp3, b3=bp3;// green
int r4=rp4, g4=gp4, b4=bp4;// red



 if (red >= r1-range && red <=  r1+range && green >= g1-range && green <= g1+range && blue >= b1-range && blue <= b1+range){ //black
   c=1;
    if(check1==false){
             a++;
        m();
    }
   check1=true;
   check2=false;
   check3=false;
   check4=false;
 
 
 }
 if (red >= r2-range && red <=  r2+range && green >= g2-range && green <= g2+range && blue >= b2-range && blue <= b2+range){ // blue
   c=2;
    if(check2==false){
             a++;
        m();
    }
   check2=true;
   check1=false;
   check4=false;
   check3=false;
 
 
 }
 if (red >= r3-range && red <=  r3+range && green >= g3-range && green <= g3+range && blue >= b3-range && blue <= b3+range){ // green
  c=3;
    if(check3==false){
       a++;
        m();
    }
   check3=true;
   check1=false;
   check2=false;
   check4=false;
  
    
 }
 if (red >= r4-range && red <=  r4+range && green >= g4-range && green <= g4+range && blue >= b4-range && blue <= b4+range){// red
  c=4;
    if(check4==false){
             a++;
        m();
    }
   check4=true;
   check1=false;
   check2=false;
   check3=false;
   
 }



if(a>3){
  a=0;
 color[0]=0;
 color[1]=0;
 color[2]=0;
   check1=false;
   check2=false;
   check3=false;
   check4=false;
   i=0;
}
 a_old=a;

if((a_old-a)==0 && check5==false) {
  time1= millis();
  check5=true;
} 

if ( (unsigned long) (millis() - time1) > 1200)
    {
          reset();
          check5=false;
    }

//========= bỏ màu đen line=============
if ( color[0]==1)
    {
          reset();
    }



if(mode==2){
int mau;
   if (red >= r1-range && red <=  r1+range && green >= g1-range && green <= g1+range && blue >= b1-range && blue <= b1+range){ //black
    mau=1;
   }
   else if (red >= r2-range && red <=  r2+range && green >= g2-range && green <= g2+range && blue >= b2-range && blue <= b2+range){ // blue
     mau=2;
   }
   else if (red >= r3-range && red <=  r3+range && green >= g3-range && green <= g3+range && blue >= b3-range && blue <= b3+range){ // green
    mau=3;
   }
   else if (red >= r4-range && red <=  r4+range && green >= g4-range && green <= g4+range && blue >= b4-range && blue <= b4+range){// red
 
    mau=4;
    
   }
   else mau=0;
return mau;


}
  // Serial.print(color[0]);
  // Serial.print("    ");
  // Serial.print(color[1]);
  // Serial.print("    ");
  // Serial.print(color[2]);
  // Serial.print("...........");
  //  Serial.println(a);


//  Serial.print(r1);
//   Serial.print("    ");
//   Serial.print(g1);
//   Serial.print("    ");
//   Serial.print(b1);
//   Serial.print("black");
//    Serial.println(a);
   
//    Serial.print(r2);
//   Serial.print("    ");
//   Serial.print(g2);
//   Serial.print("    ");
//   Serial.print(b2);
//   Serial.print("blue");
//    Serial.println(a);

//    Serial.print(r3);
//   Serial.print("    ");
//   Serial.print(g3);
//   Serial.print("    ");
//   Serial.print(b3);
//   Serial.print("green");
//    Serial.println(a);
}
