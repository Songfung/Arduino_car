
#include <Servo.h>
#include <SoftwareSerial.h>
 SoftwareSerial BT(12,13);//RX,TX


// L298N 馬達驅動板
// 宣告 MotorA 為右邊
// 宣告 MotorB 為左邊

#define MotorA_I1     8  //定義 I1 接腳
#define MotorA_I2     9  //定義 I2 接腳
#define MotorB_I3    10  //定義 I3 接腳
#define MotorB_I4    11  //定義 I4 接腳
#define MotorA_PWMA    5  //定義 PWMA (PWM調速) 接腳
#define MotorB_PWMB    6  //宣告 PWMB (PWM調速) 接腳






//定義RGB腳位

int ledpin_R=10;
int ledpin_G=5;
int ledpin_B=6;


void setup()
{
  Serial.begin(9600); 
  BT.begin(38400);
  
  pinMode(MotorA_I1,OUTPUT);
  pinMode(MotorA_I2,OUTPUT);
  pinMode(MotorB_I3,OUTPUT);
  pinMode(MotorB_I4,OUTPUT);
  pinMode(MotorA_PWMA,OUTPUT);
  pinMode(MotorB_PWMB,OUTPUT);
  
  analogWrite(MotorA_PWMA,200);    //設定馬達 (右) 轉速
  analogWrite(MotorB_PWMB,200);    //設定馬達 (左) 轉速


 
    pinMode(ledpin_R,OUTPUT);
    pinMode(ledpin_G,OUTPUT);
    pinMode(ledpin_B,OUTPUT);


}

void advance(int a)    // 前進
{
    digitalWrite(MotorA_I1,LOW);   //馬達（右）順時針轉動
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,LOW);   //馬達（左）逆時針轉動
    digitalWrite(MotorB_I4,HIGH);
    delay(a * 10);
}

void turnR(int d)    //右轉
{   
  digitalWrite(MotorA_I1,HIGH);   //馬達（右）順時針轉動
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,LOW);    //馬達（左）順時針轉動
    digitalWrite(MotorB_I4,HIGH);
    
    delay(d * 10);
}

void turnL(int e)    //左轉
{
    digitalWrite(MotorA_I1,LOW);    //馬達（右）逆時針轉動
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,HIGH);   //馬達（左）逆時針轉動
    digitalWrite(MotorB_I4,LOW);
    delay(e * 10);
}    

void stopRL(int f)  //停止
{
    digitalWrite(MotorA_I1,LOW);   //馬達（右）停止轉動
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,LOW);   //馬達（左）停止轉動
    digitalWrite(MotorB_I4,LOW);
    delay(f * 10);
}

void back(int g)    //後退
{
    digitalWrite(MotorA_I1,HIGH);    //馬達（右）逆時針轉動
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,HIGH);    //馬達（左）順時針轉動
    digitalWrite(MotorB_I4,LOW);
    delay(g * 10);     
}



void rgb()
{
  int r=0;
  int g=255;
  int b=255;

  for(int i=0;i<255;i++){
      analogWrite(10,r);
      analogWrite(5,g);
      analogWrite(6,b);
      g++; 
      delay(3);
    }

  for(int i=0;i<255;i++){
         analogWrite(10,r);
         analogWrite(5,g);
         analogWrite(6,b);
         g--;  
         delay(3);  
  
    }
  for(int i=0;i<255;i++){
        analogWrite(10,r);
        analogWrite(5,g);
        analogWrite(6,b);
        r--;
        delay(3);
      }

      for(int i=0;i<255;i++){
        analogWrite(10,r);
        analogWrite(5,g);
        analogWrite(6,b);
        g++; 
        delay(3);                 
      }

}



void loop()
{

  rgb();
  
      advance(120);//square
      turnL(28);
      advance(120);
      turnL(30);
      advance(120);
      turnL(30);
      advance(120);
      turnL(29);
      
      advance(60);
      turnL(32);
      
      advance(120);//T step
      turnL(30);
      advance(60);
      back(60);
      turnR(34);
       back(120);
       advance(120);

       turnR(28);
       advance(60);
       back(60);
       turnL(28); 
       back(60);
       
       
       
       

      
      turnL(150);// turn two rounds
      turnR(150);

  

  int cmd = Serial.read();  // 讀取藍芽訊號並於下方進行判斷
    
  switch(cmd)  // 執行藍芽對應指令
  {
    case 'B':  // 倒車
      back(50);
      break;
 
    case 'L':  // 左轉
      turnL(40);
      break;
        
    case 'R':  // 右轉
      turnR(30);
      break;
      
    case 'F':  // 前進
      advance(80);     
      break;
        
    case 'S':  // 停止
        stopRL(5);
        break;
        
  ////////////////////////////////////////////////////////
  //  您可以額外再自行定義指令，搭配藍芽或 PC端遙控軟體
  //  新增的指令可以採用 case 來宣告特定接收字元運作，並
  //  使用 break; 來終止。
  ////////////////////////////////////////////////////////

    case 'T':  // 自我檢測
        break;
        
    case 'J':  // 舞蹈
        break;
        
    case 'N':  // 超音波測距查詢
        break;
  }

  
}


 




  
