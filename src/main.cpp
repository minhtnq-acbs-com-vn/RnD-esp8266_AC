#include <Arduino.h>
#include <Headers/Command_Variable/packet.h>
#include <Headers/Command_Variable/acConfig.h>
#include <Headers/GPIO/pin.h>
#include <Headers/Network/client.h>
#include <Headers/Network/mqtt.h>
#include <Headers/Network/topic.h>

// Function declaration
// STATIC
void setupAC();
void checkAC();
void configAC(bool option);
void readButtonTransmit();
void readButtonLoop();
void publishFlag(const String flag);
void publishConfirm(String type);
// NETWORK
void wifiConnect();
void mqttReconnect();
void wifiCheck();
void failedReconnect();
// DATA HANDLING
void callback(char *topic, byte *message, unsigned int length);

void setup()
{
  // Init Serial console
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");

  // Init wifi and mqtt
  wifiConnect();
  client.setServer(mqttServer, port);
  client.setCallback(callback);

  pinMode(buttonLoop, INPUT);
  pinMode(buttonTransmit, INPUT);
  delay(200);
  setupAC();
  EEPROM.begin(romSize);
  EEPROM.get(romAddress, lastDecode);
}

void loop()
{
  if (!client.connected())
  {
    mqttReconnect();
  }
  client.loop();
  readButtonLoop();
  readButtonTransmit();
  wifiCheck();
}

/////////////STATIC FUNCTION/////////////
void setupAC()
{
  ac.next.protocol = decode_type_t::DAIKIN;      // Set a protocol to use.
  ac.next.model = 1;                             // Some A/Cs have different models. Try just the first.
  ac.next.mode = stdAc::opmode_t::kCool;         // Run in cool mode initially.
  ac.next.celsius = true;                        // Use Celsius for temp units. False = Fahrenheit
  ac.next.degrees = 25;                          // 25 degrees.
  ac.next.fanspeed = stdAc::fanspeed_t::kMedium; // Start the fan at medium.
  ac.next.swingv = stdAc::swingv_t::kOff;        // Don't swing the fan up or down.
  ac.next.swingh = stdAc::swingh_t::kOff;        // Don't swing the fan left or right.
  ac.next.light = true;                          // Turn off any LED/Lights/Display that we can.
  ac.next.beep = true;                           // Turn off any beep from the A/C if we can.
  ac.next.econo = false;                         // Turn off any economy modes if we can.
  ac.next.filter = false;                        // Turn off any Ion/Mold/Health filters if we can.
  ac.next.turbo = false;                         // Don't use any turbo/powerful/etc modes.
  ac.next.quiet = false;                         // Don't use any quiet/silent/etc modes.
  ac.next.sleep = -1;                            // Don't set any sleep time or modes.
  ac.next.clean = false;                         // Turn off any Cleaning options if we can.
  ac.next.clock = -1;                            // Don't set any current time if we can avoid it.
  ac.next.power = false;                         // Initially start with the unit off.

  Serial.println("Try to turn on & off every supported A/C type ...");
}

void checkAC()
{
  int sizeOfArray = sizeof(chosenBrand) / sizeof(int);

  int startTimeRan = millis();
  for (int i = 0; i < sizeOfArray; i++)
  {
    int buttonValue = digitalRead(buttonLoop);
    if (buttonValue == HIGH)
    {
      break;
    }
    decode_type_t protocol = chosenBrand[i];
    Serial.println("Protocol " + String(protocol) + " / " +
                   typeToString(protocol) + " is supported.");
    ac.next.protocol = protocol; // Change the protocol used.
    lastDecode = protocol;
    EEPROM.put(romAddress, lastDecode);
    EEPROM.commit();
    ac.next.power = true; // We want to turn on the A/C unit.
    acPower = true;
    Serial.println("Sending a message to turn ON the A/C unit.");
    ac.sendAc();
    delay(3000); // Wait 3 second.
  }
  int finalTimeRan = millis() - startTimeRan;
  Serial.print("Loop all brand time: ");
  Serial.println(finalTimeRan);
  delay(5000);
  Serial.println("Starting from the begining again ...");
}

void configAC(bool option)
{
  ac.next.protocol = lastDecode;
  ac.next.power = option;
  acPower = option;
  ac.sendAc();
}

void readButtonLoop()
{
  int buttonValue = digitalRead(buttonLoop);
  if (buttonValue == LOW)
  {
    checkAC();
  }
}

void readButtonTransmit()
{
  int buttonValue = digitalRead(buttonTransmit);
  if (buttonValue == LOW)
  {
    while (digitalRead(buttonTransmit) == LOW)
      ;
    if (acPower == true)
    {
      configAC(true);
      Serial.print("Sent turn off signal: ");
      Serial.println(typeToString(lastDecode));
    }
    else if (acPower == false)
    {
      configAC(false);
      Serial.print("Sent turn on signal: ");
      Serial.println(typeToString(lastDecode));
    }

    Serial.println("buttonTransmit Pressed");
  }
}

void publishConfirm()
{
  client.publish(topicACACK, deviceConfirmed.c_str());
}
/////////////STATIC FUNCTION/////////////

/////////////NETWORK FUNCTION/////////////
// Connect wifi
void wifiConnect()
{
  wifiManager.setTimeout(180);
  if (!wifiManager.autoConnect("AutoConnectAP"))
  {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  Serial.println("connected...yeey :)");
}

// Connect to mqtt broker and subscribe to specific topic(s)
void mqttReconnect()
{
  while (!client.connected())
  {
    Serial.println("Attemping MQTT connection...");
    if (client.connect(mqttClientID, mqttUsername, mqttPassword))
    {
      Serial.println("Connected");

      //***Subscribe all topic you need***
      client.subscribe(topicACServer);
    }
    else
    {
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void wifiCheck()
{
  uint32_t notConnectedCounter = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    notConnectedCounter++;
    if (notConnectedCounter > 300)
    { // Reset board if not connected after 15s
      Serial.println("Resetting due to Wifi not connecting...");
      WiFi.reconnect();
      // failedReconnect();
    }
  }
}

void failedReconnect()
{
  delay(10000);                  // let esp take time reconnect
  for (int i = 0; i < 6000; i++) // wait for 5 minutes before reset esp
  {
    delay(500);
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    ESP.restart();
  }
}
/////////////NETWORK FUNCTION/////////////

/////////////DATA HANDLING FUNCTION/////////////
// Handle mqtt packet here
void callback(char *topic, byte *message, unsigned int length)
{
  Serial.println(topic);
  String strMsg;
  for (unsigned int i = 0; i < length; i++)
  {
    strMsg += (char)message[i];
  }
  Serial.println(strMsg);
  //***Insert code here to control other devices***
  if (strMsg == serverRequestACOn)
  {
    configAC(true);
    publishConfirm();
  }
  else if (strMsg == serverRequestACOff)
  {
    configAC(false);
    publishConfirm();
  }
}
/////////////DATA HANDLING FUNCTION/////////////