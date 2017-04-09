#include <engine/Config.h>
#include <engine/DebugPrint.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

Config::Config()
{
	configFilePath = "anri.conf";
	load();
}

Config::~Config()
{

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
	std::map<std::string, std::string>::iterator p = configEntries.find(key);

	return std::stoi(p->second);
}

std::string Config::getStringValueByKey(std::string key)
{
	std::map<std::string, std::string>::iterator p = configEntries.find(key);

	return p->second;
}
