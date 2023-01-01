#include "../Headers/wificustom.h"

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