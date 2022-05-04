#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_Star : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_Star();
	~Effect_Star();

	// delete Function
	Effect_Star(const Effect_Star& _Other) = delete;
	Effect_Star(Effect_Star&& _Other) noexcept = delete;
	Effect_Star& operator=(const Effect_Star& _Other) = delete;
	Effect_Star& operator=(Effect_Star&& _Other) noexcept = delete;

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