#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_Exhale : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_Exhale();
	~Effect_Exhale();

	// delete Function
	Effect_Exhale(const Effect_Exhale& _Other) = delete;
	Effect_Exhale(Effect_Exhale&& _Other) noexcept = delete;
	Effect_Exhale& operator=(const Effect_Exhale& _Other) = delete;
	Effect_Exhale& operator=(Effect_Exhale&& _Other) noexcept = delete;

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