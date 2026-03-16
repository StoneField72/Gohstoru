
#include "SceneManager.h"
#include <cassert>


void SceneManager::Uninitialize()
{
	for (auto scene : m_scenes)
	{
		if (scene.second != nullptr)
		{
			scene.second->Uninitialize();
			delete scene.second;
		}
	}

	m_scenes.clear();
}

void SceneManager::AddScene(std::string name, Scene* scene)
{
	m_scenes[name] = scene;
}

void SceneManager::SetScene(std::string name)
{
#ifdef _DEBUG
	//指定されたシーンが登録されているかチェックする
	if (m_scenes.find(name) == m_scenes.end())
	{
		assert(false);//アサーションで止める
		return;
	}
#endif

	m_nextSceneName = name;
}

void SceneManager::Update(void)
{
	m_scenes[m_activeSceneName]->Update();
}

void SceneManager::LateUpdate(void)
{
	m_scenes[m_activeSceneName]->LateUpdate();
}

void SceneManager::Render(void)
{
	m_scenes[m_activeSceneName]->Render();
}

void SceneManager::SceneTransition(void)
{
	//シーンの切り替えが必要かチェックする
	if (m_activeSceneName != m_nextSceneName)
	{
		//実行中のシーンを終了させる
		if (m_scenes.find(m_activeSceneName) != m_scenes.end())
			m_scenes[m_activeSceneName]->Uninitialize();

		m_activeSceneName = m_nextSceneName;//次のシーンをアクティブにする

		m_scenes[m_activeSceneName]->Initialize();//変更先のシーンを初期化する
	}
}
