#pragma once


class GameSystem
{
public:
	GameSystem();
	virtual ~GameSystem();

	bool Initialize();
	void UnInitialize();

	void GameLoop();
};

