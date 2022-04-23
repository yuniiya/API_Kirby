#include "WaddleDee.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>

WaddleDee::WaddleDee()
{

}
WaddleDee::~WaddleDee()
{

}

void WaddleDee::Start()
{
	AnimationRender = CreateRenderer();
	AnimationRender->SetPivotType(RenderPivot::BOT);
	AnimationRender->SetPivot({ 0.f, 140.f });

	// Waddle
	AnimationRender->CreateAnimation("WaddleDee_Left.bmp", "Waddle_Walk_Left", 0, 4, 0.5f, true);
	AnimationRender->CreateAnimation("WaddleDee_Left.bmp", "Waddle_Swallowed_Left", 8, 8, 0.5f, false);
	AnimationRender->CreateAnimation("WaddleDee_Left.bmp", "Waddle_Damaged_Left", 9, 9, 0.5f, false);

	// Waddle
	AnimationRender->CreateAnimation("WaddleDee_Right.bmp", "Waddle_Walk_Right", 0, 4, 0.5f, true);
	AnimationRender->CreateAnimation("WaddleDee_Right.bmp", "Waddle_Swallowed_Right", 5, 5, 0.5f, false);
	AnimationRender->CreateAnimation("WaddleDee_Right.bmp", "Waddle_Damaged_Right", 6, 6, 0.5f, false);

	AnimationName_ = "Walk_";
	AnimationRender->ChangeAnimation("Waddle_Walk_Left");
	//CurDir_ = MonsterDir::Left;

}

void WaddleDee::Update()
{
	DirAnimationCheck();
}

void WaddleDee::Render()
{
}