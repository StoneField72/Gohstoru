
#include "Shooting.h"
#include "Camera.h"
#include "Object.h"
#include "DxLibUtil.h"
#include "Collision.h"
#include "Stage_object.h"


Shot::Shot()
{
	for (int i = 0; i < 10; i++)
	{
		CameraCollisionCenter[i] = VGet(0.0f, 0.0f, 0.0f);
	}

	for (int i = 0; i < Ball_Count; i++)
	{
		BallPos[i] = VGet(0.0f, 0.0f, 0.0f);
		hitFlag[i] = false;
	}

	score = 0;
	TotalScore = 0;

	GraphHandle1 = -1;
	GraphHandle2 = -1;
	GraphHandle3 = -1;

	for (int i = 0; i < 10; i++)
	{
		NumburGraphHandle[i] = -1;
	}

	distance = 0.0f;
	shotCore = VGet(0.0f, 0.0f, 0.0f);

	SideBallCount[0] = 1;//1
	SideBallCount[1] = 3;//2
	SideBallCount[2] = 5;
	SideBallCount[3] = 7;
	SideBallCount[4] = 9;
	SideBallCount[5] = 11;
	SideBallCount[6] = 13;
	SideBallCount[7] = 15;
	SideBallCount[8] = 17;
	SideBallCount[9] = 19;

	camDir = VGet(0.0f, 0.0f, 0.0f);
	front = VNorm(VGet(0.0f, 0.0f, 0.0f));
	up = VNorm(VGet(0.0f, 1.0f, 0.0f));
	right = VNorm(VGet(0.0f, 0.0f, 0.0f));
	angleY = 0.0f;

	filmCount = 10;
	Shuttercooltime = 0;
	ShutterCoolDown = false;
	enemyCount = 0;
	Bonus = 0;
	GameTime = 0;

	Turn = false;
	TurnWait = 0;

	for (int i = 0; i < filmCount; i++)
	{
		film[i] = 0;
	}

	UIHandle1 = -1;
	UIHandle2 = -1;
	UIHandle3 = -1;
	UIHandle4 = -1;
	UIHandle5 = -1;
	FontHandle1 = -1;
}

Shot::~Shot()
{
	DeleteGraph(GraphHandle1);
	DeleteGraph(GraphHandle2);
	DeleteGraph(GraphHandle3);
	DeleteGraph(UIHandle1);
	DeleteGraph(UIHandle2);
	DeleteGraph(UIHandle3);
	DeleteGraph(UIHandle4);
	DeleteGraph(UIHandle5);
	DeleteFontToHandle(FontHandle1);

	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(NumburGraphHandle[i]);
	}
}

void Shot::Initialize()
{
	GraphHandle1 = LoadGraph("Resource/asset/Finder.png");
	//GraphHandle1 = LoadGraph("asset/TitleFinder.png");
	GraphHandle2 = LoadGraph("Resource/asset/Camera.png");
	GraphHandle3 = LoadGraph("Resource/UI/Photo.png");
	UIHandle1 = LoadGraph("Resource/UI/Time.png");
	UIHandle2 = LoadGraph("Resource/UI/No.png");
	UIHandle3 = LoadGraph("Resource/UI/Sa.png");
	UIHandle4 = LoadGraph("Resource/UI/Ghost.png");
	UIHandle5 = LoadGraph("Resource/UI/残り枚数.png");

	FontHandle1 = CreateFontToHandle("HGS創英角ｺﾞｼｯｸUB", 30, 6);

	for (int i = 0; i < 10; i++)
	{
		CameraCollisionCenter[i] = VGet(0.0f, 0.0f, 0.0f);
	}

	for (int i = 0; i < Ball_Count; i++)
	{
		BallPos[i] = VGet(0.0f, 0.0f, 0.0f);
		hitFlag[i] = false;
	}

	score = 0;
	TotalScore = 0;

	distance = 0.0f;
	shotCore = VGet(0.0f, 0.0f, 0.0f);

	SideBallCount[0] = 1;//1
	SideBallCount[1] = 3;//2
	SideBallCount[2] = 5;
	SideBallCount[3] = 7;
	SideBallCount[4] = 9;
	SideBallCount[5] = 11;
	SideBallCount[6] = 13;
	SideBallCount[7] = 15;
	SideBallCount[8] = 17;
	SideBallCount[9] = 19;

	camDir = VGet(0.0f, 0.0f, 0.0f);
	front = VNorm(VGet(0.0f, 0.0f, 0.0f));
	up = VNorm(VGet(0.0f, 1.0f, 0.0f));
	right = VNorm(VGet(0.0f, 0.0f, 0.0f));
	angleY = 0.0f;

	filmCount = 10;
	Shuttercooltime = 0;
	ShutterCoolDown = false;
	enemyCount = 0;
	Bonus = 0;
	GameTime = 0;

	for (int i = 0; i < filmCount; i++)
	{
		film[i] = 0;
	}

	// 数字グラフィックを分割読みこみ
// 分割数は全部で10こ、１列当たり10個の分割数でそれが１行だけあるので
// 以下のような記述になります。
	LoadDivGraph("Resource/UI/Num.png", 10, 10, 1, WIDTH, HEIGHT, NumburGraphHandle);

	Turn = false;
	TurnWait = 0;
}

