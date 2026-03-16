#pragma once

#include "object.h"
#include "FSM.h"
#include "DxLibBox.h"
#include "BoxModel.h"


class Player : public GameObject
{
private:
	BoxModel steve;

	FSM* m_fsm;

	float m_frame;

public:
	Player();
	~Player();

	void Init() override;
	void Uninit() override;
	int Update() override;
	void Draw() override;

	void SetFSM(FSM* fsm);
};
