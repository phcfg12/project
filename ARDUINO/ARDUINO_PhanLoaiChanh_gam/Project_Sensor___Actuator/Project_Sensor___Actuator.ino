// cb vat can hong ngoai
int cambien = 2;
int giatri;

// servo motor
#include <Servo.h>
int servo = 9;
Servo myServo;
 
// load cell & lcd
#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>   // thư viện sử dụng lcd giao tiếp với i2c 
#define LOADCELL_DOUT_PIN  6
#define LOADCELL_SCK_PIN  7
LiquidCrystal_I2C lcd(0x27, 16,2);

HX711 scale;

float calibration_factor = 445.5182051;//trọng số

// stepper motor
int tep = 5;
int dir = 4;
int ena = 3;

int a=0;
int b=0;
int c=0;
void setup() {
  // cb vat can hong ngoai
  Serial.begin(9600);
  pinMode(cambien, INPUT);

  // servo motor
    
  myServo.attach(servo);

  // load cell & lcd
  Serial.begin(9600);
  scale.set_scale(calibration_factor);
  scale.begin (LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.tare();  //đặt lại giá trị về 0
 
  lcd.init(); // Khởi động màn hình LCD, bắt đầu cho phép Arduino sử dụng màn hình
  lcd.backlight();  // Bật đèn nền LCD 16×2

  // stepper motor
  
  pinMode(ena,OUTPUT); // Enable pin dùng để khởi động motor
  pinMode(tep,OUTPUT); // Step chân xung
  pinMode(dir,OUTPUT); // Dir xác định chiều quay
  digitalWrite(ena,HIGH); 
}

void loop() {
  // cb vat can hong ngoai
  myServo.write(0);
  Serial.print("gia tri cua cam bien vat can:\t");
  Serial.print(giatri);
  Serial.print("\n");
  giatri = digitalRead(cambien); //Đọc giá trị digital từ cảm biến và gán vào biến giatri
  if(giatri==0){
    a=a+1;
    while(a>0 && b==0){
      myServo.write(90);
      delay(2000);
      myServo.write(0);
      delay(2000);
      b=b+1;
      break;
    }
  }

  // load cell & lcd
  scale.set_scale(calibration_factor);  //điều chỉnh theo trọng số ban đầu
 
  float weight = scale.get_units(10); // lấy giá trị trung bình của 10 lần đọc
  if (weight <= 0.1) {
    weight = 0;
  }

  Serial.print("weight:\t");
  Serial.print(scale.get_units());
  Serial.print("\n");

  lcd.setCursor(0, 0); // dat con tro ve hang dau tien
  lcd.print("Weight[g]:");
  lcd.setCursor(0, 1); // dat con tro den hang thu hai
  lcd.print(weight); // in gia tri weight vao hang thu 2
  delay(2000);
  // stepper motor
  if(weight>=50){
    digitalWrite(ena,LOW); // Set Enable LOW - khởi động motor
    digitalWrite(dir,LOW); //Chân dir dùng để xác định chiều quay (hoặc thay đổi dây của motor)
    for(int x = 0; x < 800; x++) //Quay 1/4 vòng
    {
      digitalWrite(tep,HIGH); // Cạnh lên
      delayMicroseconds(1000); //Thời gian xuất xung = tốc độ quay
      digitalWrite(tep,LOW); // Cạnh xuống
      delayMicroseconds(1000);
    }
    Delay(2000, can);
    digitalWrite(dir,HIGH); //ngược
    for(int x = 0; x < 800; x++) //Quay 1/4 vòng
    {
      digitalWrite(tep,HIGH); // Cạnh lên
      delayMicroseconds(1000); //Thời gian xuất xung = tốc độ quay
      digitalWrite(tep,LOW); // Cạnh xuống
      delayMicroseconds(1000);
    }
    Delay(2000, can);
    c=0;
  }
  if(weight<50 && weight>5){
    digitalWrite(ena,LOW); // Set Enable LOW - khởi động motor
    digitalWrite(dir,HIGH); //Chân dir dùng để xác định chiều quay (hoặc thay đổi dây của motor)
    for(int x = 0; x < 800; x++) //Quay 1/4 vòng
    {
      digitalWrite(tep,HIGH); // Cạnh lên
      delayMicroseconds(1000); //Thời gian xuất xung = tốc độ quay
      digitalWrite(tep,LOW); // Cạnh xuống
      delayMicroseconds(1000);
    }
    Delay(2000, can);
    digitalWrite(dir,LOW); //ngược
    for(int x = 0; x < 800; x++) //Quay 1/4 vòng
    {
      digitalWrite(tep,HIGH); // Cạnh lên
      delayMicroseconds(1000); //Thời gian xuất xung = tốc độ quay
      digitalWrite(tep,LOW); // Cạnh xuống
      delayMicroseconds(1000);
    }
    Delay(2000, can);
    c=0;
  }
  if(c==0){
    b=0;
  }
}

void can(){
  scale.set_scale(calibration_factor);  //điều chỉnh theo trọng số ban đầu
 
  float weight = scale.get_units(10); // lấy giá trị trung bình của 10 lần đọc
  if (weight <= 0.1) {
    weight = 0;
  }
  lcd.setCursor(0, 0); // dat con tro ve hang dau tien
  lcd.print("Weight[g]:");
  lcd.setCursor(0, 1); // dat con tro den hang thu hai
  lcd.print(weight); // in gia tri i vao hang thu 2
  
}
void Delay(float delayTime, void (func)()){
    unsigned long endTime = millis() + delayTime;
    while(millis() < endTime)
    {
      func();
    }
}