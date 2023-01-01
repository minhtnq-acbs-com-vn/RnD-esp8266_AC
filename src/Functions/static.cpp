#include "../Headers/static.h"


// Control relay
void setLight(String state)
{
  if (state == "on")
    digitalWrite(lightTrigger, HIGH);
  else if (state == "off")
    digitalWrite(lightTrigger, LOW);
}

void publishConfirm(String type)
{
  if (type == "ac")
    client.publish(topicACACK, deviceACConfirmed.c_str());
  else if (type == "light")
    client.publish(topicACACK, deviceLightConfirmed.c_str());
}