#include "httpclient.h"
#include <ESP8266HTTPClient.h>
String httpPostToENDpoint(String endPoint,String body,String token){
    WiFiClient client;
    HTTPClient http;
    http.begin(client,"http://192.168.100.39:4009/zilogiot/api/v2.1/"+endPoint);
    http.addHeader("Content-Type", "application/json");  
    if(validatingEndpoint(endPoint) == true){
        Serial.println(token);
        http.addHeader("Authorization",token);
    }
    int httpCode = http.POST(body);
    String payload = http.getString();
    Serial.println(httpCode);
    return payload;
}

String httpGetToENDpoint(String endPoint){
    WiFiClient client;
    HTTPClient http;
    http.begin(client,"http://192.168.100.39:4009/zilogiot/api/v2.1/"+endPoint);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.GET();
    String payload = http.getString();
    Serial.println(httpCode);
    return payload;
}
int validatingEndpoint(String enpoint){
    String AuthEndpoint [] = {"id-tag","weight-got"};
    for(int i=0;i<sizeof AuthEndpoint/sizeof AuthEndpoint[0];i++){
        if(AuthEndpoint[i] == enpoint){
            return true;
        }
    }
    return false;
}