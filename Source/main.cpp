

#include "GameSystem.h"
#include <windows.h>

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameSystem gameSystem;	// ゲームシステムのインスタンスを生成

	// ゲームシステムの初期化
	gameSystem.Initialize();

	// ゲームシステム実行
	gameSystem.GameLoop();

	// ゲームシステムの終了処理
	gameSystem.UnInitialize();

	return 0;	
}
