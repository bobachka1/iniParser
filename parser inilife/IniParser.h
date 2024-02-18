#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

namespace Consts{
const char separator = ';';
const char equal = '=';
const char open_bracket = '[';
const char close_bracket = ']';
} 

class iniParser
{
public:
	iniParser() = delete;
	iniParser(const std::string& filename);
	template<typename T>
	T getValue(const std::string& Section, const std::string& key)
	{
		T data;
		if (sizeof(data) == sizeof(std::string))
			return getStringValue(Section, key);
		else if (sizeof(data) == sizeof(int))
			return std::stoi(getStringValue(Section, key));
		else if (sizeof(data) == sizeof(double))
			return std::stod(getStringValue(Section, key));
		else if (sizeof(data) == sizeof(float))
			return std::stof(getStringValue(Section, key));
		else
			throw std::runtime_error("Wrong type");
	}
	~iniParser() = default;
private:
	std::string _file;
	std::map<std::string, std::map<std::string, std::string>> _mIni;
	std::string _Section;
	std::string _line;
	std::string _key;
	std::string _value;
	std::string getStringValue(const std::string& Section, const std::string& key);
};