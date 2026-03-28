#pragma once

#include <vector>
#include "Object.h"

/*** シーン基底クラス ***/
class Scene 
{
protected:
	std::vector<GameObject*> m_objects;

public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void Initialize(void) = 0;
	virtual void Uninitialize(void) = 0;
	virtual Scene* Update(void) = 0;
	virtual void LateUpdate(void) = 0;
	virtual void Render(void) = 0;
};
