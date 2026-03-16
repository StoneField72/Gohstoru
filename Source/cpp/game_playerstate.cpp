
#include "game_playerstate.h"
#include "Master.h"
#include "game_player.h"
#include "Collision.h"
#include "DxLibUtil.h"

bool PlayerDir(GameObject* parent);


//アイドル状態
void PSIdle::OnEnter(GameObject* parent)
{
	//スピードを0に
	parent->SetSpeed(0.0f);
	//アニメーションをidleに変更
	parent->GetAnimator()->SetAnimation("idle");
}

void PSIdle::OnExit(GameObject* parent)
{
}

int PSIdle::Update(GameObject* parent)
{
	//ゲームが開始するまで動けなくする
	if (Master::shot->GetGameTime() > 90 || Master::shot->GetGameTime() == 0)
	{
		return PLAYER_STATE_IDLE;
	}

	bool isMove = PlayerDir(parent);

	// WASDのどれかが押されていれば移動状態へ遷移する
	if (isMove == true)
	{
		return PLAYER_STATE_WALK;// 戻り値として遷移先のSTATEを返す
	}

	//カメラを覗いているフラグが立っていたらカメラ状態に移行する
	if (Master::shot->GetTurn() == true)
	{
		return PLAYER_STATE_CAMERA;
	}

	//スキル（未実装）
	if (CheckHitKey(KEY_INPUT_Y))
	{
		return PLAYER_STATE_SKILL;
	}

	// キー入力を得る
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	return PLAYER_STATE_IDLE;
}


//歩き状態
void PSWalk::OnEnter(GameObject* parent)
{
	//アニメーションをwalkに変更
	parent->GetAnimator()->SetAnimation("walk");
	//SEを再生
	Master::sound->PlaySE(6); 
}

void PSWalk::OnExit(GameObject* parent)
{
	//SEを止める
	Master::sound->StopSE(6);
}

int PSWalk::Update(GameObject* parent)
{
	// 移動中はスピードが5.0になる
	parent->SetSpeed(13.0f);

	bool isMove = PlayerDir(parent);

	// 移動していない
	if (isMove == false)
	{
		return PLAYER_STATE_IDLE;// 待機状態に遷移する
	}

	VECTOR dir = VGet(0.0f, 0.0f, 0.0f);

	// プレイヤーの移動方向を正規化してセット
	if (VSize(dir) > 0.1f)
	{
		parent->SetSpeed(5.0f);
		parent->SetDir(VNorm(dir));
	}

	//カメラを覗いているフラグが立っていたらカメラ状態に移行する
	if (Master::shot->GetTurn() == true)
	{
		return PLAYER_STATE_CAMERA_WALK;
	}

	return PLAYER_STATE_WALK;
}

//カメラ状態
void PSCamera::OnEnter(GameObject* parent)
{
	//アニメーションをcameraに変更
	//parent->GetAnimator()->SetAnimation("camera");
}

void PSCamera::OnExit(GameObject* parent)
{
}

int PSCamera::Update(GameObject* parent)
{
	Master::shot->CameraRange(parent);

	// スピードが0.0になる
	parent->SetSpeed(0.0f);


	if (Master::shot->GetTurn() == false)
	{
		return PLAYER_STATE_IDLE;
	}

	bool isMove = PlayerDir(parent);

	// WASDのどれかが押されていればカメラ移動状態へ遷移する
	if (isMove == true)
	{
		return PLAYER_STATE_CAMERA_WALK;// 戻り値として遷移先のSTATEを返す
	}

	// キー入力を得る
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	return PLAYER_STATE_CAMERA;
}


//カメラ状態
void PSCameraWalk::OnEnter(GameObject* parent)
{
}

void PSCameraWalk::OnExit(GameObject* parent)
{
}

int PSCameraWalk::Update(GameObject* parent)
{
	Master::shot->CameraRange(parent);

	// 移動中はスピードが5.0になる
	parent->SetSpeed(5.0f);

	bool isMove = PlayerDir(parent);

	if (Master::shot->GetTurn() == false)
	{
		return PLAYER_STATE_WALK;
	}
	// 移動していない
	if (isMove == false)
	{
		return PLAYER_STATE_CAMERA;// 待機状態に遷移する
	}

	// キー入力を得る
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	VECTOR dir = VGet(0.0f, 0.0f, 0.0f);

	// プレイヤーの移動方向を正規化してセット
	if (VSize(dir) > 0.1f)
	{
		parent->SetSpeed(5.0f);
		parent->SetDir(VNorm(dir));
	}

	// 入力がなければIdle状態へ遷移する
	if (key == 0)
	{
		return PLAYER_STATE_IDLE;
	}

	return PLAYER_STATE_CAMERA_WALK;
}

