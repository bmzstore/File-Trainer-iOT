#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define CommonSenseMetricSystem
#define trigPin 12//D6
#define echoPin 13//D7
#define OLED_RESET D5
Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 64)
//Koneksi LCD-> SCL Ke D1 dan SDA ke D2
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
void setup()   {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // SCL=D1  SDA=D2
  display.clearDisplay(); 
  display.setTextColor(WHITE); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  #ifdef CommonSenseMetricSystem
  distance = (duration/2) / 29.1;
  #endif
  #ifdef ImperialNonsenseSystem
  distance = (duration/2) / 73.914;
  #endif
  char time[30];
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2); 
  display.print("Ultrasonic");
  display.setCursor(8,30);
  display.setTextSize(4); 
  display.print(distance);
  display.setCursor(60,37);
  display.setTextSize(3); 
  display.print("Cm");
  display.display();
}

void drawStr(uint8_t x, uint8_t y, char* str){
  display.setCursor(x, y); 
  display.println(str);
}
