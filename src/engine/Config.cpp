#include <engine/Config.h>
#include <engine/DebugPrint.h>
#include <fstream>
#include <iostream>
#include <algorithm>

Config::Config()
{
    configFilePath = "anri.conf";
    load();
}

Config::~Config()
{
    ANRI_DE debugPrint("Config destructor fired.");

    configEntries.clear();
}

Config& Config::getInstance()
{
    static Config instance;

    return instance;
}

void Config::load()
{
    std::ifstream cFile (configFilePath);

    if(cFile.is_open())
    {
        std::string line;
        while(getline(cFile, line))
        {
            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

            if(line[0] == '#' || line.empty())
                continue;

            unsigned long delimiterPos = line.find('=');
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            ANRI_DE debugPrint("Read config line: %s=%s", key.c_str(), value.c_str());
            configEntries[key] = value;
        }
        cFile.close();
    }
    else
    {
        ANRI_DE debugPrint("Unable to open configuration file: %s", configFilePath.c_str());
    }
}

int Config::getIntValueByKey(std::string key)
{
    return std::stoi(configEntries.find(key)->second);
}

std::string Config::getStringValueByKey(std::string key)
{
    return configEntries.find(key)->second;
}
