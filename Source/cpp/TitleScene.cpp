#include "TitleScene.h"
#include "LoadScene.h"
#include "GameScene.h"
#include <DxLib.h>
#include "Master.h"
#include "GameSystem.h"
#include "Stage_object.h"
#include <EffekseerForDXLib.h>

TitleScene::TitleScene() 
{
	//画像ハンドルの読み込み
	GraphHandle2 = -1;

	DispGhostType = 0;
	for (int i = 0; i < 6; i++)
	{
		EnemyHandle[i] = -1;
	}
	for (int i = 0; i < 9; i++)
	{
		EnemyTexHandle[i] = -1;
	}
	ModelY = 0.0f;
	for (int i = 0; i < 6; i++)
	{
		GhostNameHandle[0] = -1;
	}

	for (int i = 0; i < 10; i++)
	{
		SavePhoto[i] = -1;
	}

	CameraHandle = -1;
	InCameraGraphHandle = -1;
	CameraFrameHandle = -1;

	TitleTextHandle = -1;
	MenuHandle = -1;
	SelectHandle = -1;
	selectAlpha = 100;
	backHandle = -1;
	BGMtextHandle = -1;
	SEtextHandle = -1;
	GoodPhotoGraphHandle = -1;
	MeetGhostGraphHandle = -1;
	GameStartGraphHandle = -1;
	SettingGraphHandle = -1;
	PhotoGraphHandle = -1;
	StartIconGraphHandle = -1;
	VolumeUpGraphHandle = -1;
	VolumeDownGraphHandle = -1;
	MenutextGraphHandle = -1;
	RightGraphHandle = -1;
	LeftGraphHandle = -1;

	//フォントハンドルの読み込み
	FontHandle = -1;
	FontHandle2 = -1;

	SkyHandle = -1;
	GhostHandle = -1;
	texHandle = -1;
	GroundHandle = -1;
	treetexHandle = -1;

	//モデルハンドルの読み込み
	for (int i = 0; i < 5; i++)
	{
		TreeHandle[i] = -1;
	}

	//変数の初期化
	{
		TitleType = 1;
		BottunCoolTime = 0;
		Mode = 0;
		Menu = 0;
		Choice = 0;
		CameraX = -5000;
		BGMVolume = 0;
		SEVolume = 0;
		MouseX = 0;
		MouseY = 0;
		windOffset = 0.0f;
		SaveSelect = 0;
	}
}

