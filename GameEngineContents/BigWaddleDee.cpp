#include "BigWaddleDee.h"
#include "Monster.h"
#include "Player.h"
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
	MonsterColCheck();

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
	float4 PlayerPos = Player::MainPlayer->GetPosition();
	float4 MonsterPos = GetPosition();

	// 플레이어가 몬스터 왼쪽에 있다
	if (PlayerPos.x < MonsterPos.x)
	{
		MoveDir.x -= 1.5f * GameEngineTime::GetDeltaTime();
	}
	else if (PlayerPos.x > MonsterPos.x)
	{
		// 몬스터 오른쪽에 있다
		MoveDir.x += 1.5f * GameEngineTime::GetDeltaTime();
	}

	SetMove(MoveDir);
}

void BigWaddleDee::DamagedUpdate()
{
	float4 PlayerPos = Player::MainPlayer->GetPosition();
	float4 MonsterPos = GetPosition();

	// 플레이어가 몬스터 왼쪽에 있다
	if (PlayerPos.x < MonsterPos.x)
	{
		MoveDir.x = 0.3f;
	}
	else if (PlayerPos.x > MonsterPos.x)
	{
		// 몬스터 오른쪽에 있다
		MoveDir.x = -0.3f;
	}

	SetMove(MoveDir);

	DamagedTime_ -= GameEngineTime::GetDeltaTime();

	if (DamagedTime_ < 0)
	{
		Death();
	}
}

void BigWaddleDee::WalkStart()
{
	Speed_ = 50.0f;
	AnimationName_ = "Walk_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void BigWaddleDee::SwallowedStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "Swallowed_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void BigWaddleDee::DamagedStart()
{
	DamagedTime_ = 0.8f;

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

void BigWaddleDee::MonsterColCheck()
{

	if (CurState_ == MonsterState::Swallowed)
	{
		if (10.0f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
		{
			Death();
		}
	}

	std::vector<GameEngineCollision*> SwallowColList;

	if (true == MonsterCollision->CollisionResult("InhaleCol", SwallowColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < SwallowColList.size(); i++)
		{
			// (엑터 제외한) 콜리전만 파괴 

			ChangeState(MonsterState::Swallowed);
			return;
		}
	}


	std::vector<GameEngineCollision*> ColList;

	if (true == MonsterCollision->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		//for (size_t i = 0; i < ColList.size(); i++)
		//{
		//	// (엑터 제외한) 콜리전만 파괴 
		//	ColList[i]->GetActor()->Death();
		//}

		ChangeState(MonsterState::Damaged);
		return;
	}


}
