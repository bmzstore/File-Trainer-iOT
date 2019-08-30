#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
//Koneksi LCD-> SCL Ke D1 dan SDA ke D2
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#define DHTPIN 14     //D5
#define DHTTYPE    DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  delay(5000);
  //read temperature and humidity
  int t = dht.readTemperature();
  int h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  // clear display
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(3,0);
  display.print("Temperature/Humidity");
  display.setCursor(12,8);
  display.print("Monitoring System");
  // display temperature
  display.setTextSize(1);
  display.setCursor(0,30);
  display.print("Temperature");
  display.setTextSize(2);
  display.setCursor(10,40);
  display.print(t);
  display.print("");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  // display humidity
  display.setTextSize(1);
  display.setCursor(73, 30);
  display.print("Humidity");
  display.setTextSize(2);
  display.setCursor(79, 40);
  display.print(h);
  display.print("%"); 
  
  display.display(); 
}