void Shot::Update()
{
	
}

//UIの表示(写真を撮る1フレームだけ表示しない)
void Shot::UIRender()
{
	Cooltime();
	FinderScreen();

	DrawExtendGraph(100, 55, 210, 75, UIHandle5, TRUE);//残り枚数のUI画像
	DrawExtendGraph(10, 10, 90, 80, GraphHandle3, TRUE);
	
	if (filmCount >= 10)
	{
		NumDraw(filmCount, 155, 35);
	}
	else
	{
		NumDraw(filmCount, 145, 35);
	}
										
	//DrawFormatString(1100, 30, GetColor(255, 255, 255), "[M]上空カメラ ON");
	//DrawFormatString(1100, 50, GetColor(255, 255, 255), "[N]上空カメラOFF");

	if (GameTime <= 90)
	{
		//制限時間
		DrawExtendGraph(SCREEN_SIZE_X / 2 - 150, 30, SCREEN_SIZE_X / 2 + 90, 80, UIHandle1, TRUE);
		// 制限時間をグラフィック数字で表示
		NumDraw(GameTime, SCREEN_SIZE_X / 2 + 20, 35);

		//DrawBox(415, 25, 420 + 455, 65, GetColor(0, 0, 0), true);
		//DrawBox(420, 30, 420 + (GameTime * 5), 60, GetColor(100, 100, 255), true);
		//DrawExtendGraph(400 + (GameTime * 5), 10, 460 + (GameTime * 5), 80, UIHandle4, TRUE);
	

		//覗いていないとき
		if (Turn == false)
		{
			DrawExtendGraph(920, 640, 1250, 700, UIHandle2, TRUE);
		}
		else
		{
			DrawExtendGraph(930, 540, 1180, 600, UIHandle3, TRUE);
		}
	}
	else
	{
		switch (GameTime)
		{
		case 91:

			break;
		case 92:
			NumDraw(1, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 3);
			break;
		case 93:
			NumDraw(2, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 3);
			break;
		case 94:
			NumDraw(3, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 3);
			break;

		default:
			break;
		}
	}
}

