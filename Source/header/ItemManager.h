#pragma once
#include "Object.h"
#include <vector>

class ItemManager : public GameObject
{
private:
	int BoxHandle;	// ƒ‚ƒfƒ‹ƒnƒ“ƒhƒ‹	
	int BoxTexHandle;
	int BoxOpenedHandle;

	VECTOR ObjPosition;
	VECTOR ObjRotation;

	bool Open;

	float OpenCount;

public:
	ItemManager(VECTOR position, VECTOR rotation);
	~ItemManager();

	void Init() override;
	void Uninit() override;
	int Update() override;
	void Draw() override;
};
