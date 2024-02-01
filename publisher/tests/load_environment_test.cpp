#include <gtest/gtest.h>
#include "load_environment.hpp"

TEST(LoadEnvironmentTest, EnvironmentIsLoaded)
{
    std::vector<std::string> keys = {"QUEUE_URL", "CLIENT_ID", "TOPIC"};
    std::map<std::string, std::string> env = loadEnvironment(keys);
    EXPECT_EQ(env.size(), keys.size());
}