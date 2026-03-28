
#include "Picture.h"
#include "Object.h"
#include "Shooting.h"

Photo::Photo()
{
	screenshotScreen = MakeScreen(1280, 720, TRUE); // Zバッファ付き
	fadeAlpha = 0; // 最初は完全に透明
	isFadingIn = false;
	NotakePicture = 0;

	Basepoint = 160;
	AlbumShowFlag = false;

	for (int i = 0; i < screenshotCount; i++)
	{
		screenshotGraphs[i] = 0;
	}
	
	BackGraphHandle = -1;
	ArrowHandle = -1;

	screenshotIndex = 0;

	MouseX = 0;
	MouseY = 0;
	SelectPhoto = 0;
	KeyHitCT = 0;
	slidecount = 0;
	Slided = false;

	for (int i = 0; i < 10; i++)
	{
		Good[i] = false;
	}
	LoveGraphHandle = -1;
	NotLoveGraphHandle = -1;
}

Photo::~Photo()
{
	
}

void Photo::Initialize()
{
	screenshotScreen = MakeScreen(1280, 720, TRUE); // Zバッファ付き
	fadeAlpha = 0; // 最初は完全に透明
	isFadingIn = false;
	NotakePicture = 0;

	Basepoint = 160;

	for (int i = 0; i < screenshotCount; i++)
	{
		screenshotGraphs[i] = 0;
	}

	screenshotIndex = 0;

	AlbumShowFlag = false;

	BackGraphHandle = LoadGraph("Resource/asset/AlbumBack3.jpg");
	ArrowHandle = LoadGraph("Resource/UI/Picback.png");

	LoveGraphHandle = LoadGraph("Resource/UI/Love.png");
	NotLoveGraphHandle = LoadGraph("Resource/UI/NotLove.png");

	screenshotIndex = 0;

	SelectPhoto = 0;
	KeyHitCT = 0;
}

void Photo::Update()
{

}

void Photo::Uninitialize()
{
	for (int i = 0; i < screenshotCount; i++)
	{
		DeleteGraph(screenshotGraphs[i]);
	}

	DeleteGraph(BackGraphHandle);
	DeleteGraph(ArrowHandle);
	DeleteGraph(LoveGraphHandle);
	DeleteGraph(NotLoveGraphHandle);
}

//写真保存用スクリーンをセットする
void Photo::SetShotScreen()
{
	SetDrawScreen(screenshotScreen);
}

//写真を保存する
void Photo::SavePicture()
{
	if (screenshotIndex < 10) {
		char filename[64];
		sprintf_s(filename, "Resource/Screenshot/Shot%d.png", screenshotIndex + 1);

		// スクリーンショット保存1115*585
		SaveDrawScreenToBMP(85, 25, 1195, 610, filename);
		screenshotGraphs[screenshotIndex] = LoadGraph(filename);

		screenshotIndex++;
	}

	fadeAlpha = 0;
	isFadingIn = true;

	NotakePicture = 0;
}

//フェードを減らす処理（？）
void Photo::Decreasefade()
{
	NotakePicture++;

	if (NotakePicture >= 300)
	{
		// アルファ値を徐々に減らす（0まで）
		fadeAlpha -= 3;
		if (fadeAlpha <= 0)
		{
			fadeAlpha = 0;
		}
	}
}

