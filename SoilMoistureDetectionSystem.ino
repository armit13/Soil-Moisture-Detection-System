#include <WiFi.h>
#include <Wire.h>               
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
const char *ssid =  "Armit Singh";     
const char *pass =  "armit@18"; 
WiFiClient client;
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "armit" 
#define MQTT_PASS "aio_Zvjl42Ez9hWlhSGi0Q4OMkPbNL5N" 
const float moisturePin = A0;             
float moisturePercentage;             
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
Adafruit_MQTT_Publish SoilMoistureSystem = Adafruit_MQTT_Publish(&mqtt,MQTT_NAME "/f/SoilMoistureSystem");
void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");              
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
 void loop()
{
    MQTT_connect();
  moisturePercentage = ( (analogRead(moisturePin) / 1023.00) * 100 ) ;
  Serial.print("Soil Moisture is  = ");
  Serial.println(moisturePercentage);
  String data1 = String(moisturePercentage);
       if (! SoilMoistureSystem.publish(moisturePercentage))
       {                     
         delay(1000);   
          }
 delay(1000);
}
void MQTT_connect() 
{
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) 
  {
    return;
  }
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) 
  { 
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) 
       {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
}
