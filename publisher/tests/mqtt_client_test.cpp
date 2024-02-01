#include "mqtt_client_test.hpp"

void MQTT_ClientTest::SetUp()
{
    mockClient = new MockMQTT_Client();
}

void MQTT_ClientTest::TearDown()
{
    delete mockClient;
}

TEST_F(MQTT_ClientTest, SendMessageIsCalled)
{
    MessageWithTopic msg("topic", "message");
    EXPECT_CALL(*mockClient, SendMessage(msg));
    mockClient->SendMessage(msg);
}