//当たり判定の位置の更新
void Shot::SpherePos_Init()
{
	//1
	BallPos[0] = VAdd(CameraCollisionCenter[0], VScale(right, 0.0f));
	//2
	BallPos[1] = VAdd(CameraCollisionCenter[1], VScale(right, -400.0f));
	BallPos[2] = VAdd(CameraCollisionCenter[1], VScale(right, 400.0f));
	//3
	BallPos[3] = VAdd(CameraCollisionCenter[2], VScale(right, -800.0f));
	BallPos[4] = VAdd(CameraCollisionCenter[2], VScale(right, 0.0f));//
	BallPos[5] = VAdd(CameraCollisionCenter[2], VScale(right, 800.0f));
	//4
	BallPos[6] = VAdd(CameraCollisionCenter[3], VScale(right, -1200.0f));
	BallPos[7] = VAdd(CameraCollisionCenter[3], VScale(right, -400.0f));
	BallPos[8] = VAdd(CameraCollisionCenter[3], VScale(right, 400.0f));
	BallPos[9] = VAdd(CameraCollisionCenter[3], VScale(right, 1200.0f));
	//5
	BallPos[10] = VAdd(CameraCollisionCenter[4], VScale(right, -1600.0f));
	BallPos[11] = VAdd(CameraCollisionCenter[4], VScale(right, -800.0f));
	BallPos[12] = VAdd(CameraCollisionCenter[4], VScale(right, 0.0f));
	BallPos[13] = VAdd(CameraCollisionCenter[4], VScale(right, 800.0f));
	BallPos[14] = VAdd(CameraCollisionCenter[4], VScale(right, 1600.0f));
	//6
	BallPos[15] = VAdd(CameraCollisionCenter[5], VScale(right, -2000.0f));
	BallPos[16] = VAdd(CameraCollisionCenter[5], VScale(right, -1200.0f));
	BallPos[17] = VAdd(CameraCollisionCenter[5], VScale(right, -400.0f));
	BallPos[18] = VAdd(CameraCollisionCenter[5], VScale(right, 400.0f));
	BallPos[19] = VAdd(CameraCollisionCenter[5], VScale(right, 1200.0f));
	BallPos[20] = VAdd(CameraCollisionCenter[5], VScale(right, 2000.0f));
	//7
	BallPos[21] = VAdd(CameraCollisionCenter[6], VScale(right, -2400.0f));
	BallPos[22] = VAdd(CameraCollisionCenter[6], VScale(right, -1600.0f));
	BallPos[23] = VAdd(CameraCollisionCenter[6], VScale(right, -800.0f));
	BallPos[24] = VAdd(CameraCollisionCenter[6], VScale(right, 0.0f));
	BallPos[25] = VAdd(CameraCollisionCenter[6], VScale(right, 800.0f));
	BallPos[26] = VAdd(CameraCollisionCenter[6], VScale(right, 1600.0f));
	BallPos[27] = VAdd(CameraCollisionCenter[6], VScale(right, 2400.0f));
	//8
	BallPos[28] = VAdd(CameraCollisionCenter[7], VScale(right, -2800.0f));
	BallPos[29] = VAdd(CameraCollisionCenter[7], VScale(right, -2000.0f));
	BallPos[30] = VAdd(CameraCollisionCenter[7], VScale(right, -1200.0f));
	BallPos[31] = VAdd(CameraCollisionCenter[7], VScale(right, -400.0f));
	BallPos[32] = VAdd(CameraCollisionCenter[7], VScale(right, 400.0f));
	BallPos[33] = VAdd(CameraCollisionCenter[7], VScale(right, 1200.0f));
	BallPos[34] = VAdd(CameraCollisionCenter[7], VScale(right, 2000.0f));
	BallPos[35] = VAdd(CameraCollisionCenter[7], VScale(right, 2800.0f));
	//9
	BallPos[36] = VAdd(CameraCollisionCenter[8], VScale(right, -3200.0f));
	BallPos[37] = VAdd(CameraCollisionCenter[8], VScale(right, -2400.0f));
	BallPos[38] = VAdd(CameraCollisionCenter[8], VScale(right, -1600.0f));
	BallPos[39] = VAdd(CameraCollisionCenter[8], VScale(right, -800.0f));
	BallPos[40] = VAdd(CameraCollisionCenter[8], VScale(right, 0.0f));
	BallPos[41] = VAdd(CameraCollisionCenter[8], VScale(right, 800.0f));
	BallPos[42] = VAdd(CameraCollisionCenter[8], VScale(right, 1600.0f));
	BallPos[43] = VAdd(CameraCollisionCenter[8], VScale(right, 2400.0f));
	BallPos[44] = VAdd(CameraCollisionCenter[8], VScale(right, 3200.0f));
	//10
	BallPos[45] = VAdd(CameraCollisionCenter[9], VScale(right, -3600.0f));
	BallPos[46] = VAdd(CameraCollisionCenter[9], VScale(right, -2800.0f));
	BallPos[47] = VAdd(CameraCollisionCenter[9], VScale(right, -2000.0f));
	BallPos[48] = VAdd(CameraCollisionCenter[9], VScale(right, -1200.0f));
	BallPos[49] = VAdd(CameraCollisionCenter[9], VScale(right, -400.0f));
	BallPos[50] = VAdd(CameraCollisionCenter[9], VScale(right, 400.0f));
	BallPos[51] = VAdd(CameraCollisionCenter[9], VScale(right, 1200.0f));
	BallPos[52] = VAdd(CameraCollisionCenter[9], VScale(right, 2000.0f));
	BallPos[53] = VAdd(CameraCollisionCenter[9], VScale(right, 2800.0f));
	BallPos[54] = VAdd(CameraCollisionCenter[9], VScale(right, 3600.0f));
}


