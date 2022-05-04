#include "Effect_IceBox.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_IceBox::Effect_IceBox()
	: AnimationRenderer_(nullptr)
{

}

Effect_IceBox::~Effect_IceBox()
{

}

void Effect_IceBox::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 140.f });


	AnimationRenderer_->CreateAnimation("Effect.bmp", "IceBox_", 51, 53, 0.1f, false);

	AnimationName_ = "IceBox_";
	//ChangeDirText_ = "Left";
	//AnimationRenderer_->ChangeAnimation("Slide_Left");


	Death(0.8f);
}

void Effect_IceBox::Update()
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


