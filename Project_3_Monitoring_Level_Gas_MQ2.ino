#include <MQ2.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int Analog_Input = A0;
int lpg, co, smoke;

MQ2 mq2(Analog_Input);

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();
  mq2.begin();
}
void loop(){
  float* values= mq2.read(true); //set it false if you don't want to print the values in the Serial
  //lpg = values[0];
  lpg = mq2.readLPG();
  //co = values[1];
  co = mq2.readCO();
  //smoke = values[2];
  smoke = mq2.readSmoke();
 // Serial.setCursor(0,0);
  Serial.print("LPG:");
  Serial.print(lpg);
  Serial.print(" CO:");
  Serial.print(co);
//  Serial.setCursor(0,1);
  Serial.print("SMOKE:");
  Serial.print(smoke);
  Serial.print(" PPM");
  delay(1000);
}

