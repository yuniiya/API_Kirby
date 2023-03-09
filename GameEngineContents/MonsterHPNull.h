#pragma once
#include <GameEngine/GameEngineActor.h>

class MonsterHPNull : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterHPNull();
	~MonsterHPNull();

	// delete Function
	MonsterHPNull(const MonsterHPNull& _Other) = delete;
	MonsterHPNull(MonsterHPNull&& _Other) noexcept = delete;
	MonsterHPNull& operator=(const MonsterHPNull& _Other) = delete;
	MonsterHPNull& operator=(MonsterHPNull&& _Other) noexcept = delete;

public:
	GameEngineRenderer* MonsterHPBar;

protected:
	void Start() override;
	void Update() override;
};
