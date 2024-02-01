#ifndef MQTT_CLIENT_TEST
#define MQTT_CLIENT_TEST

#include "mqtt_client_mock.hpp"
#include <gtest/gtest.h>

class MQTT_ClientTest : public ::testing::Test
{
    public: 
        void SetUp();
        void TearDown();
    protected:
        MockMQTT_Client* mockClient;
};

#endif