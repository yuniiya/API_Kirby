#include "Effect_BossStar.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_BossStar::Effect_BossStar()
	: AnimationRenderer_(nullptr)
{

}
Effect_BossStar::~Effect_BossStar()
{

}

void Effect_BossStar::Start()
{
	AttackCollision_ = CreateCollision("BossStarCol", {70.f, 70.f});

	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 220.f });

	AnimationRenderer_->CreateAnimation("Effect_BossStar.bmp", "BossStar_", 23, 26, 0.15f, true);
	//AnimationRenderer_->CreateAnimation("Effect.bmp", "DoorStar_", 6, 7, 0.8f, true);

	AnimationName_ = "BossStar_";
}

void Effect_BossStar::Update()
{
	AnimationRenderer_->ChangeAnimation(AnimationName_);
}
