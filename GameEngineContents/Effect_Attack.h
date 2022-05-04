#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_Attack : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_Attack();
	~Effect_Attack();

	// delete Function
	Effect_Attack(const Effect_Attack& _Other) = delete;
	Effect_Attack(Effect_Attack&& _Other) noexcept = delete;
	Effect_Attack& operator=(const Effect_Attack& _Other) = delete;
	Effect_Attack& operator=(Effect_Attack&& _Other) noexcept = delete;

public:
	//PlayerDir CurDir_;
	EffectDir Dir_;

	float4 MoveDir;

	std::string AnimationName_;
	std::string ChangeDirText_;

	GameEngineCollision* AttackCollision_;

	GameEngineImage* MapColImage_;

	void ColMapUpdate();

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