//写る範囲の描画
void Shot::CameraRange(GameObject* parent)
{
	SpherePos_Init();

	shotCore = VAdd(BallPos[0], parent->GetPos());

	Camera* pCamera = Master::camera;
	// 押されたキーから移動するベクトルを作る

	camDir = VNorm(VSub(pCamera->GetLookAtPosition(), pCamera->GetPosition()));

	// Z+ を正面として、向きを合わせる回転角
	angleY = atan2(camDir.x, camDir.z);

	for (int i = 0; i < 10; i++)
	{
		CameraCollisionCenter[i] = VGet(0.0f, 0.0f, 0.0f);
		CameraCollisionCenter[i].x = sinf(angleY);
		CameraCollisionCenter[i].z = cosf(angleY);

		CameraCollisionCenter[i].x *= (i * 400.0f) + 600.0f;
		CameraCollisionCenter[i].z *= (i * 400.0f) + 600.0f;
	}

	front = VSub(CameraCollisionCenter[0], CameraCollisionCenter[1]);
	front = VNorm(front);
	right = VCross(front, up);
	right = VNorm(right);

	CameraCheck(parent);


	VECTOR diff = VSub(pCamera->GetLookAtPosition(), pCamera->GetPosition());
	float dist = VSize(diff);

	if (dist < 0.001f)
	{
		camDir = VGet(0.0f, 0.0f, 1.0f);  // デフォルト前方向
	}
	else 
	{
		camDir = VNorm(diff);
	}
}


//撮影時の獲得ポイント計算
void Shot::Shutter()
{
	CameraRange(GetPlayerObject());

	std::list<GameObject*> enemys = Master::objectManager->GetObjectsByTag("Enemy");
	// プレイヤーのゲームオブジェクトを取得
	GameObject* player = GetPlayerObject();
	VECTOR playerPos = player->GetPos();

	score = 0;
	Bonus = 0;
	enemyCount = 0;

	for (GameObject* enemy : enemys)
	{
		//敵が見えているなら
		if (!enemy->GetInvisible() && enemy->GetInThePic())
		{
			distance = Collision::GetDistance(shotCore, enemy->GetPos());
			enemy->SetScore(1000 - (distance / 10));

			score += enemy->GetScore();

			if (enemy->GetScore() >= 800)
			{
				AddScore(enemy->GetScore(), 1);
			}
			else if(enemy->GetScore() < 800 && enemy->GetScore() >= 500)
			{
				AddScore(enemy->GetScore(), 2);
			}
			else if (enemy->GetScore() < 500)
			{
				AddScore(enemy->GetScore(), 3);
			}

			//ボーナス（ポイント追加計算）
			//こちらを向いていたら
			VECTOR targetPos = enemy->GetPos();     // 被写体の位置
			VECTOR targetDir = enemy->GetDir();     // 被写体の向き（Z軸方向）
			// 被写体からカメラへのベクトル
			VECTOR toCamera = VSub(playerPos, targetPos);
			toCamera = VNorm(toCamera);             // 正規化
			// 向きの一致度（内積）
			float dot = VDot(targetDir, toCamera);

			// dotが1に近いほどカメラを向いている
			if (dot > 0.8f)
			{
				AddLog("こちらを向いている");
				AddScore((enemy->GetScore() / 2), 4);
				score += (enemy->GetScore() / 2);
			}

			enemyCount++;
		}

		enemy->SetScore(0);
	}

	//ボーナス（ポイント追加計算）
	//2体以上写っていたら
	if (enemyCount >= 2)
	{
		Bonus = score / 10;

		for (int i = 0; i < enemyCount - 1; i++)
		{
			score += Bonus;
			AddLog("複数体写っている");
			AddScore(Bonus, 4);
		}

		Bonus = 0;
		enemyCount = 0;
	}

	if (score == 0)
	{
		AddLog("なにも写っていない…");
	}

	AddScore(score, 0);
	//撮影した写真のスコアを保存する
	film[10 - filmCount] = score;

	//残りの撮影可能回数を１減らす
	filmCount -= 1;
	if (filmCount <= 0)
	{
		for (int i = 0; i < 10; i++)
		{
			TotalScore += film[i];
		}

		filmCount = 0;
	}
	if (filmCount == 5)
	{
		AddLog("写真残り５枚");
	}

	//撮影のクールタイムに入る
	ShutterCoolDown = true;
	Shuttercooltime = 90;
}


