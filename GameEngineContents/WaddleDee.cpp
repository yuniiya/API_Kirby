#include "WaddleDee.h"
#include "Monster.h"
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

void WaddleDee::ChangeState(MonsterState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case MonsterState::Idle:
			IdleStart();
			break;
		case MonsterState::Walk:
			WalkStart();
			break;
		case MonsterState::Attack:
			AttackStart();
			break;
		case MonsterState::Damaged:
			DamagedStart();
			break;
		}
	}

	CurState_ = _State;
}

void WaddleDee::MonsterStateUpdate()
{
	switch (CurState_)
	{
	case MonsterState::Idle:
		IdleUpdate();
		break;
	case MonsterState::Walk:
		WalkUpdate();
		break;
	case MonsterState::Attack:
		AttackUpdate();
		break;
	case MonsterState::Damaged:
		DamagedUpdate();
		break;
	}
}

void WaddleDee::Start()
{
	//// 히트 박스

	AnimationRender = CreateRenderer();
	AnimationRender->SetPivotType(RenderPivot::BOT);
	AnimationRender->SetPivot({ 0.f, 140.f });

	// Waddle - Left
	AnimationRender->CreateAnimation("WaddleDee_Left.bmp", "Waddle_Walk_Left", 0, 4, 0.2f, true);
	AnimationRender->CreateAnimation("WaddleDee_Left.bmp", "Waddle_Swallowed_Left", 8, 8, 0.5f, false);
	AnimationRender->CreateAnimation("WaddleDee_Left.bmp", "Waddle_Damaged_Left", 9, 9, 0.5f, false);

	// Waddle - Right
	AnimationRender->CreateAnimation("WaddleDee_Right.bmp", "Waddle_Walk_Right", 0, 4, 0.2f, true);
	AnimationRender->CreateAnimation("WaddleDee_Right.bmp", "Waddle_Swallowed_Right", 5, 5, 0.5f, false);
	AnimationRender->CreateAnimation("WaddleDee_Right.bmp", "Waddle_Damaged_Right", 6, 6, 0.5f, false);

	AnimationName_ = "Walk_";
	AnimationRender->ChangeAnimation("Waddle_Walk_Left");
	CurState_ = MonsterState::Walk;
}

void WaddleDee::Update()
{
	ColMapUpdate();

	

	DirAnimationCheck();
	MonsterStateUpdate();
}

void WaddleDee::Render()
{
}

void WaddleDee::WalkUpdate()
{
	StagePixelCheck(Speed_);
	MovePixelCheck();
	WallPixelCheck(-80.f, 80.f);

	if (CurDir_ == MonsterDir::Left)
	{
		MoveDir = float4::LEFT;
		//SetMove(MoveDir);
		
	}
	else if (CurDir_ == MonsterDir::Right)
	{
		MoveDir = float4::RIGHT;
		//SetMove(MoveDir);
		//WallPixelCheck(20.f, 20.f);
	}

	

}

void WaddleDee::DamagedUpdate()
{
}

void WaddleDee::WalkStart()
{
	Speed_ = 10.0f;

	AnimationName_ = "Walk_";
	MonsterAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void WaddleDee::DamagedStart()
{
	AnimationName_ = "Damaged";
	MonsterAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText_);
}