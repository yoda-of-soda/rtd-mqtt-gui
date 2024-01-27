#include <mqtt/async_client.h>

#ifndef CALLBACK_HPP
#define CALLBACK_HPP

class Callback : public virtual mqtt::callback
{
public:
    virtual void connected(const mqtt::string &cause) override;
    virtual void connection_lost(const std::string &cause) override;
    virtual void delivery_complete(mqtt::delivery_token_ptr token) override;
};

#endif