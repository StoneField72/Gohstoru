#pragma once

#include "DxLib.h"
#include "Master.h"
#include <vector>
#include <string>

void AddLog(const std::string& message);

void AddScore(int amount, int LogType);

void DrawLogs();

void ClearAllLogs();

//線形補間
VECTOR DxLibLerp(VECTOR& start, VECTOR& end, float t);

//敵の座標取得
GameObject* GetEnemyObject(GameObject* parent);

//プレイヤーの座標取得
GameObject* GetPlayerObject();

//オブジェクト
GameObject* GetStageObject(GameObject* parent);