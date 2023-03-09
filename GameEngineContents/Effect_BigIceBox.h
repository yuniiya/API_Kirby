#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"
#include "IceKirby.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_BigIceBox : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_BigIceBox();
	~Effect_BigIceBox();

	// delete Function
	Effect_BigIceBox(const Effect_BigIceBox& _Other) = delete;
	Effect_BigIceBox(Effect_BigIceBox&& _Other) noexcept = delete;
	Effect_BigIceBox& operator=(const Effect_BigIceBox& _Other) = delete;
	Effect_BigIceBox& operator=(Effect_BigIceBox&& _Other) noexcept = delete;

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