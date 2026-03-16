#pragma once

#include "object.h"
#include "FSM.h"
#include "DxLibBox.h"
#include "BoxModel.h"


class Enemy : public GameObject
{
private:
	FSM* m_fsm;

	float m_frame;

	float alpha;

	//モデルハンドル
	int mnModelHandle;          // 読み込んだモデルのハンドル
	int mnModelIdleHandle;
	int texHandle;
	int texHandle1;
	int texHandle2;

	//アニメーション関連
	float AnimTotalTime;
	float AnimNowTime;
	int AnimAttachIndex;
	int MoveAnimFrameIndex;

	int GhostType;

	int oweGraphHandle;

	int ShowCount;

public:
	Enemy();
	~Enemy();

	void Init() override;
	void Uninit() override;
	int Update() override;
	void Draw() override;

	void SetFSM(FSM* fsm);
};
