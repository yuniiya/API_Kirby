#include "Effect_DoorStar.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_DoorStar::Effect_DoorStar()
	: AnimationRenderer_(nullptr)
{

}
Effect_DoorStar::~Effect_DoorStar()
{

}

void Effect_DoorStar::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 220.f });

	AnimationRenderer_->CreateAnimation("Default_Att_Right.bmp", "DoorStar_", 23, 26, 0.15f, true);
	//AnimationRenderer_->CreateAnimation("Effect.bmp", "DoorStar_", 6, 7, 0.8f, true);

	AnimationName_ = "DoorStar_";
}

void Effect_DoorStar::Update()
{
	AnimationRenderer_->ChangeAnimation(AnimationName_);
}


