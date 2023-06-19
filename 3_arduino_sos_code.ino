int sensorPin = A0;   
int ledPin = 11;      
int sensorValue = 0;  
int count = 0;
int sw1 = 12;
int NSP = 255;
int val ;

#include <Wire.h> //LCD 라이브러리
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); //LCD 라이브러리

#include <SoftwareSerial.h> //HC_06라이브러리
SoftwareSerial mySerial(2,3); //HC_06라이브러리

void setup() {
  Serial.begin(9600); //9600 PC시리얼 모니터 통신
  mySerial.begin(9600);//아두이노-블루투스모듈간 통신
  
  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기
  lcd.setCursor(0,0); //LCD 1번째 줄에
  lcd.print("COUNTER:00000000"); //제목을 출력
  lcd.setCursor(0,1); //LCD 2번째 줄에
  lcd.print("Calorie:00000000"); //제목을 출력 
  
  pinMode(ledPin, OUTPUT); //LED 출력
  pinMode(sw1, INPUT); //스위치 입력
  pinMode(10,OUTPUT); //DC모터 출력

  analogWrite(10, 0); //DC모터 정지
  delay(1000); // 지연시간
}

void loop() {
  float cal = count*0.29; //근접센서 코드
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue); //시리얼 모니터 출력
  delay(400); // 지연시간
  if(sensorValue>600)
  {
    digitalWrite(ledPin, HIGH); 
  }
  else
    digitalWrite(ledPin, LOW); //근접센서 코드
    
 if(digitalRead(11) == HIGH){
    lcd.setCursor(8,0); //LCD 1번째 줄에
    lcd.print(count); //count값 출력
    delay(500);  //지연시간
    count++;  //count1씩증가
    lcd.setCursor(8,1); //LCD 2번째 줄에
    lcd.print(cal); //cal값 출력
    } 
     
 if(count>2) //count가 조건값이 되면
 {
 analogWrite(10, NSP); //DC모터 if문 조건값 만족시 실행
 }
 else{
 analogWrite(10,LOW); //DC모터 조건 불충족시 정지
 }

 mySerial.print("카운트"); //앱인벤터 카운터 출력
 mySerial.print(count);//앱인벤터 카운터값 출력
 mySerial.print("칼로리"); //앱인벤터 칼로리 출력
 mySerial.print(cal); //앱인벤터 칼로리값 출력
 delay(2000); // 지연시간

if(digitalRead(sw1) == LOW) //스위치가 눌리면
    {
    lcd.setCursor(0,0); //LCD 1번째 줄에
    lcd.print("COUNTER:00000000"); //제목을 출력
    lcd.setCursor(0,1); //LCD 2번째 줄에
    lcd.print("Calorie:00000000"); //제목을 출력 
    lcd.setCursor(8,0); //LCD 1번째 줄에
    lcd.print(count = 0); //count 0으로 초기화
    delay(500);  //지연시간
    lcd.setCursor(8,1); //LCD 2번째 줄에  
    lcd.print(count = 0); //count 0으로 초기화
    }
}
