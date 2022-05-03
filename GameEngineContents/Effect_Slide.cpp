#include "Effect_Slide.h"
#include "Player.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_Slide::Effect_Slide()
	: AnimationRenderer_(nullptr)
{

}
Effect_Slide::~Effect_Slide()
{

}

void Effect_Slide::DirAnimationCheck()
{

}

void Effect_Slide::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 140.f });


	AnimationRenderer_->CreateAnimation("Effect_Slide_Left.bmp", "Slide_Left", 0, 6, 0.25f, true);
	AnimationRenderer_->CreateAnimation("Effect_Slide_Right.bmp", "Slide_Right", 0, 6, 0.25f, true);


	AnimationRenderer_->ChangeAnimation("Slide_Left");
}

void Effect_Slide::Update()
{

}



