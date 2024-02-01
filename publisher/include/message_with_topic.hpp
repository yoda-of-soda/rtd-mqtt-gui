#include <string>
#include <mqtt/buffer_ref.h>

#ifndef MESSAGEWITHTOPIC_HPP
#define MESSAGEWITHTOPIC_HPP

class MessageWithTopic
{
public:
    MessageWithTopic(std::string topic, std::string message);
    MessageWithTopic(std::string topic, float numericMessage);
    std::string message;
    mqtt::string_ref topic;
    bool operator==(const MessageWithTopic& other) const;
};

#endif  