#include "BigWaddleDee.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>

BigWaddleDee::BigWaddleDee()
{
	CurState_ = MonsterState::Max;
	MoveDir = float4::LEFT;
}
BigWaddleDee::~BigWaddleDee()
{

}

void BigWaddleDee::ChangeState(MonsterState _State)
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
		case MonsterState::Swallowed:
			SwallowedStart();
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

void BigWaddleDee::MonsterStateUpdate()
{
	switch (CurState_)
	{
	case MonsterState::Idle:
		IdleUpdate();
		break;
	case MonsterState::Walk:
		WalkUpdate();
		break;
	case MonsterState::Swallowed:
		SwallowedUpdate();
		break;
	case MonsterState::Attack:
		AttackUpdate();
		break;
	case MonsterState::Damaged:
		DamagedUpdate();
		break;
	}
}

void BigWaddleDee::Start()
{
	// 히트 박스
	MonsterCollision = CreateCollision("BigWaddleHitBox", { 110, 110 });

	AnimationRender = CreateRenderer();
	AnimationRender->SetPivotType(RenderPivot::CENTER);
	AnimationRender->SetPivot({ 0.f, 35.f });

	// Big Waddle - Left
	MonsterAnimationRenderer->CreateAnimation("BigWaddleDee_Right.bmp", "Walk_Right", 0, 4, 0.8f, true);
	MonsterAnimationRenderer->CreateAnimation("BigWaddleDee_Right.bmp", "Swallowed_Right", 5, 5, 0.8f, false);
	MonsterAnimationRenderer->CreateAnimation("BigWaddleDee_Right.bmp", "Damaged_Right", 6, 6, 0.8f, false);

	// Big Waddle - Right
	MonsterAnimationRenderer->CreateAnimation("BigWaddleDee_Right.bmp", "Walk_Right", 0, 4, 0.8f, true);
	MonsterAnimationRenderer->CreateAnimation("BigWaddleDee_Right.bmp", "Swallowed_Right", 8, 8, 0.8f, false);
	MonsterAnimationRenderer->CreateAnimation("BigWaddleDee_Right.bmp", "Damaged_Right", 9, 9, 0.8f, false);


	AnimationName_ = "Walk_";
	ChangeDirText_ = "Left";
	ChangeState(MonsterState::Walk);
}

void BigWaddleDee::Update()
{
	ColMapUpdate();

	DirAnimationCheck();
	MonsterStateUpdate();

	// 항상 땅에 붙어있도록 체크
	GroundPixelCheck();
}

void BigWaddleDee::Render()
{
}

void BigWaddleDee::WalkUpdate()
{
}

void BigWaddleDee::SwallowedUpdate()
{
}

void BigWaddleDee::DamagedUpdate()
{
}

void BigWaddleDee::WalkStart()
{
	Speed_ = 10.0f;
	AnimationName_ = "Walk_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void BigWaddleDee::SwallowedStart()
{
	AnimationName_ = "Swallowed_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void BigWaddleDee::DamagedStart()
{
	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}
