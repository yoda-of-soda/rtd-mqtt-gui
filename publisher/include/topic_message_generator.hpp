#include <random>
#include <vector>
#include "message_with_topic.hpp"

#ifndef TOPICMESSAGEGENERATOR_HPP
#define TOPICMESSAGEGENERATOR_HPP

class TopicMessageGenerator
{
public:
    TopicMessageGenerator(std::vector<std::string> topics);
    MessageWithTopic GenerateMessage(std::string topic);
    MessageWithTopic GenerateMessage();

private:
    std::vector<std::string> topics;
    std::mt19937 numberGenerator;

    float getRandomFloat(float min, float max);
    std::string getRandomTopic();
    bool topicIsInvalid(std::string topic);
};

#endif