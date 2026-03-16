#pragma once

#include "object.h"
#include "IState.h"
#include <map>

class FSM
{
private:
	int currentState;	//Œ»İÀs‚µ‚Ä‚¢‚éState‚ÌID
	std::map<int, IState*> stateMap;//ID‚ÆState‚ÌŠÖ˜A•t‚¯

public:
	FSM();
	virtual ~FSM();

	void RegisterState(const int id, IState* state);
	void SetCurrentState(const int id, GameObject* parent);

	void Update(GameObject* parent);
};
