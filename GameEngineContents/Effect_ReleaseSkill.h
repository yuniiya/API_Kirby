#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_ReleaseSkill : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_ReleaseSkill();
	~Effect_ReleaseSkill();

	// delete Function
	Effect_ReleaseSkill(const Effect_ReleaseSkill& _Other) = delete;
	Effect_ReleaseSkill(Effect_ReleaseSkill&& _Other) noexcept = delete;
	Effect_ReleaseSkill& operator=(const Effect_ReleaseSkill& _Other) = delete;
	Effect_ReleaseSkill& operator=(Effect_ReleaseSkill&& _Other) noexcept = delete;

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