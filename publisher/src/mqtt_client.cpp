#include <mqtt/async_client.h>
#include "message_with_topic.hpp"
#include "mqtt_client.hpp"

MQTT_Client::MQTT_Client(std::string url, std::string clientId) : client(url, clientId)
{
    client.set_callback(callback);

    mqtt::token_ptr conntok = client.connect();
    conntok->wait();
};

void MQTT_Client::SendMessage(MessageWithTopic msg)
{
    mqtt::message_ptr message = mqtt::make_message(msg.topic, msg.message);
    message->set_qos(1);

    mqtt::token_ptr pubtok = client.publish(message);
    pubtok->wait();
};

MQTT_Client::~MQTT_Client()
{
    this->client.disconnect()->wait();
};
