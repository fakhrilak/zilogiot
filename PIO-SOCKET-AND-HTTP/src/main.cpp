#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "httpclient.h"
#include <ArduinoJson.h>
#include "timbangan.h"
#include <SocketIoClient.h>
SocketIoClient Socket;
String token;
const char* ssid     = "202108-001";
const char* password = "hardrock";
StaticJsonDocument<200> doc;

void event(const char * payload, size_t length) {
  Serial.print("ini actuators : ");
  deserializeJson(doc, payload);
  int pin = doc["io"];
  int status = doc["changestate"];
  digitalWrite(pin,status);
  Serial.println("Changed");
}
void sensors(const char * payload, size_t length) {
  Serial.print("ini sensor : ");
  
  deserializeJson(doc, payload);
  int pin = doc["io"];
  Serial.println(pin);
  String pinstr = String(pin);
  
  int read = digitalRead(pin);
  Serial.println(read);
  String readstr = String(read);
  String Data = "{\"data\":\""+  readstr 
                  +"\",\"pin\":\""+ pinstr
                  +"\"}";
  Socket.emit("from-sensor",Data.c_str());
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  String payload = httpGetToENDpoint("/");

  deserializeJson(doc, payload);

  // set OUTPUT
  const char* out = doc["config_output"];
  for(int i =0;i<strlen(out);i++){

    int data = out[i] - '0';
    pinMode(data,OUTPUT);
  }

  // set INPUT
  const char* inp = doc["config_input"];
  for(int l =0;l<strlen(inp);l++){

    int data2 = inp[l] - '0';
    pinMode(data2,INPUT);
  }

  Socket.begin("192.168.100.39",4009);
  Serial.println("connect?");

  Socket.on("tocontrollers-actuator",event);
  Socket.on("tocontrollers-sensor",sensors);
}

void loop() {
 Socket.loop();
 delay(200);
}