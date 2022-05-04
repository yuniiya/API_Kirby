#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_AttackEnd : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_AttackEnd();
	~Effect_AttackEnd();

	// delete Function
	Effect_AttackEnd(const Effect_AttackEnd& _Other) = delete;
	Effect_AttackEnd(Effect_AttackEnd&& _Other) noexcept = delete;
	Effect_AttackEnd& operator=(const Effect_AttackEnd& _Other) = delete;
	Effect_AttackEnd& operator=(Effect_AttackEnd&& _Other) noexcept = delete;

public:
	//PlayerDir CurDir_;
	EffectDir Dir_;

	float4 MoveDir;

	std::string AnimationName_;
	std::string ChangeDirText_;

	GameEngineCollision* AttackCollision_;

	GameEngineImage* MapColImage_;

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