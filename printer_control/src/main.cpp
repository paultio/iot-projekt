// Includes global variables and librarys that the relay shield uses
#include <Arduino.h>
#include <ittiot.h>
 
#define MODULE_TOPIC "PRINTERS/relay"
#define WIFI_NAME "c3c2c4"
#define WIFI_PASSWORD "331982219"
#define MQTT_SERVER "192.168.0.22"
#define MQTT_PORT "1883"

#define RELAY_PIN 5 // The relay has been connected to pin 5
 
// If message received switch relay
void iot_received(String topic, String msg)
{
  Serial.print("MSG FROM USER callback, topic: ");
  Serial.print(topic);
  Serial.print(" payload: ");
  Serial.println(msg);
 
  if(topic == MODULE_TOPIC)
  {
    // If message received and it is 1, then switch relay on
    if(msg == "1")
    {
      digitalWrite(RELAY_PIN, HIGH);
    }
    // If message received and it is 0, then switch relay on
    if(msg == "0")
    {
      digitalWrite(RELAY_PIN, LOW);
    }
  }
}
 
// Function started after the connection to the server is established.
void iot_connected()
{
  Serial.println("MQTT connected callback");
  iot.subscribe(MODULE_TOPIC); // subscribe to topic relay
  iot.log("Printer on/off");
}
 
void setup()
{
  Serial.begin(115200); // setting up serial connection parameter
  Serial.println("Booting");
 
  // iot.setConfig("wname", WIFI_NAME);
  // iot.setConfig("wpass", WIFI_PASSWORD);
  // iot.setConfig("msrv", MQTT_SERVER);
  // iot.setConfig("mport", MQTT_PORT);
  iot.setConfig("wname", "TalTech");
  iot.setConfig("wpass", "");
  iot.setConfig("msrv", "193.40.245.72");
  iot.setConfig("mport", "1883");
  iot.setConfig("muser", "test");
  iot.setConfig("mpass", "test");
  iot.printConfig(); // print json config to serial
  iot.setup(); // Initialize IoT library
 
  pinMode(RELAY_PIN, OUTPUT); // The relay pin is defined as output type
}
 
void loop()
{
  iot.handle(); // IoT behind the plan work, it should be periodically called
  delay(200); // Wait for 0.2 seconds
}