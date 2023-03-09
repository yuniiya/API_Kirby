#pragma once
#include <GameEngine/GameEngineActor.h>

class MonsterHP : public GameEngineActor
{
public:
	static MonsterHP* MainBossHP;

	// constrcuter destructer
	MonsterHP();
	~MonsterHP();

	// delete Function
	MonsterHP(const MonsterHP& _Other) = delete;
	MonsterHP(MonsterHP&& _Other) noexcept = delete;
	MonsterHP& operator=(const MonsterHP& _Other) = delete;
	MonsterHP& operator=(MonsterHP&& _Other) noexcept = delete;

public:
	void SetHP(float _CurHP, float _MaxHP);

	static GameEngineRenderer* GetRenderer()
	{
		return MonsterHPBar;
	}
private:
	static GameEngineRenderer* MonsterHPBar;

protected:
	void Start() override;
	void Update() override;
};
