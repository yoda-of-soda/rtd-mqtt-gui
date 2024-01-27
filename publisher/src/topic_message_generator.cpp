#include <random>
#include <vector>
#include "message_with_topic.hpp"
#include "topic_message_generator.hpp"

TopicMessageGenerator::TopicMessageGenerator(std::vector<std::string> topics)
{
    this->topics = topics;
    std::random_device randomDevice;
    this->numberGenerator = std::mt19937(randomDevice());
}

MessageWithTopic TopicMessageGenerator::GenerateMessage(std::string topic)
{
    if (topicIsInvalid(topic))
    {
        topic = getRandomTopic();
    }
    float randomNumber = getRandomFloat(0, 100);
    return MessageWithTopic(topic, randomNumber);
}

MessageWithTopic TopicMessageGenerator::GenerateMessage()
{
    return GenerateMessage(getRandomTopic());
}

float TopicMessageGenerator::getRandomFloat(float min, float max)
{
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(numberGenerator);
}

std::string TopicMessageGenerator::getRandomTopic()
{
    std::uniform_int_distribution<int> distribution(0, topics.size() - 1);
    std::size_t randomIndex = distribution(numberGenerator);
    return topics[randomIndex];
}

bool TopicMessageGenerator::topicIsInvalid(std::string topic)
{
    for (std::size_t i = 0; i < topics.size(); i++)
    {
        if (topics[i] == topic)
            return true;
    }
    return false;
}