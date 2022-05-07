#pragma once
#include <GameEngine/GameEngineActor.h>

class MonsterHP : public GameEngineActor
{
public:

	// constrcuter destructer
	MonsterHP();
	~MonsterHP();

	// delete Function
	MonsterHP(const MonsterHP& _Other) = delete;
	MonsterHP(MonsterHP&& _Other) noexcept = delete;
	MonsterHP& operator=(const MonsterHP& _Other) = delete;
	MonsterHP& operator=(MonsterHP&& _Other) noexcept = delete;

public:
	GameEngineRenderer* MonsterHPBar;

protected:
	void Start() override;
	void Update() override;
};
