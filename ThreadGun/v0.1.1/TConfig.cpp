#include"TConfig.hpp"

namespace TConfig
{
	std::map<std::string, std::string> ConfigLoadFromFile(fs::path configfile)
	{
		std::map<std::string, std::string> conmap;
		std::string label, value;
		char reader;
		bool labval = true;
		std::ifstream loader(configfile);
		if (!loader.is_open())
		{
			std::cout << "Fail to Open " << configfile << std::endl;
		}
		for (; !loader.eof();)
		{
			loader.get(reader);
			if (reader == '\n')
			{
				continue;
			}
			else if (reader == ':' && labval)
			{
				labval = !labval;
				continue;
			}
			else if (reader == ';' && !labval)
			{
				labval = !labval;
				conmap[label] = value;
				label.clear();
				value.clear();
				continue;
			}
			else if ((reader == ':' && !labval) || (reader == ';' && labval))
			{
				std::cout << "Error pattern " << reader << " " << labval << std::endl;
				continue;
			}
			if (labval)
			{
				label += reader;
			}
			else
			{
				value += reader;
			}
		}
		loader.close();
		return conmap;
	}

	std::map<std::string, std::string> ConfigLoadFromString(std::string& configstring)
	{
		std::map<std::string, std::string> conmap;
		std::string label, value;
		char reader;
		bool labval = true;
		std::istringstream loader(configstring);
		for (; !loader.eof();)
		{
			loader.get(reader);
			if (reader == '\n')
			{
				continue;
			}
			else if (reader == ':' && labval)
			{
				labval = !labval;
				continue;
			}
			else if (reader == ';' && !labval)
			{
				labval = !labval;
				conmap[label] = value;
				label.clear();
				value.clear();
				continue;
			}
			else if ((reader == ':' && !labval) || (reader == ';' && labval))
			{
				std::cout << "Error pattern " << reader << " " << labval << std::endl;
				continue;
			}
			if (labval)
			{
				label += reader;
			}
			else
			{
				value += reader;
			}
		}
		loader.clear();
		return conmap;
	}

	bool ConfigSaveToFile(std::map<std::string, std::string>& conmap, fs::path configfile)
	{
		std::ofstream saver(configfile);
		if (!saver.is_open())
		{
			std::cout << "Fail to Open " << configfile << std::endl;
			return false;
		}
		for (auto it = conmap.begin(); it != conmap.end(); it++)
		{
			saver << it->first + ":" + it->second + ";" << std::endl;
		}
		saver.close();
	}

	std::string ConfigSaveToString(std::map<std::string, std::string>& conmap)
	{
		std::ostringstream saver;
		for (auto it = conmap.begin(); it != conmap.end(); it++)
		{
			saver << it->first + ":" + it->second + ";" << std::endl;
		}
		return saver.str();
	}
}