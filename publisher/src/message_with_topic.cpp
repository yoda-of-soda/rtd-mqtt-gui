#include <string>
#include <mqtt/buffer_ref.h>
#include "message_with_topic.hpp"

MessageWithTopic::MessageWithTopic(std::string topic, std::string message)
{
    this->message = message;
    this->topic = topic;
};

MessageWithTopic::MessageWithTopic(std::string topic, float numericMessage)
{
    this->message = std::to_string(numericMessage);
    this->topic = topic;
};