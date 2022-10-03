// ****************************************************************** 
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program 
// COMP-10184 
// Mohawk College 
// I, Julia Norrish, 000839030 certify that this material is my original work.  No other person's work has been used without due acknowledgement.
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;    

// array of the installed devices
DeviceAddress tempSensor;
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 
 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 

  // get the sensor's address
  DS18B20.getAddress(tempSensor, 0);

  // check if a sensor is installed and print an error message if there's nothing installed
  if (!DS18B20.getAddress(tempSensor, 0)){
    Serial.println("No DS18B20 temperature sensors are installed!");
  }
  else {
    // print the address of the sensor
    for (uint8_t i = 0; i < 8; i++) {
      if (tempSensor[i] < 16) Serial.print("0");
        Serial.print(tempSensor[i], HEX);
    }
  }

  Serial.println();
} 
 
void loop() { 
  float fTemp; 
 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 


  String tempJudgement = "";

  // store the appropriate value depending on the temperature
  if (fTemp < 10){
    tempJudgement = "Cold!";
  }
  else if (fTemp >= 10 && fTemp <= 15)
  {
    tempJudgement = "Cool";
  }
  else if (fTemp >= 15 && fTemp <= 25)
  {
    tempJudgement = "Perfect";
  }
  else if (fTemp >= 25 && fTemp <= 30)
  {
    tempJudgement = "Warm";
  }
  else if (fTemp >= 30 && fTemp <= 35)
  {
    tempJudgement = "Hot";
  }
  else if (fTemp > 35)
  {
    tempJudgement = "Too Hot!";
  }


  // print value to the USB port 
  if (DS18B20.getAddress(tempSensor, 0)){
    Serial.println("Current temperature is: " + String(fTemp) + " C or " + tempJudgement);
  }
  
 
  // wait 5s (5000ms) before doing this again 
  delay(5000); 
} 
