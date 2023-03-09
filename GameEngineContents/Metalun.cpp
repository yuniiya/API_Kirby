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
	// ó�� ������ Left
	MonsterDir PrevDir_ = CurDir_;

	float4 PlayerPos = Player::MainPlayer->GetPosition();
	float4 MonsterPos = GetPosition();

	// �÷��̾ ���� ���ʿ� �ִ�
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

	// ������ �޶�����
	if (PrevDir_ != CurDir_)
	{
		AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
		CurDir_ = PrevDir_;
	}
}

void Metalun::Start()
{
	// ��Ʈ �ڽ�
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

	// �׻� ���� �پ��ֵ��� üũ
	GroundPixelCheck();
}

void Metalun::Render()
{
}


void Metalun::IdleUpdate()
{
	// �����Ÿ� ������ ������ Walk�� ��ȯ
	if (300.f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
	{
		ChangeState(MonsterState::Walk);
		return;
	}
}

void Metalun::WalkUpdate()
{
	// �����Ÿ� ������ ����� �ٽ� Idle�� ��ȯ 
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

	// �÷��̾ ���� ���ʿ� �ִ�
	if (PlayerPos.x < MonsterPos.x)
	{
		MoveDir.x -= 2.5f * GameEngineTime::GetDeltaTime();
	}
	else if (PlayerPos.x > MonsterPos.x)
	{
		// ���� �����ʿ� �ִ�
		MoveDir.x += 2.5f * GameEngineTime::GetDeltaTime();
	}

	SetMove(MoveDir);
}

void Metalun::DamagedUpdate()
{
	float4 PlayerPos = Player::MainPlayer->GetPosition();
	float4 MonsterPos = GetPosition();

	// �÷��̾ ���� ���ʿ� �ִ�
	if (PlayerPos.x < MonsterPos.x)
	{
		MoveDir.x = 0.3f;
	}
	else if (PlayerPos.x > MonsterPos.x)
	{
		// ���� �����ʿ� �ִ�
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

void Metalun::IdleStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "Idle_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Metalun::WalkStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "Walk_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Metalun::SwallowedStart()
{
	MoveDir = float4::ZERO;

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
	// ���� �΋H���� �ݴ� �������� ��ȯ

	MonsterDir CheckDir_ = CurDir_;

	float4 LeftCheck = GetPosition() + float4{ -_x, 0.0f };
	float4 RightCheck = GetPosition() + float4{ _x, 0.0f };

	int LeftColor = MapColImage_->GetImagePixel(LeftCheck);
	int RightColor = MapColImage_->GetImagePixel(RightCheck);

	if (CurDir_ == MonsterDir::Left)
	{
		// ������ ���̸� �ݴ� �������� 
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
	// ����� ����� �� -> Swallowed
	std::vector<GameEngineCollision*> SwallowColList;

	if (true == MonsterCollision->CollisionResult("InhaleCol", SwallowColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < SwallowColList.size(); i++)
		{
			ChangeState(MonsterState::Swallowed);
			return;
		}
	}

	// �������� �ִ� ���̸� Death�� ó��
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

	//{
	//	std::vector<GameEngineCollision*> ColList;

	//	if (true == MonsterCollision->CollisionResult("SlideCol", ColList, CollisionType::Rect, CollisionType::Rect))
	//	{

	//		ChangeState(MonsterState::Damaged);
	//		return;
	//	}
	//}
}
