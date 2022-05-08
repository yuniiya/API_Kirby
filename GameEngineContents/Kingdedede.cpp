#include "Kingdedede.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>
#include "Effect_BossStar.h"
#include "Player.h"
#include "WaddleDee.h"

Kingdedede::Kingdedede()
	: Speed_(100.f)
	, IdleTime_(2.f)
	, DamagedTime_(1.5f)
	, JumpTime_(1.3f)
	, ScreamTime_(1.f)
	, CurDir_(MonsterDir::Left)
{
	CurState_ = MonsterState::Max;
	MoveDir = float4::LEFT;
}

Kingdedede::~Kingdedede()
{

}

void Kingdedede::ChangeState(MonsterState _State)
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
		case MonsterState::Jump:
			JumpStart();
			break;
		case MonsterState::JumpDown:
			JumpDownStart();
			break;
		case MonsterState::Scream:
			ScreamStart();
			break;
		case MonsterState::Attack:
			AttackStart();
			break;
		case MonsterState::Damaged:
			DamagedStart();
			break;
		case MonsterState::Dead:
			DeadStart();
			break;
		}
	}

	CurState_ = _State;
}

void Kingdedede::MonsterStateUpdate()
{
	switch (CurState_)
	{
	case MonsterState::Idle:
		IdleUpdate();
		break;
	case MonsterState::Walk:
		WalkUpdate();
		break;
	case MonsterState::Jump:
		JumpUpdate();
		break;
	case MonsterState::JumpDown:
		JumpDownUpdate();
		break;
	case MonsterState::Scream:
		ScreamUpdate();
		break;
	case MonsterState::Attack:
		AttackUpdate();
		break;
	case MonsterState::Damaged:
		DamagedUpdate();
		break;
	case MonsterState::Dead:
		DeadUpdate();
		break;
	}
}

void Kingdedede::DirCheck()
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

void Kingdedede::Start()
{
	// 히트 박스
	MonsterCollision = CreateCollision("BossHitBox", { 200, 200 }, {0.f, -40.f});


	AnimationRender = CreateRenderer();
	AnimationRender->SetPivotType(RenderPivot::CENTER);
	AnimationRender->SetPivot({ 0.f, 55.f });

	// Boss - Left
	AnimationRender->CreateAnimation("King_Left.bmp", "Idle_Left", 0, 3, 0.2f, true);
	AnimationRender->CreateAnimation("King_Left.bmp", "Walk_Left", 4, 7, 0.3f, true);
	AnimationRender->CreateAnimation("King_Jump_Left.bmp", "Jump_Left", 8, 9, 0.5f, false);
	AnimationRender->CreateAnimation("King_Jump_Left.bmp", "JumpDown_Left", 10, 10, 0.3f, false);
	AnimationRender->CreateAnimation("King_Left.bmp", "Scream_Left", 21, 22, 0.3f, true);
	AnimationRender->CreateAnimation("King_Left.bmp", "Attack_Left", 14, 17, 0.3f, false);
	AnimationRender->CreateAnimation("King_Left.bmp", "Damaged_Left", 27, 27, 0.5f, false);
	AnimationRender->CreateAnimation("King_Left.bmp", "Dead_Left", 29, 30, 0.3f, true);


	// Boss - Right
	AnimationRender->CreateAnimation("King_Right.bmp", "Idle_Right", 0, 3, 0.2f, true);
	AnimationRender->CreateAnimation("King_Right.bmp", "Walk_Right", 4, 7, 0.3f, true);
	AnimationRender->CreateAnimation("King_Jump_Right.bmp", "Jump_Right", 8, 9, 0.5f, false);
	AnimationRender->CreateAnimation("King_Jump_Right.bmp", "JumpDown_Right", 10, 10, 0.3f, false);
	AnimationRender->CreateAnimation("King_Right.bmp", "Scream_Right", 21, 22, 0.3f, true);
	AnimationRender->CreateAnimation("King_Right.bmp", "Attack_Right", 14, 17, 0.3f, false);
	AnimationRender->CreateAnimation("King_Right.bmp", "Damaged_Right", 27, 27, 0.5f, false);
	AnimationRender->CreateAnimation("King_Right.bmp", "Dead_Right", 29, 30, 0.3f, true);

	AnimationName_ = "Idle_";
	ChangeDirText_ = "Left";
	ChangeState(MonsterState::Idle);
}

void Kingdedede::Update()
{
	ColMapUpdate();

	//DirAnimationCheck();
	MonsterStateUpdate();

	MonsterColCheck();

	// 항상 땅에 붙어있도록 체크
	if (RGB(0, 0, 0) != BottomPixelColorCheck(50.f))
	{
		SetMove(float4{ 0, 1.f });
	}

	int LeftCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ -70.f, 0.f });
	int RightCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ 70.f, 0.f });

	float4 Pos = MoveDir;

	if (RGB(0, 0, 0) == LeftCheck)
	{
		MoveDir = float4{ 1.f, 0.0f };
		SetMove(MoveDir);
	}
	else if (RGB(0, 0, 0) == RightCheck)
	{
		MoveDir = float4{ -1.f, 0.0f };
		SetMove(MoveDir);
	}
}

void Kingdedede::Render()
{
}


void Kingdedede::IdleUpdate()
{
	DirCheck();

	if (PrevState_ != MonsterState::Scream) 
	{
		if (410.f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x)
			&& 400.f < std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
		{
			WalkSound_.Stop();
			ChangeState(MonsterState::Scream);
			return;
		}
	}
	

	IdleTime_ -= GameEngineTime::GetDeltaTime();

	if (IdleTime_ < 0)
	{
		ChangeState(MonsterState::Walk);
		return;
	}
}

