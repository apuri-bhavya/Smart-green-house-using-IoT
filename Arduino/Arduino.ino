Arduino code 
#include <DHT.h> 
#include <SoftwareSerial.h> 
// Pins 
const int moistureRelayPin = 4; 
const int fanRelayPin = 5; 
const int moistureSensorPin = A0; 
#define DHTPIN 2 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 
// Serial to NodeMCU: RX=10, TX=11 
SoftwareSerial nodemcu(10, 11); 
void setup() { 
Serial.begin(9600); 
nodemcu.begin(9600); 
pinMode(moistureRelayPin, OUTPUT); 
pinMode(fanRelayPin, OUTPUT); 
pinMode(moistureSensorPin, INPUT); 
dht.begin(); 
Serial.println("Arduino Greenhouse Controller Started"); 
} 
void loop() { 
int moistureValue = analogRead(moistureSensorPin); 
moistureValue = map(moistureValue, 700, 300, 0, 100); 
moistureValue = constrain(moistureValue, 0, 100); 
float temp = dht.readTemperature(); 
// Relay Controls 
digitalWrite(moistureRelayPin, (moistureValue < 15) ? LOW : HIGH); 
digitalWrite(fanRelayPin, (!isnan(temp) && temp > 33) ? LOW : HIGH); 
// Format String Same as You Showed 
String mystring; 
if (!isnan(temp)) { 
mystring = "Moisture: " + String(moistureValue) + "%, Temp: " + String(temp) + 
"C"; 
} else { 
mystring = "Error reading DHT11"; 
} 
Serial.println(mystring); 
nodemcu.println(mystring); 
delay(2000); 
}