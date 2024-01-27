#include <mqtt/async_client.h>
#include "callback.hpp"

void Callback::connected(const mqtt::string &cause)
{
    std::cout << "Connected to the broker" << std::endl;
}

void Callback::connection_lost(const std::string &cause)
{
    std::cerr << "Connection lost: " << cause << std::endl;
}

void Callback::delivery_complete(mqtt::delivery_token_ptr token)
{
    std::cout << "Message delivered" << std::endl;
}
