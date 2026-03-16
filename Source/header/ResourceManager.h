#pragma once

#include <map>
#include <string>
#include <list>


class ResourceManager
{
private:
	std::map<std::string, int> m_images;
	std::map<std::string, int> m_effects;

public:
	ResourceManager() = default;
	~ResourceManager() = default;

	int LoadImageFromFile(std::string name);
	int GetImage(std::string name);

	int LoadEffectFromFile(std::string name, float baseScale = 1.0f);
	int GetEffect(std::string name);

	void UnloadImage(std::string name);
	void UnloadImage(int handle);

	void UnloadEffect(std::string tag);

	void Uninitialize(void);
};
