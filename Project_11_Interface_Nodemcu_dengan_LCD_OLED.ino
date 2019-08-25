#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET D5
/* Object named display, of the class Adafruit_SSD1306 */
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

uint8_t s = 0, m = 52, h = 9;

void setup()   {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); /* Initialize display with address 0x3C */
  display.clearDisplay();  /* Clear display */
   /* Select font size of text. Increases with size of argument. */
  display.setTextColor(WHITE);  /* Color of text*/
}

void loop() {
  updateWatch();/* Every second increment clock and display */
  delay(1000);
}

void updateWatch() {
  s = s + 1;
  if (s == 60) {
    s = 0;
    m = m + 1;
  }
  if (m == 60) {
    m = 0;
    h = h + 1;
  }
  if (h == 13)
    h = 1;

  writeOLED();
}

void writeOLED(){
  char time[30];
  display.clearDisplay();  /* Clear display */
  sprintf(time, "%02d:%02d:%02d", h, m, s);
  display.setTextSize(2); 
  drawStr(8, 0, "B_Mz Store");
  display.setTextSize(1); 
  drawStr(15, 20, "Sabtu 17/08/2019");
  drawStr(41, 30, time);
  drawStr(15, 40, "Let's Make Things");
  drawStr(45, 50, "Better!");
  display.display();
}

void drawStr(uint8_t x, uint8_t y, char* str){
  display.setCursor(x, y);  /* Set x,y coordinates */
  display.println(str);
}
