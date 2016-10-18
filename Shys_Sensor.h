/*
  Shys_Sensor.h - Library for SmartHomeYourSelf Sensor basic-functionality
  created by Daniel Scheidler, March 2015
*/
#ifndef Shys_Sensor_h
#define Shys_Sensor_h

#include "Arduino.h"
#include "SPI.h"
#include "Ethernet.h"

class Shys_Sensor{
  public:
    Shys_Sensor(byte mac[], byte ip[], byte dns[], byte gate[], byte mask[], byte piAddress[]);
    void setSensorValue(long sensorId, long  sensorValue);
    void init();
  private:
    EthernetClient _interfaceClient;
    byte* _piAddress;
    byte* _mac;
    byte* _ip;
    byte* _dns;
    byte* _gate;
    byte* _mask;
    void clientPrintIp(byte inIp[]);
    void serialPrintIp(byte inIp[]);
};

#endif
