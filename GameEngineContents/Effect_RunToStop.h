#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_RunToStop : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_RunToStop();
	~Effect_RunToStop();

	// delete Function
	Effect_RunToStop(const Effect_RunToStop& _Other) = delete;
	Effect_RunToStop(Effect_RunToStop&& _Other) noexcept = delete;
	Effect_RunToStop& operator=(const Effect_RunToStop& _Other) = delete;
	Effect_RunToStop& operator=(Effect_RunToStop&& _Other) noexcept = delete;

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