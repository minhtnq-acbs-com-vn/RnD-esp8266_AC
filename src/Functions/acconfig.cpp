#include "../Headers/acconfig.h"

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
      break;
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
    delay(1000); // Wait 1 second.
  }
  int finalTimeRan = millis() - startTimeRan;
  Serial.print("Loop all brand time: ");
  Serial.println(finalTimeRan);
}

void configAC(bool option)
{
  ac.next.protocol = lastDecode;
  ac.next.power = option;
  acPower = option;
  ac.sendAc();

  publishConfirm("ac");
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
    (acPower == true) ? configAC(false) : configAC(true);
    Serial.println("buttonTransmit Pressed");
  }
}