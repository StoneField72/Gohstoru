#include "LoadScene.h"
#include "GameScene.h"
#include <DxLib.h>
#include "Master.h"
#include "GameSystem.h"


LoadScene::LoadScene()
{
	//画像ハンドルの読み込み
	GraphHandle2 = -1;
}

LoadScene::~LoadScene()
{
	//画像ハンドルの削除
	DeleteGraph(GraphHandle2);

	// シーン内のオブジェクトを削除
	Master::objectManager->ClearObjects();
	for (auto obj : m_objects)
		SAFE_DELETE(obj);

	m_objects.clear(); // オブジェクトのクリア

	Master::resManager->Uninitialize();
}

void LoadScene::Initialize()
{
	//画像ハンドルの読み込み
	GraphHandle2 = LoadGraph("Resource/asset/AlbumBack2.jpg");
	Master::fade->SetFadeOut(false);
}

void LoadScene::Uninitialize()
{
	Master::objectManager->ClearObjects();

	// シーン内のオブジェクトを削除
	for (auto obj : m_objects)
		SAFE_DELETE(obj);

	m_objects.clear(); // オブジェクトのクリア

	Master::resManager->Uninitialize();
}

Scene* LoadScene::Update()
{
	return new GameScene(); // Enterキーでゲームへ
}

void LoadScene::LateUpdate()
{

}

void LoadScene::Render()
{
	DrawGraph(0, 0, GraphHandle2, FALSE);
}
