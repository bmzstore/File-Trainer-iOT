#define BLYNK_PRINT Serial  
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>

char auth[] = "YdINrhT2bPV3-VInmTYIJOVYBIrgidXR";// Token Trainer IOT

char ssid[] = "xxxxxxxx"; // Nama Wifi
char pass[] = "xxxxxxxx";  // Password Wifi

#define DHTPIN 2 
#define DHTTYPE DHT11     // DHT 11


DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Serial.print("Temp = ");
  Serial.print(t);
  Serial.print("Humi = ");
  Serial.println(h);
}

void setup()
{
  Serial.begin(9600); 
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
