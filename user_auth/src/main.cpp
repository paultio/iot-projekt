#include <Arduino.h>
#include <ittiot.h>
#include <Switch.h>
 
#define WIFI_NAME "c3c2c4"
#define WIFI_PASSWORD "331982219"
#define MQTT_PORT "1883"
#define MQTT_TOPIC "PRINTERS/auth"
#define MQTT_SERVER "192.168.0.22"

const byte buttonPin = D3;
Switch button = Switch(buttonPin);

void iot_connected()
{
  Serial.println("MQTT connected callback");
  iot.log("User authentication");
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Booting");
 
  pinMode(buttonPin, INPUT);

  // iot.setConfig("wname", WIFI_NAME);
  // iot.setConfig("wpass", WIFI_PASSWORD);
  // iot.setConfig("mport", MQTT_PORT); 
  // iot.setConfig("mserv", MQTT_SERVER); 
  iot.setConfig("wname", "TalTech");
  iot.setConfig("wpass", "");
  iot.setConfig("msrv", "193.40.245.72");
  iot.setConfig("mport", "1883");
  iot.setConfig("muser", "test");
  iot.setConfig("mpass", "test");
  iot.printConfig();
  iot.setup();
}
 
void loop()
{
  // IoT behind the plan work, it should be periodically called
  iot.handle();
 
  // Askes in which state the button is, pressed, long pressed, double click, or released.
  button.poll();
 
  // If the button is long pressed, it publishes message “LongPressed”
  if (button.longPress()) {
    iot.publishMsg(MQTT_TOPIC, "ON");
  }
 
  // If the button is double clicked, it publishes message “DoubleClick”
  if (button.doubleClick()) {
    iot.publishMsg(MQTT_TOPIC, "WARN");
  }
 
  // If the button is pushed down, it publishes message “ButtonPushed”
  if (button.pushed()) {
    iot.publishMsg(MQTT_TOPIC, "OFF");
  }
 
  delay(3);
}