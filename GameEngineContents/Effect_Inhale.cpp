#include "Effect_Inhale.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_Inhale::Effect_Inhale()
	: AnimationRenderer_(nullptr)
	, Dir_(EffectDir::Right)
{

}
Effect_Inhale::~Effect_Inhale()
{

}

void Effect_Inhale::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 180.f });


	AnimationRenderer_->CreateAnimation("Effect_Inhale_Left.bmp", "Inhale_Left", 0, 1, 0.2f, true);
	AnimationRenderer_->CreateAnimation("Effect_Inhale_Right.bmp", "Inhale_Right", 0, 1, 0.2f, true);

	AnimationName_ = "Inhale_";
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


