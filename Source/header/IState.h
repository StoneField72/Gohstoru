#pragma once

#include "object.h"

class IState
{
public:
	IState() = default;
	virtual ~IState() = default;

	virtual void OnEnter(GameObject* parent) = 0;
	virtual void OnExit(GameObject* parent) = 0;
	virtual int Update(GameObject* parent) = 0;
};
