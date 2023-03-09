#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_Inhale : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_Inhale();
	~Effect_Inhale();

	// delete Function
	Effect_Inhale(const Effect_Inhale& _Other) = delete;
	Effect_Inhale(Effect_Inhale&& _Other) noexcept = delete;
	Effect_Inhale& operator=(const Effect_Inhale& _Other) = delete;
	Effect_Inhale& operator=(Effect_Inhale&& _Other) noexcept = delete;

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