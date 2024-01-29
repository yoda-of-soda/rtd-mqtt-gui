#include <iostream>
#include <vector>
#include <map>
#include "topic_message_generator.hpp"
#include "mqtt_client.hpp"
#include "load_environment.hpp"

int main()
{
    std::map<std::string, std::string> env = loadEnvironment({"QUEUE_URL", "CLIENT_ID", "TOPIC"});

    std::vector<std::string> topics = {"Item A", "Item B", "Item C"};
    TopicMessageGenerator *messageGenerator = new TopicMessageGenerator(topics);

    MQTT_Client client(env["QUEUE_URL"], env["CLIENT_ID"]);

    while (true)
    {
        for (const std::string &topic : topics)
        {
            MessageWithTopic msg = messageGenerator->GenerateMessage(topic);
            client.SendMessage(msg);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    }

    delete messageGenerator;

    return 0;
}