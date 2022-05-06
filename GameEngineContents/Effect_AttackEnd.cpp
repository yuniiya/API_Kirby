#include "Effect_AttackEnd.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>

Effect_AttackEnd::Effect_AttackEnd()
	: AnimationRenderer_(nullptr)
	, AttackCollision_(nullptr)
	, MapColImage_(nullptr)
	, Dir_(EffectDir::Right)
{

}
Effect_AttackEnd::~Effect_AttackEnd()
{

}


void Effect_AttackEnd::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 220.f });

	AttackCollision_ = CreateCollision("AttackCol", { 70.f, 70.f }, {});


	AnimationRenderer_->CreateAnimation("Effect.bmp", "Attack_End", 15, 19, 0.08f, false);

	AnimationName_ = "Attack_End";

	//Death(1.f);
}

void Effect_AttackEnd::Update()
{
	AnimationRenderer_->ChangeAnimation(AnimationName_);

	if (AnimationRenderer_->IsEndAnimation())
	{
		Death();
	}

}



