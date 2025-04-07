#pragma once

#include <string>

inline std::string get_env(const std::string &key, const std::string &default_value = "")
{
    const char *value = std::getenv(key.c_str());
    return value ? value : default_value;
}

struct Config
{
    std::string host;
    std::string port;

    static Config New()
    {
        Config config;
        config.host = get_env("HOST", "0.0.0.0");
        config.port = get_env("PORT", "50051");
        return config;
    }
};