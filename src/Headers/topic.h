#ifndef TOPIC_H
#define TOPIC_H

// Setup topic
// From device
inline const char *topicACDevice = "640ee59066f4b889269ff405/AC/G2";
inline const char *topicACACK = "640ee59066f4b889269ff405/AC/G2/ACK";
// To device
inline const char *topicACServer = "640ee59066f4b889269ff405/AC/G2/server";

inline String topic[] = {topicACServer, topicACACK, topicACDevice};
inline String topicKey[] = {"subscribe", "ack", "publish"};

#endif