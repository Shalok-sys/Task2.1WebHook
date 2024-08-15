#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#include <WiFiNINA.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321 - DHT22 sensor has a higher range as compared to DHT11.

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);      // Initialize serial 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  Serial.println(F("DHT22 test!"));

  dht.begin();
  ThingSpeak.begin(client);  // Initialize ThingSpeak 
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(1000);     
    } 
    Serial.println("\nConnected.");
  }
  delay(1000); // After being successfully connected, wait for one second before reading humidity and temperature from the DHT22 sensor.
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();


  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

// Results will be printed on the serial monitor for cross-verifying.
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));

  
  // set the fields with the values
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);


  // write to the ThingSpeak channel 
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  


  
  delay(60000); // Wait 60 seconds to update the channel. So, the values of temperature and humidity in thingsspeak dashboard will change after 60 seconds only.
}
