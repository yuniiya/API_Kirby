#include "BigWaddleDee.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>

BigWaddleDee::BigWaddleDee()
	: Speed_(50.f)
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
	MonsterCollision = CreateCollision("DefaultMonster", { 110, 110 });

	AnimationRender = CreateRenderer();
	AnimationRender->SetPivotType(RenderPivot::CENTER);
	AnimationRender->SetPivot({ 0.f, 35.f });

	// Big Waddle - Left
	AnimationRender->CreateAnimation("BigWaddleDee_Left.bmp", "Walk_Left", 0, 4, 0.2f, true);
	AnimationRender->CreateAnimation("BigWaddleDee_Left.bmp", "Swallowed_Left", 5, 5, 0.2f, false);
	AnimationRender->CreateAnimation("BigWaddleDee_Left.bmp", "Damaged_Left", 6, 6, 0.2f, false);

	// Big Waddle - Right
	AnimationRender->CreateAnimation("BigWaddleDee_Right.bmp", "Walk_Right", 0, 4, 0.2f, true);
	AnimationRender->CreateAnimation("BigWaddleDee_Right.bmp", "Swallowed_Right", 8, 8, 0.2f, false);
	AnimationRender->CreateAnimation("BigWaddleDee_Right.bmp", "Damaged_Right", 9, 9, 0.2f, false);


	AnimationName_ = "Walk_";
	ChangeDirText_ = "Left";
	ChangeState(MonsterState::Walk);
}

void BigWaddleDee::Update()
{
	ColMapUpdate();

	//DirAnimationCheck();
	MonsterStateUpdate();

	// 항상 땅에 붙어있도록 체크
	GroundPixelCheck();
}

void BigWaddleDee::Render()
{
}

void BigWaddleDee::WalkUpdate()
{
	if (RGB(0, 0, 0) == BottomPixelColorCheck(30.f))
	{
		WallPixelCheck(30.f, Speed_);
	}
}

void BigWaddleDee::SwallowedUpdate()
{
}

void BigWaddleDee::DamagedUpdate()
{
}

void BigWaddleDee::WalkStart()
{
	Speed_ = 50.0f;
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


void BigWaddleDee::WallPixelCheck(float _x, float _Speed)
{
	// 벽에 부딫히면 반대 방향으로 전환

	MonsterDir CheckDir_ = CurDir_;

	float4 LeftCheck = GetPosition() + float4{ -_x, 0.0f };
	float4 RightCheck = GetPosition() + float4{ _x, 0.0f };

	int LeftColor = MapColImage_->GetImagePixel(LeftCheck);
	int RightColor = MapColImage_->GetImagePixel(RightCheck);

	if (CurDir_ == MonsterDir::Left)
	{
		if (RGB(0, 0, 0) == LeftColor)
		{
			CurDir_ = MonsterDir::Right;
			ChangeDirText_ = "Right";
			AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
			MoveDir.x = 1.f;
		}
		else
		{
			MoveDir.x = -1.f;
		}
	}


	if (CurDir_ == MonsterDir::Right)
	{

		if (RGB(0, 0, 0) == RightColor)
		{
			CurDir_ = MonsterDir::Left;
			ChangeDirText_ = "Left";
			AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
			MoveDir.x = -1.f;
		}
		else
		{
			MoveDir.x = 1.f;
		}
	}

	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * _Speed);
}
