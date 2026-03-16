#pragma once
#pragma once

#include "FSM.h"


enum ENEMY_STATE
{
	ENEMY_STATE_IDLE,	//ë“ã@
	ENEMY_STATE_RUN,	//ì¶ëñ
	ENEMY_STATE_WANDERING,	//úpúj
	ENEMY_STATE_SURPRISED,	//ã¡Ç´

	ENEMY_STATE_NUM
};


//ÉAÉCÉhÉãèÛë‘
class ESIdle : public IState
{
public:
	void OnEnter(GameObject* parent) override;
	void OnExit(GameObject* parent) override;
	int Update(GameObject* parent) override;

private:
	 int IdleType;
	 int IdleCount;
};

//ì¶ëñèÛë‘
class ESRun : public IState
{
public:
	void OnEnter(GameObject* parent) override;
	void OnExit(GameObject* parent) override;
	int Update(GameObject* parent) override;
};

//úpújèÛë‘
class ESWandering : public IState
{
public:
	void OnEnter(GameObject* parent) override;
	void OnExit(GameObject* parent) override;
	int Update(GameObject* parent) override;

private:
	VECTOR nextPos;
};

//Ç—Ç¡Ç≠ÇËèÛë‘
class ESSurprised : public IState
{
public:
	void OnEnter(GameObject* parent) override;
	void OnExit(GameObject* parent) override;
	int Update(GameObject* parent) override;

private:
	int Count;
	VECTOR CurrentPos;
	VECTOR CurrentDir;
	int GraphHandle;
};

