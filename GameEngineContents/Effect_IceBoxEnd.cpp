#include "Effect_IceBoxEnd.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "GameEngineBase/GameEngineSound.h"

Effect_IceBoxEnd::Effect_IceBoxEnd()
	: AnimationRenderer_(nullptr)
{

}

Effect_IceBoxEnd::~Effect_IceBoxEnd()
{

}

void Effect_IceBoxEnd::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 220.f });

	AnimationRenderer_->CreateAnimation("Effect.bmp", "IceBoxEnd_", 51, 56, 0.08f, false);

	AnimationName_ = "IceBoxEnd_";

	GameEngineSound::SoundPlayOneShot("Attack.wav");
}

void Effect_IceBoxEnd::Update()
{
	AnimationRenderer_->ChangeAnimation(AnimationName_);

	if (AnimationRenderer_->IsEndAnimation())
	{
		Death();
	}
}
