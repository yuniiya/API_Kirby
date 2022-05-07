#include "Effect_IceBreath.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "GameEngine//GameEngineCollision.h"

Effect_IceBreath::Effect_IceBreath()
	: AnimationRenderer_(nullptr)
	, AttackCollision_(nullptr)
	, Dir_(EffectDir::Right)
{

}
Effect_IceBreath::~Effect_IceBreath()
{

}

void Effect_IceBreath::Start()
{
	AttackCollision_ = CreateCollision("IceBreathCol",{170.f, 70.f}, {40.f, -10.f});

	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 210.f });


	AnimationRenderer_->CreateAnimation("Effect_Ice_Left.bmp", "IceBreath_Left", 0, 18, 0.03f, true);
	AnimationRenderer_->CreateAnimation("Effect_Ice_Right.bmp", "IceBreath_Right", 0, 18, 0.03f, true);

	AnimationName_ = "IceBreath_";
	//ChangeDirText_ = "Left";
	//AnimationRenderer_->ChangeAnimation("Slide_Left");


	//Death(1.2f);
}

void Effect_IceBreath::Update()
{
	if (Dir_ == EffectDir::Right)
	{
		ChangeDirText_ = "Right";
	}
	else if (Dir_ == EffectDir::Left)
	{
		ChangeDirText_ = "Left";
	}
	AnimationRenderer_->ChangeAnimation(AnimationName_ + ChangeDirText_);

}
