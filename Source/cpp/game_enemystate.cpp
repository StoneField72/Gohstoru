
#include "game_enemystate.h"
#include "Master.h"
#include "game_enemy.h"
#include "DxLibUtil.h"
#include "Shooting.h"
#include "Collision.h"

void PEDrawLine(GameObject* parent);

//アイドル状態
void ESIdle::OnEnter(GameObject* parent)
{
	parent->SetSpeed(0.0f);

	//アニメーションをidleに変更
	parent->GetAnimator()->SetAnimation("idle");

	//待機用変数を初期化する
	IdleCount = 0;
	IdleType = 0;
}

void ESIdle::OnExit(GameObject* parent)
{
}

int ESIdle::Update(GameObject* parent)
{
	parent->SetInvisible(false);

	//ゲームが開始するまで動かない
	if(Master::shot->GetGameTime() > 90 || Master::shot->GetGameTime() == 0)
	{
		return ENEMY_STATE_IDLE;
	}

	//待機カウントを増やす
	IdleCount++;

	//待機カウントが120以上になったら
	if (IdleCount >= 120)
	{
		//カウントを0に戻す
		IdleCount = 0;

		//状態を抽選する
		IdleType = GetRand(4);
	}

	//プレイヤーのゲームオブジェクトを取得
	GameObject* player = GetPlayerObject();

	// プレイヤーに向かう差分ベクトルを作成する
	VECTOR vDist = VSub(parent->GetPos(), player->GetPos());

	// 差分ベクトルの大きさ（長さ）を取得
	float distance = VSize(vDist);// 差分ベクトルの大きさを調べる

	// プレイヤーとの距離1000で逃走開始
	if (distance < 1000.0f)
	{
		//驚き状態に以降
		return ENEMY_STATE_SURPRISED;
	}

	//〇m以上離れていたら不可視
	if (distance > 2000.0f)
	{
		parent->SetInvisible(true);
	}

	//待機タイプがだったら徘徊状態に移行する
	if (IdleType == 4)
	{
		return ENEMY_STATE_WANDERING;
	}
	else//それ以外なら待機継続
	{
		return ENEMY_STATE_IDLE;
	}
}


//////
//逃走クラス
/////
void ESRun::OnEnter(GameObject* parent)
{
	//スピードを15に設定
	parent->SetSpeed(15.0f);

	//アニメーションをwalkに変更
	parent->GetAnimator()->SetAnimation("walk");
}

void ESRun::OnExit(GameObject* parent)
{
}

int ESRun::Update(GameObject* parent)
{
	parent->SetInvisible(false);

	// プレイヤーのゲームオブジェクトを取得
	GameObject* player = GetPlayerObject();

    // プレイヤーから離れる差分ベクトルを作成する
    VECTOR vDist = VSub(parent->GetPos(), player->GetPos());
    // 差分ベクトルの大きさ（長さ）を取得
    float distance = VSize(vDist);// 差分ベクトルの大きさを調べる

    parent->SetDir(VNorm(vDist));   

	// プレイヤーとの距離1000で
	if (distance > 2000.0f)
	{
		parent->SetInvisible(true);
	}

    // プレイヤーとの距離2000で逃走終了
    if (distance > 3500.0f)
    {
		parent->SetSelect(false);
        return ENEMY_STATE_IDLE;// 待機状態へ遷移する
    }

	return ENEMY_STATE_RUN;
}


void ESSurprised::OnEnter(GameObject* parent)
{
	//スピードを0にする
	parent->SetSpeed(0.0f);

	//カウントを初期化
	Count = 0;

	//アニメーションをwalkに変更
	parent->GetAnimator()->SetAnimation("surprised");

	//遷移時のEnemyの座標と向きを保存
	CurrentPos = parent->GetPos();
	CurrentDir = parent->GetDir();

	//画像を読み込む(びっくりマーク)
	GraphHandle = LoadGraph("Resource/asset/Bikkuri.png");

	//ログを表示
	AddLog("おばけを驚かしてしまった...");

	//SEを再生
	Master::sound->PlaySE(3);
}

