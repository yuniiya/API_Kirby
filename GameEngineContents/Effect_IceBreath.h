#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_IceBreath : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_IceBreath();
	~Effect_IceBreath();

	// delete Function
	Effect_IceBreath(const Effect_IceBreath& _Other) = delete;
	Effect_IceBreath(Effect_IceBreath&& _Other) noexcept = delete;
	Effect_IceBreath& operator=(const Effect_IceBreath& _Other) = delete;
	Effect_IceBreath& operator=(Effect_IceBreath&& _Other) noexcept = delete;

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