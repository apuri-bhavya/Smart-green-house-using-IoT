NodeMCU code 
#define BLYNK_TEMPLATE_ID "TMPL3Wd7wVHXc" 
#define BLYNK_TEMPLATE_NAME "Greenhouse" 
#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h> 
#include <SoftwareSerial.h> 
// Blynk credentials 
char auth[]="jydvfvjeicgwkchdvjxg";
// Your WIFI credentials.
// Set password to "" for open networks.
char ssid[] = "abc"; 
char pass[] = "T3ss4bn"; 
BlynkTimer timer; 
// Use SoftwareSerial if hardware serial is used for debug 
SoftwareSerial nodemcuSerial(D1, D2); // RX, TX (D1 = GPIO5, D2 = GPIO4) 
String myString = ""; 
char rdata; 
void setup() { 
Serial.begin(9600); 
nodemcuSerial.begin(9600); 
Blynk.begin(auth, ssid, pass); 
timer.setInterval(1000L, sendToBlynk); 
} 
void loop() { 
Blynk.run(); 
timer.run(); 
while (nodemcuSerial.available()) { 
rdata = nodemcuSerial.read(); 
myString += rdata; 
} 
} 
void sendToBlynk() { 
if (myString.length() > 0) { 
Blynk.virtualWrite(V12, myString);  // Display complete sensor string in Terminal 
myString = "";  // Clear after sending 
} 
}