#include <Arduino.h>
#include <ittiot.h>
#include <Adafruit_PN532.h>
 
#define WIFI_NAME "c3c2c4"
#define WIFI_PASSWORD "331982219"
#define MQTT_PORT "1883"
#define MQTT_TOPIC "PRINTERS/NFC"
#define MQTT_SERVER "192.168.0.22"
 
//Define pins for communication with the NFC reader
#define PN532_SCK  D5
#define PN532_MOSI D7
#define PN532_SS   D3
#define PN532_MISO D6
 
//Setup Adafruit PN532 library
Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);
 
void iot_connected()
{
  Serial.println("MQTT connected callback");
  iot.log("User authentication");
}
 
void setup()
{
  Serial.begin(115200);
  Serial.println("Booting");
 
  iot.setConfig("wname", WIFI_NAME);
  iot.setConfig("wpass", WIFI_PASSWORD);
  iot.setConfig("mport", MQTT_PORT); 
  iot.setConfig("mserv", MQTT_SERVER); 
  iot.printConfig();
  iot.setup();
 
  nfc.begin();
  Serial.println("Waiting for an ISO14443A Card ...");
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.println("Didn't find PN53x board");
    while (1);
  }
  
  nfc.SAMConfig();
  Serial.println(versiondata);
}
 
void loop()
{
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;
  char buf[10];
  char str[70] = "";
 
  iot.handle();
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 1000); // Card reading function
 
  if (success)
  {
    //Concatenate card ID
    for(int i = 0; i < uidLength;i++)
    {
      String(uid[i]).toCharArray(buf,10);
      strcat(str, buf);
    }
    iot.publishMsg(MQTT_TOPIC, str); // Publish card ID to topic "NFC"
    delay(1000);
  }
}