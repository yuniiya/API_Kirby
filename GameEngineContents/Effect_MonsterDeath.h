#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_MonsterDeath : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_MonsterDeath();
	~Effect_MonsterDeath();

	// delete Function
	Effect_MonsterDeath(const Effect_MonsterDeath& _Other) = delete;
	Effect_MonsterDeath(Effect_MonsterDeath&& _Other) noexcept = delete;
	Effect_MonsterDeath& operator=(const Effect_MonsterDeath& _Other) = delete;
	Effect_MonsterDeath& operator=(Effect_MonsterDeath&& _Other) noexcept = delete;

public:
	//PlayerDir CurDir_;
	EffectDir Dir_;


	std::string AnimationName_;
	std::string ChangeDirText_;

public:
	void SetDir(EffectDir _Dir)
	{
		Dir_ = _Dir;
	}

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;

};