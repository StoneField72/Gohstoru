#pragma once

#include <string>
#include "FSM.h"
#include "Object.h"


class FSMFactory
{
public:
	static FSM* Create(const std::string& fsmType, GameObject* pObj);
};
