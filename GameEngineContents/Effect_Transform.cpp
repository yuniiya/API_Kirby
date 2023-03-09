#include "Effect_Transform.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_Transform::Effect_Transform()
	: AnimationRenderer_(nullptr)
{

}
Effect_Transform::~Effect_Transform()
{

}

void Effect_Transform::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 230.f });


	AnimationRenderer_->CreateAnimation("Effect_Transform.bmp", "Transform_", 0, 4, 0.06f, false);

	AnimationName_ = "Transform_";
	//ChangeDirText_ = "Left";
	//AnimationRenderer_->ChangeAnimation("Slide_Left");


}

void Effect_Transform::Update()
{
	AnimationRenderer_->ChangeAnimation(AnimationName_);

	if (AnimationRenderer_->IsEndAnimation())
	{
		Death();
	}

}



