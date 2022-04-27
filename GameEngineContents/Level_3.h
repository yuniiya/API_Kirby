#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>

class Level_3 : public GameEngineLevel
{
public:
	// constrcuter destructer
	Level_3();
	~Level_3();

	// delete Function
	Level_3(const Level_3& _Other) = delete;
	Level_3(Level_3&& _Other) noexcept = delete;
	Level_3& operator=(const Level_3& _Other) = delete;
	Level_3& operator=(Level_3&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

};
