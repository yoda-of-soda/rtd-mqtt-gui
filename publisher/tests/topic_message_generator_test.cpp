#include "topic_message_generator_test.hpp"

void TopicMessageGeneratorTest::SetUp()
{
    topics = {"Item A", "Item B", "Item C"};
    messageGenerator = new TopicMessageGenerator(topics);
}

void TopicMessageGeneratorTest::TearDown()
{
    delete messageGenerator;
}

bool TopicMessageGeneratorTest::TopicIsInvalid(TopicMessageGenerator &msgGen, std::string topic)
{
    return msgGen.topicIsInvalid(topic);
}

TEST_F(TopicMessageGeneratorTest, NumberValueWithinBoundaries)
{
    for (int i = 0; i < 10; i++)
    {
        MessageWithTopic message = messageGenerator->GenerateMessage(topics[0]);
        EXPECT_NE(message.message, "");
        float numericValue = std::stof(message.message);
        EXPECT_GE(numericValue, 0.0F);
        EXPECT_LE(numericValue, 100.0F);
    }
}

TEST_F(TopicMessageGeneratorTest, NumberValueIsRandom)
{
    float previousValue = -1.0F;
    for (int i = 0; i < 10; i++)
    {
        MessageWithTopic message = messageGenerator->GenerateMessage(topics[0]);
        float numericValue = std::stof(message.message);
        EXPECT_NE(numericValue, previousValue);
        previousValue = numericValue;
    }
}

TEST_F(TopicMessageGeneratorTest, TopicsMatch)
{
    for(const std::string& topic : topics)
    {
        MessageWithTopic message = messageGenerator->GenerateMessage(topic);
        EXPECT_EQ(message.topic.to_string(), topic);
    }
}

TEST_F(TopicMessageGeneratorTest, TopicValidatorWorks)
{
    for (const std::string topic : topics)
    {
        EXPECT_FALSE(TopicIsInvalid(*messageGenerator, topic));
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}