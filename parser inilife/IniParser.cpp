#include "IniParser.h"

iniParser::iniParser(const std::string& filename) : _file(filename)
{
	std::ifstream file(_file);
	if (!file.is_open())
	{
		throw std::runtime_error("file is not found");
	}
	while (std::getline(file, _line))
	{
		if (_line.empty() || _line[0] == Consts::separator)
		{
			continue;
		}
		if (_line[0] == Consts::open_bracket && _line[_line.length() - 1] == Consts::close_bracket)
		{
			_Section = _line.substr(1, _line.length() - 2);
		}
		else
		{
			std::istringstream iss(_line);
			if (std::getline(iss, _key, Consts::equal))
			{
				if (std::getline(iss, _value))
				{
					size_t pos = _value.find(Consts::separator);
					if (pos != std::string::npos)
					{
						_value = _value.substr(0, pos);
					}
					_mIni[_Section][_key] = _value;
				}
			}
		}
	}
	file.close();
}
std::string iniParser::getStringValue(const std::string& Section, const std::string& key)
{
	std::map<std::string, std::map<std::string, std::string>>::iterator it1 = _mIni.find(Section);
	if (it1 == _mIni.end())
	{
		throw std::runtime_error(Section + " not found");
	}
	else
	{
		std::map<std::string, std::string>& m1 = _mIni[Section];
		if (!m1.count(key))
		{
			throw std::runtime_error("There are no key : " + key + ", in the section " + Section);
		}
	}
	return _mIni[Section][key];
}