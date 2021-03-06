#ifndef ANRI_CONFIG_H
#define ANRI_CONFIG_H

#include <string>
#include <map>

class Config
{
    public:
        static Config& getInstance();
        int getIntValueByKey(std::string key) const;
        std::string getStringValueByKey(std::string key) const;
        bool getBoolValueByKey(std::string key) const;

        Config(Config const&) = delete;
        Config(Config&&) = delete;

    private:
        Config();
        virtual ~Config();

        std::string configFilePath;
        std::map<std::string, std::string> configEntries;

        void load();

};

#endif //ANRI_CONFIG_H
