#ifndef TOPIC_H
#define TOPIC_H

// Setup topic
// From device
inline const char *topicACDevice = "AC/room1";
inline const char *topicACACK = "AC/room1/ACK";
// To device
inline const char *topicACServer = "AC/room1/server";

inline String topic[] = {topicACServer, topicACACK, topicACDevice};
inline String topicKey[] = {"subscribe", "ack", "publish"};

#endif