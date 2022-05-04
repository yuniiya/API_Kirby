#include "Effect_Star.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>


Effect_Star::Effect_Star()
	: AnimationRenderer_(nullptr)
{

}
Effect_Star::~Effect_Star()
{

}

void Effect_Star::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 140.f });


	AnimationRenderer_->CreateAnimation("Effect2.bmp", "Star_", 8, 9, 0.2f, true);

	AnimationName_ = "Star_";
	//ChangeDirText_ = "Left";
	//AnimationRenderer_->ChangeAnimation("Slide_Left");


	Death(0.3f);
}

void Effect_Star::Update()
{
	AnimationRenderer_->ChangeAnimation(AnimationName_);

	MoveDir.y = -0.2f;

	SetMove(MoveDir);
}



