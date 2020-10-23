
#include <SPI.h>
#include <MFRC522.h>
String a="22";
String b="11272051";
String c="99261251";
String item;
int x[9];
#define SS_PIN 49
#define RST_PIN 11
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

 
}
 void loop()
 {
  rifd();
              if(item==b)
                {
                  analogWrite(12,0);
                  delay(100);
                  
                }
                if(item==c)
                {
                  analogWrite(12,150);
                  delay(100);
                }
                item="";
  }
void rifd() {

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;


 for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
  printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
   rfid.PICC_HaltA();

  
  rfid.PCD_StopCrypto1();
  
}



void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : "");
    Serial.print(buffer[i], DEC);
    item+=String(buffer[i]);
  }

  Serial.println(" ");
  Serial.println(item);
  

}



