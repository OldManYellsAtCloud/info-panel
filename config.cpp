#include "config.h"
#include <stdlib.h>
#include <filesystem>
#include <unistd.h>
#include <thread>
#include <limits>
#include "logger.h"

static const std::string CONFIG_NAME {"info-panel.cfg"};

config::config()
{
    std::string homeFolder {getenv("HOME")};
    if (homeFolder == NULL) {
        LOG(LOG_ERR, "Could not determine home folder. Using /tmp folder for config.");
        homeFolder = "/tmp";
    }
    std::string configFolder {homeFolder + "/.config"};
    std::string fullConfigPath {configFolder + "/" + CONFIG_NAME};

    if (!std::filesystem::exists(configFolder)) {
        std::filesystem::create_directory(configFolder);
    }

    std::fstream configFile;
    configFile.open(fullConfigPath);

    std::string line;
    while (getline(configFile, line)) {
        if (line.find("=") != std::string::npos) {
            parseLine(line);
        }
    }

    last_modified = last_saved = time(NULL);
    configFile.close();
    t = std::thread(&config::saveThread, this);
}

int config::getIntConfig(const std::string &key)
{
    if (intDict.find(key) != intDict.end())
        return intDict[key];
    return std::numeric_limits<int>::max();
}

void config::setIntConfig(const std::string &key, int value)
{
    intDict[key] = value;
    last_modified = time(NULL);
}

float config::getFloatConfig(const std::string &key)
{
    if (floatDict.find(key) != floatDict.end())
        return floatDict[key];
    return std::numeric_limits<float>::max();
}

void config::setFloatConfig(const std::string &key, const float &value)
{
    floatDict[key] = value;
    last_modified = time(NULL);
}

std::string config::getStringConfig(const std::string &key)
{
    if (stringDict.find(key) != stringDict.end())
        return stringDict[key];
    return "";
}

void config::setStringConfig(const std::string &key, const std::string &value)
{
    stringDict[key] = value;
    last_modified = time(NULL);
}

void config::parseLine(const std::string &line)
{
    int delimIndex = line.find("=");
    std::string key = line.substr(0, delimIndex);
    std::string value = line.substr(delimIndex + 1, line.length());
    std::cout << "key: " << key << ", value: " << value << std::endl;

    try {
        if (value.find(".") == std::string::npos) { // try to parse it as int if there is no decimal separator
            int i = std::stoi(value);
            intDict.insert({key, i});
            std::cout << "int value" << std::endl;
        } else { // try to parse it as float, if there is a decimal separator
            float f = std::stof(value);
            floatDict.insert({key, f});
            std::cout << "float value" << std::endl;
        }
    } catch (std::invalid_argument const &ex) { // if parsing as number fails, keep it as string
        stringDict.insert({key, value});
        std::cout << "string value" << std::endl;
    }
}

void config::saveThread()
{
    std::string homeFolder {getenv("HOME")};
    if (homeFolder == NULL) {
        LOG(LOG_ERR, "Could not determine home folder. Using /tmp folder for config.");
        homeFolder = "/tmp";
    }
    std::string configFolder {homeFolder + "/.config"};
    std::string fullConfigPath {configFolder + "/" + CONFIG_NAME};
    std::fstream configFile;

    while (true) {
        if (last_modified > last_saved) {
            if (std::filesystem::exists(fullConfigPath))
                std::filesystem::rename(fullConfigPath, fullConfigPath + ".backup");

            configFile.open(fullConfigPath, std::fstream::out);

            for (auto it = intDict.begin(); it != intDict.end(); ++it) {
                configFile << it->first << "=" << it->second << std::endl;
            }

            for (auto it = floatDict.begin(); it != floatDict.end(); ++it) {
                configFile << it->first << "=" << it->second << std::endl;
            }

            for (auto it = stringDict.begin(); it != stringDict.end(); ++it) {
                configFile <<  it->first << "=" << it->second << std::endl;
            }

            configFile.close();
            if (std::filesystem::exists(fullConfigPath + ".backup"))
                std::filesystem::remove(fullConfigPath + ".backup");

            last_modified = last_saved = time(NULL);
        } else {
            sleep(5);
        }
    }
}
