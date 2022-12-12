#include <Arduino.h>
#include <ittiot.h>
#include <Adafruit_NeoPixel.h>
#include <Buzzer.h>
 
#define MODULE_TOPIC "PRINTERS/status"
#define WIFI_NAME "c3c2c4"
#define WIFI_PASSWORD "331982219"
#define MQTT_SERVER "192.168.0.22"
#define MQTT_PORT "1883"
 
 
#define BUZZER_PIN D8
Buzzer buzzer(BUZZER_PIN);

#define PIN D2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
 

void iot_received(String topic, String msg)
{
  if (msg == "ON")
  {
    pixels.setPixelColor(0, 0, 255, 0);
    //buzzer.sound(Note.toInt(),time.toInt());
    // NOTE: C4, E4, G4
    buzzer.sound(262, 100);
    buzzer.sound(330, 100);
    buzzer.sound(392, 100);

  }
  else if (msg == "OFF")
  {
    pixels.setPixelColor(0, 0, 0, 0);

    buzzer.sound(392, 100);
    buzzer.sound(330, 100);
    buzzer.sound(262, 100);
  }
  else if (msg == "WARN")
  {
    // Set color to yellow 
    pixels.setPixelColor(0, 255, 255, 0);
    // Warning sound
    buzzer.sound(262, 100);
    buzzer.sound(262, 100);
    buzzer.sound(262, 100);
    buzzer.sound(262, 100);
    buzzer.sound(262, 100);
  }
  else if (msg == "ERROR")
  {
    // Set color to red
    pixels.setPixelColor(0, 255, 0, 0);
    buzzer.sound(262, 1000);
    
  }
  pixels.show();

  Serial.print("MSG FROM USER callback, topic: ");
  Serial.print(topic);
  Serial.print(" payload: ");
  Serial.println(msg);
 
}
 
// Subscrining to a MQTT topic, to get the RGB color code for the RGB LED
void iot_connected()
{
  Serial.println("MQTT connected callback");
  iot.subscribe(MODULE_TOPIC);
  iot.log("Printer status");
}
 
// Setting up some parameters for the ESP microcontroller
void setup()
{
  Serial.begin(115200); // setting up serial connection parameter
  Serial.println("Booting");
 
  iot.setConfig("wname", WIFI_NAME);
  iot.setConfig("wpass", WIFI_PASSWORD);
  iot.setConfig("msrv", MQTT_SERVER);
  iot.setConfig("mport", MQTT_PORT);
  iot.printConfig(); // print json config to serial
  iot.setup();
 
  pixels.begin(); // This initializes the NeoPixel library.
}
 
//Main code, which runs in loop
void loop()
{
  iot.handle(); // Calls iot.handle out
  delay(200); // Delay of 200 ms
}