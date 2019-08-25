#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define TRIGGERPIN 14 //D5
#define ECHOPIN    12 //D6

char auth[] = "YdINrhT2bPV3-VInmTYIJOVYBIrgidXR";


char ssid[] = "xxxxxxxx";
char pass[] = "xxxxxxxx";

WidgetLCD lcd(V1);

void setup()
{
  
  Serial.begin(9600);
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  Blynk.begin(auth, ssid, pass);
  lcd.clear();
  lcd.print(0, 0, "Distance in cm"); 
}

void loop()
{
  lcd.clear();
  lcd.print(1, 0, "Distance in cm")
  long duration, distance;
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(3); 
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12); 
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println("Cm");
  lcd.print(7, 1, distance);
  Blynk.run();

  delay(500);

}
