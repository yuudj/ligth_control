#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "secrets.h"

int threshold = 40; // touch threshold
uint16_t tempTouch=0;
uint16_t debounceTime= 1000;
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish temp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/casa.temp");
Adafruit_MQTT_Publish hum = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/casa.hum");

unsigned long previousMillis = 0;

unsigned long mqtt_retries = 0; // counter
unsigned long wifi_retries = 0; // counter

typedef struct
{
  int in_pin;
  bool value;
  int out_pin;
  unsigned long  previousMillis; //previos touch value to debounce
} ligth_type;

// definir input y funcion a ejecutar, esto es medio al pedo
ligth_type LIGTS[8];

void setSensor(int index, int in_pin, int out_pin, void (*userFunc)(void))
{
  LIGTS[index].in_pin = in_pin;
  LIGTS[index].value = false;
  LIGTS[index].out_pin = out_pin;
  LIGTS[index].previousMillis=0;
  pinMode(out_pin, OUTPUT);
  touchAttachInterrupt(in_pin, userFunc, threshold);
}

void toggleRelay(int index)
{
  
  if(millis() - LIGTS[index].previousMillis < debounceTime)
    return;
  
  // updates the status and change the output
  LIGTS[index].value = !LIGTS[index].value;
  LIGTS[index].previousMillis = millis() ;
  digitalWrite( LIGTS[index].out_pin,  LIGTS[index].value);

  Serial.println(touchRead( LIGTS[index].in_pin ));  // print the value
  Serial.print("RELAY ");
  Serial.print( LIGTS[index].out_pin);
  Serial.print(" " );
  Serial.println( LIGTS[index].value);
}

// handles the interrupt
void gotTouch0() { toggleRelay(0); }
void gotTouch1() { toggleRelay(1); }
void gotTouch2() { toggleRelay(2); }
void gotTouch3() { toggleRelay(3); }
void gotTouch4() { toggleRelay(4); }
void gotTouch5() { toggleRelay(5); }
void gotTouch6() { toggleRelay(6); }
void gotTouch7() { toggleRelay(7); }
void gotTouch8()
{
  //todo: display
}

void setup()
{
  Serial.begin(9600);
  delay(10);
  // inicializar los touch
  setSensor(0, T0, 5, gotTouch0);
  //setSensor(1, T1, 16, gotTouch1);
  setSensor(2, T2, 17, gotTouch2);
  setSensor(3, T3, 18, gotTouch3);
  setSensor(4, T4, 19, gotTouch4);
  setSensor(5, T5, 23, gotTouch5);
  setSensor(6, T6, 25, gotTouch6);
  setSensor(7, T7, 26, gotTouch7);

  WiFi_connect();
  MQTT_connect();
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 3000)
  {
    previousMillis = currentMillis;
    
    MQTT_connect();
    Serial.println(touchRead( T0 ));  // print the value
    //TODO: update display
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
int MQTT_connect()
{
  int ret;
  // Stop if already connected.
  if (mqtt.connected())
  {
    return 1;
  }

  Serial.print("Connecting to MQTT... ");

  mqtt_retries = 3;
  while ((ret = mqtt.connect()) != 0 && mqtt_retries > 0)
  { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(2000); // wait 5 seconds
    mqtt_retries--;
  }

  if (mqtt.connected())
  {
    Serial.print("MQTT connected");
    return 1;
  }
  else
  {
    Serial.print("MQTT timeout");
    return 0;
  }
}

int WiFi_connect()
{

  if (WiFi.status() == WL_CONNECTED)
    return 1;

  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  wifi_retries = 20;
  // timeout
  while (WiFi.status() != WL_CONNECTED && wifi_retries > 0)
  {
    delay(500);
    wifi_retries--;
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    return 1;
  }
  else
  {
    Serial.println("WiFi conection timed out");
    return 0;
  }
}
