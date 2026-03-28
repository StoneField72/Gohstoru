#pragma once


#include "Object.h"
#include <list>
#include <string>


class ObjectManager
{
private:
	std::list<GameObject*> objList;
	std::list<std::pair<std::string, int>> effectList;

	MATRIX matView;

public:
	ObjectManager() = default;
	~ObjectManager() = default;

	void UpdateObjects();
	void RenderObjects();

	std::list<GameObject*> GetObjectsByTag(std::string tag);
	GameObject* GetObjectByTag(std::string tag);
	std::list<GameObject*>& GetObjectList() { return objList; }

	void AddObject(GameObject* obj);
	void ClearObjects();
	void ClearObjectsForce();
	void RemoveObject(GameObject* obj);
	void RemoveObjectByTag(std::string tag);

	void AddEffect(std::string name, std::string tag, VECTOR pos, VECTOR rot, VECTOR scale);
	void UpdateEffect(std::string tag, VECTOR pos, VECTOR rot, VECTOR scale);
	int GetEffectByTag(std::string tag);

	void RestoreViewMatrix();
};
