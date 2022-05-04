#include "Effect_Attack.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_Attack::Effect_Attack()
	: AnimationRenderer_(nullptr)
{

}
Effect_Attack::~Effect_Attack()
{

}

void Effect_Attack::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 140.f });


	AnimationRenderer_->CreateAnimation("Effect.bmp", "Attack_", 6, 7, 0.2f, true);

	AnimationName_ = "Attack_";
	//ChangeDirText_ = "Left";
	//AnimationRenderer_->ChangeAnimation("Slide_Left");


	Death(1.2f);
}

void Effect_Attack::Update()
{
	AnimationRenderer_->ChangeAnimation(AnimationName_);

	//if (Dir_ == EffectDir::Right)
	//{
	//	ChangeDirText_ = "Right";
	//}
	//else if (Dir_ == EffectDir::Left)
	//{
	//	ChangeDirText_ = "Left";
	//}
	//AnimationRenderer_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}



