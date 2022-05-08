#include "Pengy.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include "Effect_MonsterDeath.h"
#include "Effect_IceBreath.h"

Pengy::Pengy()
	: Speed_(100.f)
	, DamagedTime_(0.8f)
	, AttackEndTime_(1.f)
	, IdleTime_(3.f)
{
	CurState_ = MonsterState::Max;
	MoveDir = float4::LEFT;
}

Pengy::~Pengy()
{

}

void Pengy::ChangeState(MonsterState _State)
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

void Pengy::MonsterStateUpdate()
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

void Pengy::DirCheck()
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

void Pengy::Start()
{
	// 히트 박스
	MonsterCollision = CreateCollision("PengyCol", { 70, 70 });


	AnimationRender = CreateRenderer();
	AnimationRender->SetPivotType(RenderPivot::CENTER);
	AnimationRender->SetPivot({ 0.f, 35.f });

	// Pengy - Left
	AnimationRender->CreateAnimation("Pengy_Left.bmp", "Idle_Left", 0, 0, 0.1f, false);
	AnimationRender->CreateAnimation("Pengy_Left.bmp", "Walk_Left", 1, 2, 0.1f, true);
	//AnimationRender->CreateAnimation("Pengy_Left.bmp", "Swallowed_Left", 7, 7, 0.1f, false);
	AnimationRender->CreateAnimation("Pengy_Left.bmp", "Attack_Left", 3, 5, 0.1f, false);
	AnimationRender->CreateAnimation("Pengy_Left.bmp", "Damaged_Left", 7, 7, 0.1f, false);

	// Pengy _ Right
	AnimationRender->CreateAnimation("Pengy_Right.bmp", "Idle_Right", 0, 0, 0.1f, false);
	AnimationRender->CreateAnimation("Pengy_Right.bmp", "Walk_Right", 1, 2, 0.1f, true);
	//AnimationRender->CreateAnimation("Pengy_Right.bmp", "Swallowed_Left", 7, 7, 0.1f, false);
	AnimationRender->CreateAnimation("Pengy_Right.bmp", "Attack_Right", 3, 5, 0.1f, false);
	AnimationRender->CreateAnimation("Pengy_Right.bmp", "Damaged_Right", 7, 7, 0.1f, false);

	AnimationName_ = "Idle_";
	ChangeDirText_ = "Left";
	ChangeState(MonsterState::Idle);
}

void Pengy::Update()
{
	ColMapUpdate();

	MonsterStateUpdate();
	DirCheck();

	MonsterColCheck();

	// 항상 땅에 붙어있도록 체크
	GroundPixelCheck();
}

void Pengy::Render()
{
}


void Pengy::IdleUpdate()
{
	IdleTime_ -= GameEngineTime::GetDeltaTime();


	if (IdleTime_ < 0)
	{

		// 일정거리 안으로 들어오면 Walk로 전환
		if (300.f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
		{
			ChangeState(MonsterState::Walk);
			return;
		}

		// 일정거리 안에서 더 가까워지면 Attack으로 전환
		if (170.f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
		{
			ChangeState(MonsterState::Attack);
			return;
		}
	}

}

void Pengy::WalkUpdate()
{
	// 일정거리 밖으로 벗어나면 다시 Idle로 전환 
	if (300.0f < std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
	{
		ChangeState(MonsterState::Idle);
		return;
	}

	// 일정거리 안에서 더 가까워지면 Attack으로 전환
	if (170.f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
	{
		ChangeState(MonsterState::Attack);
		return;
	}

	if (RGB(0, 0, 0) == BottomPixelColorCheck(30.f))
	{
		WallPixelCheck(30.f, Speed_);
	}
}

void Pengy::SwallowedUpdate()
{
	float4 PlayerPos = Player::MainPlayer->GetPosition();
	float4 MonsterPos = GetPosition();

	// 플레이어가 몬스터 왼쪽에 있다
	if (PlayerPos.x < MonsterPos.x)
	{
		MoveDir.x -= 3.f * GameEngineTime::GetDeltaTime();
	}
	else if (PlayerPos.x > MonsterPos.x)
	{
		// 몬스터 오른쪽에 있다
		MoveDir.x += 3.f * GameEngineTime::GetDeltaTime();
	}

	SetMove(MoveDir);
}

void Pengy::AttackUpdate()
{
	AttackEndTime_ -= GameEngineTime::GetDeltaTime();

	//if (AnimationRender->IsEndAnimation())
	//{
	//	AnimationRender->ChangeAnimation("Idle_" + ChangeDirText_);
	//}


	if (AttackEndTime_ < 0)
	{
		IceBreath_->Death();

		ChangeState(MonsterState::Idle);
		return;
	}
}

void Pengy::DamagedUpdate()
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
		ChangeState(MonsterState::Idle);
		return;
		/*Death();

		{
			GameEngineSound::SoundPlayOneShot("Damaged.wav");

			Effect_MonsterDeath* Effect = GetLevel()->CreateActor<Effect_MonsterDeath>((int)ORDER::EFFECT);
			Effect->SetPosition(GetPosition());
		}*/
	}
}

void Pengy::IdleStart()
{
	IdleTime_ = 3.f;

	MoveDir = float4::ZERO;

	AnimationName_ = "Idle_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Pengy::WalkStart()
{
	MoveDir = float4::ZERO;

	Speed_ = 50.0f;
	AnimationName_ = "Walk_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Pengy::SwallowedStart()
{
	//IceBreath_->Death();

	MoveDir = float4::ZERO;

	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Pengy::AttackStart()
{
	{
		IceBreath_ = GetLevel()->CreateActor<Effect_IceBreath>((int)ORDER::EFFECT);

		if (CurDir_ == MonsterDir::Right)
		{
			IceBreath_->SetPosition(GetPosition() + float4{ 165.f, 10.f });
			IceBreath_->SetDir(EffectDir::Right);

		}
		else if (CurDir_ == MonsterDir::Left)
		{
			IceBreath_->SetPosition(GetPosition() + float4{ -165.f, 10.f });
			IceBreath_->SetDir(EffectDir::Left);
		}
	}

	AttackEndTime_ = 1.5f;

	GameEngineSound::SoundPlayOneShot("IceBreath1.wav");

	AnimationName_ = "Attack_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Pengy::DamagedStart()
{
	MoveDir = float4::ZERO;

	GameEngineSound::SoundPlayOneShot("Damaged2.wav");

	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Pengy::WallPixelCheck(float _x, float _Speed)
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

void Pengy::MonsterColCheck()
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
		IceBreath_->Death();
		ChangeState(MonsterState::Damaged);
		return;
	}

	//{
	//	std::vector<GameEngineCollision*> ColList;

	//	if (true == MonsterCollision->CollisionResult("SlideCol", ColList, CollisionType::Rect, CollisionType::Rect))
	//	{

	//		ChangeState(MonsterState::Damaged);
	//		return;
	//	}
	//}
}