#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>

class BossRoomLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BossRoomLevel();
	~BossRoomLevel();

	// delete Function
	BossRoomLevel(const BossRoomLevel& _Other) = delete;
	BossRoomLevel(BossRoomLevel&& _Other) noexcept = delete;
	BossRoomLevel& operator=(const BossRoomLevel& _Other) = delete;
	BossRoomLevel& operator=(BossRoomLevel&& _Other) noexcept = delete;

	GameEngineSoundPlayer BgmPlayer;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

};
