// include the library code:
#include <LiquidCrystal.h>


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const float count = 0;
const int lm35Pin = A0;
int flag = 0 ;
float v_value = 0;
float voltage = 0;

float sensitivity = 0.100;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT);
  pinMode(A3, INPUT);
  digitalWrite(7, HIGH);
  pinMode(8, OUTPUT);
  lcd.begin(16, 2);

}

void loop() {

  int count_cell = analogRead(A3);
  float voltage_cell = (float)( count_cell * 28.0 ) / 1024;

  if ( digitalRead(7)) {
    if (voltage_cell <= 4.5 && flag == 0) {
      digitalWrite(8, HIGH);
    }
  }
  else {
    digitalWrite(8, LOW);
  }

  int count = analogRead(A1);
  float current = (count - 512) * (5.0 / 1024.0) / sensitivity;

  float sensorValue = (float)analogRead(lm35Pin);
  sensorValue = ((sensorValue) * 4.88) / 10;
  float temperatureCelsius = sensorValue;

  v_value = analogRead(A2);
  voltage = (v_value * 25) / 1023;
  if (temperatureCelsius > 50) {
    flag = 1;
  }
  else {
    flag = 0;
  }

  lcd.setCursor(0 , 0);
  // print the number of seconds since reset:
  lcd.print("cu");
  lcd.print(current);
  lcd.print("A ");
  lcd.print("T");
  lcd.print(temperatureCelsius);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("V ");
  lcd.print(voltage);
  lcd.print(" cel ");
  lcd.print(voltage_cell);

  Serial.print("cur ");
  Serial.print(" ");
  Serial.print(current);
  Serial.print(" ");

  Serial.print(temperatureCelsius);
  Serial.print(" ");
  Serial.print("vol");
  Serial.print("  ");
  Serial.print(voltage );
  Serial.print("vol");
  Serial.print("  ");
  Serial.println(voltage_cell );
  Serial.print("cout");
  Serial.print("  ");
  Serial.println(sensorValue);

  delay(500);
}
