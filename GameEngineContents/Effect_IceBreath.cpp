#include "Effect_IceBreath.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_IceBreath::Effect_IceBreath()
	: AnimationRenderer_(nullptr)
{

}
Effect_IceBreath::~Effect_IceBreath()
{

}

void Effect_IceBreath::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 140.f });


	AnimationRenderer_->CreateAnimation("Effect_Ice_Left.bmp", "Ice_Left", 0, 18, 0.25f, true);
	AnimationRenderer_->CreateAnimation("Effect_Ice_Right.bmp", "Ice_Right", 0, 18, 0.25f, true);

	AnimationName_ = "RunToStop_";
	//ChangeDirText_ = "Left";
	//AnimationRenderer_->ChangeAnimation("Slide_Left");


	Death(1.2f);
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
