#ifndef TOPICMESSAGEGENERATORTEST_HPP
#define TOPICMESSAGEGENERATORTEST_HPP

#include <gtest/gtest.h>
#include "topic_message_generator.hpp"

class TopicMessageGeneratorTest : public ::testing::Test
{
    protected:
        TopicMessageGenerator* messageGenerator;
        std::vector<std::string> topics;

    void SetUp() override;
    void TearDown() override;
    bool TopicIsInvalid(TopicMessageGenerator& msgGen, std::string topic);
};

#endif