TitleScene::~TitleScene()
{
	//画像ハンドルの削除
	DeleteGraph(GraphHandle2);
	DeleteGraph(treetexHandle);
	DeleteGraph(MenuHandle);
	DeleteGraph(SelectHandle);
	DeleteGraph(backHandle);
	DeleteGraph(BGMtextHandle);
	DeleteGraph(SEtextHandle);
	DeleteGraph(GoodPhotoGraphHandle);
	DeleteGraph(MeetGhostGraphHandle);
	DeleteGraph(InCameraGraphHandle);
	DeleteGraph(CameraFrameHandle);
	DeleteGraph(GameStartGraphHandle);
	DeleteGraph(SettingGraphHandle);
	DeleteGraph(PhotoGraphHandle);
	DeleteGraph(StartIconGraphHandle);
	DeleteGraph(VolumeUpGraphHandle);
	DeleteGraph(VolumeDownGraphHandle);
	DeleteGraph(MenutextGraphHandle);
	DeleteGraph(RightGraphHandle);
	DeleteGraph(LeftGraphHandle);
	DeleteGraph(TitleTextHandle);

	//フォントハンドルの削除
	DeleteFontToHandle(FontHandle);
	DeleteFontToHandle(FontHandle2);

	//モデルハンドルの削除
	MV1DeleteModel(SkyHandle);
	MV1DeleteModel(GhostHandle);
	MV1DeleteModel(CameraHandle);

	for (int i = 0; i < 6; i++)
	{
		MV1DeleteModel(EnemyHandle[i]);
	}
	for (int i = 0; i < 9; i++)
	{
		DeleteGraph(EnemyTexHandle[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		MV1DeleteModel(TreeHandle[i]);
	}
	for (int i = 0; i < 6; i++)
	{
		DeleteGraph(GhostNameHandle[0]);
	}

	// シーン内のオブジェクトを削除
	Master::objectManager->ClearObjects();
	for (auto obj : m_objects)
		SAFE_DELETE(obj);

	m_objects.clear(); // オブジェクトのクリア

	Master::resManager->Uninitialize();
}

void TitleScene::Initialize()
{
	SkyHandle = MV1LoadModel("Resource/asset/Title/sky.mv1");
	EnemyHandle[0] = MV1LoadModel("Resource/asset/Enemy/TestGhost.mv1");
	EnemyHandle[1] = MV1LoadModel("Resource/asset/Enemy/Ghost4.mv1");
	EnemyHandle[2] = MV1LoadModel("Resource/asset/Enemy/Ghost5.mv1");
	EnemyHandle[3] = MV1LoadModel("Resource/asset/Enemy/Ghost3.mv1");
	EnemyHandle[4] = MV1LoadModel("Resource/asset/Enemy/Ghost6.mv1");
	EnemyHandle[5] = MV1LoadModel("Resource/asset/Enemy/Ghost2.mv1");

	EnemyTexHandle[0] = LoadGraph("Resource/asset/Enemy/Ghost Kid Normal.png");
	MV1SetTextureGraphHandle(EnemyHandle[0], 2, EnemyTexHandle[0], TRUE); // 0はテクスチャ番号

	EnemyTexHandle[1] = LoadGraph("Resource/asset/Enemy/Witch Hat 2.png");
	EnemyTexHandle[2] = LoadGraph("Resource/asset/Enemy/Kid Ghost_blinn3_BaseColor.png");
	MV1SetTextureGraphHandle(EnemyHandle[1], 1, EnemyTexHandle[1], TRUE); // 0はテクスチャ番号
	MV1SetTextureGraphHandle(EnemyHandle[1], 2, EnemyTexHandle[2], TRUE); // 0はテクスチャ番号

	EnemyTexHandle[3] = LoadGraph("Resource/asset/Enemy/Witch Hat 3.png");
	EnemyTexHandle[4] = LoadGraph("Resource/asset/Enemy/Ghost Kid Normal.png");
	MV1SetTextureGraphHandle(EnemyHandle[2], 1, EnemyTexHandle[3], TRUE); // 0はテクスチャ番号
	MV1SetTextureGraphHandle(EnemyHandle[2], 4, EnemyTexHandle[4], TRUE); // 0はテクスチャ番号

	EnemyTexHandle[5] = LoadGraph("Resource/asset/Enemy/Kid Ghost_blinn1_BaseColor.png");
	MV1SetTextureGraphHandle(EnemyHandle[3], 2, EnemyTexHandle[5], TRUE); // 0はテクスチャ番号

	EnemyTexHandle[6] = LoadGraph("Resource/asset/Enemy/Axe.png");
	EnemyTexHandle[7] = LoadGraph("Resource/asset/Enemy/Ghost Kid Blooded1.png");
	MV1SetTextureGraphHandle(EnemyHandle[4], 0, EnemyTexHandle[6], TRUE); // 0はテクスチャ番号
	MV1SetTextureGraphHandle(EnemyHandle[4], 3, EnemyTexHandle[7], TRUE); // 0はテクスチャ番号

	EnemyTexHandle[8] = LoadGraph("Resource/asset/Enemy/Kid Ghost_blinn2_BaseColor.png");
	MV1SetTextureGraphHandle(EnemyHandle[5], 2, EnemyTexHandle[8], TRUE); // 0はテクスチャ番号

	for (int i = 0; i < 6; i++)
	{
		MV1SetPosition(EnemyHandle[i], VGet(0.0f, 450.0f, -2800.0f));
		MV1SetScale(EnemyHandle[i], VGet(1.0f, 1.0f, 1.0f));
		MV1SetRotationXYZ(EnemyHandle[i] , VGet(0.0f, -DX_PI_F, 0.0f));
	}

	GhostNameHandle[0] = LoadGraph("Resource/UI/ノーマルおばけ.png");
	GhostNameHandle[1] = LoadGraph("Resource/UI/赤帽子おばけ.png");
	GhostNameHandle[2] = LoadGraph("Resource/UI/青帽子おばけ.png");
	GhostNameHandle[3] = LoadGraph("Resource/UI/角おばけ.png");
	GhostNameHandle[4] = LoadGraph("Resource/UI/斧刺さりおばけ.png");
	GhostNameHandle[5] = LoadGraph("Resource/UI/オレンジおばけ.png");

	// ４頂点分のデータをセット
	//左上
	Vertex[0].pos = VGet(-5000.0f, -200.0f, 5000.0f);
	Vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;
	//右上
	Vertex[1].pos = VGet(5000.0f, -200.0f, 5000.0f);
	Vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[1].dif = GetColorU8(255, 255, 255, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 1.0f;
	Vertex[1].sv = 0.0f;
	//左下
	Vertex[2].pos = VGet(-5000.0f, -200.0f, -3000.0f);
	Vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[2].dif = GetColorU8(255, 255, 255, 225);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 1.0f;
	//右下
	Vertex[3].pos = VGet(5000.0f, -200.0f, -5000.0f);
	Vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[3].dif = GetColorU8(255, 255, 255, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 1.0f;
	Vertex[3].v = 1.0f;
	Vertex[3].su = 1.0f;
	Vertex[3].sv = 1.0f;

	// ２ポリゴン分のインデックスデータをセット
	Index[0] = 0;
	Index[1] = 1;
	Index[2] = 2;
	Index[3] = 3;
	Index[4] = 2;
	Index[5] = 1;

	//霧
	SetFogEnable(TRUE);
	SetFogColor(20, 20, 20);
	SetFogStartEnd(100.0f, 3000.0f);

	GroundHandle = LoadGraph("Resource/asset/Ground.png");
	treetexHandle = LoadGraph("Resource/asset/diffuse2.png");

	TitleTextHandle = LoadGraph("Resource/UI/ゴース撮る.png");
	MenuHandle = LoadGraph("Resource/UI/Menu.png");
	SelectHandle = LoadGraph("Resource/UI/select.png");
	backHandle = LoadGraph("Resource/UI/戻る.png");
	BGMtextHandle = LoadGraph("Resource/UI/BGM.png");
	SEtextHandle = LoadGraph("Resource/UI/SE.png");
	GoodPhotoGraphHandle = LoadGraph("Resource/UI/保存した写真.png");
	MeetGhostGraphHandle = LoadGraph("Resource/UI/出会ったおばけ.png");
	GameStartGraphHandle = LoadGraph("Resource/UI/ゲームを始める.png");
	SettingGraphHandle = LoadGraph("Resource/UI/歯車.png");
	PhotoGraphHandle = LoadGraph("Resource/UI/Photo.png");
	StartIconGraphHandle = LoadGraph("Resource/UI/CameraIcon.png");
	VolumeUpGraphHandle = LoadGraph("Resource/UI/VolumeUp.png");
	VolumeDownGraphHandle = LoadGraph("Resource/UI/VolumeDown.png");
	MenutextGraphHandle = LoadGraph("Resource/UI/メニュー.png");
	RightGraphHandle = LoadGraph("Resource/UI/RightSelect.png");
	LeftGraphHandle = LoadGraph("Resource/UI/LeftSelect.png");

	GhostHandle = MV1LoadModel("Resource/asset/Enemy/TestGhost.mv1");
	texHandle = LoadGraph("Resource/asset/Enemy/Ghost Kid Normal.png");
	MV1SetTextureGraphHandle(GhostHandle, 2, texHandle, TRUE); // 0はテクスチャ番号
	MV1SetPosition(GhostHandle, VGet(-800.0f, 50.0f, -500.0f));
	MV1SetScale(GhostHandle, VGet(5.0f, 5.0f, 5.0f));
	MV1SetRotationXYZ(GhostHandle, VGet(0.0f, DX_PI_F, -DX_PI_F / 6));

	CameraHandle = MV1LoadModel("Resource/asset/Camera/Camera.mv1");
	MV1SetPosition(CameraHandle, VGet(-50.0f, 350.0f, -2650.0f));
	MV1SetScale(CameraHandle, VGet(50.0f, 50.0f, 50.0f));
	MV1SetRotationXYZ(CameraHandle, VGet(0.0f, -DX_PI_F, 0.0f));
	InCameraGraphHandle = LoadGraph("Resource/asset/Camera/InCamera.png");
	CameraFrameHandle = LoadGraph("Resource/asset/TitleFinder.png");

	for (int i = 0; i < 5; i++)
	{
		TreeHandle[i] = MV1LoadModel("Resource/asset/Tree.mv1");
		MV1SetTextureGraphHandle(TreeHandle[i], 0, treetexHandle, FALSE);
	}


	MV1SetPosition(TreeHandle[0], VGet(-800.0f, -200.0f, -1800.0f));
	MV1SetScale(TreeHandle[0], VGet(1.0f, 1.0f, 1.0f));
	MV1SetRotationXYZ(TreeHandle[0], VGet(0.0f, DX_PI_F / 3, 0.0f));

	MV1SetPosition(TreeHandle[1], VGet(800.0f, -200.0f, -1600.0f));
	MV1SetScale(TreeHandle[1], VGet(1.0f, 1.0f, 1.0f));
	MV1SetRotationXYZ(TreeHandle[1], VGet(0.0f, -DX_PI_F / 2, 0.0f));

	MV1SetPosition(TreeHandle[2], VGet(-800.0f, -200.0f, -600.0f));
	MV1SetScale(TreeHandle[2], VGet(1.0f, 1.0f, 1.0f));
	MV1SetRotationXYZ(TreeHandle[2], VGet(0.0f, -DX_PI_F / 2, 0.0f));

	MV1SetPosition(TreeHandle[3], VGet(1200.0f, -200.0f, 0.0f));
	MV1SetScale(TreeHandle[3], VGet(1.0f, 1.0f, 1.0f));
	MV1SetRotationXYZ(TreeHandle[3], VGet(0.0f, -DX_PI_F / 2, 0.0f));

	MV1SetPosition(TreeHandle[4], VGet(0.0f, -200.0f, 600.0f));
	MV1SetScale(TreeHandle[4], VGet(1.0f, 1.0f, 1.0f));
	MV1SetRotationXYZ(TreeHandle[4], VGet(0.0f, -DX_PI_F / 2, 0.0f));

	//画像ハンドルの読み込み
	GraphHandle2 = LoadGraph("Resource/UI/TitlePush.png");

	//フォントハンドルの読み込み
	FontHandle = CreateFontToHandle("HG明朝E", 100, 6, DX_FONTTYPE_NORMAL);
	FontHandle2 = CreateFontToHandle("HG明朝E", 30, 6, DX_FONTTYPE_NORMAL);

	for (int i = 0; i < 10; i++)
	{
		sprintf_s(savefilename, "Resource/保存した写真/Save%d.png", i + 1);

		// SoftImageとして読み込む（LoadGraphより強力）
		int soft = LoadSoftImage(savefilename);

		if (soft != -1)
		{
			// SoftImageからGraphを作成
			SavePhoto[i] = CreateGraphFromSoftImage(soft);
			// SoftImageは不要なので削除
			DeleteSoftImage(soft);
		}
		else
		{
			// 読み込み失敗した場合のログ
			//printfDx("SoftImage読み込み失敗: %s\n", savefilename);
			// 失敗した場合は -1 を入れておく
			SavePhoto[i] = -1;
		}
	}

	SaveSelect = 1;

	BGMVolume = Master::sound->GetBGMVolume();
	SEVolume = Master::sound->GetSEVolume();
	Master::sound->ChangeBGMVolume(BGMVolume);
	Master::sound->ChangeSEVolume(SEVolume);

	// カメラの位置と向きを設定
	SetCameraPositionAndTarget_UpVecY(
		VGet(0.0f, 500.0f, -3000.0f),
		VGet(0.0f, 500.0f, 0.0f)
	);

	// カメラのクリッピング距離を設定
	SetCameraNearFar(18.0f, 14000.0f);

	//背景色の設定
	SetBackgroundColor(35, 59, 108);

	// Zバッファに書き込む準備
	SetUseZBufferFlag(true);
	SetWriteZBufferFlag(true);

	// 背景用の描画先を作る
	backgroundScreen = MakeScreen(1280, 720, TRUE);

	SetMouseDispFlag(TRUE);

	// オブジェクトマネージャーに登録
	Master::objectManager->ClearObjects();
	for (auto obj : m_objects)
	{
		if (obj->IsActive() == false)// オブジェクトが非アクティブなら登録しない
			continue;

		Master::objectManager->AddObject(obj); //オブジェクトの登録
	}
}

void TitleScene::Uninitialize()
{
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(SavePhoto[i]);
	}

	Master::objectManager->ClearObjects();
	// シーン内のオブジェクトを削除
	for (auto obj : m_objects)
		SAFE_DELETE(obj);

	m_objects.clear(); // オブジェクトのクリア

	Master::resManager->Uninitialize();
}

Scene* TitleScene::Update()
{
	// マウスの位置を取得
	GetMousePoint(&MouseX, &MouseY);

	//シーン遷移
	if (Master::fade->GetChangeScene() == true)
	{
		Master::fade->SetChangeScene(false);
		
		if (Mode == 1 && Menu == 0) 
		{
			//return new GameScene(); // Enterキーでゲームへ
			return new LoadScene(); // Enterキーでゲームへ
		}
		else if (Mode == 1 && Menu == 1 && Choice ==1)
		{
			Master::fade->SetFadeIn(true);
			Mode = 2;
			Menu = 0;
			Choice = 0;
		}
		else if (Mode == 1 && Menu == 1 && Choice == 2)
		{
			Master::fade->SetFadeIn(true);
			Mode = 3;
			Menu = 0;
			Choice = 0;
		}
		else if (Mode == 3 && Choice == 1)
		{
			Master::fade->SetFadeIn(true);
			Mode = 1;
			Menu = 0;
			Choice = 0;
		}
		else
		{
			Mode = 1;
			Menu = 0;

			// 数フレーム後に元に戻す 
			SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f)); // 通常の明るさ
			Master::fade->SetFadeIn(true);
		}
	}

	if (alphaUp == true)
	{
		selectAlpha += 2;

		if (selectAlpha >= 200)
		{
			selectAlpha = 200;
			alphaUp = false;
		}
	}
	else
	{
		selectAlpha -= 2;

		if (selectAlpha <= 100)
		{
			selectAlpha = 100;
			alphaUp = true;
		}
	}

	if (BottunCoolTime > 0)
	{
		BottunCoolTime--;
	}

	if (Menu < 0)
	{
		Menu = 0;
	}
	else if (Menu > 2)
	{
		Menu = 2;
	}

	switch (Mode)
	{
	case 0://タイトル画面

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) && Master::fade->GetFadeIn() == false)
		{
			Master::fade->SetFadeOut(true);
			Master::sound->PlaySE(1);
			SetLightDifColor(GetColorF(5.0f, 5.0f, 5.0f, 1.0f)); // すごく明るく 
		}
		break;

	case 1://メニュー画面

		if ((CheckHitKey(KEY_INPUT_LEFT)) && BottunCoolTime == 0)
		{
			Menu--;
			BottunCoolTime = 10;
			Choice = 0;
		}
		if ((CheckHitKey(KEY_INPUT_RIGHT)) && BottunCoolTime == 0)
		{
			Menu++;
			BottunCoolTime = 10;
			Choice = 0;
		}

		if (MouseY >= 150 + (int)(windOffset * 2) && MouseY <= 210 + (int)(windOffset * 2))
		{
			if (MouseX >= 145 && MouseX <= 275)
			{
				//スペースで決定
				if ((GetMouseInput() & MOUSE_INPUT_LEFT))
				{
					Menu = 0;
					Choice = 0;
				}
			}
			else if (MouseX > 275 && MouseX <= 405)
			{
				//スペースで決定
				if ((GetMouseInput() & MOUSE_INPUT_LEFT))
				{
					Menu = 1;
					Choice = 0;
				}
			}
			else if (MouseX > 405 && MouseX <= 535)
			{
				if ((GetMouseInput() & MOUSE_INPUT_LEFT))
				{
					Menu = 2;
					Choice = 0;
				}
			}
		}

		if (Choice < 0)
		{
			Choice = 0;
		}

		switch (Menu)
		{
		case 0:
			if (Choice > 1)
			{
				Choice = 1;
			}

			if (MouseX >= 150 && MouseX <= 300 &&
				MouseY >= 220 + (int)(windOffset * 2) && MouseY <= 250 + (int)(windOffset * 2))
			{
				Choice = 1;

				if ((GetMouseInput() & MOUSE_INPUT_LEFT))
				{
					Master::sound->PlaySE(0);
					Master::fade->SetFadeOut(true);
				}
			}
			else
			{
				Choice = 0;
			}

			break;
		case 1:
			if (Choice > 2)
			{
				Choice = 2;
			}

			if (MouseX >= 150 && MouseX <= 300 &&
				MouseY >= 220 + (int)(windOffset * 2) && MouseY <= 250 + (int)(windOffset * 2) &&
				Master::fade->GetFadeOut() == false)
			{
				Choice = 1;

				if ((GetMouseInput() & MOUSE_INPUT_LEFT))
				{
					Master::sound->PlaySE(0);
					Master::fade->SetFadeOut(true);
				}
			}
			else if (MouseX >= 152 && MouseX <= 320 &&
				MouseY >= 250 + (int)(windOffset * 2) && MouseY <= 320 + (int)(windOffset * 2) && 
				Master::fade->GetFadeOut() == false)
			{
				Choice = 2;

				if ((GetMouseInput() & MOUSE_INPUT_LEFT))
				{
					Master::sound->PlaySE(0);
					Master::fade->SetFadeOut(true);
				}
			}

			break;
		case 2:
			if (Choice > 2)
			{
				Choice = 2;
			}

			if (MouseX >= 150 && MouseX <= 300 &&
				MouseY >= 220 + (int)(windOffset * 2) && MouseY <= 250 + (int)(windOffset * 2))
			{
				if ((GetMouseInput() & MOUSE_INPUT_LEFT))
				{
					Master::sound->PlaySE(0);
					Choice = 1;
				}
			}
			else if (MouseX >= 168 && MouseX <= 300 &&
					MouseY >= 250 + (int)(windOffset * 2) && MouseY <= 280 + (int)(windOffset * 2))
			{
				if ((GetMouseInput() & MOUSE_INPUT_LEFT))
				{
					Master::sound->PlaySE(0);
					Choice = 2;
				}
			}

			//音量調整
			if (Choice == 1)
			{
				if (MouseX >= 600 && MouseX <= 700)
				{
					if (MouseY >= 250 + (int)(windOffset * 2) && MouseY <= 340 + (int)(windOffset * 2))
					{
						//左クリックで決定
						if ((GetMouseInput() & MOUSE_INPUT_LEFT))
						{
							BGMVolume++;
							Master::sound->ChangeBGMVolume(BGMVolume);
							Master::sound->PlaySE(0);
						}
					}
					if (MouseY >= 450 + (int)(windOffset * 2) && MouseY <= 540 + (int)(windOffset * 2))
					{
						//左クリックで決定
						if ((GetMouseInput() & MOUSE_INPUT_LEFT))
						{
							BGMVolume--;
							Master::sound->ChangeBGMVolume(BGMVolume);
							Master::sound->PlaySE(0);
						}
					}
				}
			}
			if (Choice == 2)
			{
				if (MouseX >= 600 && MouseX <= 700)
				{
					if (MouseY >= 270 + (int)(windOffset * 2) && MouseY <= 320 + (int)(windOffset * 2))
					{
						//左クリックで決定
						if ((GetMouseInput() & MOUSE_INPUT_LEFT))
						{
							SEVolume++;
							Master::sound->ChangeSEVolume(SEVolume);
							Master::sound->PlaySE(0);
						}
					}
					if (MouseY >= 470 + (int)(windOffset * 2) && MouseY <= 520 + (int)(windOffset * 2))
					{
						//左クリックで決定
						if ((GetMouseInput() & MOUSE_INPUT_LEFT))
						{
							SEVolume--;
							Master::sound->ChangeSEVolume(SEVolume);
							Master::sound->PlaySE(0);
						}
					}
				}
			}
			break;

		default:
			break;
		}

		break;

	case 2://ライブラリ
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) &&
			MouseX >= 150 && MouseX <= 180 &&
			MouseY >= 330 + (int)(windOffset * 2) && MouseY <= 420 + (int)(windOffset * 2) &&
			BottunCoolTime == 0)
		{
			SaveSelect--;
			BottunCoolTime = 10;

			if (SaveSelect < 0)
			{
				SaveSelect = 0;
			}
		}
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) &&
			MouseX >= 950 && MouseX <= 980 &&
			MouseY >= 330 + (int)(windOffset * 2) && MouseY <= 420 + (int)(windOffset * 2) &&
			BottunCoolTime == 0)
		{
			SaveSelect++;
			BottunCoolTime = 10;

			if (SaveSelect > 8)
			{
				SaveSelect = 8;
			}
		}

		if (MouseX >= SCREEN_SIZE_X - 370 && MouseX <= SCREEN_SIZE_X - 320 &&
			MouseY >= 600 + (int)(windOffset * 2) && MouseY <= 620 + (int)(windOffset * 2))
		{
			Choice = 1;

			if ((GetMouseInput() & MOUSE_INPUT_LEFT))
			{
				Master::fade->SetFadeOut(true);
				Master::sound->PlaySE(0);
			}
		}
		else
		{
			Choice = 0;
		}

		break;

	case 3://出会ったおばけたち
		if (Choice < 0)
		{
			Choice = 0;
		}
		if (Choice > 1)
		{
			Choice = 1;
		}

		if (MouseX >= SCREEN_SIZE_X - 370 && MouseX <= SCREEN_SIZE_X - 320 &&
			MouseY >= 630 + (int)(windOffset * 2) && MouseY <= 650 + (int)(windOffset * 2))
		{
			Choice = 1;

			if ((GetMouseInput() & MOUSE_INPUT_LEFT))
			{
				Master::fade->SetFadeOut(true);
				Master::sound->PlaySE(0);
			}
		}
		else
		{
			Choice = 0;
		}

		ModelY += 0.01f;
		for (int i = 0; i < 6; i++)
		{
			MV1SetPosition(EnemyHandle[i], VGet(0.0f, 450.0f - windOffset, -2800.0f));
			MV1SetRotationXYZ(EnemyHandle[i], VGet(0.0f, -DX_PI_F + ModelY, 0.0f));
		}


		// ３Ｄ空間上に三角形を描画する
		DrawTriangle3D(
			VGet(-175.0f, 595.0f - windOffset, -2780.0f),
			VGet(120.0f, 595.0f - windOffset, -2780.0f),
			VGet(-175.0f, 393.0f - windOffset, -2780.0f), GetColor(0, 0, 200), TRUE);
		// ３Ｄ空間上に三角形を描画する
		DrawTriangle3D(
			VGet(120.0f, 595.0f - windOffset, -2780.0f),
			VGet(120.0f, 393.0f - windOffset, -2780.0f),
			VGet(-175.0f, 393.0f - windOffset, -2780.0f), GetColor(0, 0, 200), TRUE);

		if (DispGhostType < 0)
		{
			DispGhostType = 5;
		}
		if (DispGhostType > 5)
		{
			DispGhostType = 0;
		}

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) && 
			MouseX >= 400 && MouseX <= 480 &&
			MouseY >= 320 + (int)(windOffset * 2) && MouseY <= 440 + (int)(windOffset * 2) &&
			BottunCoolTime == 0)
		{
			DispGhostType--;
			BottunCoolTime = 10;
		}

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) &&
			MouseX >= 800 && MouseX <= 880 &&
			MouseY >= 320 + (int)(windOffset * 2) && MouseY <= 440 + (int)(windOffset * 2) &&
			BottunCoolTime == 0)
		{
			DispGhostType++;
			BottunCoolTime = 10;
		}

		break;
	default:
		break;
	}

	windOffset = sin(GetNowCount() * 0.002f) * 8; // ゆらゆら動く値

	// カメラの位置と向きを設定
	SetCameraPositionAndTarget_UpVecY(
		VGet(0.0f, 500.0f, -3000.0f),
		VGet(0.0f, 500.0f, 0.0f)
	);

	if (BGMVolume <= 0)
	{
		BGMVolume = 0;
	}
	else if (BGMVolume >= 100)
	{
		BGMVolume = 100;
	}

	if (SEVolume <= 0)
	{
		SEVolume = 0;
	}
	else if (SEVolume >= 100)
	{
		SEVolume = 100;
	}

	// オブジェクトの更新処理を行う
	Master::objectManager->UpdateObjects();

	return this;
}

