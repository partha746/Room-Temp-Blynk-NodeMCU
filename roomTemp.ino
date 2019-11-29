#include <DHT.h>;
#include <ESP8266WiFiMulti.h>
#include <BlynkSimpleEsp8266.h>

#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float hum;  //Stores humidity value
float temp; //Stores temperature value

char auth[] = "jpg_3lWnYJVuCb80OW16bSr6bzYI5clF";
  
ESP8266WiFiMulti wifiMulti;

void blynkConnect()
{
  Blynk.begin(auth, "T3", "diwana_746");
}
 
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);

  wifiMulti.addAP("T2", "diwana_746");
  wifiMulti.addAP("T3", "diwana_746");
  
  dht.begin();

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("Connected to SSID: %s & IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void loop() {
  hum = dht.readHumidity();
  temp = dht.readTemperature();
//  Serial.printf("Temp : %f and Hum : %f", temp, hum);
//  Serial.println();
  if(!Blynk.connected()){
    blynkConnect();    
  }
  Blynk.virtualWrite(V3, hum);
  Blynk.virtualWrite(V4, temp);
  Blynk.run(); 
  delay(5000);
}
