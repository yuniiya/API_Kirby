#include "Metalun.h"
#include "Monster.h"
#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>
#include "Effect_MonsterDeath.h"

Metalun::Metalun()
	: Speed_(30.f)
	, DamagedTime_(0.8f)
{
	CurState_ = MonsterState::Max;
	MoveDir = float4::LEFT;
}

Metalun::~Metalun()
{

}

void Metalun::ChangeState(MonsterState _State)
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
		case MonsterState::Damaged:
			DamagedStart();
			break;
		}
	}

	CurState_ = _State;
}

void Metalun::MonsterStateUpdate()
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
	case MonsterState::Damaged:
		DamagedUpdate();
		break;
	}
}

void Metalun::DirCheck()
{
	// 처음 방향은 Left
	MonsterDir PrevDir_ = CurDir_;

	float4 PlayerPos = Player::MainPlayer->GetPosition();
	float4 MonsterPos = GetPosition();

	// 플레이어가 몬스터 왼쪽에 있다
	if (PlayerPos.x < MonsterPos.x)
	{
		PrevDir_ = MonsterDir::Left;
		ChangeDirText_ = "Left";
	}
	else if (PlayerPos.x > MonsterPos.x)
	{
		PrevDir_ = MonsterDir::Right;
		ChangeDirText_ = "Right";
	}

	// 방향이 달라졌다
	if (PrevDir_ != CurDir_)
	{
		AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
		CurDir_ = PrevDir_;
	}
}

void Metalun::Start()
{
	// 히트 박스
	MonsterCollision = CreateCollision("MetalunCol", { 70, 70 });


	AnimationRender = CreateRenderer();
	AnimationRender->SetPivotType(RenderPivot::CENTER);
	AnimationRender->SetPivot({ 0.f, 35.f });

	// Pengy - Left
	AnimationRender->CreateAnimation("Metalun_Left.bmp", "Idle_Left", 1, 2, 0.8f, true);
	AnimationRender->CreateAnimation("Metalun_Left.bmp", "Walk_Left", 8, 21, 0.8f, true);
	AnimationRender->CreateAnimation("Metalun_Left.bmp", "Damaged_Left", 22, 22, 0.1f, false);

	// Pengy _ Right
	AnimationRender->CreateAnimation("Metalun_Right.bmp", "Idle_Right", 1, 2, 0.8f, true);
	AnimationRender->CreateAnimation("Metalun_Right.bmp", "Walk_Right", 8, 21, 0.8f, true);
	AnimationRender->CreateAnimation("Metalun_Right.bmp", "Damaged_Right", 22, 22, 0.1f, false);

	AnimationName_ = "Idle_";
	ChangeDirText_ = "Left";
	ChangeState(MonsterState::Idle);
}

void Metalun::Update()
{
	ColMapUpdate();

	//DirAnimationCheck();
	MonsterStateUpdate();
	DirCheck();

	MonsterColCheck();

	// 항상 땅에 붙어있도록 체크
	GroundPixelCheck();
}

void Metalun::Render()
{
}


void Metalun::IdleUpdate()
{
	// 일정거리 안으로 들어오면 Walk로 전환
	if (300.f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
	{
		ChangeState(MonsterState::Walk);
		return;
	}
}

void Metalun::WalkUpdate()
{
	// 일정거리 밖으로 벗어나면 다시 Idle로 전환 
	if (300.0f < std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
	{
		ChangeState(MonsterState::Idle);
		return;
	}

	if (RGB(0, 0, 0) == BottomPixelColorCheck(30.f))
	{
		WallPixelCheck(30.f, Speed_);
	}
}

void Metalun::SwallowedUpdate()
{
	float4 PlayerPos = Player::MainPlayer->GetPosition();
	float4 MonsterPos = GetPosition();

	// 플레이어가 몬스터 왼쪽에 있다
	if (PlayerPos.x < MonsterPos.x)
	{
		MoveDir.x -= 0.02f * GameEngineTime::GetDeltaTime();
	}
	else if (PlayerPos.x > MonsterPos.x)
	{
		// 몬스터 오른쪽에 있다
		MoveDir.x += 0.02f * GameEngineTime::GetDeltaTime();
	}

	SetMove(MoveDir);
}

void Metalun::DamagedUpdate()
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
		//Death();

		{
			GameEngineSound::SoundPlayOneShot("Damaged.wav");

			Effect_MonsterDeath* Effect = GetLevel()->CreateActor<Effect_MonsterDeath>((int)ORDER::EFFECT);
			Effect->SetPosition(GetPosition());
		}
	}
}

void Metalun::IdleStart()
{
	AnimationName_ = "Idle_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Metalun::WalkStart()
{
	AnimationName_ = "Walk_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Metalun::SwallowedStart()
{
	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}


void Metalun::DamagedStart()
{
	GameEngineSound::SoundPlayOneShot("Damaged2.wav");

	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Metalun::WallPixelCheck(float _x, float _Speed)
{
	// 벽에 부딫히면 반대 방향으로 전환

	MonsterDir CheckDir_ = CurDir_;

	float4 LeftCheck = GetPosition() + float4{ -_x, 0.0f };
	float4 RightCheck = GetPosition() + float4{ _x, 0.0f };

	int LeftColor = MapColImage_->GetImagePixel(LeftCheck);
	int RightColor = MapColImage_->GetImagePixel(RightCheck);

	if (CurDir_ == MonsterDir::Left)
	{
		// 왼쪽이 벽이면 반대 방향으로 
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

void Metalun::MonsterColCheck()
{
	// 흡수에 닿았을 때 -> Swallowed
	std::vector<GameEngineCollision*> SwallowColList;

	if (true == MonsterCollision->CollisionResult("InhaleCol", SwallowColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < SwallowColList.size(); i++)
		{
			ChangeState(MonsterState::Swallowed);
			return;
		}
	}

	// 삼켜지고 있는 중이면 Death로 처리
	if (CurState_ == MonsterState::Swallowed)
	{
		if (15.0f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
		{
			Death();
		}
	}

	{
		std::vector<GameEngineCollision*> ColList;

		if (true == MonsterCollision->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			ChangeState(MonsterState::Damaged);
			return;
		}
	}

}
