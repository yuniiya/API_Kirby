#include "Effect_MonsterDeath.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_MonsterDeath::Effect_MonsterDeath()
	: AnimationRenderer_(nullptr)
	, Dir_(EffectDir::Right)
{

}
Effect_MonsterDeath::~Effect_MonsterDeath()
{

}

void Effect_MonsterDeath::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 110.f });


	//AnimationRenderer_->CreateAnimation("Effect2.bmp", "Effect_1", 44, 44, 0.1f, false);
	AnimationRenderer_->CreateAnimation("Effect2.bmp", "Effect_2", 27, 30, 0.03f, false);

	AnimationName_ = "Effect_2";;
}

void Effect_MonsterDeath::Update()
{
	AnimationRenderer_->ChangeAnimation(AnimationName_);

	if (AnimationRenderer_->IsEndAnimation())
	{
		Death();
	}

	//	AnimationRenderer_->ChangeAnimation("Effect_2");

	//	if (AnimationRenderer_->IsEndAnimation())
	//	{
	//		Death();
	//	}
	//}

	

}
