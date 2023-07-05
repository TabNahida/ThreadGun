#include<iostream>
#include<fstream>
#include<filesystem>
#include<string>
#include<sstream>
#include<map>
#include<vector>
namespace fs = std::filesystem;

namespace TConfig
{
	std::map<std::string, std::string> ConfigLoadFromFile(fs::path configfile);
	std::map<std::string, std::string> ConfigLoadFromString(std::string& configstring);
	bool ConfigSaveToFile(std::map<std::string, std::string>& conmap, fs::path configfile);
	std::string ConfigSaveToString(std::map<std::string, std::string>& conmap);
}