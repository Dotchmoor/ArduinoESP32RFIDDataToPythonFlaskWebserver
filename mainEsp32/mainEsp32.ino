#include "serverCommunication.h"
#include "RFIDScanner.h"

#define timeDelay 2000

const char* ssid = "NETZWERK-NAME";
const char* password = "NETZWERK-PASSWORT";

const char* serverName = "http://von-Flask-ausgegebene_IP/";

communicator com(ssid, password, serverName);
scanner sc;


void setup() {
  Serial.begin(115200);
  
  sc.scannerSetup();
  com.connectToWifi();
}


void loop() {
  String UID = "";
  
  UID = sc.scann();

  if(UID != ""){
    com.sendPOST(UID);
    
    delay(timeDelay);
  }
}
