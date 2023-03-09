#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"
#include "IceKirby.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_IceBox : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_IceBox();
	~Effect_IceBox();

	// delete Function
	Effect_IceBox(const Effect_IceBox& _Other) = delete;
	Effect_IceBox(Effect_IceBox&& _Other) noexcept = delete;
	Effect_IceBox& operator=(const Effect_IceBox& _Other) = delete;
	Effect_IceBox& operator=(Effect_IceBox&& _Other) noexcept = delete;

public:
	//PlayerDir CurDir_;
	EffectDir Dir_;
	float4 MoveDir;

	float IceTime_;

	std::string AnimationName_;
	std::string ChangeDirText_;

	bool IsSlide;
	bool IsCrack;
	bool IsSlideSound;

public:
	void SetDir(EffectDir _Dir)
	{
		Dir_ = _Dir;
	}

	void SlideOn();
	void CrackOn();

	void PlaySlideSound();

protected:
	GameEngineCollision* IceCollision_;
	GameEngineImage* MapColImage_;

protected:
	void CollisionCheck();
	void ColMapUpdate();

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;
};