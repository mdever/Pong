#pragma once
#include<map>
#include <fstream>
#include <iostream>
#include <sstream>
class ResourceManager
{
public:
	~ResourceManager();

	static ResourceManager * getResourceManager(std::string file_name);
	std::string get_property(std::string);
private:
	ResourceManager(std::string filename);
	static bool isInstantiated;
	static ResourceManager * singleton;
	std::map<std::string, void *> resource_map;
	std::string file_name;
	std::string contents;
};

