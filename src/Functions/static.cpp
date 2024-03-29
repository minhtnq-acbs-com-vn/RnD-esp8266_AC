#include "../Headers/static.h"


// Control relay
void setLight(String state)
{
  if (state == "on")
    digitalWrite(lightTrigger, LOW);
  if (state == "off")
    digitalWrite(lightTrigger, HIGH);
  publishConfirm("light");
}

void publishConfirm(String type)
{
  if (type == "ac")
    client.publish(topicACACK, deviceACConfirmed.c_str());
  if (type == "light")
    client.publish(topicACACK, deviceLightConfirmed.c_str());
}