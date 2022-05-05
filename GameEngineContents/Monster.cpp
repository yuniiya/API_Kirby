#include "Monster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"

Monster::Monster()
	: Speed_(20.f)
	, Gravity_(100.f)
	, CurDir_(MonsterDir::Left)
	, CurState_(MonsterState::Idle)
	, InputDir_(CurDir_)
	, MapColImage_(nullptr)
	, MonsterAnimationRenderer(nullptr)
{

}
Monster::~Monster()
{

}


void Monster::GravityOn()
{
	MoveDir.y = 1.f * GameEngineTime::GetDeltaTime() * Gravity_;
}


void Monster::ChangeState(MonsterState _State)
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

void Monster::MonsterStateUpdate()
{
	if (CurState_ != CurState_)
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
}


void Monster::ColMapUpdate()
{
	std::string CurrentLevel = GetLevel()->GetNameCopy();

	//if (nullptr == MapColImage_)
	//{
	//	MapColImage_ = GameEngineImageManager::GetInst()->Find("Level1_ColMap.bmp");
	//}


	if ("Level_1" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level1_ColMap.bmp");
	}
	else if ("Level_2" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level2_ColMap.bmp");
	}
	else if ("Level_3" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level3_ColMap.bmp");
	}
	else if ("Level_4" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level4_ColMap.bmp");
	}
	else if ("TitleLevel" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Title_ColMap.bmp");
	}
	else if ("BossRoomLevel" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("BossRoom_ColMap.bmp");
	}
	else if ("BossLevel" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("BossLevel_ColMap.bmp");
	}
	else
		return;
}

void Monster::Start()
{


	MonsterAnimationRenderer = CreateRenderer();
	MonsterAnimationRenderer->SetPivotType(RenderPivot::BOT);
	MonsterAnimationRenderer->SetPivot({ 0.f, 140.f });

	// Default Left
	{
		// Snooter
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Left.bmp", "Snooter_Idle_Left", 8, 11, 0.5f, true);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Left.bmp", "Snooter_Walk_Left", 0, 3, 0.5f, false);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Left.bmp", "Snooter_Swallow_Left", 4, 6, 0.5f, false);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Left.bmp", "Snooter_Swallow_Left2", 9, 9, 0.5f, false);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Left.bmp", "Snooter_Swallow_Left3", 8, 8, 0.5f, false);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Left.bmp", "Snooter_Swallow_Left4", 7, 8, 0.1f, false);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Left.bmp", "Snooter_Attack_Left", 10, 17, 0.1f, false);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Left.bmp", "Snooter_Damaged_Left", 18, 18, 0.1f, false);

		
	}

	// Skilled Left
	{
	
		
		// Metalun

		// Boxin

		// Boss
	}

	// Default Right
	{
		// Snooter
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Right.bmp", "Snooter_Idle_Right", 8, 11, 0.5f, true);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Right.bmp", "Snooter_Walk_Right", 0, 3, 0.5f, true);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Right.bmp", "Snooter_Swallow_Right", 4, 6, 0.5f, false);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Right.bmp", "Snooter_Swallow_Right2", 9, 9, 0.5f, false);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Right.bmp", "Snooter_Swallow_Right3", 8, 8, 0.5f, false);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Right.bmp", "Snooter_Swallow_Right4", 7, 8, 0.1f, false);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Right.bmp", "Snooter_Attack_Right", 10, 17, 0.1f, false);
		//MonsterAnimationRenderer->CreateAnimation("Snooter_Right.bmp", "Snooter_Damaged_Right", 18, 18, 0.1f, false);

	}

	// Skilled Right
	{


		// Metalun

		// Boxin

		// Boss
	}
}

int Monster::BottomPixelColorCheck(float _y)
{
	float4 CheckPos = GetPosition() + float4{ 0.0f, _y };
	int Color = MapColImage_->GetImagePixel(CheckPos);

	return Color;
}

void Monster::StagePixelCheck(float _Speed)
{
	float4 NextPos = GetPosition() + MoveDir * GameEngineTime::GetDeltaTime();
	float4 LeftCheckPos = NextPos + float4{ -20.f, 0.f };
	float4 RightCheckPos = NextPos + float4{ 20.f, 0.f };

	int LeftColor = MapColImage_->GetImagePixel(LeftCheckPos);
	int RightColor = MapColImage_->GetImagePixel(LeftCheckPos);

	if (RGB(0, 0, 0) != LeftColor)
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * _Speed);
	}

	if (RGB(0, 0, 0) != RightColor)
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * _Speed);
	}

}

//void Monster::WallPixelCheck(float _x, float _Speed)
//{
//	// 벽에 부딫히면 반대 방향으로 전환
//
//	MonsterDir CheckDir_ = CurDir_;
//
//	float4 LeftCheck = GetPosition() + float4{ -_x, 0.0f };
//	float4 RightCheck = GetPosition() + float4{ _x, 0.0f };
//
//	int LeftColor = MapColImage_->GetImagePixel(LeftCheck);
//	int RightColor = MapColImage_->GetImagePixel(RightCheck);
//
//	if (CurDir_ == MonsterDir::Left)
//	{
//		MoveDir.x = -1.f * _Speed;
//		SetMove(MoveDir * GameEngineTime::GetDeltaTime());
//
//		if (RGB(0, 0, 0) == LeftColor)
//		{
//			CurDir_ = MonsterDir::Right;
//			ChangeDirText_ = "Right";
//		}
//	}
//	else if (CurDir_ == MonsterDir::Right)
//	{
//		MoveDir.x = 1.f * _Speed;
//		SetMove(MoveDir * GameEngineTime::GetDeltaTime());
//
//		if (RGB(0, 0, 0) == RightColor)
//		{
//			CurDir_ = MonsterDir::Left;
//			ChangeDirText_ = "Left";
//		}
//	}
//
//	if (CheckDir_ != CurDir_)
//	{
//		AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
//		CurDir_ = CheckDir_;
//	}
//}

void Monster::GroundPixelCheck()
{
	// 땅에 닿도록 내려준다

	if (RGB(0, 0, 0) != BottomPixelColorCheck(30.f))
	{
		SetMove(float4{0, 1.f});
	}
}


void Monster::DirAnimationCheck()
{
	// 처음 방향은 Left
	MonsterDir PrevDir_ = CurDir_;

	if (PrevDir_ == MonsterDir::Right)
	{
		PrevDir_ = MonsterDir::Right;
		ChangeDirText_ = "Right";
	}

	if (PrevDir_ == MonsterDir::Left)
	{
		PrevDir_ = MonsterDir::Left;
		ChangeDirText_ = "Left";
	}

	if (PrevDir_ != CurDir_)
	{
		MonsterAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText_);
		CurDir_ = PrevDir_;
	}
}
