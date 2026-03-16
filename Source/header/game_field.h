#pragma once

#include "object.h"


class Field : public GameObject
{
private:
	int skyhandle;
	int floorhandle; // 画像
	int floornormalhandle; // 法線マップ
	VECTOR TopLeft; // 左上座標
	int diameter; // 半径

	VERTEX3D Vertex[4];
	WORD Index[6];

	int woodhandle[60];
	int woodtexhandle;

	int grasshandle[100];
	int grasstexhandle1;
	int grasstexhandle2;

public:
	Field();
	~Field();

	void Init() override;
	void Uninit() override;
	int Update() override;
	void Draw() override;
};

