#include <gmock/gmock.h>
#include "Imqtt_client.hpp"

class MockMQTT_Client : public IMQTT_Client
{
    public:
        MOCK_METHOD(void, SendMessage, (MessageWithTopic msg));
};