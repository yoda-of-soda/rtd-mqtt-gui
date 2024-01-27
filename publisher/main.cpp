#include <iostream>
#include <vector>
#include <map>
#include "topic_message_generator.hpp"
#include "mqtt_client.hpp"
#include "load_environment.hpp"

int main()
{
    std::map<std::string, std::string> env = loadEnvironment({"QUEUE_URL", "CLIENT_ID", "TOPIC"});

    std::vector<std::string> topics = {"FUN", "WORK", "CHORES"};
    TopicMessageGenerator *messageGenerator = new TopicMessageGenerator(topics);

    MQTT_Client client(env["QUEUE_URL"], env["CLIENT_ID"]);

    while (true)
    {
        for (const std::string &topic : topics)
        {
            MessageWithTopic msg = messageGenerator->GenerateMessage(topic);
            client.SendMessage(msg);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    delete messageGenerator;

    return 0;
}