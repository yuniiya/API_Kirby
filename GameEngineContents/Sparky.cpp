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
	, JumpTime_(1.5f)
	, JumpDownTime_(0.6f)
	, HitCount_(2)
	, IsHit(false)
{
	CurState_ = MonsterState::Max;
	MoveDir = float4::LEFT;
}

Sparky::~Sparky()
{

}

void Sparky::Hit()
{
	IsHit = true;

	HitCount_ -= 1;
	
	if (HitCount_ < 0)
	{
		HitCount_ = 0;
	}
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
		case MonsterState::JumpDown:
			JumpDownStart();
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
	case MonsterState::JumpDown:
		JumpDownUpdate();
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
	AttackCollision = CreateCollision("SparkyAttackCol", { 130, 130});
	AttackCollision->Off();


	AnimationRender = CreateRenderer();
	AnimationRender->SetPivotType(RenderPivot::CENTER);
	AnimationRender->SetPivot({ 0.f, 35.f });

	// Sparky - Left
	//AnimationRender->CreateAnimation("Sparky_Attack.bmp", "Idle_Left", 0, 4, 0.1f, false);
	AnimationRender->CreateAnimation("Sparky_Left.bmp", "Idle_Left", 4, 5, 0.1f, true);
	AnimationRender->CreateAnimation("Sparky_Left.bmp", "Jump_Left", 0, 3, 0.4f, false);
	AnimationRender->CreateAnimation("Sparky_Left.bmp", "JumpDown_Left", 3, 3, 0.4f, false);
	AnimationRender->CreateAnimation("Sparky_Right.bmp", "Attack_Left", 4, 7, 0.05f, true);
	AnimationRender->CreateAnimation("Sparky_Left.bmp", "Damaged_Left", 9, 9, 0.1f, false);

	// Sparky - Right
	//AnimationRender->CreateAnimation("Sparky_Attack.bmp", "Idle_Right", 0, 4, 0.1f, false);
	AnimationRender->CreateAnimation("Sparky_Right.bmp", "Idle_Right", 4, 5, 0.1f, true);
	AnimationRender->CreateAnimation("Sparky_Right.bmp", "Jump_Right", 0, 3, 0.1f, false);
	AnimationRender->CreateAnimation("Sparky_Right.bmp", "JumpDown_Right", 3, 3, 0.1f, false);
	AnimationRender->CreateAnimation("Sparky_Right.bmp", "Attack_Right", 4, 7, 0.05f, true);
	AnimationRender->CreateAnimation("Sparky_Right.bmp", "Damaged_Right", 9, 9, 0.1f, false);

	AnimationName_ = "Idle_";
	ChangeDirText_ = "Left";
	ChangeState(MonsterState::Idle);
}

void Sparky::Update()
{
	ColMapUpdate();

	MonsterStateUpdate();

	MonsterColCheck();

	// 항상 땅에 붙어있도록 체크
	GroundPixelCheck();
}

void Sparky::Render()
{
}


void Sparky::IdleUpdate()
{
	DirCheck();

	// 일정거리 안으로 들어오면 Jump로 전환
	if (350.f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
	{
	/*	ChangeState(MonsterState::Jump);
		return;*/
		JumpDownTime_ -= GameEngineTime::GetDeltaTime();
		if (JumpDownTime_ < 0)
		{
			ChangeState(MonsterState::Jump);
			return;
		}
	
	}


	//AttReadyTime_ -=  GameEngineTime::GetDeltaTime();
	//// 공격 준비 
	//if (AttReadyTime_ < 0)
	//{
	//	ChangeState(MonsterState::Attack);
	//	return;
	//}
}

void Sparky::JumpUpdate()
{
	DirCheck();
	// 일정거리 밖으로 벗어나면 다시 Idle로 전환 
	//if (220.0f < std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
	//{
	//	JumpEffSound_.Stop();
	//	ChangeState(MonsterState::Idle);
	//	return;
	//}

	// 일정거리 가까워지면 Attack으로 전환
	if (130.f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
	{
		JumpEffSound_.Stop();
		ChangeState(MonsterState::Attack);
		return;
	}

	MoveDir.y = -350.f * GameEngineTime::GetDeltaTime();

	if (CurDir_ == MonsterDir::Left)
	{
		MoveDir.x = -0.3f;
	}
	else if(CurDir_ == MonsterDir::Right)
	{
		MoveDir.x = 0.3f;
	}

	SetMove(MoveDir);

	
	JumpTime_ -= GameEngineTime::GetDeltaTime();

	if (JumpTime_ < 0)
	{
		JumpEffSound_.Stop();
		ChangeState(MonsterState::JumpDown);
		return;
		
	}

	//SetMove(MoveDir);

	//if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	//{
	//	MoveDir = float4::ZERO;
	//	ChangeState(MonsterState::Idle);
	//	return;
	//}
}

void Sparky::JumpDownUpdate()
{
	MoveDir.y += 7.f * GameEngineTime::GetDeltaTime();

	if (CurDir_ == MonsterDir::Left)
	{
		MoveDir.x = -0.5f;
	}
	else if (CurDir_ == MonsterDir::Right)
	{
		MoveDir.x = 0.5f;
	}

	SetMove(MoveDir);

	if (RGB(0, 0, 0) == BottomPixelColorCheck(30.f))
	{
		ChangeState(MonsterState::Idle);
		return;
	}
}

void Sparky::SwallowedUpdate()
{
	DirCheck();
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

void Sparky::AttackUpdate()
{
	AttackTime_ -= GameEngineTime::GetDeltaTime();

	if (AttackTime_ < 0)
	{
		AttackEffSound_.Stop();
		ChangeState(MonsterState::Idle);
		return;
	}
}

void Sparky::DamagedUpdate()
{
	DirCheck();

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
		/*if (HitCount_ = 0)
		{
			Death();

			{
				GameEngineSound::SoundPlayOneShot("Damaged.wav");

				Effect_MonsterDeath* Effect = GetLevel()->CreateActor<Effect_MonsterDeath>((int)ORDER::EFFECT);
				Effect->SetPosition(GetPosition());
			}

		}*/
		
	}
}


void Sparky::IdleStart()
{
	MoveDir = float4::ZERO;

	AttReadyTime_ = 2.f;

	AnimationName_ = "Idle_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Sparky::JumpStart()
{
	JumpEffSound_.Stop();
	JumpEffSound_ = GameEngineSound::SoundPlayControl("Jump.wav");

	JumpTime_ = 0.6f;
	//Speed_ = 50.0f;
	AnimationName_ = "Jump_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Sparky::JumpDownStart()
{
	JumpDownTime_ = 1.5f;

	//Speed_ = 50.0f;
	AnimationName_ = "JumpDown_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Sparky::SwallowedStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Sparky::AttackStart()
{
	MoveDir = float4::ZERO;

	AttackEffSound_.Stop();
	AttackEffSound_ = GameEngineSound::SoundPlayControl("Spark2.wav");
	
	AttackCollision->On();

	AttackTime_ = 2.f;

	AnimationName_ = "Attack_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Sparky::DamagedStart()
{
	MoveDir = float4::ZERO;

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
			JumpEffSound_.Stop();
			AttackEffSound_.Stop();
			//AttackCollision->Off();

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
		//Hit();
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