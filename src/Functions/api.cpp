#include "../Headers/api.h"

void sentDeviceInfo()
{
    HTTPClient http;
    String payload = "";
    http.begin(secureClient, apiHost);
    http.addHeader("userid", userID);
    http.addHeader("system", systemKey);
    String json = packToJson();
    Serial.println(json);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(json);
    Serial.println(http.errorToString(httpCode));
    while (httpCode != 200)
    {
        http.end();
        delay(10000);
        http.begin(secureClient, apiHost);
        http.addHeader("userid", userID);
        http.addHeader("system", systemKey);
        String json = packToJson();
        http.addHeader("Content-Type", "application/json");
        int httpCode = http.POST(json);
        Serial.println(http.errorToString(httpCode));
        if (httpCode == 200)
            break;
    }

    // Check the returning code
    payload = http.getString(); // Get the request response payload
    Serial.println(payload);    // Print the response payload

    http.end();
}

String getDeviceInfo()
{
    HTTPClient http;
    String payload = "";
    http.begin(secureClient, apiQuery);
    http.addHeader("userid", userID);
    http.addHeader("system", systemKey);

    int httpCode = http.GET();
    Serial.println(http.errorToString(httpCode));
    while (httpCode != 200)
    {
        http.end();
        delay(10000);
        http.begin(secureClient, apiQuery);
        http.addHeader("userid", userID);
        http.addHeader("system", systemKey);
        int httpCode = http.GET();
        Serial.println(http.errorToString(httpCode));
        if (httpCode == 200)
            break;
    }
    // Check the returning code
    payload = http.getString(); // Get the request response payload
    Serial.println(payload);
    http.end();
    return payload;
}

void setupDeviceConfig()
{
    String payload = getDeviceInfo();
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, payload);
    if (error)
        Serial.println(error.f_str());
    else
    {
        setupPacketConfig(doc);
        setupPin(doc);
    }
}

void setupPacketConfig(DynamicJsonDocument doc)
{
    deviceACConfirmed = doc["ack"]["ac"].as<String>();
    deviceLightConfirmed = doc["ack"]["light"].as<String>();
    serverRequestACOn = doc["request"]["acOn"].as<String>();
    serverRequestACOff = doc["request"]["acOff"].as<String>();
    serverRequestLightOn = doc["request"]["lightOn"].as<String>();
    serverRequestLightOff = doc["request"]["lightOff"].as<String>();
    requestAPI = doc["request"]["api"].as<String>();
}

void setupPin(DynamicJsonDocument doc)
{
    kIrLed = doc["pin"]["ac1"].as<int>();
    buttonTransmit = doc["pin"]["buttonTransmit"].as<int>();
    buttonLoop = doc["pin"]["buttonLoop"].as<int>();
    lightTrigger = doc["pin"]["lightTrigger"].as<int>();
}

void printChanges(String option)
{
    for (auto &element : ack)
    {
        Serial.println(element);
    }
    for (auto &element : request)
    {
        Serial.println(element);
    }

    for (auto &element : pin)
    {
        Serial.println(element);
    }
}