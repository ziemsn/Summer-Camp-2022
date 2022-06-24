#include <LiquidCrystal.h>

const int irLED = A1;
const int resetButton = 6;

int irState;
int penaltyState;
int resetState = 0;
int restartState;

int h = 0;
int m = 0;
int s = 0;
int ms = 0;

int bestH = 100;
int bestM = 59;
int bestS = 59;
int bestMS = 590;


const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void StopWatch() {

  lcd.setCursor(1,0);
  lcd.print("TIME: ");
  lcd.print(h);
  lcd.print(":");
  lcd.print(m);
  lcd.print(":");
  lcd.print(s);
  lcd.print(".");
  lcd.print(ms);

  ms += 10;
  delay(10);

  if(ms == 590){
    ms = 0;
    s +=1;
  }
  if (s == 60){
    s = 0;
    m += 1;
  }
  if (m == 60){
    m = 0;
    h += 1;
  }

  irState = analogRead(irLED);
  resetState = digitalRead(resetButton);

  if (restartState == HIGH){
    lcd.clear();  
    h = 0;
    m = 0;
    s = 0;
    ms = 0;
    bestH = 0;
    bestM = 0;
    bestS = 0;
    bestMS = 0;
    return;
  }
  

  if ((irState < 100) && (s > 5)){
    if(m < bestM){

    bestH = h;
    bestM = m;
    bestS = s;
    bestMS = ms;
  }
    StopWatch_Stop();
  }
  if (resetState == HIGH){
    StopWatch_Reset();
  }

  else{
    StopWatch();
  }
}

void StopWatch_Stop(){
 
//  lcd.setCursor(0,1);
//  lcd.print("BEST TIME: ");
//  lcd.print(bestH);
//  lcd.print(":");
//  lcd.print(bestM);
//  lcd.print(":");
//  lcd.print(bestS);
//  lcd.print(".");
//  lcd.print(bestMS);
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("STOPWATCH");
  lcd.setCursor(1,0);
  lcd.print("TIME: ");
  lcd.print(h);
  lcd.print(":");
  lcd.print(m);
  lcd.print(":");
  lcd.print(s);
  lcd.print(".");
  lcd.print(ms);
 
  resetState = digitalRead(resetButton);


  if (restartState == HIGH){
    lcd.clear();  
    h = 0;
    m = 0;
    s = 0;
    ms = 0;
    bestH = 0;
    bestM = 0;
    bestS = 0;
    bestMS = 0;
    return;
  }
  
  if (resetState == HIGH){
    StopWatch_Reset();
    loop();
  }

  if (resetState == LOW){
    StopWatch_Stop();
  }
}

void StopWatch_Reset(){

  lcd.clear();  
  h = 0;
  m = 0;
  s = 0;
  ms = 0;
  return;
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
 
  pinMode(irLED, INPUT);
  pinMode(resetButton, INPUT);

}

void loop() {
  
  irState = analogRead(irLED);
  resetState = digitalRead(resetButton);

  Serial.print(irState);
  Serial.print(", ");
  Serial.println(resetState);
 
  lcd.setCursor(3,1);
  lcd.print("STOPWATCH");
  lcd.setCursor(1,0);
  lcd.print("TIME: ");
  lcd.print(h);
  lcd.print(":");
  lcd.print(m);
  lcd.print(":");
  lcd.print(s);
  lcd.print(".");
  lcd.print(ms);

  if (irState < 100){
    StopWatch();
  }

  if (restartState == HIGH){
    lcd.clear();  
    h = 0;
    m = 0;
    s = 0;
    ms = 0;
    bestH = 0;
    bestM = 0;
    bestS = 0;
    bestMS = 0;
    return;
  }
}
