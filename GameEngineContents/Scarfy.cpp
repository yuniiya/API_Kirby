#include "Scarfy.h"
#include "Monster.h"
#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>


Scarfy::Scarfy()
	: Speed_(250.0f)
{
	CurState_ = MonsterState::Max;
	MoveDir = float4::LEFT;
}
Scarfy::~Scarfy()
{

}

void Scarfy::ChangeState(MonsterState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case MonsterState::Idle:
			IdleStart();
			break;
		case MonsterState::Jump:
			JumpStart();
			break;
		case MonsterState::Swallowed:
			SwallowedStart();
			break;
		case MonsterState::Damaged:
			DamagedStart();
			break;
		}
	}

	CurState_ = _State;
}

void Scarfy::MonsterStateUpdate()
{
	switch (CurState_)
	{
	case MonsterState::Idle:
		IdleUpdate();
		break;
	case MonsterState::Jump:
		JumpUpdate();
		break;
	case MonsterState::Swallowed:
		SwallowedUpdate();
		break;
	case MonsterState::Damaged:
		DamagedUpdate();
		break;
	}
}

void Scarfy::DirCheck()
{
	float4 PlayerPos = Player::MainPlayer->GetPosition();
	float4 MonsterPos = GetPosition();

	// 플레이어가 몬스터 왼쪽에 있다
	if (PlayerPos.x < MonsterPos.x)
	{
		CurDir_ = MonsterDir::Left;
		ChangeDirText_ = "Left";
	}
	else if (PlayerPos.x > MonsterPos.x)
	{
		// 몬스터 오른쪽에 있다
		CurDir_ = MonsterDir::Right;
		ChangeDirText_ = "Right";

	}

	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}


void Scarfy::Start()
{
	// 히트 박스
	MonsterCollision = CreateCollision("DefaultMonster", { 70, 70 });

	AnimationRender = CreateRenderer();
	AnimationRender->SetPivotType(RenderPivot::CENTER);
	AnimationRender->SetPivot({ 0.f, 35.f });

	// Scarfy - Left
	AnimationRender->CreateAnimation("Scarfy_Left.bmp", "Idle_Left", 0, 0, 0.2f, false);
	AnimationRender->CreateAnimation("Scarfy_Left.bmp", "Jump_Left", 1, 2, 0.2f, false);
	AnimationRender->CreateAnimation("Scarfy_Left.bmp", "Damaged_Left", 3, 3, 0.1f, false);

	// Scarfy - Right
	AnimationRender->CreateAnimation("Scarfy_Right.bmp", "Idle_Right", 0, 0, 0.2f, false);
	AnimationRender->CreateAnimation("Scarfy_Right.bmp", "Jump_Right", 1, 2, 0.2f, false);
	AnimationRender->CreateAnimation("Scarfy_Right.bmp", "Damaged_Right", 3, 3, 0.1f, false);

	AnimationName_ = "Idle_";
	ChangeDirText_ = "Left";
	ChangeState(MonsterState::Idle);
}

void Scarfy::Update()
{
	ColMapUpdate();

	//DirAnimationCheck();
	DirCheck();
	MonsterStateUpdate();
	MonsterColCheck();
}

void Scarfy::Render()
{
}

void Scarfy::IdleUpdate()
{
	MoveDir = float4::DOWN;
	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);

	// 바닥에 닿으면 Jump로 전환
	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
		if (0.38f <= GetAccTime())
		{
			ReSetAccTime();

			ChangeState(MonsterState::Jump);
			return;
		}
	}

	
}

void Scarfy::JumpUpdate()
{
	MoveDir = float4::UP;
	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);

	if (RGB(0, 0, 0) != BottomPixelColorCheck(50.f))
	{
		if (0.38f <= GetAccTime())
		{
			ReSetAccTime();

			ChangeState(MonsterState::Idle);
			return;
		}
	}
}


void Scarfy::SwallowedUpdate()
{
	float4 PlayerPos = Player::MainPlayer->GetPosition();
	float4 MonsterPos = GetPosition();

	// 플레이어가 몬스터 왼쪽에 있다
	if (PlayerPos.x < MonsterPos.x)
	{
		MoveDir.x -= 2.f * GameEngineTime::GetDeltaTime();
	}
	else if (PlayerPos.x > MonsterPos.x)
	{
		// 몬스터 오른쪽에 있다
		MoveDir.x += 2.f * GameEngineTime::GetDeltaTime();
	}

	SetMove(MoveDir);
}

void Scarfy::DamagedUpdate()
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

void Scarfy::IdleStart()
{
	MoveDir = float4::ZERO;

	//Speed_ = 50.0f;
	AnimationName_ = "Idle_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Scarfy::JumpStart()
{
	MoveDir = float4::ZERO;

	//Speed_ = 500.0f;
	AnimationName_ = "Jump_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Scarfy::SwallowedStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Scarfy::DamagedStart()
{
	MoveDir = float4::ZERO;
	DamagedTime_ = 0.8f;

	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Scarfy::MonsterColCheck()
{
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


	if (CurState_ == MonsterState::Swallowed)
	{
		if (5.0f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
		{
			Death();
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