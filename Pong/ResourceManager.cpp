#include "ResourceManager.h"


ResourceManager::ResourceManager(std::string filename) : file_name(filename)
{
	std::ifstream in(file_name);
	if (in.is_open())
	{
		std::string string;
		while (std::getline(in, string)) {
			this->contents.append(string);
		}
		in.close();
	}
	else {
		std::cout << "Could not open file " << file_name << std::endl;
	}

	std::cout << "Contents of the file are " << this->contents;
}


ResourceManager::~ResourceManager()
{
}

ResourceManager * ResourceManager::getResourceManager(std::string file_name)
{
	if (!isInstantiated)
	{
		singleton = new ResourceManager(file_name);
		return singleton;
	}
	else {
		return singleton;
	}
}

bool ResourceManager::isInstantiated = false;
ResourceManager * ResourceManager::singleton = nullptr;
