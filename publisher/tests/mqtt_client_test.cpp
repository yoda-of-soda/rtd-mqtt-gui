#include "mocks/mqtt_client.hpp"
#include <gtest/gtest.h>

class MQTT_ClientTest : public ::testing::Test
{
    public: 
        void SetUp()
        {
            mockClient = new MockMQTT_Client();
        }

        void TearDown()
        {
            delete mockClient;
        }
    protected:
        MockMQTT_Client* mockClient;
};

TEST_F(MQTT_ClientTest, SendMessageIsCalled)
{
    MessageWithTopic msg("topic", "message");
    EXPECT_CALL(*mockClient, SendMessage(msg));
    mockClient->SendMessage(msg);
}

