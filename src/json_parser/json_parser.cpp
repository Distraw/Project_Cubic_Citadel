#include "json_parser.h"

JsonParser::JsonParser()
{

}

void JsonParser::open(string filename)
{
	_filename = filename;
	
	ifstream file;
	file.open(filename);
	if (!file.is_open())
		throw exception("JsonParser: JSON file was not found");
	
	file >> _json_data;
}

auto JsonParser::get(string name)
{
	if (_json_data.contains(name.c_str())) return _json_data[name];
	else throw runtime_error("JsonParser: Key '" + name + "' not found in " + _filename);
}