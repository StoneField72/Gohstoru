
#include "game_enemy.h"
#include "Master.h"
#include "DxLib.h"
#include <cassert>
#include "DxLibUtil.h"


Enemy::Enemy()
{
	m_fsm = nullptr;

	mnModelHandle =     -1;//モデルハンドル
	mnModelIdleHandle = -1;//待機アニメーション用モデルハンドル

	texHandle = -1;//テクスチャ用画像ハンドル
	texHandle1 = -1;//		
	texHandle2 = -1;//

	AnimAttachIndex = 0;
	AnimNowTime = 0;
	AnimTotalTime = 0;
	MoveAnimFrameIndex = 0;
	m_frame = 0;

	alpha = 0.0f;//透明度用変数
	GhostType = 0;//敵の種類
	ShowCount = 0;
}

Enemy::~Enemy()
{
	Uninit();

	//各ハンドルの解放
	MV1DeleteModel(mnModelHandle);
	MV1DeleteModel(mnModelIdleHandle);

	DeleteGraph(texHandle);
	DeleteGraph(texHandle1);
	DeleteGraph(texHandle2);
}

void Enemy::Init()
{
	//敵のタイプを抽選する
	GhostType = GetRand(5);

	alpha = 0.0f;

	//キャラクター画像の読み込み
	m_fsm = nullptr;

	SetUseZBuffer3D(TRUE);//Zバッファ有効
	SetWriteZBuffer3D(TRUE);//Zバッファ書き込み有効
	SetUseBackCulling(TRUE);//背面ポリゴンのカリング

	SetUseLighting(FALSE);

	// 3Dモデルの読み込み
	switch (GhostType)
	{
	case 0://ノーマル
		mnModelHandle = MV1LoadModel("Resource/asset/Enemy/TestGhost.mv1");
		mnModelIdleHandle = MV1LoadModel("Resource/asset/Enemy/TestGhost.mv1");

		texHandle2 = LoadGraph("Resource/asset/Enemy/Ghost Kid Normal.png");
		MV1SetTextureGraphHandle(mnModelHandle, 2, texHandle2, TRUE); // 0はテクスチャ番号
		break;

	case 1://赤ウィッチ
		mnModelHandle = MV1LoadModel("Resource/asset/Enemy/Ghost4.mv1");
		mnModelIdleHandle = MV1LoadModel("Resource/asset/Enemy/Ghost4.mv1");

		texHandle1 = LoadGraph("Resource/asset/Enemy/Witch Hat 2.png");
		texHandle2 = LoadGraph("Resource/asset/Enemy/Kid Ghost_blinn3_BaseColor.png");
		MV1SetTextureGraphHandle(mnModelHandle, 1, texHandle1, TRUE); // 0はテクスチャ番号
		MV1SetTextureGraphHandle(mnModelHandle, 2, texHandle2, TRUE); // 0はテクスチャ番号
		break;

	case 2://青ウィッチ
		mnModelHandle = MV1LoadModel("Resource/asset/Enemy/Ghost5.mv1");
		mnModelIdleHandle = MV1LoadModel("Resource/asset/Enemy/Ghost5.mv1");

		texHandle1 = LoadGraph("Resource/asset/Enemy/Witch Hat 3.png");
		texHandle2 = LoadGraph("Resource/asset/Enemy/Ghost Kid Normal.png");
		MV1SetTextureGraphHandle(mnModelHandle, 1, texHandle1, TRUE); // 0はテクスチャ番号
		MV1SetTextureGraphHandle(mnModelHandle, 4, texHandle2, TRUE); // 0はテクスチャ番号
		break;

	case 3://角
		mnModelHandle = MV1LoadModel("Resource/asset/Enemy/Ghost3.mv1");
		mnModelIdleHandle = MV1LoadModel("Resource/asset/Enemy/Ghost3.mv1");

		texHandle2 = LoadGraph("Resource/asset/Enemy/Kid Ghost_blinn1_BaseColor.png");
		MV1SetTextureGraphHandle(mnModelHandle, 2, texHandle2, TRUE); // 0はテクスチャ番号
		break;

	case 4://斧刺さり
		mnModelHandle = MV1LoadModel("Resource/asset/Enemy/Ghost6.mv1");
		mnModelIdleHandle = MV1LoadModel("Resource/asset/Enemy/Ghost6.mv1");

		texHandle = LoadGraph("Resource/asset/Enemy/Axe.png");
		texHandle2 = LoadGraph("Resource/asset/Enemy/Ghost Kid Blooded1.png");
		MV1SetTextureGraphHandle(mnModelHandle, 0, texHandle, TRUE); // 0はテクスチャ番号
		MV1SetTextureGraphHandle(mnModelHandle, 3, texHandle2, TRUE); // 0はテクスチャ番号
		break;

	case 5://橙
		mnModelHandle = MV1LoadModel("Resource/asset/Enemy/Ghost2.mv1");
		mnModelIdleHandle = MV1LoadModel("Resource/asset/Enemy/Ghost2.mv1");

		texHandle2 = LoadGraph("Resource/asset/Enemy/Kid Ghost_blinn2_BaseColor.png");
		MV1SetTextureGraphHandle(mnModelHandle, 2, texHandle2, TRUE); // 0はテクスチャ番号
		break;

	default:
		break;
	}


	AnimAttachIndex = MV1AttachAnim(mnModelHandle, 0, mnModelIdleHandle);
	AnimTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, AnimAttachIndex);
	AnimNowTime = 0.0f;
	MV1SetAttachAnimTime(mnModelHandle, AnimAttachIndex, AnimNowTime);
	// アニメーションで移動しているフレームの番号を検索する
