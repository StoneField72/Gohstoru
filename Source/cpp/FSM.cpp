
#include "FSM.h"

using namespace std;

FSM::FSM()
{
	stateMap.clear();
	currentState = 0;
}

FSM::~FSM()
{
	//mapコンテナの解放
	for (const auto& pair : stateMap)
		delete (pair.second);//登録されたStateのインスタンスを削除する

	stateMap.clear();
}

void FSM::SetCurrentState(const int id, GameObject* parent)
{
	currentState = id;
	stateMap[currentState]->OnEnter(parent);
}

void FSM::RegisterState(const int id, IState* state)
{
	stateMap[id] = state;
}

void FSM::Update(GameObject* parent)
{
	int ret = stateMap[currentState]->Update(parent);

	//状態のトランジション
	if (currentState != ret)
	{
		stateMap[currentState]->OnExit(parent);//現在のStateの終了処理
		stateMap[ret]->OnEnter(parent);//新しいStateの開始処理
		currentState = ret;//新しいStateを設定
	}
}
