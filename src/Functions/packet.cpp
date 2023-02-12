#include "../Headers/packet.h"

String packToJson()
{
    DynamicJsonDocument doc(1024);
    doc["deviceName"] = deviceName;
    doc["room"] = roomName;
    doc["deviceModule"] = deviceModule;

    int pos = 0;
    JsonObject topicObj = doc.createNestedObject("topic");
    for (auto &elementKey : topicKey)
    {
        topicObj[elementKey] = topic[pos];
        pos++;
    }

    pos = 0;
    JsonObject ackObj = doc.createNestedObject("ack");
    for (auto &elementKey : ackKey)
    {
        ackObj[elementKey] = ack[pos];
        pos++;
    }

    pos = 0;
    JsonObject requestObj = doc.createNestedObject("request");
    for (auto &elementKey : requestKey)
    {
        requestObj[elementKey] = request[pos];
        pos++;
    }

    pos = 0;
    JsonObject pinObj = doc.createNestedObject("pin");
    for (auto &elementKey : pinKey)
    {
        pinObj[elementKey] = pin[pos];
        pos++;
    }

    String json;
    serializeJson(doc, json);
    return json;
}