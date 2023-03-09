#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>

class Level_4 : public GameEngineLevel
{
public:
	// constrcuter destructer
	Level_4();
	~Level_4();

	// delete Function
	Level_4(const Level_4& _Other) = delete;
	Level_4(Level_4&& _Other) noexcept = delete;
	Level_4& operator=(const Level_4& _Other) = delete;
	Level_4& operator=(Level_4&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

};