//カメラに写っているかの判定
void Shot::CameraCheck(GameObject* parent)
{
	std::list<GameObject*> enemys = Master::objectManager->GetObjectsByTag("Enemy");
	std::list<GameObject*> trees = Master::objectManager->GetObjectsByTag("tree");

	//球の当たり判定
	for (int i = 0; i < Ball_Count; i++)
	{
		hitFlag[i] = false;

		for (GameObject* enemy : enemys)
		{
			//敵が見えているなら
			if (!enemy->GetInvisible())
			{
				//球と敵の判定
				hitFlag[i] |= Collision::CheckSphereToSphere
				(
					VAdd(BallPos[i], parent->GetPos()),
					400.0f,
					enemy->GetPos(),
					100.0f
				);

				if (hitFlag[i] == true)
				{
					enemy->SetInThePic(true);

					hitFlag[i] = false;

					break;
				}
			}
		}
	}
}

//覗き込む
void Shot::Finder()
{
	if (TurnWait > 0)
	{
		TurnWait--;
	}

	if (GetMouseInput() & MOUSE_INPUT_RIGHT && TurnWait == 0 && GameTime <= 90)
	{
		if (Turn == true)
		{
			Turn = false;
		}
		else
		{
			Turn = true;
		}

		TurnWait = 25;
	}
}

//覗き込む演出
void Shot::FinderScreen()
{
	if (Turn == true)
	{
		if (TurnWait > 15)
		{
			DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		}
		else if(TurnWait <= 15)
		{
			DrawExtendGraph(0, 0, 1280, 720, GraphHandle1, TRUE);
		}
	}
	else
	{
		if (TurnWait > 15)
		{
			DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		}
	}
}

void Shot::Cooltime()
{
	if (ShutterCoolDown)
	{
		Shuttercooltime -= 2;

		if (Shuttercooltime <= 0)
		{
			Shuttercooltime = 0;
			ShutterCoolDown = false;
		}
	}
}


// 数値をグラフィック表示する関数
void Shot::NumDraw(int Num, int x, int y)
{
	int i, BeamWidth;

	// Numが十進数で何桁になるか調べる
	BeamWidth = 0;
	for (i = 10; Num >= i; i *= 10)
	{
		BeamWidth++;
	}

	for (i = 0; i <= BeamWidth; i++)
	{
		// 数字の描画(透過色あり)
		// NumHandle 配列には要素番号０には『０』のグラフィック識別番号が
		// １には『１』のグラフィック識別番号が入っているので、
		// DrawGraph( 0 , 0 , NumHandle[ 0 ] , TRUE ) ; とすれば
		// 『０』のグラフィックを描画できることをお忘れなく
		DrawGraph(x, y, NumburGraphHandle[Num % 10], TRUE);

		// 描画Ｘ座標を移動
		x -= (WIDTH - 8);

		// １番下の桁が描画し終わったので一桁下げる
		Num /= 10;
	}
}