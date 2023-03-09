#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"
#include "IceKirby.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_Hammer : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_Hammer();
	~Effect_Hammer();

	// delete Function
	Effect_Hammer(const Effect_Hammer& _Other) = delete;
	Effect_Hammer(Effect_Hammer&& _Other) noexcept = delete;
	Effect_Hammer& operator=(const Effect_Hammer& _Other) = delete;
	Effect_Hammer& operator=(Effect_Hammer&& _Other) noexcept = delete;

public:
	//PlayerDir CurDir_;
	EffectDir Dir_;
	float4 MoveDir;

	float IceTime_;

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