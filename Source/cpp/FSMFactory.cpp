
#include "FSMFactory.h"
#include "game_playerstate.h"
#include "game_enemystate.h"


FSM* FSMFactory::Create(const std::string& fsmType, GameObject* obj)
{
	FSM* fsm = nullptr;

	if (fsmType == "Player")
	{
		fsm = new FSM;
		fsm->RegisterState(PLAYER_STATE_IDLE, new PSIdle());
		fsm->RegisterState(PLAYER_STATE_WALK, new PSWalk());
		fsm->RegisterState(PLAYER_STATE_CAMERA, new PSCamera());
		fsm->RegisterState(PLAYER_STATE_CAMERA_WALK, new PSCameraWalk());
		fsm->RegisterState(PLAYER_STATE_SKILL, new PSSkill());
		fsm->SetCurrentState(PLAYER_STATE_IDLE, obj);	//‰ŠúState‚Ìİ’è
	}
	else if(fsmType == "Enemy")
	{
		fsm = new FSM;
		fsm->RegisterState(ENEMY_STATE_IDLE, new ESIdle());
		fsm->RegisterState(ENEMY_STATE_RUN, new ESRun());
		fsm->RegisterState(ENEMY_STATE_WANDERING, new ESWandering());
		fsm->RegisterState(ENEMY_STATE_SURPRISED, new ESSurprised());
		fsm->SetCurrentState(ENEMY_STATE_IDLE, obj);	//‰ŠúState‚Ìİ’è
	}

	return fsm;
}


