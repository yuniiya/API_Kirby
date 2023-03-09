#include "Effect_Slide.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_Slide::Effect_Slide()
	: AnimationRenderer_(nullptr)
	, Dir_(EffectDir::Right)
{

}
Effect_Slide::~Effect_Slide()
{

}

void Effect_Slide::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 140.f });


	AnimationRenderer_->CreateAnimation("Effect_Slide_Left.bmp", "Slide_Left", 0, 6, 0.1f, false);
	AnimationRenderer_->CreateAnimation("Effect_Slide_Right.bmp", "Slide_Right", 0, 6, 0.1f, false);

	AnimationName_ = "Slide_";
	//ChangeDirText_ = "Left";
	//AnimationRenderer_->ChangeAnimation("Slide_Left");
	

	Death(0.8f);
}

void Effect_Slide::Update()
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



