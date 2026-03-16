#pragma once
#include "Object.h"
#include <vector>
#include "object.h"

class StageObject : public GameObject
{
private:
	int ObjectHandle;	// ƒ‚ƒfƒ‹ƒnƒ“ƒhƒ‹	

	VECTOR ObjPosition;
	VECTOR ObjScale;
	VECTOR ObjRotation;

	VECTOR Objsize;
	VECTOR Treesize;
	
	int textureHandle1;
	int textureHandle2;

public:
	StageObject(const char* filename, VECTOR position, VECTOR Scale, VECTOR rotation);
	StageObject(const char* filename, const char* texturePath1, VECTOR position, VECTOR Scale, VECTOR rotation);
	StageObject(const char* filename, const char* texturePath1, const char* texturePath2, VECTOR position, VECTOR Scale, VECTOR rotation);
	~StageObject();

	void Init() override;
	void Uninit() override;
	int Update() override;
	void Draw() override;

	VECTOR GetScale() { return Objsize; }
};