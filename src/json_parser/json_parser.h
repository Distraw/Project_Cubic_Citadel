#pragma once
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace std;
using namespace nlohmann;

class JsonParser
{
private:
	string _filename;

	json _json_data;
public:
	JsonParser();
	void open(string filename);

	auto get(string name);
};