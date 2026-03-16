#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include <DxLib.h>
#include "Master.h"
#include "DxLibUtil.h"


ResultScene::ResultScene()
{
	FontHandle = -1;
	FontHandle2 = -1;

	GoodGraphHandle = -1;
	BackTitleGraphHandle = -1;
	GoalbumGraphHandle = -1;
	ClosealbumGraphHandle = -1;
	MouseX = 0;
	MouseY = 0;
	KeyHitCT = 0;

	SGraphHandle = -1;
	AGraphHandle = -1;
	BGraphHandle = -1;
	CGraphHandle = -1;
	DGraphHandle = -1;
	TotalScoreHandle = -1;
	RankGraphHandle = -1;
	BackGraphHandle = -1;
	ScoreGraphHandle = -1;
}

ResultScene::~ResultScene()
{
	DeleteFontToHandle(FontHandle);
	DeleteFontToHandle(FontHandle2);
	DeleteGraph(GoodGraphHandle);
	DeleteGraph(BackTitleGraphHandle);
	DeleteGraph(GoalbumGraphHandle);
	DeleteGraph(ClosealbumGraphHandle);

	DeleteGraph(SGraphHandle);
	DeleteGraph(AGraphHandle);
	DeleteGraph(BGraphHandle);
	DeleteGraph(CGraphHandle);
	DeleteGraph(DGraphHandle);
	DeleteGraph(TotalScoreHandle);
	DeleteGraph(RankGraphHandle);
	DeleteGraph(BackGraphHandle);
	DeleteGraph(ScoreGraphHandle);
}

void ResultScene::Initialize()
{
	FontHandle = CreateFontToHandle("HG明朝E", 50, 6, DX_FONTTYPE_NORMAL);
	FontHandle2 = CreateFontToHandle("HG明朝E", 200, 6, DX_FONTTYPE_NORMAL);

	GoodGraphHandle = LoadGraph("Resource/asset/Good.png");
	BackTitleGraphHandle = LoadGraph("Resource/UI/タイトルにもどる.png");
	GoalbumGraphHandle = LoadGraph("Resource/UI/写真を見る.png");
	ClosealbumGraphHandle = LoadGraph("Resource/UI/閉じる.png");
	RankGraphHandle = LoadGraph("Resource/UI/Rank.png");
	BackGraphHandle = LoadGraph("Resource/UI/カーテン.jpg");

	SGraphHandle = LoadGraph("Resource/UI/S.png");
	AGraphHandle = LoadGraph("Resource/UI/A.png");
	BGraphHandle = LoadGraph("Resource/UI/B.png");
	CGraphHandle = LoadGraph("Resource/UI/C.png");
	DGraphHandle = LoadGraph("Resource/UI/D.png");
	TotalScoreHandle = LoadGraph("Resource/UI/Total Score.png");
	ScoreGraphHandle = LoadGraph("Resource/UI/Score.png");

	SetMouseDispFlag(TRUE);
	Master::sound->PlaySE(2);
}

void ResultScene::Uninitialize()
{
	Master::photoManager->OffSlided();
}

Scene* ResultScene::Update()
{
	// マウスの位置を取得
	GetMousePoint(&MouseX, &MouseY);

	if (Master::fade->GetChangeScene() == TRUE)
	{
		Master::fade->SetChangeScene(false);
		return new TitleScene(); // Enterキーでゲームへ
	}

	//スライド中
	if (Master::photoManager->GetSlided() == false)
	{

	}
	else
	{
		//
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) && MouseX >= 20 && MouseX <= 280 &&
			MouseY >= 660 && MouseY <= SCREEN_SIZE_Y - 10 && KeyHitCT == 0)
		{
			if (ShowPhoto)
			{
				ShowPhoto = false;
			}
			else
			{
				ShowPhoto = true;
			}

			KeyHitCT = 20;
		}
		else
		{
			KeyHitCT--;

			if (KeyHitCT <= 0)
			{
				KeyHitCT = 0;
			}
		}

		if (CheckHitKey(KEY_INPUT_RETURN) ||
			((GetMouseInput() & MOUSE_INPUT_LEFT) && MouseX >= 1000 && MouseX <= SCREEN_SIZE_X - 10 &&
				MouseY >= 660 && MouseY <= SCREEN_SIZE_Y - 10))
		{
			Master::fade->SetFadeOut(true);
		}
	}

    return this;
}

void ResultScene::LateUpdate()
{

}