//	MoveAnimFrameIndex = MV1SearchFrame(mnModelHandle, "MESH_Infantry");
	// アニメーションで移動しているフレームを無効にする
	MV1SetFrameUserLocalMatrix(
		mnModelHandle,
		MoveAnimFrameIndex,
		MV1GetFrameLocalMatrix(mnModelHandle, MoveAnimFrameIndex)
	);

	// 3Dモデルの位置を設定
    MV1SetPosition(mnModelHandle, this->GetPos());
	MV1SetRotationXYZ(mnModelHandle, this->GetDir());
	MV1SetScale(mnModelHandle, VGet(3.0f, 3.0f, 3.0f));

	oweGraphHandle = LoadGraph("Resource/asset/Enemy/owe.png");
}

void Enemy::Uninit()
{
	SAFE_DELETE(m_fsm);

	Master::resManager->Uninitialize();
}

int Enemy::Update()
{
	AnimTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, AnimAttachIndex);

	m_fsm->Update(this);

	// Z+ を正面として、向きを合わせる回転角
	float angleY = atan2(m_dir.x, m_dir.z);

	MV1SetPosition(mnModelHandle, VSub(this->GetPos(), VGet(0.0f, 100.0f, 0.0f)));
	MV1SetRotationXYZ(mnModelHandle, VGet(0.0f, angleY, 0.0f));

	///アニメーション
	AnimNowTime += 0.5f;
	if (AnimNowTime >= AnimTotalTime)
	{
		MV1SetAttachAnimTime(mnModelHandle, AnimAttachIndex, AnimTotalTime);
		AnimNowTime -= AnimTotalTime;

		MV1SetAttachAnimTime(mnModelHandle, AnimAttachIndex, 0.0f);

		MV1SetAttachAnimTime(mnModelHandle, AnimAttachIndex, AnimNowTime);
	}
	else
	{
		MV1SetAttachAnimTime(mnModelHandle, AnimAttachIndex, AnimNowTime);
	}
	////////////////////////////////////

	return 0;
}

void Enemy::Draw()
{
	//不可視フラグが立っていればモデルの透明度を下げる
	if (!this->GetInvisible() && alpha != 0.5f)
	{
		alpha += 0.01f;

		if (alpha >= 0.5f)
		{
			alpha = 0.5f;
		}
	}
	else
	{
		alpha -= 0.01f;

		if (alpha <= 0.0f)
		{
			alpha = 0.0f;
		}
	}

	//モデルに透明度を適用する
	MV1SetOpacityRate(mnModelHandle, alpha);

	if (alpha > 0.0f)
	{
		SetUseLighting(false);
		SetFogEnable(FALSE);

		MV1DrawModel(mnModelHandle);

		SetFogEnable(TRUE);
		SetUseLighting(true);
	}


	if (this->GetSelect() == true)
	{
		ShowCount++;

		if (ShowCount >= 1200)
		{
			this->SetSelect(false);
			ShowCount = 0;
		}

		SetFogEnable(FALSE);
		DrawCone3D(VAdd(this->GetPos(), VGet(0.0f, 150.0f, 0.0f)), VAdd(this->GetPos(), VGet(0.0f, 225.0f, 0.0f)), 40.0f, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
		SetFogEnable(TRUE);
	}
}

void Enemy::SetFSM(FSM* fsm)
{
	assert(fsm);

	m_fsm = fsm;
}