void ESSurprised::OnExit(GameObject* parent)
{
	//遷移してきた時の座標と向きに戻す
	parent->SetPos(CurrentPos);
	parent->SetDir(CurrentDir);

	//画像ハンドルを削除
	DeleteGraph(GraphHandle);
}

int ESSurprised::Update(GameObject* parent)
{
	parent->SetInvisible(false);

	//カウントを増やす
	Count++;

	//飛び跳ねている風の演出
	if (Count <= 10)//カウントが10以下なら
	{
		//Enemyをジャンプさせる
		parent->SetPos(VAdd(parent->GetPos(), VGet(0.0f, ((float)Count), 0.0f)));
	}
	else if (Count > 10 && Count <= 18)//カウントが11以上18以下なら
	{
		//Enemyを下げる
		parent->SetPos(VSub(parent->GetPos(), VGet(0.0f, ((float)Count), 0.0f)));
	}

	// プレイヤーのゲームオブジェクトを取得
	GameObject* player = GetPlayerObject();
	// プレイヤーに向かう差分ベクトルを作成する
	VECTOR vDist = VSub(player->GetPos(), parent->GetPos());
	
	//びっくりマークを表示
	DrawBillboard3D(VAdd(parent->GetPos(), VGet(0.0f, 280.0f, 0.0f)), 0.5f, 0.5f, 30.0f, 0.0f, GraphHandle, TRUE);

	// 差分ベクトルの大きさ（長さ）を取得
	float distance = VSize(vDist);// 差分ベクトルの大きさを調べる

	parent->SetDir(VNorm(vDist));

	//カウントが30以上になったら
	if (Count >= 30)
	{
		//カウントを0に
		Count = 0;

		//逃走状態に遷移する
		return ENEMY_STATE_RUN;
	}

	return ENEMY_STATE_SURPRISED;
}


//////
//徘徊クラス
//////
void ESWandering::OnEnter(GameObject* parent)
{
	//スピードを7に設定する
	parent->SetSpeed(5.0f);

	//アニメーションをwalkに変更
	parent->GetAnimator()->SetAnimation("walk");

	//移動する場所を決める
	nextPos = VGet((GetRand(10000) - 5000), 0.0f, (GetRand(10000) - 5000));
}

void ESWandering::OnExit(GameObject* parent)
{
}

int ESWandering::Update(GameObject* parent)
{
	parent->SetInvisible(false);

	//プレイヤーのゲームオブジェクトを取得
	GameObject* player = GetPlayerObject();
	// プレイヤーに向かう差分ベクトルを作成する
	VECTOR vDist = VSub(parent->GetPos(), player->GetPos());
	// 差分ベクトルの大きさ（長さ）を取得
	float distance = VSize(vDist);// 差分ベクトルの大きさを調べる
	// プレイヤーとの距離1000で逃走開始
	if (distance < 1000.0f)
	{
		//驚き状態に以降
		return ENEMY_STATE_SURPRISED;
	}

	// プレイヤーとの距離1000で
	if (distance > 2000.0f)
	{
		parent->SetInvisible(true);
	}

	// プレイヤーに向かう差分ベクトルを作成する
	VECTOR nextvDist = VSub(nextPos, parent->GetPos());
	// 差分ベクトルの大きさ（長さ）を取得
	float  nextdistance = VSize(nextvDist);// 差分ベクトルの大きさを調べる

	//移動
	parent->SetDir(VNorm(nextvDist));

	VECTOR Size = VGet(200.0f, 300.0f, 100.0);
	auto stage = Master::objectManager->GetObjectsByTag("stage");
	for (auto fighter : stage)
	{
		for (auto obj : Master::objectManager->GetObjectList())
		{
			if (obj->GetTag() == "stage")
			{
				//オブジェクトとプレイヤーの当たり判定
				if (Collision::CheckCollisionAABB(nextPos, Size, obj->GetPos(), obj->GetScale()))
				{
					return ENEMY_STATE_IDLE;
				}
			}
		}
	}

	// 目的地点との距離100で移動終了
	if (nextdistance < 100.0f)
	{
		//待機状態に以降
		return ENEMY_STATE_IDLE;
	}

	return ENEMY_STATE_WANDERING;
}