void ResultScene::Render()
{
	DrawExtendGraph(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, BackGraphHandle, TRUE);

	if (Master::photoManager->GetSlided() == false)
	{
		Master::photoManager->SlideAlbum();

		Master::shot->NumDraw(GetRand(10000), SCREEN_SIZE_X / 2, 120);
	}
	else
	{
		DrawExtendGraph(SCREEN_SIZE_X / 2 - 250, 230, (SCREEN_SIZE_X / 2) + 70, 300, TotalScoreHandle, TRUE);
		if (Master::shot->GetTotalScore() >= 10000)
		{
			Master::shot->NumDraw(Master::shot->GetTotalScore(), SCREEN_SIZE_X / 2 + 220, 250);
		}
		else if (Master::shot->GetTotalScore() < 10000 && Master::shot->GetTotalScore() >= 1000)
		{
			Master::shot->NumDraw(Master::shot->GetTotalScore(), SCREEN_SIZE_X / 2 + 170, 250);
		}

		DrawExtendGraph(SCREEN_SIZE_X / 2 - 200, 350, (SCREEN_SIZE_X / 2), 450, RankGraphHandle, TRUE);
		if (Master::shot->GetTotalScore() >= 10000)
		{
			DrawExtendGraph(SCREEN_SIZE_X / 2, 330, (SCREEN_SIZE_X / 2) + 200, 500, SGraphHandle, TRUE);
		}
		else if (Master::shot->GetTotalScore() >= 8000 && Master::shot->GetTotalScore() < 10000)
		{
			DrawExtendGraph(SCREEN_SIZE_X / 2, 330, (SCREEN_SIZE_X / 2) + 200, 500, AGraphHandle, TRUE);
		}
		else if (Master::shot->GetTotalScore() >= 6000 && Master::shot->GetTotalScore() < 8000)
		{
			DrawExtendGraph(SCREEN_SIZE_X / 2, 330, (SCREEN_SIZE_X / 2) + 200, 500, BGraphHandle, TRUE);
		}
		else if (Master::shot->GetTotalScore() >= 4000 && Master::shot->GetTotalScore() < 6000)
		{
			DrawExtendGraph(SCREEN_SIZE_X / 2, 330, (SCREEN_SIZE_X / 2) + 200, 500, CGraphHandle, TRUE);
		}
		else if (Master::shot->GetTotalScore() >= 2000 && Master::shot->GetTotalScore() < 4000)
		{
			DrawExtendGraph(SCREEN_SIZE_X / 2, 330, (SCREEN_SIZE_X / 2) + 200, 500, DGraphHandle, TRUE);
		}
		else if (Master::shot->GetTotalScore() < 2000)
		{
			DrawFormatStringFToHandle(SCREEN_SIZE_X / 2, 300, GetColor(255, 255, 255), FontHandle2, "-");
		}

		if (ShowPhoto)
		{
			//アルバムを表示
			Master::photoManager->DisplayAlbum();

			if (Master::photoManager->GetSelectPhoto() < 10)
			{
				DrawFormatString(10, 10, GetColor(255, 255, 255), "%d/10", Master::photoManager->GetSelectPhoto() + 1);
				DrawExtendGraph(SCREEN_SIZE_X / 2 - 150, 30, SCREEN_SIZE_X / 2 + 30, 80, ScoreGraphHandle, TRUE);
				if (Master::shot->FilmScore(Master::photoManager->GetSelectPhoto()) >= 1000)
				{
					Master::shot->NumDraw(Master::shot->FilmScore(Master::photoManager->GetSelectPhoto()), SCREEN_SIZE_X / 2 + 150, 40);
				}
				else if (Master::shot->FilmScore(Master::photoManager->GetSelectPhoto()) < 1000)
				{
					Master::shot->NumDraw(Master::shot->FilmScore(Master::photoManager->GetSelectPhoto()), SCREEN_SIZE_X / 2 + 100, 40);
				}

				//スコアが2000を超えている写真にはグッドマークをつける
				if (Master::shot->FilmScore(Master::photoManager->GetSelectPhoto()) >= 2000)
				{
					DrawExtendGraph(SCREEN_SIZE_X / 6, 50, (SCREEN_SIZE_X / 6) + 200, 190, GoodGraphHandle, TRUE);
				}
			}
			//アルバムを閉じる
			DrawExtendGraph(20, 660, 210, SCREEN_SIZE_Y - 10, ClosealbumGraphHandle, TRUE);
		}
		else
		{
			//アルバムを開く の文字
			DrawExtendGraph(20, 660, 280, SCREEN_SIZE_Y - 10, GoalbumGraphHandle, TRUE);
		}

		//タイトルにもどるの文字
		DrawExtendGraph(1000, 660, SCREEN_SIZE_X - 10, SCREEN_SIZE_Y - 10, BackTitleGraphHandle, TRUE);
	}
}
