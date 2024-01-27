#include <map>
#include <string>
#include <vector>
#include <stdexcept>

std::map<std::string, std::string> loadEnvironment(std::vector<std::string> keys)
{
    std::map<std::string, std::string> output;

    for (std::string key : keys)
    {
        char *value = std::getenv(key.c_str());
        if (value)
        {
            output[key] = value;
        }
        else
        {
            throw std::runtime_error("Missing environment variable: " + key);
        }
    }
    return output;
}