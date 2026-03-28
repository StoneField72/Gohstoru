#pragma once

#include "FSM.h"


enum PLAYER_STATE
{
	PLAYER_STATE_IDLE,	//待機
	PLAYER_STATE_WALK,	//歩き
	PLAYER_STATE_CAMERA,	//カメラ
	PLAYER_STATE_CAMERA_WALK,	//カメラ歩き
	PLAYER_STATE_SKILL,

	PLAYER_STATE_NUM
};


//アイドル状態
class PSIdle : public IState
{
public:
	void OnEnter(GameObject* parent) override;
	void OnExit(GameObject* parent) override;
	int Update(GameObject* parent) override;
};


//歩き状態
class PSWalk : public IState
{
public:
	void OnEnter(GameObject* parent) override;
	void OnExit(GameObject* parent) override;
	int Update(GameObject* parent) override;
};


//カメラ状態
class PSCamera : public IState
{
public:
	void OnEnter(GameObject* parent) override;
	void OnExit(GameObject* parent) override;
	int Update(GameObject* parent) override;
};


//カメラ歩き状態
class PSCameraWalk : public IState
{
public:
	void OnEnter(GameObject* parent) override;
	void OnExit(GameObject* parent) override;
	int Update(GameObject* parent) override;
};

//カメラ歩き状態
class PSSkill : public IState
{
public:
	void OnEnter(GameObject* parent) override;
	void OnExit(GameObject* parent) override;
	int Update(GameObject* parent) override;

private:
	int rand = 0;
	int Selected;
	int Count;
};
