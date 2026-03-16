#pragma once

#include <map>
#include <string>
#include "Scene.h"


class SceneManager
{
protected:
	std::string m_activeSceneName;
	std::string m_nextSceneName;

	std::map<std::string, Scene*> m_scenes;

public:
	SceneManager() = default;
	virtual ~SceneManager() = default;

	void AddScene(std::string name, Scene* scene);
	void Uninitialize();

	void SetScene(std::string name);
	void SceneTransition(void);

	void Update(void);
	void LateUpdate(void);
	void Render(void);
};
