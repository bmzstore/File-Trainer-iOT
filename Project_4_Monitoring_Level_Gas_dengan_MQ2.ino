#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define CommonSenseMetricSystem
#include <MQ2.h>
#define OLED_RESET D5
int pin = A0; //A0
int lpg, co, smoke;
MQ2 mq2(pin);
Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
void setup()   {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // SCL=D1  SDA=D2
  display.clearDisplay(); 
  display.setTextColor(WHITE); 
  mq2.begin();
  Serial.begin(9600);
}

void loop() {
  float* values= mq2.read(true);
  lpg = mq2.readLPG();
  co = mq2.readCO();
  smoke = mq2.readSmoke();
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2); 
  display.print("MQ2 Sensor");
  display.setCursor(0,17);
  display.setTextSize(2); 
   display.print("LPG:");
  display.print(lpg);
  display.setCursor(0,33);
  display.setTextSize(2); 
   display.print("CO:");
  display.print(co);
  display.setCursor(0,49);
  display.setTextSize(2); 
   display.print("Smoke:");
  display.print(smoke);
  display.display(); 
}

void drawStr(uint8_t x, uint8_t y, char* str){
  display.setCursor(x, y); 
  display.println(str);
}
