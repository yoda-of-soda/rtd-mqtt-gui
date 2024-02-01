#ifndef IMQTT_CLIENT_HPP
#define IMQTT_CLIENT_HPP

#include "message_with_topic.hpp"

class IMQTT_Client
{
public:
    virtual void SendMessage(MessageWithTopic msg) = 0;
};

#endif // IMQTT_CLIENT_HPP