#include <mqtt/async_client.h>
#include "message_with_topic.hpp"
#include "callback.hpp"

#ifndef MQTT_CLIENT_HPP
#define MQTT_CLIENT_HPP

class MQTT_Client
{
public:
    MQTT_Client(std::string url, std::string clientId);
    void SendMessage(MessageWithTopic msg);
    ~MQTT_Client();
private:
    mqtt::async_client client;
    Callback callback;
};

#endif