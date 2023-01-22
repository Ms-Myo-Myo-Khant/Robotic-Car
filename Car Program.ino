#include<Servo.h>

#define leftServo 9
#define rightServo 11
#define backServo 7
//#define armServo1 8
#define armServo2 10

Servo LEFT, RIGHT, ARM2, BACK;  //ARM1
bool armCon=false;
bool liftCon=false;
bool collectorCon=false;

#define ENA 3
#define ENB 5

#define IN1  14         
#define IN2  15         
#define IN3  16         
#define IN4  17

String received_data;
int speedRight=255, speedLeft=255  ;

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
    
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  LEFT.attach(leftServo);
  RIGHT.attach(rightServo);
  //ARM1.attach(armServo1);
  ARM2.attach(armServo2);
  BACK.attach(backServo);

  //ARM1.write(10);
  ARM2.write(10);
  delay(300);
  LEFT.write(30);
  RIGHT.write(140);
  delay(300);
  BACK.write(100);
  delay(300);
} 

void loop() {
  analogWrite(ENA,speedRight);
  analogWrite(ENB,speedLeft);
  
  if(Serial.available())
  {
    delay(100);
    received_data="";
    while(Serial.available())
    {
      char c=Serial.read();
      received_data+=c;
    }
    Serial.println(received_data);
  }
  
  if(received_data=="upPressed"){
    forward();
  }
  else if(received_data=="upReleased"){
    Stop();
  }
  else if(received_data=="downPressed"){
    backward();
  }
  else if(received_data=="downReleased"){
    Stop();
  }
  else if(received_data=="leftPressed"){
    left();
  }
  else if(received_data=="leftReleased"){
    Stop();
  }
  else if(received_data=="rightPressed"){
    right();
  }
  else if(received_data=="rightReleased"){
    Stop();
  }
  else if(received_data=="trianglePressed" || received_data=="triangletReleased"){
    Stop();
  }

  if(received_data=="xPressed"){
    if(armCon==true)
    {
      //ARM1.write(60);
      ARM2.write(60);
      armCon=false;
      delay(500);
    }
    else
    {
      //ARM1.write(0);
      ARM2.write(0);
      armCon=true;
      delay(500);
    }
  }
  if(received_data=="squarePressed"){
     if(liftCon==true)
     {
      LEFT.write(30);
      delay(10);
      RIGHT.write(140);
      delay(1000);
      //ARM1.write(0);
      //ARM2.write(0);
      //delay(300);
      liftCon=false;
     }
     else
     {
      LEFT.write(180);
      delay(10);
      RIGHT.write(0);
      delay(1000);
      liftCon=true;
     }
  }
  if(received_data=="circlePressed"){
    if(collectorCon==true)
    {
      BACK.write(100);
      delay(1000);
      collectorCon=false;
    }
    else
    {
      BACK.write(0);
      delay(1000);
      collectorCon=true;
    }
  }
}

void Stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void forward()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void backward()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void left()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void right()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
