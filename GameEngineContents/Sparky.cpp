#include "Sparky.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Effect_MonsterDeath.h"


Sparky::Sparky()
	: Speed_(80.f)
	, DamagedTime_(0.8f)
	, AttackTime_(3.f)
	, AttReadyTime_(2.f)
{
	CurState_ = MonsterState::Max;
	MoveDir = float4::LEFT;
}

Sparky::~Sparky()
{

}

void Sparky::ChangeState(MonsterState _State)
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

void Sparky::MonsterStateUpdate()
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
	case MonsterState::Attack:
		AttackUpdate();
		break;
	case MonsterState::Damaged:
		DamagedUpdate();
		break;
	}
}

void Sparky::DirCheck()
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

void Sparky::Start()
{
	// 히트 박스
	MonsterCollision = CreateCollision("SparkyCol", { 70, 70 });
	AttackCollision = CreateCollision("AttackCol", { 90, 90 });
	AttackCollision->Off();


	AnimationRender = CreateRenderer();
	AnimationRender->SetPivotType(RenderPivot::CENTER);
	AnimationRender->SetPivot({ 0.f, 35.f });

	// Sparky - Left
	//AnimationRender->CreateAnimation("Sparky_Attack.bmp", "Idle_Left", 0, 4, 0.1f, false);
	AnimationRender->CreateAnimation("Sparky_Left.bmp", "Idle_Left", 4, 5, 0.1f, true);
	AnimationRender->CreateAnimation("Sparky_Left.bmp", "Jump_Left", 0, 3, 0.1f, false);
	AnimationRender->CreateAnimation("Sparky_Right.bmp", "Attack_Left", 4, 7, 1.f, true);
	AnimationRender->CreateAnimation("Sparky_Left.bmp", "Damaged_Left", 9, 9, 0.1f, false);

	// Sparky - Right
	//AnimationRender->CreateAnimation("Sparky_Attack.bmp", "Idle_Right", 0, 4, 0.1f, false);
	AnimationRender->CreateAnimation("Sparky_Right.bmp", "Idle_Right", 4, 5, 0.1f, true);
	AnimationRender->CreateAnimation("Sparky_Right.bmp", "Jump_Right", 0, 3, 0.1f, false);
	AnimationRender->CreateAnimation("Sparky_Right.bmp", "Attack_Right", 4, 7, 0.05f, true);
	AnimationRender->CreateAnimation("Sparky_Right.bmp", "Damaged_Right", 9, 9, 0.1f, false);

	AnimationName_ = "Jump_";
	ChangeDirText_ = "Left";
	ChangeState(MonsterState::Jump);
}

void Sparky::Update()
{
	ColMapUpdate();

	MonsterStateUpdate();
	DirCheck();

	MonsterColCheck();

	// 항상 땅에 붙어있도록 체크
	GroundPixelCheck();
}

void Sparky::Render()
{
}


void Sparky::IdleUpdate()
{
	AttReadyTime_ -=  GameEngineTime::GetDeltaTime();
	// 공격 준비 
	if (AttReadyTime_ < 0)
	{
		ChangeState(MonsterState::Attack);
		return;
	}
}

void Sparky::JumpUpdate()
{
	// 처음에는 점프
	// 일정거리 가까워지면 Attack으로 전환
	if (150.f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
	{
		ChangeState(MonsterState::Idle);
		return;
	}
}

void Sparky::SwallowedUpdate()
{
	float4 PlayerPos = Player::MainPlayer->GetPosition();
	float4 MonsterPos = GetPosition();

	// 플레이어가 몬스터 왼쪽에 있다
	if (PlayerPos.x < MonsterPos.x)
	{
		MoveDir.x -= 0.05f * GameEngineTime::GetDeltaTime();
	}
	else if (PlayerPos.x > MonsterPos.x)
	{
		// 몬스터 오른쪽에 있다
		MoveDir.x += 0.05f * GameEngineTime::GetDeltaTime();
	}

	SetMove(MoveDir);
}

void Sparky::AttackUpdate()
{
	AttackTime_ -= GameEngineTime::GetDeltaTime();

	if (AttackTime_ < 0)
	{
		ChangeState(MonsterState::Jump);
		return;
	}
}

void Sparky::DamagedUpdate()
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
			//GameEngineSound::SoundPlayOneShot("Damaged.wav");

			Effect_MonsterDeath* Effect = GetLevel()->CreateActor<Effect_MonsterDeath>((int)ORDER::EFFECT);
			Effect->SetPosition(GetPosition());
		}
	}
}


void Sparky::IdleStart()
{
	AttReadyTime_ = 2.f;

	AnimationName_ = "Idle_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Sparky::JumpStart()
{
	Speed_ = 50.0f;
	AnimationName_ = "Jump_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Sparky::SwallowedStart()
{
	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Sparky::AttackStart()
{
	AttackCollision->On();

	AttackTime_ = 3.f;

	AnimationName_ = "Attack_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Sparky::DamagedStart()
{
	GameEngineSound::SoundPlayOneShot("Damaged2.wav");

	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Sparky::WallPixelCheck(float _x, float _Speed)
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

void Sparky::MonsterColCheck()
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
		if (10.0f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
		{
			Death();
		}
	}

	std::vector<GameEngineCollision*> ColList;

	if (true == MonsterCollision->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		ChangeState(MonsterState::Damaged);
		return;
	}
}