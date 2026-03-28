
#include "GameSystem.h"
#include "DxLib.h"
#include "Master.h"
#include "Scene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include <stdlib.h>
#include <time.h>
#include "EffekseerForDXLib.h"


#define CRT_SECURE_NO_WARNINGS

//Masterの各インスタンスの初期化
ObjectManager* Master::objectManager = nullptr;
SceneManager* Master::sceneManager = nullptr;
ResourceManager* Master::resManager = nullptr;
Camera* Master::camera = nullptr;
Shot* Master::shot = nullptr;
Photo* Master::photoManager = nullptr;
Fade* Master::fade = nullptr;
Sound* Master::sound = nullptr;

#define SCREEN_SIZE_X 1280
#define SCREEN_SIZE_Y 720

GameSystem::GameSystem()
{

}

GameSystem::~GameSystem()
{

}

// Initialize the game system
bool GameSystem::Initialize()
{
	srand((unsigned)time(NULL));

	SetWindowText("ゴース撮る");					// ウィンドウのタイトル

	//ウィンドウモードに変更
	ChangeWindowMode(TRUE);

	//常に実行状態にする
	SetAlwaysRunFlag(TRUE);

	//垂直同期を無効にする
	SetWaitVSyncFlag(FALSE);

	//ウィンドウサイズを設定
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//DXライブラリ初期化処理
	if (DxLib_Init() == -1)
		return false;	// エラーが起きたら直ちに終了

	//描画先画面をバックバッファに設定
	SetDrawScreen(DX_SCREEN_BACK);

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return false;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	//Masterの各インスタンスを作成する
	Master::objectManager = new ObjectManager();
	Master::sceneManager = new SceneManager();
	Master::resManager = new ResourceManager();
	Master::camera = new Camera();
	Master::shot = new Shot();
	Master::photoManager = new Photo();
	Master::fade = new Fade();
	Master::sound = new Sound();
	Master::sound->Initialize();
	Master::photoManager->Initialize();

	//シーンマネージャーにシーンを追加する
	Scene* gameScene = new GameScene();
	Master::sceneManager->AddScene("GAME", gameScene);

	//初期実行シーンをセットする
	Master::sceneManager->SetScene("GAME");
	Master::sceneManager->SceneTransition();// シーンの遷移を行う

	return true;
}

void GameSystem::UnInitialize()
{
	Master::resManager->Uninitialize();
	Master::objectManager->ClearObjectsForce();
	Master::sceneManager->Uninitialize();
	Master::photoManager->Uninitialize();
	Master::sound->Uninitialize();

	//Masterの各インスタンスを解放する
	SAFE_DELETE(Master::resManager);
	SAFE_DELETE(Master::objectManager);
	SAFE_DELETE(Master::sceneManager);
	SAFE_DELETE(Master::camera);
	SAFE_DELETE(Master::shot);
	SAFE_DELETE(Master::photoManager);
	SAFE_DELETE(Master::fade);
	SAFE_DELETE(Master::sound);

	// Effekseerを終了する。
	Effkseer_End();

	//DXライブラリ使用の終了処理
	DxLib_End();
}


// Update the game system
void GameSystem::GameLoop()
{
	LONGLONG currentTime = GetNowHiPerformanceCount();
	LONGLONG lastTime = currentTime;

	Scene* currentScene = new TitleScene();
	//Scene* currentScene = new GameScene();
	currentScene->Initialize();

	// ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		currentTime = GetNowHiPerformanceCount();

		if ((currentTime - lastTime) > 1000000.0f / 60)
		{
			lastTime = currentTime;

			// 画面を初期化
			ClearDrawScreen();

			Scene* nextScene = currentScene->Update();
			currentScene->LateUpdate();
			currentScene->Render();

			//フェード待機処理
			Master::fade->WaitFade();

			ScreenFlip();

			//シーン切り替え処理
			if (nextScene != currentScene)
			{
				//シーンの後処理
				currentScene->Uninitialize();

				delete currentScene;

				currentScene = nextScene;

				//シーンの初期化処理
				currentScene->Initialize();
			
				Master::fade->SetFadeIn(TRUE);
			}	
		}
	}

	delete currentScene;
}
