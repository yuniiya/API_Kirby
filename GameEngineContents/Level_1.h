#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>
//#include "PlayLevel.h"

class Player;
class Level_1 : public GameEngineLevel
{
public:
	// constrcuter destructer
	Level_1();
	~Level_1();

	// delete Function
	Level_1(const Level_1& _Other) = delete;
	Level_1(Level_1&& _Other) noexcept = delete;
	Level_1& operator=(const Level_1& _Other) = delete;
	Level_1& operator=(Level_1&& _Other) noexcept = delete;

	float SoundTime;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	//Player* Kirby;
	Player* MainPlayer;
	

};
