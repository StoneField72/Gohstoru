#pragma once

#include "ObjectManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Shooting.h"
#include "Picture.h"
#include "Fade.h"
#include "SoundManager.h"


class Master
{
public:
	static ObjectManager* objectManager;
	static SceneManager* sceneManager;
	static ResourceManager* resManager;
	static Camera* camera;
	static Shot* shot;
	static Photo* photoManager;
	static Fade* fade;
	static Sound* sound;
};
