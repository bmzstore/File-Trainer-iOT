#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//Koneksi LCD-> SCL Ke D1 dan SDA ke D2
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int sensor_pin = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */
char auth[] = "YdINrhT2bPV3-VInmTYIJOVYBIrgidXR";

char ssid[] = "xxxxxxxxxx";
char pass[] = "xxxxxxxxxx";

void setup() {
  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600); /* Define baud rate for serial communication */
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  
  float moisture_percentage;

  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );

  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.println("%");
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20,0);
  display.print("Soil Moisture");
  display.setTextSize(2);
  display.setCursor(0,17);
  display.print("Nilai:");
  display.setTextSize(3);
  display.setCursor(0,35);
  display.print(moisture_percentage);
  display.setTextSize(3);
  display.print(" %");
  display.display();
  Blynk.virtualWrite(V4, moisture_percentage);
  Blynk.run();
  delay(100);
}


