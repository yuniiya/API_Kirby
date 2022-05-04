#include "Effect_AttackEnd.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_AttackEnd::Effect_AttackEnd()
	: AnimationRenderer_(nullptr)
{

}
Effect_AttackEnd::~Effect_AttackEnd()
{

}

void Effect_AttackEnd::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 140.f });


	AnimationRenderer_->CreateAnimation("Effect.bmp", "AttackEnd_", 15, 19, 0.1f, false);

	AnimationName_ = "AttackEnd_";
	//ChangeDirText_ = "Left";
	//AnimationRenderer_->ChangeAnimation("Slide_Left");


	Death(0.8f);
}

void Effect_AttackEnd::Update()
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



