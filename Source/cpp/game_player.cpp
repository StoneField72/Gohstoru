
#include "game_player.h"
#include "Master.h"
#include "DxLib.h"
#include <cassert>


Player::Player()
{
	m_fsm = nullptr;
}

Player::~Player()
{
	Uninit();
}

void Player::Init()
{
	//キャラクター画像の読み込み
	m_fsm = nullptr;

	SetUseZBuffer3D(TRUE);//Zバッファ有効
	SetWriteZBuffer3D(TRUE);//Zバッファ書き込み有効
	SetUseBackCulling(TRUE);//背面ポリゴンのカリング

	SetUseLighting(FALSE);

	DxLibBox body;
	body.Create(100.0f, 150.0f, 50.0f);	//体の初期化
	body.SetUVFront (0.3125f, 0.3125f, 0.125f, 0.1875);
	body.SetUVBack  (0.4375f, 0.3125f, 0.125f, 0.1875);
	body.SetUVUp    (0.3125f, 0.25f, 0.125f, 0.0625);
	body.SetUVBottom(0.4375f, 0.25f, 0.125f, 0.0625);
	body.SetUVRight (0.5625f, 0.3125f, 0.0625f, 0.1875);
	body.SetUVLeft  (0.25f, 0.3125f, 0.0625f, 0.1875);
	body.SetTexture("Resource/asset/steve120.png");
	steve.AddBox("body", body);

	DxLibBox head;
	head.Create(100.0f, 100.0f, 100.0f);	//頭の初期化
	head.SetPos(0.0f, 125.0f, 0.0f);
	head.SetTexture("Resource/asset/steve120.png");
	steve.AddBox("head", head, "body");

	DxLibBox rarm;
	rarm.Create(50.0f, 150.0f, 50.0f);
	rarm.SetUVFront (0.6875f, 0.3125f, 0.0625f, 0.1875f);
	rarm.SetUVBack  (0.8125f, 0.3125f, 0.0625f, 0.1875f);
	rarm.SetUVUp    (0.6875f, 0.25f, 0.0625f, 0.0625f);
	rarm.SetUVBottom(0.75f, 0.25f, 0.0625f, 0.0625f);
	rarm.SetUVRight (0.625f, 0.3125f, 0.0625f, 0.1875f);
	rarm.SetUVLeft  (0.75f, 0.3125f, 0.0625f, 0.1875f);
	rarm.SetPos(75.0f, 55.0f, 0.0f);
	rarm.SetOffset(0.0f, -55.0f, 0.0f);
	rarm.SetTexture("Resource/asset/steve120.png");
	steve.AddBox("rarm", rarm, "body");

	DxLibBox larm;
	larm.Create(50.0f, 150.0f, 50.0f);
	larm.SetUVFront(0.6875f, 0.3125f, 0.0625f, 0.1875f);
	larm.SetUVBack(0.8125f, 0.3125f, 0.0625f, 0.1875f);
	larm.SetUVUp(0.6875f, 0.25f, 0.0625f, 0.0625f);
	larm.SetUVBottom(0.75f, 0.25f, 0.0625f, 0.0625f);
	larm.SetUVRight(0.75f, 0.3125f, 0.0625f, 0.1875f);
	larm.SetUVLeft(0.625f, 0.3125f, 0.0625f, 0.1875f);
	larm.SetPos(-75.0f, 55.0f, 0.0f);
	larm.SetOffset(0.0f, -55.0f, 0.0f);
	larm.SetTexture("Resource/asset/steve120.png");
	steve.AddBox("larm", larm, "body");

	DxLibBox rleg;
	rleg.Create(50.0f, 150.0f, 50.0f);
	rleg.SetUVFront(0.0625f, 0.3125f, 0.0625f, 0.1875f);
	rleg.SetUVBack(0.1875f, 0.3125f, 0.0625f, 0.1875f);
	rleg.SetUVUp(0.0625f, 0.25f, 0.0625f, 0.0625f);
	rleg.SetUVBottom(0.125f, 0.25f, 0.0625f, 0.0625f);
	rleg.SetUVRight(0.125f, 0.3125f, 0.0625f, 0.1875);
	rleg.SetUVLeft(0.0f, 0.3125f, 0.0625f, 0.1875f);
	rleg.SetPos(25.0, -80.0f, 0.0f);
	rleg.SetOffset(0.0f, -70.0f, 0.0f);
	rleg.SetTexture("Resource/asset/steve120.png");
	steve.AddBox("rleg", rleg, "body");

	DxLibBox lleg;
	lleg.Create(50.0f, 150.0f, 50.0f);
	lleg.SetUVFront(0.0625f, 0.3125f, 0.0625f, 0.1875f);
	lleg.SetUVBack(0.1875f, 0.3125f, 0.0625f, 0.1875f);
	lleg.SetUVUp(0.0625f, 0.25f, 0.0625f, 0.0625f);
	lleg.SetUVBottom(0.125f, 0.25f, 0.0625f, 0.0625f);
	lleg.SetUVRight(0.125f, 0.3125f, 0.0625f, 0.1875);
	lleg.SetUVLeft(0.0f, 0.3125f, 0.0625f, 0.1875f);
	lleg.SetPos(-25.0, -80.0f, 0.0f);
	lleg.SetOffset(0.0f, -70.0f, 0.0f);
	lleg.SetTexture("Resource/asset/steve120.png");
	steve.AddBox("lleg", lleg, "body");


	//アニメーションの初期化
	AnimationClip walk;
	{
		{//rarm
			Animation anim;
			anim.AddKeyFrame(KeyFrame(  0, VGet(0.0f, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 15, VGet(DX_PI_F / 4, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 30, VGet(0.0f, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 45, VGet(-DX_PI_F / 4, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame(60, VGet(0.0f, 0.0f, 0.0f)));
			anim.SetTag("rarm");
			walk.AddAnimation(anim);
		}
		{//larm
			Animation anim;
			anim.AddKeyFrame(KeyFrame(  0, VGet(0.0f, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 15, VGet(-DX_PI_F / 4, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 30, VGet(0.0f, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 45, VGet(DX_PI_F / 4, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame(60, VGet(0.0f, 0.0f, 0.0f)));
			anim.SetTag("larm");
			walk.AddAnimation(anim);
		}
		{//rleg
			Animation anim;
			anim.AddKeyFrame(KeyFrame(  0, VGet(0.0f, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 15, VGet(-DX_PI_F / 4, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 30, VGet(0.0f, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 45, VGet(DX_PI_F / 4, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame(60, VGet(0.0f, 0.0f, 0.0f)));
			anim.SetTag("rleg");
			walk.AddAnimation(anim);
		}
		{//lleg
			Animation anim;
			anim.AddKeyFrame(KeyFrame(  0, VGet(0.0f, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 15, VGet(DX_PI_F / 4, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 30, VGet(0.0f, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 45, VGet(-DX_PI_F / 4, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame(60, VGet(0.0f, 0.0f, 0.0f)));
			anim.SetTag("lleg");
			walk.AddAnimation(anim);
		}
	}
	walk.SetEndFrame(60.0f);
	walk.SetLoop(true);
	m_animator.AddAnimationClip("walk", walk);


	AnimationClip idle;
	{
		{//rarm
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(0.0f, 0.0f, 0.0f)));
			anim.SetTag("rarm");
			idle.AddAnimation(anim);
		}
		{//larm
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(0.0f, 0.0f, 0.0f)));
			anim.SetTag("larm");
			idle.AddAnimation(anim);
		}
		{//rleg
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(0.0f, 0.0f, 0.0f)));
			anim.SetTag("rleg");
			idle.AddAnimation(anim);
		}
		{//lleg
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(0.0f, 0.0f, 0.0f)));
			anim.SetTag("lleg");
			idle.AddAnimation(anim);
		}
	}

	idle.SetEndFrame(120.0f);
	idle.SetLoop(true);
	m_animator.AddAnimationClip("idle", idle);

	AnimationClip breaking;
	{
		{//rarm
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(0.0f, 0.0f, 0.0f)));
			anim.SetTag("rarm");
			breaking.AddAnimation(anim);
		}
		{//larm
			Animation anim;
			anim.AddKeyFrame(KeyFrame(  0, VGet(DX_PI_F/2, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 30, VGet(DX_PI_F,   0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 60, VGet(DX_PI_F/2, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame( 90, VGet(DX_PI_F,   0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame(120, VGet(DX_PI_F/2, 0.0f, 0.0f)));
			anim.SetTag("larm");
			breaking.AddAnimation(anim);
		}
		{//rleg
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(0.0f, 0.0f, 0.0f)));

			anim.SetTag("rleg");
			breaking.AddAnimation(anim);
		}
		{//lleg
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(0.0f, 0.0f, 0.0f)));
			anim.SetTag("lleg");
			breaking.AddAnimation(anim);
		}
	}

	breaking.SetEndFrame(120.0f);
	breaking.SetLoop(true);
	m_animator.AddAnimationClip("breaking", breaking);


	AnimationClip camera;
	{
		{//rarm
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0,   VGet(DX_PI_F / 2, 5.0f, 0.0f)));
			anim.SetTag("rarm");
			camera.AddAnimation(anim);
		}
		{//larm
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(DX_PI_F / 1.5, -5.0f, 0.0f)));
			anim.SetTag("larm");
			camera.AddAnimation(anim);
		}
		{//rleg
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(0.0f, 0.0f, 0.0f)));

			anim.SetTag("rleg");
			camera.AddAnimation(anim);
		}
		{//lleg
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(0.0f, 0.0f, 0.0f)));
			anim.SetTag("lleg");
			camera.AddAnimation(anim);
		}
	}
	camera.SetEndFrame(60.0f);
	camera.SetLoop(true);
	m_animator.AddAnimationClip("camera", camera);


	AnimationClip camerawalk;
	{
		{//rarm
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(DX_PI_F / 2, 5.0f, 0.0f)));
			anim.SetTag("rarm");
			camerawalk.AddAnimation(anim);
		}
		{//larm
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(DX_PI_F / 1.5, -5.0f, 0.0f)));
			anim.SetTag("larm");
			camerawalk.AddAnimation(anim);
		}
		{//rleg
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(0.0f, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame(15, VGet(-DX_PI_F / 4, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame(30, VGet(0.0f, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame(45, VGet(DX_PI_F / 4, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame(60, VGet(0.0f, 0.0f, 0.0f)));
			anim.SetTag("rleg");
			camerawalk.AddAnimation(anim);
		}
		{//lleg
			Animation anim;
			anim.AddKeyFrame(KeyFrame(0, VGet(0.0f, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame(15, VGet(DX_PI_F / 4, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame(30, VGet(0.0f, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame(45, VGet(-DX_PI_F / 4, 0.0f, 0.0f)));
			anim.AddKeyFrame(KeyFrame(60, VGet(0.0f, 0.0f, 0.0f)));
			anim.SetTag("lleg");
			camerawalk.AddAnimation(anim);
		}
	}
	camerawalk.SetEndFrame(60.0f);
	camerawalk.SetLoop(true);
	m_animator.AddAnimationClip("camerawalk", camerawalk);

	m_animator.SetModel(&steve);

	//Master::resManager->LoadEffectFromFile("Resource/Effect/Light.efkefc", 10.0f);
}

void Player::Uninit()
{
	steve.Uninit();
	SAFE_DELETE(m_fsm);
}

int Player::Update()
{
	m_fsm->Update(this);

	steve.GetBox("body")->SetPos(m_pos.x, m_pos.y, m_pos.z);

	m_animator.Update();//アニメーションの更新

	{
		Camera* pCamera = Master::camera;

		VECTOR camDir = VSub(pCamera->GetPosition(),pCamera->GetLookAtPosition());// カメラの向いてる方向
		camDir = VNorm(camDir);

		// Z+ を正面として、向きを合わせる回転角
		float angleY = atan2f(camDir.x, camDir.z);

		if (Master::shot->GetGameTime() <= 90)
		{
			steve.GetBox("body")->SetRot(VGet(0.0f, angleY, 0.0f));
		}
	}

	steve.Update();

	Master::shot->Finder();

	return 0;
}

void Player::Draw()
{
	if (Master::shot->GetTurn() == false)
	{
		steve.Draw();
	}
}

void Player::SetFSM(FSM* fsm)
{
	assert(fsm);

	m_fsm = fsm;
}
