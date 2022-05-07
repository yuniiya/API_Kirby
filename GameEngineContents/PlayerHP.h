#pragma once
#include <GameEngine/GameEngineActor.h>

class PlayerHP : public GameEngineActor
{
public:
	static PlayerHP* MainHP;

	// constrcuter destructer
	PlayerHP();
	~PlayerHP();

	// delete Function
	PlayerHP(const PlayerHP& _Other) = delete;
	PlayerHP(PlayerHP&& _Other) noexcept = delete;
	PlayerHP& operator=(const PlayerHP& _Other) = delete;
	PlayerHP& operator=(PlayerHP&& _Other) noexcept = delete;

public:
	GameEngineRenderer* PlayerHPBar;

protected:
	void Start() override;
	void Update() override;
};
