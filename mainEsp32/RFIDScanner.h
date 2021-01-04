#include <SPI.h>      
#include <MFRC522.h>  

#define RST_PIN     22          
#define SS_PIN      21
#define red_led 17
#define green_led 16
#define blue_led 2

MFRC522 mfrc522(SS_PIN, RST_PIN); 


class scanner{
  public:
    void scannerSetup();
    String scann();
};


void scanner::scannerSetup(){
  SPI.begin();      
  mfrc522.PCD_Init();
}


String scanner::scann(){
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return "";
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return "";
  }

  
  String content= "";

  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  content.toUpperCase();
  
  Serial.println();
  Serial.print(" PICC type: ");
  
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  
  Serial.println(mfrc522.PICC_GetTypeName(piccType));
  
  return content;
}
