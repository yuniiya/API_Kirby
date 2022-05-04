#include "Effect_RunToStop.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_RunToStop::Effect_RunToStop()
	: AnimationRenderer_(nullptr)
{

}
Effect_RunToStop::~Effect_RunToStop()
{

}

void Effect_RunToStop::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 140.f });


	AnimationRenderer_->CreateAnimation("Effect_RunToStop_Left.bmp", "RunToStop_Left", 0, 3, 0.1f, false);
	AnimationRenderer_->CreateAnimation("Effect_RunToStop_Right.bmp", "RunToStop_Right", 0, 3, 0.1f, false);

	AnimationName_ = "RunToStop_";
	//ChangeDirText_ = "Left";
	//AnimationRenderer_->ChangeAnimation("Slide_Left");


	Death(0.4f);
}

void Effect_RunToStop::Update()
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

