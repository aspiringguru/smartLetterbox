#include <WiFi.h>
#include <ESPAsyncWebServer.h>
  
const char* ssid = "Arc Incubator";
const char* password =  "nowireshere";
  
AsyncWebServer server(80);
  
int relayPin = 2;
  
void setup(){
  
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  
  Serial.begin(115200);
  Serial.println("serial port opened");
  Serial.println("starting wifi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to wifi, getting local ip address.");
  Serial.println(WiFi.localIP());
  Serial.println("setting up server");
  server.on("/relay/off", HTTP_PATCH, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "ok");
    digitalWrite(relayPin, LOW);
  });
  
  server.on("/relay/on", HTTP_PATCH, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain","ok");
    digitalWrite(relayPin, HIGH);
  });
  
  server.on("/relay/toggle", HTTP_PATCH, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain","ok");
    digitalWrite(relayPin, !digitalRead(relayPin));
  });
  
  server.on("/relay", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(digitalRead(relayPin)));
  });
  Serial.println("server setup, begin server.");  
  server.begin();
}
  
void loop(){}