//撮った写真を表示＆フラッシュ
void Photo::DisplayPhoto()
{
	if (screenshotGraphs[screenshotIndex - 1] != -1)
	{
		//フェードインしながら表示
		if (isFadingIn)
		{
			//撮影した写真を右上に描画
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
			DrawBox(SCREEN_SIZE_X - 333, 0, SCREEN_SIZE_X, 174, GetColor(255, 255, 255), TRUE);    // 写真の枠を描画
			DrawBox(SCREEN_SIZE_X - 323, 10, SCREEN_SIZE_X - 10, 164, GetColor(0, 0, 0), TRUE);    // 写真の枠を描画
			DrawExtendGraph(SCREEN_SIZE_X - 323, 10, SCREEN_SIZE_X - 10, 164, screenshotGraphs[screenshotIndex - 1], FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			//フラッシュ
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 - fadeAlpha));
			DrawBox(0, 0, 1280, 720, GetColor(255, 255, 255), TRUE);    // 四角形を描画
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// アルファ値を徐々に増やす（最大255まで）
			fadeAlpha += 3;
			if (fadeAlpha >= 255)
			{
				fadeAlpha = 255;
				isFadingIn = false;
			}
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
			DrawBox(SCREEN_SIZE_X - 333, 0, SCREEN_SIZE_X, 174, GetColor(255, 255, 255), TRUE);    // 写真の枠を描画
			DrawBox(SCREEN_SIZE_X - 323, 10, SCREEN_SIZE_X - 10, 164, GetColor(0, 0, 0), TRUE);    // 写真の枠を描画
			DrawExtendGraph(SCREEN_SIZE_X - 323, 10, SCREEN_SIZE_X - 10, 164, screenshotGraphs[screenshotIndex - 1], FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

void Photo::DisplayAlbum()
{
	// マウスの位置を取得
	GetMousePoint(&MouseX, &MouseY);

	if (KeyHitCT != 0)
	{
		KeyHitCT--;

		if (KeyHitCT <= 0)
		{
			KeyHitCT = 0;
		}
	}

	DrawExtendGraph(0 - 105, 0, SCREEN_SIZE_X + 120, SCREEN_SIZE_Y + 10, BackGraphHandle, FALSE);

	//矢印
	if (SelectPhoto > 0)
	{
		if ((((GetMouseInput() & MOUSE_INPUT_LEFT) && MouseX >= 430 && MouseX <= 630 && MouseY >= 630 && MouseY <= 700)))
		{
			DrawExtendGraph(440, 620, 620, 710, ArrowHandle, TRUE);
		}
		else
		{
			DrawExtendGraph(430, 610, 630, 720, ArrowHandle, TRUE);
		}
	}

	if (SelectPhoto < 9)
	{
		if ((((GetMouseInput() & MOUSE_INPUT_LEFT) && MouseX >= 650 && MouseX <= 850 && MouseY >= 630 && MouseY <= 700)))
		{
			DrawExtendGraph(840, 620, 660, 710, ArrowHandle, TRUE);
		}
		else
		{
			DrawExtendGraph(850, 610, 650, 720, ArrowHandle, TRUE);
		}
	}

	if (SelectPhoto < screenshotIndex && SelectPhoto < 10)
	{
		DrawExtendGraph(SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 4, SCREEN_SIZE_X - (SCREEN_SIZE_X / 4), SCREEN_SIZE_Y - (SCREEN_SIZE_Y / 4), screenshotGraphs[SelectPhoto], FALSE);
	
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) &&
			(MouseX >= 990 && MouseX <= 1050 && MouseY >= 100 && MouseY <= 150 && Good[SelectPhoto] == false))
		{
			Good[SelectPhoto] = true;
			GetLocalTime(&st); // 現在のローカル時刻を取得

			// コピー元のファイル名（固定でもOK） 
			sprintf_s(sourcePath, "Resource/Screenshot\\Shot%d.png", SelectPhoto);
			// コピー先のファイル名に連番をつける 
			sprintf_s(destinationPath, "Resource/保存した写真\\Save%d.png", SelectPhoto);

			CopyFile(sourcePath, destinationPath, FALSE);
		}

		if (Good[SelectPhoto] == true && SelectPhoto < 10)
		{
			DrawExtendGraph(990, 100, 1050, 150, LoveGraphHandle, TRUE);
		}
		else
		{
			DrawExtendGraph(990, 100, 1050, 150, NotLoveGraphHandle, TRUE);
		}
	}
	else if (SelectPhoto >= screenshotIndex && SelectPhoto < 10)
	{
		DrawBox(SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 4, SCREEN_SIZE_X - (SCREEN_SIZE_X / 4), SCREEN_SIZE_Y - (SCREEN_SIZE_Y / 4), GetColor(0, 0, 0), TRUE);
		DrawFormatString(320, 174, GetColor(255, 255, 255), "NO DATA");
	}

	if((((GetMouseInput() & MOUSE_INPUT_LEFT) && MouseX >= 650 && MouseX <= 850 && MouseY >= 630 && MouseY <= 700)) 
		&& KeyHitCT == 0)
	{
		SelectPhoto += 1;
		KeyHitCT = 20;
	}

	if ((((GetMouseInput() & MOUSE_INPUT_LEFT) && MouseX >= 430 && MouseX <= 630 && MouseY >= 630 && MouseY <= 700))
		&& KeyHitCT == 0)
	{
		SelectPhoto -= 1;
		KeyHitCT = 20;
	}

	//１枚目の写真より前にいけないように止める
	if (SelectPhoto < 0)
	{
		SelectPhoto = 0;
	}
	//10枚目の写真より後ろにいけないように止める
	if (SelectPhoto > 9)
	{
		SelectPhoto = 9;
	}
}


void Photo::SlideAlbum()
{
	slidecount += 15;

	for (int i = 0; i < 10; i++)
	{
		if (i < screenshotIndex)
		{
			DrawExtendGraph((SCREEN_SIZE_X - slidecount)        + (i * 400), 252, 
				           ((SCREEN_SIZE_X + 384) - slidecount) + (i * 400), 468, 
				screenshotGraphs[i], FALSE);
		}
	}

	if (slidecount > 6000)
	{
		Slided = true;
	}
}