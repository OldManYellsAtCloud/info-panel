#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <time.h>
#include <fstream>
#include <map>
#include <thread>

class config
{
private:
    config();
    time_t last_saved, last_modified;

    std::map<std::string, int> intDict;
    std::map<std::string, float> floatDict;
    std::map<std::string, std::string> stringDict;

    void parseLine(const std::string& line);
    void saveThread();

    std::thread t;


public:

    static config& getConfig(){
        static config config {};
        return config;
    }

    config(config const&) = delete;
    void operator=(config const&) = delete;

    int getIntConfig(const std::string& key);
    void setIntConfig(const std::string& key, int value);

    float getFloatConfig(const std::string& key);
    void setFloatConfig(const std::string& key, const float& value);

    std::string getStringConfig(const std::string& key);
    void setStringConfig(const std::string& key, const std::string& value);
};

#endif // CONFIG_H
