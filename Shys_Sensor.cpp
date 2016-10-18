#include "Arduino.h"
#include "Ethernet.h"
#include "Shys_Sensor.h"
#include "SPI.h"

const int  MAX_BUFFER_LEN = 80;
char _buffer[MAX_BUFFER_LEN+1];


/**
 *  Constructor for Sensor
 */
Shys_Sensor::Shys_Sensor(byte mac[], byte ip[], byte dns[], byte gate[], byte mask[], byte piAddress[]){
  _mac       = mac;
  _ip        = ip;
  _dns       = dns;
  _gate      = gate;
  _mask      = mask;
  _piAddress = piAddress;
}

/**
 *  Initialize Network
 */
void Shys_Sensor::init(){
  Ethernet.begin(_mac, _ip, _dns, _gate, _mask);

  if(Serial){
    Serial.println("HomeControl - Sensor");
    Serial.print("IP: ");
    Serial.println(Ethernet.localIP());
  }
}

/** 
 *  Send Sensor-Value to the PI
 */
void Shys_Sensor::setSensorValue(long sensorId, long sensorValue){

  if (_interfaceClient.connect(_piAddress, 80)) {
      delay(800);
    
      if(Serial){
        Serial.print("Send Value ");
        Serial.print(sensorValue);
        Serial.print(" for Sensor ");
        Serial.println(sensorId);
      }

      _interfaceClient.print("GET /signalInput.php?sensorId=");
      _interfaceClient.print(sensorId);
      _interfaceClient.print("&sensorWert=");
      _interfaceClient.print(sensorValue);
      _interfaceClient.println(" HTTP/1.1");
      _interfaceClient.print("Host: ");
      clientPrintIp(_piAddress);
      _interfaceClient.println("Connection: close");
      _interfaceClient.println();

      unsigned long startTime = millis();
      while (!_interfaceClient.available() && (millis() - startTime ) < 5000) {
      }

      //while (_interfaceClient.available()) {
      //  char c = _interfaceClient.read();
      //  Serial.print(c);
      //}
      
      if (_interfaceClient.connected()) {
        Serial.println("disconnecting.");
        _interfaceClient.stop();
      }
    } else {
       Serial.println("Could not connect to ");
       serialPrintIp(_piAddress);
       Serial.println(" -  Port 80");
    }
}

void Shys_Sensor::clientPrintIp(byte inIp[]){
      char ipTmp[4];

      itoa((int)_piAddress[0], ipTmp, 10);
      _interfaceClient.print(ipTmp);
      _interfaceClient.print(".");         

      itoa((int)_piAddress[1], ipTmp, 10);
      _interfaceClient.print(ipTmp);
      _interfaceClient.print(".");

      itoa((int)_piAddress[2], ipTmp, 10);
      _interfaceClient.print(ipTmp);
      _interfaceClient.print(".");
      
      itoa((int)_piAddress[3], ipTmp, 10);
      _interfaceClient.print(ipTmp);
}


void Shys_Sensor::serialPrintIp(byte inIp[]){
      char ipTmp[4];

      itoa((int)_piAddress[0], ipTmp, 10);
      Serial.print(ipTmp);
      Serial.print(".");         

      itoa((int)_piAddress[1], ipTmp, 10);
      Serial.print(ipTmp);
      Serial.print(".");

      itoa((int)_piAddress[2], ipTmp, 10);
      Serial.print(ipTmp);
      Serial.print(".");
      
      itoa((int)_piAddress[3], ipTmp, 10);
      Serial.print(ipTmp);
}