void TitleScene::LateUpdate()
{
	//座標更新
	for (auto obj : Master::objectManager->GetObjectList())
	{
		obj->SetPos(VAdd(obj->GetPos(), VScale(obj->GetDir(), obj->GetSpeed())));
	}
}

void TitleScene::Render()
{
	//モデル
	MV1DrawModel(SkyHandle);

	DrawPolygonIndexed3D(Vertex, 4, Index, 2, GroundHandle, false);

	for (int i = 0; i < 5; i++)
	{
		MV1DrawModel(TreeHandle[i]);
	}

	MV1DrawModel(CameraHandle);
	MV1SetPosition(CameraHandle, VGet(-50.0f, 350.0f - windOffset, -2650.0f));

	//UI
	switch (Mode)
	{
	case 0://タイトル画面

		// 背景を描画
		SetDrawScreen(backgroundScreen);

		// カメラの位置と向きを設定
		SetCameraPositionAndTarget_UpVecY(
			VGet(0.0f, 500.0f, -2000.0f),
			VGet(-500.0f, 500.0f, 0.0f)
		);

		//モデル
		MV1DrawModel(SkyHandle);
		DrawPolygonIndexed3D(Vertex, 4, Index, 2, GroundHandle, false);
		MV1DrawModel(GhostHandle);
		for (int i = 0; i < 5; i++)
		{
			MV1DrawModel(TreeHandle[i]);
		}

		//裏画面に戻す
		SetDrawScreen(DX_SCREEN_BACK);

		// 3. スコープの中に背景テクスチャを貼る
		DrawRectGraph(140, 100 + (int)(windOffset * 2), 150, 100 + (int)(windOffset * 2), 850, 565, backgroundScreen, TRUE);
		DrawExtendGraph(135, 90 + (int)(windOffset * 2), 1015, 670 + (int)(windOffset * 2), CameraFrameHandle, TRUE);

		//クリックまたはSPACEを押してスタート という文字
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, selectAlpha);
		DrawExtendGraph(SCREEN_SIZE_X / 2 - 150, SCREEN_SIZE_Y / 2 + 200, SCREEN_SIZE_X / 2 + 150, SCREEN_SIZE_Y / 2 + 230, GraphHandle2, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		
		//仮のタイトルロゴ
		//DrawFormatStringFToHandle(SCREEN_SIZE_X / 7, SCREEN_SIZE_Y / 6 + (int)(windOffset * 2), GetColor(255, 255, 255), FontHandle, "Title");
		DrawExtendGraph(SCREEN_SIZE_X / 7, SCREEN_SIZE_Y / 6 + (int)(windOffset * 2), SCREEN_SIZE_X / 7 + 300, SCREEN_SIZE_Y / 6 + 80 + (int)(windOffset * 2), TitleTextHandle, TRUE);
		break;

	case 1://メニュー画面
		//
		DrawBox(135, 90 + (int)(windOffset * 2), 1015, 670 + (int)(windOffset * 2), GetColor(0, 0, 0), TRUE);
		DrawExtendGraph(150, 90 + (int)(windOffset * 2), 270, 120 + (int)(windOffset * 2), MenutextGraphHandle, TRUE);
		DrawBox(145, 200 + (int)(windOffset * 2), 1005, 210 + (int)(windOffset * 2), GetColor(200, 0, 0), TRUE);

		switch (Menu)
		{
		case 0:
			DrawBox(145, 140 + (int)(windOffset * 2), 275, 210 + (int)(windOffset * 2), GetColor(200, 0, 0), TRUE);
			break;

		case 1:
			DrawBox(275, 140 + (int)(windOffset * 2), 405, 210 + (int)(windOffset * 2), GetColor(200, 0, 0), TRUE);
			break;

		case 2:
			DrawBox(405, 140 + (int)(windOffset * 2), 535, 210 + (int)(windOffset * 2), GetColor(200, 0, 0), TRUE);
			break;

		default:
			break;
		}

		DrawExtendGraph(170, 150 + (int)(windOffset * 2), 250, 195 + (int)(windOffset * 2), StartIconGraphHandle, TRUE);
		DrawExtendGraph(300, 150 + (int)(windOffset * 2), 380, 195 + (int)(windOffset * 2), PhotoGraphHandle, TRUE);
		DrawExtendGraph(435, 145 + (int)(windOffset * 2), 505, 200 + (int)(windOffset * 2), SettingGraphHandle, TRUE);

		switch (Menu)
		{
		case 0:
			DrawExtendGraph(150, 220 + (int)(windOffset * 2), 300, 250 + (int)(windOffset * 2), GameStartGraphHandle, TRUE);

			if (Choice == 1)
			{
				DrawBox(140, 220 + (int)(windOffset * 2), 150, 250 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
				DrawBox(150, 220 + (int)(windOffset * 2), 300, 250 + (int)(windOffset * 2), GetColor(255, 0, 0), FALSE);
				DrawBox(300, 220 + (int)(windOffset * 2), 310, 250 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
			}

			break;
		case 1:
			DrawExtendGraph(150, 220 + (int)(windOffset * 2), 300, 250 + (int)(windOffset * 2), GoodPhotoGraphHandle, TRUE);
			DrawExtendGraph(152, 250 + (int)(windOffset * 2), 320, 280 + (int)(windOffset * 2), MeetGhostGraphHandle, TRUE);

			switch (Choice)
			{
			case 1:
				DrawBox(140, 220 + (int)(windOffset * 2), 150, 250 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
				DrawBox(150, 220 + (int)(windOffset * 2), 300, 250 + (int)(windOffset * 2), GetColor(255, 0, 0), FALSE);
				DrawBox(300, 220 + (int)(windOffset * 2), 310, 250 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
				break;
			case 2:
				DrawBox(142, 250 + (int)(windOffset * 2), 152, 280 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
				DrawBox(152, 250 + (int)(windOffset * 2), 320, 280 + (int)(windOffset * 2), GetColor(255, 0, 0), FALSE);
				DrawBox(320, 250 + (int)(windOffset * 2), 330, 280 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
				break;
			default:
				break;
			}

			break;
		case 2:
			DrawExtendGraph(150, 220 + (int)(windOffset * 2), 300, 250 + (int)(windOffset * 2), BGMtextHandle, TRUE);
			DrawExtendGraph(168, 250 + (int)(windOffset * 2), 300, 280 + (int)(windOffset * 2), SEtextHandle, TRUE);

			if (Choice > 0)
			{
				if ((GetMouseInput() & MOUSE_INPUT_LEFT) && 
					MouseX >= 600 && MouseX <= 700 && 
					MouseY >= 250 + (int)(windOffset * 2) && MouseY <= 340 + (int)(windOffset * 2))
				{
					DrawExtendGraph(605, 275 + (int)(windOffset * 2), 695, 315 + (int)(windOffset * 2), VolumeUpGraphHandle, TRUE);
				}
				else
				{
					DrawExtendGraph(600, 270 + (int)(windOffset * 2), 700, 320 + (int)(windOffset * 2), VolumeUpGraphHandle, TRUE);
				}
				if ((GetMouseInput() & MOUSE_INPUT_LEFT) &&
					MouseX >= 600 && MouseX <= 700 &&
					MouseY >= 450 + (int)(windOffset * 2) && MouseY <= 540 + (int)(windOffset * 2))
				{
					DrawExtendGraph(605, 475 + (int)(windOffset * 2), 695, 515 + (int)(windOffset * 2), VolumeDownGraphHandle, TRUE);
				}
				else
				{
					DrawExtendGraph(600, 470 + (int)(windOffset * 2), 700, 520 + (int)(windOffset * 2), VolumeDownGraphHandle, TRUE);
				}
			}

			switch (Choice)
			{
			case 1:
				DrawBox(140, 220 + (int)(windOffset * 2), 150, 250 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
				DrawBox(150, 220 + (int)(windOffset * 2), 300, 250 + (int)(windOffset * 2), GetColor(255, 0, 0), FALSE);
				DrawBox(300, 220 + (int)(windOffset * 2), 310, 250 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
				Master::shot->NumDraw(BGMVolume, 645, 370 + (int)(windOffset * 2));//でない
				//DrawFormatString(600, 400, GetColor(255, 255, 255), "%d", BGMVolume);
				break;
			case 2:
				DrawBox(158, 250 + (int)(windOffset * 2), 168, 280 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
				DrawBox(168, 250 + (int)(windOffset * 2), 300, 280 + (int)(windOffset * 2), GetColor(255, 0, 0), FALSE);
				DrawBox(300, 250 + (int)(windOffset * 2), 310, 280 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
				Master::shot->NumDraw(SEVolume, 645, 370 + (int)(windOffset * 2));//でない
				//DrawFormatString(600, 400, GetColor(255, 255, 255), "%d", SEVolume);
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
		break;

	case 2://ライブラリ
		DrawExtendGraph(135, 90 + (int)(windOffset * 2), 990, 670 + (int)(windOffset * 2), SavePhoto[SaveSelect], FALSE);

		DrawExtendGraph(SCREEN_SIZE_X - 370, 600 + (int)(windOffset * 2), SCREEN_SIZE_X - 320, 620 + (int)(windOffset * 2), backHandle, TRUE);
		
		if (Choice == 1)
		{
			DrawBox(SCREEN_SIZE_X - 380, 600 + (int)(windOffset * 2), SCREEN_SIZE_X - 370, 620 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
			DrawBox(SCREEN_SIZE_X - 370, 600 + (int)(windOffset * 2), SCREEN_SIZE_X - 320, 620 + (int)(windOffset * 2), GetColor(255, 0, 0), FALSE);
			DrawBox(SCREEN_SIZE_X - 320, 600 + (int)(windOffset * 2), SCREEN_SIZE_X - 310, 620 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
		}

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) &&
			MouseX >= 150 && MouseX <= 180 &&
			MouseY >= 330 + (int)(windOffset * 2) && MouseY <= 420 + (int)(windOffset * 2))
		{
			DrawTriangle(175, 355 + (int)(windOffset * 2), 155, 375 + (int)(windOffset * 2), 175, 395 + (int)(windOffset * 2), GetColor(255, 255, 255), TRUE);
		}
		else
		{
			// 三角形を描画
			DrawTriangle(180, 350 + (int)(windOffset * 2), 150, 375 + (int)(windOffset * 2), 180, 400 + (int)(windOffset * 2), GetColor(255, 255, 255), TRUE);
		}

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) &&
			MouseX >= 950 && MouseX <= 980 &&
			MouseY >= 330 + (int)(windOffset * 2) && MouseY <= 420 + (int)(windOffset * 2))
		{
			DrawTriangle(955, 355 + (int)(windOffset * 2), 975, 375 + (int)(windOffset * 2), 955, 395 + (int)(windOffset * 2), GetColor(255, 255, 255), TRUE);
		}
		else
		{
			DrawTriangle(950, 350 + (int)(windOffset * 2), 980, 375 + (int)(windOffset * 2), 950, 400 + (int)(windOffset * 2), GetColor(255, 255, 255), TRUE);
		}

		
		break;

	case 3:
		MV1DrawModel(EnemyHandle[DispGhostType]);
		DrawExtendGraph(SCREEN_SIZE_X / 2 - 100, 550 + (int)(windOffset * 2), SCREEN_SIZE_X / 2 + 100, 600 + (int)(windOffset * 2), GhostNameHandle[DispGhostType], TRUE);
		DrawExtendGraph(SCREEN_SIZE_X - 370, 630 + (int)(windOffset * 2), SCREEN_SIZE_X - 320, 650 + (int)(windOffset * 2), backHandle, TRUE);

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) &&
			MouseX >= 400 && MouseX <= 480 &&
			MouseY >= 330 + (int)(windOffset * 2) && MouseY <= 430 + (int)(windOffset * 2))
		{
			DrawExtendGraph(405, 335 + (int)(windOffset * 2), 475, 425 + (int)(windOffset * 2), LeftGraphHandle, TRUE);
		}
		else
		{
			DrawExtendGraph(400, 320 + (int)(windOffset * 2), 480, 440 + (int)(windOffset * 2), LeftGraphHandle, TRUE);
		}

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) &&
			MouseX >= 800 && MouseX <= 880 &&
			MouseY >= 330 + (int)(windOffset * 2) && MouseY <= 430 + (int)(windOffset * 2))
		{
			DrawExtendGraph(805, 335 + (int)(windOffset * 2), 875, 435 + (int)(windOffset * 2), RightGraphHandle, TRUE);
		}
		else
		{
			DrawExtendGraph(800, 320 + (int)(windOffset * 2), 880, 440 + (int)(windOffset * 2), RightGraphHandle, TRUE);
		}

		if (Choice == 1)
		{
			DrawBox(SCREEN_SIZE_X - 380, 630 + (int)(windOffset * 2), SCREEN_SIZE_X - 370, 650 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
			DrawBox(SCREEN_SIZE_X - 370, 630 + (int)(windOffset * 2), SCREEN_SIZE_X - 320, 650 + (int)(windOffset * 2), GetColor(255, 0, 0), FALSE);
			DrawBox(SCREEN_SIZE_X - 320, 630 + (int)(windOffset * 2), SCREEN_SIZE_X - 310, 650 + (int)(windOffset * 2), GetColor(255, 0, 0), TRUE);
		}
			
		break;

	default:
		break;
	}

	// オブジェクトの描画処理を行う
	Master::objectManager->RenderObjects();
}
