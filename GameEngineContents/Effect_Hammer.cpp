#include "Effect_Hammer.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "GameEngine//GameEngineCollision.h"

Effect_Hammer::Effect_Hammer()
	: AnimationRenderer_(nullptr)
	, Dir_(EffectDir::Right)
{

}
Effect_Hammer::~Effect_Hammer()
{

}

void Effect_Hammer::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::CENTER);
	AnimationRenderer_->SetPivot({ 0.f, 10.f });


	AnimationRenderer_->CreateAnimation("Effect_Boss_Left.bmp", "Swing_Left", 0, 0, 0.03f, false);
	AnimationRenderer_->CreateAnimation("Effect_Boss_Left.bmp", "Scream_Left", 1, 1, 0.03f, false);
	AnimationRenderer_->CreateAnimation("Effect_Boss_Left.bmp", "Attack_Left", 11, 12, 0.03f, false);
	AnimationRenderer_->CreateAnimation("Effect_Boss_Left.bmp", "Default_Left", 11, 11, 0.03f, false);

	AnimationRenderer_->CreateAnimation("Effect_Boss_Right.bmp", "Swing_Right", 0, 0, 0.03f, false);
	AnimationRenderer_->CreateAnimation("Effect_Boss_Right.bmp", "Scream_Right", 1, 1, 0.03f, false);
	AnimationRenderer_->CreateAnimation("Effect_Boss_Right.bmp", "Attack_Right", 11, 12, 0.03f, false);
	AnimationRenderer_->CreateAnimation("Effect_Boss_Right.bmp", "Default_Right", 11, 11, 0.03f, false);


	AnimationName_ = "Scream_";
	//ChangeDirText_ = "Left";
	//AnimationRenderer_->ChangeAnimation("Slide_Left");


	Death(1.2f);
}

void Effect_Hammer::Update()
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



