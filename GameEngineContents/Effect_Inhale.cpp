#include "Effect_Inhale.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_Inhale::Effect_Inhale()
	: AnimationRenderer_(nullptr)
{

}
Effect_Inhale::~Effect_Inhale()
{

}

void Effect_Inhale::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 140.f });


	//AnimationRenderer_->CreateAnimation("Effect_RunToStop_Left.bmp", "RunToStop_Left", 0, 3, 0.25f, true);
	//AnimationRenderer_->CreateAnimation("Effect_RunToStop_Right.bmp", "RunToStop_Right", 0, 3, 0.25f, true);

	//AnimationName_ = "RunToStop_";
	////ChangeDirText_ = "Left";
	////AnimationRenderer_->ChangeAnimation("Slide_Left");


	//Death(1.2f);
}

void Effect_Inhale::Update()
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


