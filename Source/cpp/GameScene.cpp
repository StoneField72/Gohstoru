#include "GameScene.h"
#include "ResultScene.h"
#include <DxLib.h>
#include "Master.h"
#include "DxLibUtil.h"
#include "game_player.h"
#include "game_enemy.h"
#include "Stage_object.h"
#include "FSMFactory.h"
#include "Collision.h"
#include "game_field.h"
#include "ItemManager.h"


GameScene::GameScene()
{
	//画像ハンドル
	UIHandle1 = -1;
	UIHandle2 = -1;
	FinishHandle = -1;
	ResultHandle = -1;
	OpenHandle = - 1;

	Shoot = false;

	taskUImoveX = 0.0f;
	nowTime = 0;
	remainingTime = 0;
	startTime = 0;
	timeLimit = 0;
	ItemCount = 0;
	ItemEffect = 0;

	//シェーダー用
	g_Offscreen = -1;
	g_PostPixelShader = -1;
}

GameScene::~GameScene()
{
	//ピクセルシェーダーの削除
	DeleteShader(g_PixelShader);

	//画像ハンドルの削除
	DeleteGraph(UIHandle1);
	DeleteGraph(UIHandle2);
	DeleteGraph(FinishHandle);
	DeleteGraph(ResultHandle);
	DeleteGraph(OpenHandle);

	// シーン内のオブジェクトを削除
	for (auto obj : m_objects)
		SAFE_DELETE(obj);

	m_objects.clear(); // オブジェクトのクリア

	Master::resManager->Uninitialize();

	ClearAllLogs();
}

