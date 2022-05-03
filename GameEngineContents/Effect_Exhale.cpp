#include "Effect_Exhale.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_Exhale::Effect_Exhale()
	: AnimationRenderer_(nullptr)
{

}
Effect_Exhale::~Effect_Exhale()
{

}

void Effect_Exhale::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 140.f });


	AnimationRenderer_->CreateAnimation("Effect_Left.bmp", "Exhale_Left", 0, 5, 0.2f, false);
	AnimationRenderer_->CreateAnimation("Effect_Right.bmp", "Exhale_Right", 0, 5, 0.2f, false);

	AnimationName_ = "Exhale_";
	//ChangeDirText_ = "Left";
	//AnimationRenderer_->ChangeAnimation("Slide_Left");


	Death(0.8f);
}

void Effect_Exhale::Update()
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


