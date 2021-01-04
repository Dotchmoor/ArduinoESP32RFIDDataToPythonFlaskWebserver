#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>


class communicator{
  public:
    communicator(const char* ssid, const char* password, const char* server);
    void connectToWifi();
    void sendPOST(String UID);
    
  private:
    const char* ssid;
    const char* password;
    const char* server;
};

communicator::communicator(const char* ssid, const char* password, const char* server){
  this->server = server;
  this->ssid = ssid;
  this->password = password;
}

void communicator::connectToWifi(){
  WiFi.begin(this->ssid, this->password);

  Serial.print("connecting to WiFi ");
  
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    
    delay(100);
  }
  
  Serial.println("");
  Serial.println(WiFi.localIP());
}

void communicator::sendPOST(String UID){
    HTTPClient http;
    
    http.begin(this->server);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    String httpRequestData = "UID=" + UID;           
    int httpResponseCode = http.POST(httpRequestData);
  
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    
    http.end();
}