void GameScene::Initialize()
{
	//1P側プレイヤーのインスタンスを作成する
	{
		Player* obj;
		obj = new Player();
		obj->Init();
		obj->SetLayer(1);
		obj->SetTag("player");
		obj->SetPos(VGet(0.0f, 0.0f, 4500.0f));
		obj->SetDir(VGet(1.0f, 0.0f, 0.0f)); // 1P側の初期方向を設定
		obj->SetSpeed(0.0f);
		obj->SetTeam(1);
		obj->SetActive(TRUE); //初期状態でアクティブ
		obj->SetFSM(FSMFactory::Create("Player", obj));
		m_objects.push_back(obj);
		Master::camera->Initialize(obj);
	}

	///木のモデル///////////////////////////////
	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Tree.mv1",
			"Resource/asset/diffuse.png",
			VGet(-2000.0f, -200.0f, -1000.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("tree");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Tree.mv1",
			"Resource/asset/diffuse.png",
			VGet(1500.0f, -200.0f, 1500.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("tree");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Tree.mv1",
			"Resource/asset/diffuse.png",
			VGet(-1500.0f, -200.0f, 3400.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("tree");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Tree.mv1",
			"Resource/asset/diffuse.png",
			VGet(2000.0f, -200.0f, -2000.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("tree");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Tree.mv1",
			"Resource/asset/diffuse.png",
			VGet(4500.0f, -200.0f, -800.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("tree");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Tree.mv1",
			"Resource/asset/diffuse.png",
			VGet(-3800.0f, -200.0f, 2700.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("tree");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Tree.mv1",
			"Resource/asset/diffuse.png",
			VGet(3800.0f, -200.0f, -3300.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("tree");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Tree.mv1",
			"Resource/asset/diffuse.png",
			VGet(805.0f, -200.0f, -3830.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("tree");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Tree.mv1",
			"Resource/asset/diffuse.png",
			VGet(-4000.0f, -200.0f, -3230.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("tree");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Tree.mv1",
			"Resource/asset/diffuse.png",
			VGet(-2300.0f, -200.0f, -2330.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("tree");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Tree2.mv1",
			"Resource/asset/diffuse2.png",
			VGet(4000.0f, -200.0f, 2500.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("tree");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Tree2.mv1",
			"Resource/asset/diffuse2.png",
			VGet(-3300.0f, -200.0f, -500.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("tree");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Tree2.mv1",
			"Resource/asset/diffuse2.png",
			VGet(-500.0f, -200.0f, -2500.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("tree");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}
	///////////////////////////////////////////////////

	///門のモデル//////////////////////////////////////
	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Gate/Gate.mv1",
			"Resource/asset/Gate/BLD_Structures2_A.jpg",
			"Resource/asset/Gate/BLD_Structures2_N.jpg",
			VGet(0.0f, -200.0f, 5000.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("stage");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	
	{//門の扉１
		StageObject* obj;
		obj = new StageObject("Resource/asset/Gate/Gate_Door.mv1",
			"Resource/asset/Gate/BLD_Structures2_A.jpg",
			"Resource/asset/Gate/BLD_Structures2_N.jpg",
			VGet(-280.0f, -200.0f, 5000.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, 0.0f, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("stage");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}
	{//門の扉２
		StageObject* obj;
		obj = new StageObject("Resource/asset/Gate/Gate_Door.mv1",
			"Resource/asset/Gate/BLD_Structures2_A.jpg",
			"Resource/asset/Gate/BLD_Structures2_N.jpg",
			VGet(280.0f, -200.0f, 5000.0f),
			VGet(1.0f, 1.0f, 1.0f),
			VGet(0.0f, DX_PI_F, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("stage");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	for (int i = 0; i < 6; i++)
	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Gate/Fence.mv1",
			"Resource/asset/Gate/BLD_Structures2_A.jpg",
			"Resource/asset/Gate/BLD_Structures2_N.jpg",
			VGet(-(500 + (i * 760)), -200.0f, 5000.0f),
			VGet(1.2f, 1.2f, 1.2f),
			VGet(0.0f, DX_PI_F, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("stage");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}
	for (int i = 0; i < 6; i++)
	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Gate/Fence.mv1",
			"Resource/asset/Gate/BLD_Structures2_A.jpg",
			"Resource/asset/Gate/BLD_Structures2_N.jpg",
			VGet((4240 - (i * 760)), -200.0f, 5000.0f),
			VGet(1.2f, 1.2f, 1.2f),
			VGet(0.0f, DX_PI_F + DX_PI_F, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("stage");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	for (int i = 0; i < 13; i++)
	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Gate/Fence.mv1",
			"Resource/asset/Gate/BLD_Structures2_A.jpg",
			"Resource/asset/Gate/BLD_Structures2_N.jpg",
			VGet((4280 - (i * 760)), -200.0f, -4850.0f),
			VGet(1.2f, 1.2f, 1.2f),
			VGet(0.0f, DX_PI_F + DX_PI_F, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("stage");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	for (int i = 0; i < 13; i++)
	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Gate/Fence.mv1",
			"Resource/asset/Gate/BLD_Structures2_A.jpg",
			"Resource/asset/Gate/BLD_Structures2_N.jpg",
			VGet(5000.0f, -200.0f, (5000 - (i * 760))),
			VGet(1.2f, 1.2f, 1.2f),
			VGet(0.0f, DX_PI_F / 2, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("stage");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	for (int i = 0; i < 13; i++)
	{
		StageObject* obj;
		obj = new StageObject("Resource/asset/Gate/Fence.mv1",
			"Resource/asset/Gate/BLD_Structures2_A.jpg",
			"Resource/asset/Gate/BLD_Structures2_N.jpg",
			VGet(-4800.0f, -200.0f, (5000 - (i * 760))),
			VGet(1.2f, 1.2f, 1.2f),
			VGet(0.0f, DX_PI_F / 2, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("stage");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}
	////////////////////////////////////////////

	{//車
		StageObject* obj;
		obj = new StageObject("Resource/asset/Car.mv1",
			"Resource/asset/PROP_Car1_A.jpg",
			"Resource/asset/PROP_Car1_N.jpg",
			VGet(1000.0f, -200.0f, 3000.0f),
			VGet(2.0f, 2.0f, 2.0f),
			VGet(0.0f, DX_PI_F, 0.0f)
		);
		obj->Init();
		obj->SetLayer(3);
		obj->SetTag("stage");
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	//フィールドのインスタンスを作成する
	{
		Field* obj;
		obj = new Field();
		obj->Init();
		obj->SetLayer(0);
		obj->SetTag("field");
		obj->SetPos(VGet(0.0f, -220.0f, 0.0f));
		obj->SetDir(VGet(1.0f, 0.0f, 0.0f)); // 1P側の初期方向を設定
		obj->SetSpeed(0.0f);
		obj->SetTeam(0);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	//敵
	for (int i = 0; i < 5; i++)
	{
		Enemy* obj;
		obj = new Enemy();
		obj->Init();
		obj->SetLayer(2);
		obj->SetTag("Enemy");
		obj->SetPos(VGet((GetRand(10000) - 5000), 0.0f, (GetRand(10000) - 5000)));
		obj->SetDir(VGet(1.0f, 0.0f, 0.0f));
		obj->SetSpeed(0.0f);
		obj->SetTeam(2);
		obj->SetActive(TRUE); //初期状態でアクティブ
		obj->SetFSM(FSMFactory::Create("Enemy", obj));
		m_objects.push_back(obj);
	}

	//宝箱
	{
		ItemManager* obj;
		obj = new ItemManager(
			VGet(1000.0f, -200.0f, 1000.0f),
			VGet(0.0f, DX_PI_F, 0.0f)
		);
		obj->Init();
		obj->SetTag("Chest");
		obj->SetLayer(3);
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		ItemManager* obj;
		obj = new ItemManager(
			VGet(-3500.0f, -200.0f, 500.0f),
			VGet(0.0f, DX_PI_F, 0.0f)
		);
		obj->Init();
		obj->SetTag("Chest");
		obj->SetLayer(3);
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	{
		ItemManager* obj;
		obj = new ItemManager(
			VGet(-1500.0f, -200.0f, -3500.0f),
			VGet(0.0f, DX_PI_F, 0.0f)
		);
		obj->Init();
		obj->SetTag("Chest");
		obj->SetLayer(3);
		obj->SetTeam(3);
		obj->SetActive(TRUE); //初期状態でアクティブ
		m_objects.push_back(obj);
	}

	//写真関係の初期化
	Master::shot->Initialize();
	Master::photoManager->Initialize();

	// Ｘ軸のマイナス方向のディレクショナルライトに変更
	ChangeLightTypeDir(VGet(1.0f, 1.0f, 1.0f));

	startTime = GetNowCount(); // ゲーム開始時に記録
	timeLimit = 96000;         // 制限時間（ミリ秒）＝96秒

	UIHandle1 = LoadGraph("Resource/UI/Task.png");
	UIHandle2 = LoadGraph("Resource/UI/UIStart.png");
	FinishHandle = LoadGraph("Resource/UI/終了.png");
	ResultHandle = LoadGraph("Resource/UI/結果発表.png");
	OpenHandle = LoadGraph("Resource/UI/箱を開ける.png");

	//霧
	SetFogEnable(TRUE);
	SetFogColor(0, 0, 0);
	SetFogStartEnd(100.0f, 2000.0f);

	//エフェクトを読み込む
	Master::resManager->LoadEffectFromFile("Resource/Effect/Spore.efkefc", 50.0f);
	Master::resManager->LoadEffectFromFile("Resource/Effect/Rain.efkefc", 50.0f);

	// オブジェクトマネージャーに登録
	Master::objectManager->ClearObjects();
	for (auto obj : m_objects)
	{
		if (obj->IsActive() == false)// オブジェクトが非アクティブなら登録しない
			continue;

		Master::objectManager->AddObject(obj); //オブジェクトの登録
	}

	FinishCount = 0;
	taskUImoveX = 0.0f;
	nowTime = 0;
	remainingTime = 0; // 秒単位に変換
	
	//アイテムの残り回数
	ItemCount = 3;

	// シャドウマップのハンドルを生成
	m_shadowMap = MakeShadowMap(SHADOW_SCALE_X, SHADOW_SCALE_Y);

	ChangeLightTypeDir(VNorm(VGet(-1.0f, -1.0f, -1.0f)));

	// シャドウマップが想定するライトの方向を設定
	SetShadowMapLightDirection(m_shadowMap, GetLightDirection());

	// シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea(m_shadowMap, VGet(-5000.0f, 1000.0f, -5000.0f), VGet(5000.0f, -100.0f, 5000.0f));

	SetUseLighting(true);
	SetGlobalAmbientLight(GetColorF(0.7f, 0.7f, 0.7f, 1.0f));
	MATERIALPARAM material = {};
	material.Diffuse = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = GetColorF(0.6f, 0.6f, 0.6f, 1.0f);
	SetMaterialParam(material);

	// ピクセルシェーダーを読み込む
	g_PixelShader = LoadPixelShader("Shader/SimplePS.cso");
	g_PostPixelShader = LoadPixelShader("Shader/PostPS.cso");

	//オフスクリーンバッファの作成
	g_Offscreen = MakeScreen(1280, 720, FALSE);
	g_Offscreen2 = MakeScreen(1280, 720, FALSE);

	//インデックスの設定
	g_Index[0] = 0;
	g_Index[1] = 1;
	g_Index[2] = 2;
	g_Index[3] = 1;
	g_Index[4] = 3;
	g_Index[5] = 2;

	//コンスタントバッファの作成
	constBuff = CreateShaderConstantBuffer(sizeof(COLOR_F));
	//作成したコンスタントバッファをピクセルシェーダのスロット4番にセットする
	SetShaderConstantBuffer(constBuff, DX_SHADERTYPE_PIXEL, 4);

	// フィルターの処理結果を書き込むスクリーンの作成
	highBrightScreen = MakeScreen(SCREEN_SIZE_X, SCREEN_SIZE_Y, false);
	downScaleScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, false);
	gaussScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, false);
	gaussRatio = 2500;
}

void GameScene::Uninitialize()
{
	Master::objectManager->ClearObjects();
	// シーン内のオブジェクトを削除
	for (auto obj : m_objects)
		SAFE_DELETE(obj);

	m_objects.clear(); // オブジェクトのクリア

	Master::sound->StopSE(4);
	Master::sound->StopSE(5);

	Master::resManager->Uninitialize();
}

Scene* GameScene::Update()
{
	Master::sound->PlaySE(4);
	Master::sound->PlaySE(5);

	// 毎フレーム呼び出す処理
	nowTime = GetNowCount();
	remainingTime = (timeLimit - (nowTime - startTime)) / 1000; // 秒単位に変換

	if (remainingTime <= 0)
	{
		remainingTime = 0;
	}

	Master::shot->SetGameTime(remainingTime);
	Master::camera->SetTime(remainingTime);

	if (Master::fade->GetChangeScene() == TRUE)
	{
		Master::fade->SetChangeScene(false);
		return new ResultScene();
	}

    // ゲーム処理
	//全敵キャラの画角に入っているフラグをfalseにする
	std::list<GameObject*> enemys = Master::objectManager->GetObjectsByTag("Enemy");
	for (GameObject* enemy : enemys)
	{
		enemy->SetInThePic(false);
	}

	if (GetMouseInput() & MOUSE_INPUT_LEFT &&  //マウスの左を押しているかつ
		Master::shot->GetTurn() == true && //カメラを覗いているフラグが立っているかつ
		Master::shot->GetTWait() <= 20 && //しっかり覗いている(?)かつ
		Master::shot->GetCoolTime() == 0 && //カメラのクールタイムが0になっているかつ
		Master::shot->GetFilmcount() >= 1 && //フィルムが残っているかつ
		remainingTime <= 90)//ゲームが開始しているとき
	{
		Shoot = true;//写真を撮っているフラグ
	}
	else
	{
		Shoot = false;
	}

	if (Shoot == true)//ゲームが開始しているとき
	{
		/*** 写真を撮影する ***/
		SetFogEnable(FALSE);
		// 描画先をスクリーンショット用スクリーンに変更
		Master::photoManager->SetShotScreen();
		ClearDrawScreen();

		Master::objectManager->UpdateObjects();
		Master::camera->Update();
		LateUpdate();

		Master::sound->PlaySE(1);
		Master::shot->Shutter();

		GetLocalTime(&st); // 現在のローカル時刻を取得

		SetFogEnable(TRUE);

		// 描画先を裏画面に戻す
		SetDrawScreen(DX_SCREEN_BACK);
	}
	else
	{
		Master::photoManager->Decreasefade();
	}

	//胞子
	if (Master::objectManager->GetEffectByTag("spore") == -1)
	{
		Master::objectManager->AddEffect("Resource/Effect/Spore.efkefc", "spore", VGet(0.0f, -200.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(10.0f, 10.0f, 10.0f));
	}

	//雨
	if (Master::objectManager->GetEffectByTag("rain") == -1)
	{
		//Master::objectManager->AddEffect("Resource/Effect/Rain.efkefc", "rain", VGet(0.0f, -200.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(10.0f, 10.0f, 10.0f));
	}
	
	//宝箱用
	std::list<GameObject*> Box = Master::objectManager->GetObjectsByTag("Chest");
	for (GameObject* Chest : Box)
	{
		if (Chest->GetInvisible() == true)
		{
			if (ItemCount > 0)
			{
				//アイテム残り個数を減らす
				ItemCount--;

				//ランダムでアイテムの効果を決める
				ItemEffect = GetRand(2) + 1;
			}

			Chest->SetInvisible(false);
		}
	}

	if (ItemEffect > 0)
	{
		if (ItemEffect == 1)
		{
			AddLog("特殊効果が発動した！");
			AddLog("制限時間が増えた！");
			timeLimit += 5000;//制限時間を５秒増やす
		}
		else if(ItemEffect == 2)
		{
			AddLog("特殊効果が発動した！");
			AddLog("おばけの位置が表示された！");

			std::list<GameObject*> enemys = Master::objectManager->GetObjectsByTag("Enemy");
			for (GameObject* enemy : enemys)
			{
				if (enemy->GetInvisible() == true)
				{
					enemy->SetSelect(true);
				}
			}
		}
		else if (ItemEffect == 3)
		{
			AddLog("なにも起きなかった…");
		}

		//アイテムエフェクトを0に戻す(なにも起きない)
		ItemEffect = 0;
	}

	Master::camera->Update();
	// オブジェクトの更新処理を行う
	Master::objectManager->UpdateObjects();

	g_senddata.r += 0.01f;

	COLOR_F* cb = (COLOR_F*)GetBufferShaderConstantBuffer(constBuff);
	cb->r = g_senddata.r;
	UpdateShaderConstantBuffer(constBuff);

    return this;
}

void GameScene::LateUpdate()
{
	//座標更新
	for (auto obj : Master::objectManager->GetObjectList())
	{
		obj->SetPos(VAdd(obj->GetPos(), VScale(obj->GetDir(), obj->GetSpeed())));
	}
}

void GameScene::Render()
{
	// レンダリングターゲットをオフスクリーンバッファに設定
	SetDrawScreen(g_Offscreen2);
	// オフスクリーンバッファをクリア
	ClearDrawScreen();

	Master::objectManager->RestoreViewMatrix();

	//月を描画（フォグの影響を受けない）
	SetFogEnable(FALSE);
	DrawSphere3D(VGet(6500.0f, 5500.0f, 5500.0f),
				300.0f,
				8,
				GetColor(255, 194, 14),
				GetColor(255, 194, 14),
				TRUE
			);
	SetFogEnable(TRUE);


	//影の描画
	// シャドウマップへの描画の準備
	ShadowMap_DrawSetup(m_shadowMap);
	// ステージの描画
	Master::objectManager->RenderObjects();
	// シャドウマップへの描画を終了
	ShadowMap_DrawEnd();
	// 描画に使用するシャドウマップを設定
	SetUseShadowMap(0, m_shadowMap);
	// ステージの描画
	Master::objectManager->RenderObjects();
	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);


	//カメラを見ているときだけエフェクトを描画する
	if (Master::shot->GetTurn() == true && //カメラを覗いているフラグが立っているかつ
		Master::shot->GetTWait() <= 20 && //しっかり覗いている(?)かつ
		remainingTime <= 90)//ゲームが開始しているとき
	{
		// レンダリングターゲットをオフスクリーンバッファに設定
		SetDrawScreen(g_Offscreen);

		ClearDrawScreen();

		// オフスクリーンサーフェスをテクスチャとして使用
		SetUseTextureToShader(0, g_Offscreen2);

		// ポストエフェクト用ピクセルシェーダーをセット
		SetUsePixelShader(g_PostPixelShader);

		if (Shoot == true)
		{
			// シェーダー解除（重要） 
			SetUsePixelShader(-1);
		}
		// バックバッファへポリゴンを描画
		DrawSprite(640.0f, 360.0f, 1280.0f, 720.0f);

		// シェーダー解除（重要） 
		SetUsePixelShader(-1);
	}
	else
	{
		// レンダリングターゲットをオフスクリーンバッファに設定
		SetDrawScreen(g_Offscreen);

		ClearDrawScreen();

		// 反転フラグ TRUE にする 
		DrawGraph(0, 0, g_Offscreen2, FALSE);
	}

	//オフスクリーンから輝度を抽出（？）
	SetDrawScreen(highBrightScreen);
	DrawGraph(0, 0, g_Offscreen, FALSE);
	GraphFilter(highBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 150, true, GetColor(0, 0, 0), 255);

	SetDrawScreen(downScaleScreen);
	DrawExtendGraph(0, 0, DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, highBrightScreen, FALSE);

	SetDrawScreen(gaussScreen);
	DrawGraph(0, 0, downScaleScreen, FALSE);
	GraphFilter(gaussScreen, DX_GRAPH_FILTER_GAUSS, 32, gaussRatio);

	// 描画対象を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// 通常の描画結果を描画する
	DrawGraph(0, 0, g_Offscreen, false);

	//-------------------------------------------------------
	//	 描画モードをバイリニアフィルタリングにする( 拡大したときにドットがぼやけるようにする )
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	// 描画ブレンドモードを加算にする
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// 高輝度部分を縮小してぼかした画像を画面いっぱいに２回描画する( ２回描画するのはより明るくみえるようにするため )
	DrawExtendGraph(0, 0,
		SCREEN_SIZE_X, SCREEN_SIZE_Y,
		gaussScreen, TRUE);
	DrawExtendGraph(0, 0,
		SCREEN_SIZE_X, SCREEN_SIZE_Y,
		gaussScreen, TRUE);

	// 描画ブレンドモードをブレンド無しに戻す
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	// 描画モードを二アレストに戻す
	SetDrawMode(DX_DRAWMODE_NEAREST);

	//ブルームエフェクトのデバッグ用
	//DrawExtendGraph(180 * 0 + 24, 320, 180 * 0 + 24 + 160, 120 + 320, highBrightScreen, false);
	//DrawExtendGraph(180 * 1 + 24, 320, 180 * 1 + 24 + 160, 120 + 320, downScaleScreen, false);
	//DrawExtendGraph(180 * 2 + 24, 320, 180 * 2 + 24 + 160, 120 + 320, gaussScreen, false);

	if (Shoot == true)
	{
		//写真の日付
		DrawFormatString(1000, 580, GetColor(255, 255, 255), "%04d/%02d/%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

		//画面のスクリーンショットを撮る
		Master::photoManager->SavePicture();
	}
	else
	{
		Master::shot->UIRender();
		Master::photoManager->DisplayPhoto();
		DrawLogs(); // 毎フレーム呼び出す

		//宝箱用UI
		std::list<GameObject*> Box = Master::objectManager->GetObjectsByTag("Chest");
		for (GameObject* Chest : Box)
		{
			if (Chest->GetOpeneble() == true)
			{
				//カメラを見ているときだけエフェクトを描画する
				if (Master::shot->GetTurn() != true) //カメラを覗いているフラグが立っている
				{
					DrawExtendGraph(300, 460, 480, 500, OpenHandle, TRUE);
				}
			}
		}
	}

	if (remainingTime > 91)
	{
		if (remainingTime > 93 && taskUImoveX < 650.0f)
		{
			taskUImoveX += 13.0f;
		}
		else if (remainingTime < 93)
		{
			taskUImoveX += 20.0f;
		}

		DrawExtendGraph((SCREEN_SIZE_X - 200) - taskUImoveX, SCREEN_SIZE_Y / 3 - 100, (SCREEN_SIZE_X + 200) - taskUImoveX, SCREEN_SIZE_Y / 3 - 50, UIHandle1, TRUE);
	}
	else
	{
		if (remainingTime > 90)
		{
			DrawExtendGraph(SCREEN_SIZE_X / 2 - 150, SCREEN_SIZE_Y / 3 - 20, SCREEN_SIZE_X / 2 + 150, SCREEN_SIZE_Y / 3 + 50, UIHandle2, TRUE);
		}
	}

	//フィルムを使いきるか制限時間がなくなったら終了
	if ((Master::shot->GetFilmcount() <= 0 && Master::shot->GetCoolTime() == 0) || (remainingTime == 0 && Master::shot->GetCoolTime() == 0))
	{
		Finish();
	}
}


void GameScene::Finish()
{
	FinishCount++;

	if (FinishCount <= 150)
	{
		DrawExtendGraph(SCREEN_SIZE_X / 2 - 100, SCREEN_SIZE_Y / 3 - 50, 
			SCREEN_SIZE_X / 2 + 100, SCREEN_SIZE_Y / 3, FinishHandle, true);
	}
	else if (FinishCount > 150)
	{
		DrawExtendGraph(SCREEN_SIZE_X / 2 - 130, SCREEN_SIZE_Y / 3 - 50,
			SCREEN_SIZE_X / 2 + 130, SCREEN_SIZE_Y / 3, ResultHandle, true);

		if (FinishCount == 300)
		{
			Master::fade->SetFadeOut(true);
		}
	}
}

VERTEX2DSHADER GameScene::SetVertex2D(float x, float y, float u, float v)
{
	VERTEX2DSHADER vt;

	vt.pos = VGet(x, y, 0.0f);
	vt.u = u;
	vt.v = v;
	vt.su = u;
	vt.sv = v;
	vt.rhw = 1.0f;
	vt.dif = GetColorU8(255, 255, 255, 255);
	vt.spc = GetColorU8(0, 0, 0, 0);

	return vt;
}

void GameScene::DrawSprite(float x, float y, float width, float height)
{
	float halfw = width / 2;
	float halfh = height / 2;

	g_Vertex[0] = SetVertex2D(x - halfw, y - halfh, 0.0f, 0.0f);
	g_Vertex[1] = SetVertex2D(x + halfw, y - halfh, 1.0f, 0.0f);
	g_Vertex[2] = SetVertex2D(x - halfw, y + halfh, 0.0f, 1.0f);
	g_Vertex[3] = SetVertex2D(x + halfw, y + halfh, 1.0f, 1.0f);

	DrawPolygonIndexed2DToShader(g_Vertex, 4, g_Index, 2);
}