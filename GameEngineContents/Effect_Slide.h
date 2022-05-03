#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_Slide : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_Slide();
	~Effect_Slide();

	// delete Function
	Effect_Slide(const Effect_Slide& _Other) = delete;
	Effect_Slide(Effect_Slide&& _Other) noexcept = delete;
	Effect_Slide& operator=(const Effect_Slide& _Other) = delete;
	Effect_Slide& operator=(Effect_Slide&& _Other) noexcept = delete;

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