void Kingdedede::WalkUpdate()
{
	DirCheck();

	if (270.f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
	{
		WalkSound_.Stop();
		ChangeState(MonsterState::Attack);
		return;
	}

	if (350.f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
	{
		WalkSound_.Stop();
		ChangeState(MonsterState::Jump);
		return;
	}


	if (RGB(0, 0, 0) == BottomPixelColorCheck(70.f))
	{
		WallPixelCheck(80.f, Speed_);
	}
}

void Kingdedede::JumpUpdate()
{
	JumpTime_ -= GameEngineTime::GetDeltaTime();

	MoveDir.y = -570.f * GameEngineTime::GetDeltaTime();

	if (CurDir_ == MonsterDir::Left)
	{
		MoveDir.x = -0.7f;
	}
	else if (CurDir_ == MonsterDir::Right)
	{
		MoveDir.x = 0.7f;
	}

	SetMove(MoveDir);

	if (JumpTime_ < 0)
	{
		ChangeState(MonsterState::JumpDown);
		return;
	}
}

void Kingdedede::JumpDownUpdate()
{
	MoveDir.y += 9.f * GameEngineTime::GetDeltaTime();

	if (CurDir_ == MonsterDir::Left)
	{
		MoveDir.x = -1.f;
	}
	else if (CurDir_ == MonsterDir::Right)
	{
		MoveDir.x = 1.f;
	}

	SetMove(MoveDir);

	if (RGB(0, 0, 0) == BottomPixelColorCheck(70.f))
	{
		GameEngineSound::SoundPlayOneShot("BossJumpDown.wav");

		// 착지 후 양 쪽에 Star 생성 
		{
			Effect_BossStar* Effect = GetLevel()->CreateActor<Effect_BossStar>((int)ORDER::EFFECT);
			Effect->SetPosition(GetPosition() + float4{ 200.f, 50.f });

			Effect = GetLevel()->CreateActor<Effect_BossStar>((int)ORDER::EFFECT);
			Effect->SetPosition(GetPosition() + float4{ -200.f, 50.f });
		}
	

		ChangeState(MonsterState::Idle);
		return;
	}
}

void Kingdedede::ScreamUpdate()
{
	ScreamTime_ -= GameEngineTime::GetDeltaTime();

	// 웨이들 생성
	if (ScreamTime_ < 0)
	{
		WaddleDee* Waddle = GetLevel()->CreateActor<WaddleDee>((int)ORDER::MONSTER);
		Waddle->SetPosition({ 280.f, -30.f });

	/*	Waddle = GetLevel()->CreateActor<WaddleDee>((int)ORDER::MONSTER);
		Waddle->SetPosition({ -280.f, -30.f });*/

		ChangeState(MonsterState::Idle);
		return;
	}
}

void Kingdedede::AttackUpdate()
{
	if (AnimationRender->IsEndAnimation())
	{
		GameEngineSound::SoundPlayOneShot("BossHammer.wav");

		{
			Effect_BossStar* Effect = GetLevel()->CreateActor<Effect_BossStar>((int)ORDER::EFFECT);
			if (CurDir_ == MonsterDir::Right)
			{
				Effect->SetPosition(GetPosition() + float4{ 200.f, 50.f });
			}
			else
			{
				Effect->SetPosition(GetPosition() + float4{ -200.f, 50.f });
			}
		}



		ChangeState(MonsterState::Idle);
		return;
	}
}

void Kingdedede::DamagedUpdate()
{
	DamagedTime_ -= GameEngineTime::GetDeltaTime();

	if (DamagedTime_ < 0)
	{
		ChangeState(MonsterState::Walk);
		return;
	}
}

void Kingdedede::DeadUpdate()
{
}

void Kingdedede::IdleStart()
{
	MoveDir = float4::ZERO;

	IdleTime_ = 2.f;

	AnimationName_ = "Idle_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::WalkStart()
{
	PrevState_ = MonsterState::Idle;

	MoveDir = float4::ZERO;

	WalkSound_.Stop();
	WalkSound_ = GameEngineSound::SoundPlayControl("BossWalk2.wav");

	AnimationName_ = "Walk_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::JumpStart()
{
	JumpTime_ = 1.5f;

	MoveDir = float4::ZERO;

	GameEngineSound::SoundPlayOneShot("BossJump1.wav");
	//JumpSound_.Stop();
	//JumpSound_ = GameEngineSound::SoundPlayControl("BossJump1");

	AnimationName_ = "Jump_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::JumpDownStart()
{
	MoveDir = float4::ZERO;


	AnimationName_ = "JumpDown_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::ScreamStart()
{
	PrevState_ = MonsterState::Scream;

	MoveDir = float4::ZERO;

	ScreamTime_ = 1.f;

	GameEngineSound::SoundPlayOneShot("BossSound.wav");

	AnimationName_ = "Scream_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::AttackStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "Attack_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::DamagedStart()
{
	MoveDir = float4::ZERO;

	GameEngineSound::SoundPlayOneShot("Damaged2.wav");

	DamagedTime_ = 1.5f;

	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::DeadStart()
{
	MoveDir = float4::ZERO;

	GameEngineSound::SoundPlayOneShot("Applause.wav");

	AnimationName_ = "Dead_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::WallPixelCheck(float _x, float _Speed)
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

void Kingdedede::MonsterColCheck()
{
	//{
	//	std::vector<GameEngineCollision*> ColList;

	//	if (true == MonsterCollision->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	//	{
	//		
	//		ChangeState(MonsterState::Damaged);
	//		return;
	//	}
	//}

	{
		std::vector<GameEngineCollision*> ColList;

		if (true == MonsterCollision->CollisionResult("AttackCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			WalkSound_.Stop();

			ChangeState(MonsterState::Damaged);
			return;
		}
	}

}
