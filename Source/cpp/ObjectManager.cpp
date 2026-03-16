
#include "ObjectManager.h"
#include <algorithm>
#include <vector>
#include <EffekseerForDXLib.h>
#include "Master.h"

//オブジェクトの更新処理を行う
void ObjectManager::UpdateObjects()
{
	for (auto it = objList.begin(); it != objList.end(); ) 
	{
		//Update関数が-1を返した場合はオブジェクトを削除する
		if ((*it)->Update() == -1)
			it = objList.erase(it);//削除した場合はイテレータを更新
		else
			it++;//削除しなかった場合は次のオブジェクトへ進む
	}


	for (auto it = effectList.begin(); it != effectList.end(); )
	{
		//エフェクトが終了したかチェックする
		if (IsEffekseer3DEffectPlaying((*it).second) != 0)
			it = effectList.erase(it);//エフェクトの再生が終了しているのでリストから削除する
		else
			it++;//削除しなかった場合は次のオブジェクトへ進む
	}

	// カメラのビュー行列を取得する。
	matView = GetCameraViewMatrix();

	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
}

//オブジェクトの描画処理を行う
void ObjectManager::RenderObjects()
{
	for (GameObject* obj : objList) {
		obj->Draw();
	}

	DrawEffekseer3D();
}

//　タグで指定されたオブジェクトのリストを取得する
std::list<GameObject*> ObjectManager::GetObjectsByTag(std::string tag)
{
	std::list<GameObject*> objectsWithTag;

	for (GameObject* obj : objList) {
		if (obj->GetTag() == tag) {
			objectsWithTag.push_back(obj);
		}
	}

	return objectsWithTag;
}

GameObject* ObjectManager::GetObjectByTag(std::string tag)
{
	for (GameObject* obj : objList) {
		if (obj->GetTag() == tag) {
			return obj;
		}
	}

	return nullptr;
}

//オブジェクトをリストに追加する
void ObjectManager::AddObject(GameObject* obj)
{
	if(objList.empty())
		objList.push_back(obj);
	else
	{
		//レイヤー番号により挿入位置を決定する（昇順の挿入ソート）
		auto it = objList.begin();
		while (it != objList.end() && (*it)->GetLayer() < obj->GetLayer())
			it++;

		objList.insert(it, obj);
	}
}

//DontDestroyフラグが立っていないオブジェクトを削除する
void ObjectManager::ClearObjects()
{
	if (objList.empty())
		return;

	objList.remove_if([](GameObject* obj) {
		return (!obj->IsDontDestroy());
		});
}

//全てのオブジェクトを削除する	
void ObjectManager::ClearObjectsForce()
{
	objList.clear();

	for (auto it = effectList.begin(); it != effectList.end(); )
	{
		it = effectList.erase(it);//エフェクトの再生が終了しているのでリストから削除する
	}
}

//ポインタが同一のオブジェクトを削除する
void ObjectManager::RemoveObject(GameObject* obj)
{
	if (objList.empty())
		return;

	objList.remove_if([obj](GameObject* o) {
		return (o == obj);
	});
}

//指定されたタグのオブジェクトを削除する
void ObjectManager::RemoveObjectByTag(std::string tag)
{
	if (objList.empty())
		return;

	objList.remove_if([&tag](GameObject* obj) {
		return (obj->GetTag() == tag);
	});
}

void ObjectManager::AddEffect(std::string name, std::string tag, VECTOR pos, VECTOR rot, VECTOR scale)
{
	//リソースマネージャーからハンドルを取得する
	int handle = Master::resManager->GetEffect(name);

	if (handle == -1)
		return;

	// エフェクトを再生する。
	int playingEffectHandle = PlayEffekseer3DEffect(handle);

	// 再生中のエフェクトを移動する。
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, pos.x, pos.y, pos.z);
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, rot.x, rot.y, rot.z);
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, scale.x, scale.y, scale.z);

	effectList.push_back(std::make_pair(tag, playingEffectHandle));
}

void ObjectManager::UpdateEffect(std::string tag, VECTOR pos, VECTOR rot, VECTOR scale)
{
	//リソースマネージャーからハンドルを取得する
	int playingEffectHandle = GetEffectByTag(tag);

	if (playingEffectHandle == -1)
		return;

	// 再生中のエフェクトを移動する。
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, pos.x, pos.y, pos.z);
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, rot.x, rot.y, rot.z);
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, scale.x, scale.y, scale.z);
}

int ObjectManager::GetEffectByTag(std::string tag)
{
	for (auto pair : effectList) {
		if (pair.first == tag) {
			return pair.second;
		}
	}

	return -1;
}

void ObjectManager::RestoreViewMatrix(void)
{
	SetCameraViewMatrix(matView);
	SetCameraNearFar(1.0f, 150000.0f);

	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
}
