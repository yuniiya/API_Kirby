#include "BigWaddleDee.h"
#include "Monster.h"
#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>
#include "Effect_MonsterDeath.h"
#include "Effect_BigIceBox.h"

BigWaddleDee::BigWaddleDee()
	: AnimationRender(nullptr)
	, MonsterCollision(nullptr)
	, Speed_(50.f)
	, DamagedTime_(0.8f)
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
		case MonsterState::DamagedByMetal:
			DamagedByMetalStart();
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
	case MonsterState::DamagedByMetal:
		DamagedByMetalUpdate();
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
		{
			GameEngineSound::SoundPlayOneShot("Damaged.wav");

			Effect_MonsterDeath* Effect = GetLevel()->CreateActor<Effect_MonsterDeath>((int)ORDER::EFFECT);
			Effect->SetPosition(GetPosition());
		}
	}
}

void BigWaddleDee::DamagedByMetalUpdate()
{
	DamagedUpdate();
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

void BigWaddleDee::DamagedByMetalStart()
{
	DamagedTime_ = 0.8f;

	GameEngineSound::SoundPlayOneShot("Damaged2.wav");

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
	// 흡수에 닿았을 때 -> Swallowed
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

	// 삼켜지고 있는 중이면 Death로 처리
	if (CurState_ == MonsterState::Swallowed)
	{
		if (20.0f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
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

	// 메탈 
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == MonsterCollision->CollisionResult("MetalCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			ChangeState(MonsterState::DamagedByMetal);
			return;
		}
	}

	// 디폴트 플레이어 공격
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == MonsterCollision->CollisionResult("AttackCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			ChangeState(MonsterState::Damaged);
			return;
		}
	}

	// 아이스 커비 공격
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == MonsterCollision->CollisionResult("IceBreathCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			Death();

			Effect_BigIceBox* Effect = GetLevel()->CreateActor<Effect_BigIceBox>((int)ORDER::EFFECT);
			Effect->SetPosition(GetPosition());
		}
	}

	// 얼음 콜리전
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == MonsterCollision->CollisionResult("IceBoxCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			ChangeState(MonsterState::Damaged);
			return;
		}
	}

	// 스파크 커비 공격
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == MonsterCollision->CollisionResult("SparkAttackCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{

			ChangeState(MonsterState::Damaged);
			return;
		}
	}
}
