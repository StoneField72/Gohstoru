
#include "ResourceManager.h"
#include <cassert>
#include "DxLib.h"
#include "EffekseerForDXLib.h"


// 画像の読み込み
int ResourceManager::LoadImageFromFile(std::string name)
{
	//mapに名前が登録されていなかったら読み込む
	if (m_images.find(name) == m_images.end())
		m_images[name] = LoadGraph(name.c_str());

	//画像のハンドルを返す
	return m_images[name];
}

// 画像のハンドルを名前で取得する
int ResourceManager::GetImage(std::string name)
{
	if (m_images.find(name) == m_images.end())
		return -1;

	return m_images[name];
}

// Effekseerエフェクトの読み込み
int ResourceManager::LoadEffectFromFile(std::string name, float baseScale)
{
	//mapに名前が登録されていなかったら読み込む
	if (m_effects.find(name) == m_effects.end())
	{
		int res = LoadEffekseerEffect(name.c_str(), baseScale);
		if (res == -1)
			return -1;//読み込みに失敗した場合は-1を返す

		m_effects[name] = res;
	}

	//エフェクトのハンドルを返す
	return m_effects[name];
}

// Effekseerエフェクトのハンドルを名前で取得する
int ResourceManager::GetEffect(std::string name)
{
	if (m_effects.find(name) == m_effects.end())
		return -1;

	return m_effects[name];
}

// 指定された名前の画像を解放する
void ResourceManager::UnloadImage(std::string name)
{
	auto it = m_images.find(name);

	//名前が見つからなかったら何もしない
	if (it == m_images.end())
		return;

	DeleteGraph((*it).second);

	m_images.erase(it);
}

// 指定されたハンドルの画像を解放する
void ResourceManager::UnloadImage(int handle)
{
	for (auto it = m_images.begin(); it != m_images.end(); it++) {
		if (it->second == handle)
		{
			DeleteGraph(it->second);
			it = m_images.erase(it);  // eraseの戻り値は次の要素のイテレータ
			break;
		}
	}
}

// 指定された名前のエフェクトを解放する
void ResourceManager::UnloadEffect(std::string tag)
{
	auto it = m_effects.find(tag);

	//名前が見つからなかったら何もしない
	if (it == m_effects.end())
		return;

	StopEffekseer3DEffect((*it).second);
	DeleteEffekseerEffect((*it).second);

	m_effects.erase(it);
}

// すべてのリソースを解放する
void ResourceManager::Uninitialize(void)
{
	for (auto effect : m_effects)
	{
		StopEffekseer3DEffect(effect.second);
		DeleteEffekseerEffect(effect.second);
	}

	for (auto image : m_images)
		DeleteGraph(image.second);

	m_effects.clear();
	m_images.clear();
}