void PSSkill::OnEnter(GameObject* parent)
{
	auto fighters = Master::objectManager->GetObjectsByTag("Enemy");
	for (auto enemy : fighters)
	{
		rand++;
	}

	Selected = GetRand(rand);
}

void PSSkill::OnExit(GameObject* parent)
{
	rand = 0;
	Selected = 0;
	Count = 0;
}

int PSSkill::Update(GameObject* parent)
{
	auto fighters = Master::objectManager->GetObjectsByTag("Enemy");
	for (auto enemy : fighters)
	{
		if (Count == Selected)
		{
			enemy->SetSelect(true);
		}
		else
		{
			enemy->SetSelect(false);
		}

		Count++;
	}

	// 入力がなければIdle状態へ遷移する
	return PLAYER_STATE_IDLE;
}

bool PlayerDir(GameObject* parent)
{
	VECTOR dir = VGet(0.0f, 0.0f, 0.0f);

	Camera* pCamera = Master::camera;
	// 押されたキーから移動するベクトルを作る
	
	VECTOR upMoveVec = VGet(0.0f, 0.0f, 0.0f);
	VECTOR leftMoveVec = VGet(0.0f, 0.0f, 0.0f);
	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);

	upMoveVec = VSub(pCamera->GetLookAtPosition(), pCamera->GetPosition());
	upMoveVec.y = 0.0f;
	upMoveVec = VNorm(upMoveVec);

	leftMoveVec = VCross(upMoveVec, VGet(0.0f, 1.0f, 0.0f));
	leftMoveVec = VNorm(leftMoveVec);

	if (CheckHitKey(KEY_INPUT_W))
	{
		dir.z = 1.0f;// 上方向に
		moveVec = VAdd(moveVec, upMoveVec);
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		dir.z = -1.0f;// 下方向に
		moveVec = VAdd(moveVec, VScale(upMoveVec, -1.0f));
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		dir.x = -1.0f;// 左方向に
		moveVec = VAdd(moveVec, leftMoveVec);
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		dir.x = 1.0f;// 右方向に
		moveVec = VAdd(moveVec, VScale(leftMoveVec, -1.0f));
	}

	//デバッグ用の上昇下降
	if (CheckHitKey(KEY_INPUT_UP))
	{
		//parent->SetPos(VAdd(parent->GetPos(), VGet(0.0f, 10.0f, 0.0f)));
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		//parent->SetPos(VSub(parent->GetPos(), VGet(0.0f, 10.0f, 0.0f)));
	}

	VECTOR nextPos = VAdd(parent->GetPos(), VScale(moveVec, parent->GetSpeed()));
	VECTOR playerSize = VGet(200.0f, 300.0f, 50.0f);

	// ステージオブジェクトとの衝突判定＆補正
	std::list<GameObject*> stage = Master::objectManager->GetObjectsByTag("stage");
	for (GameObject* obj : stage)
	{
		VECTOR objPos = obj->GetPos();
		VECTOR objSize = obj->GetScale();

		if (Collision::CheckCollisionAABB(nextPos, playerSize, objPos, objSize))
		{
			nextPos = Collision::ResolveAABB(nextPos, playerSize, objPos, objSize);

			// 最終的な位置に反映
			parent->SetPos(nextPos);
		}
	}
	std::list<GameObject*> tree = Master::objectManager->GetObjectsByTag("tree");
	for (GameObject* obj : tree)
	{
		VECTOR objPos = obj->GetPos();
		VECTOR objSize = VGet(200.0f, 300.0f, 200.0f);

		if (Collision::CheckCollisionAABB(nextPos, playerSize, objPos, objSize))
		{
			nextPos = Collision::ResolveAABB(nextPos, playerSize, objPos, objSize);

			// 最終的な位置に反映
			parent->SetPos(nextPos);
		}
	}

	// キー入力があったのでプレイヤーの向きを更新する
	if (VSize(dir) > 0.1f)
	{
		moveVec = VNorm(moveVec); // 斜めでも速度一定に
		// 斜めが速くなってしまうので正規化する
		dir = VNorm(dir);
		parent->SetDir(VGet(moveVec.x, 0.0f, moveVec.z));
		return true;
	}

	return false;
}