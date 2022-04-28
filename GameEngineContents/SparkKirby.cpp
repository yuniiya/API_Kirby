#include "SparkKirby.h"
#include "Player.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineLevel.h>

#include "Bullet.h"
#include "Stage.h"
#include "ContentsEnum.h"
#include "Monster.h"
#include "Scarfy.h"

SparkKirby* SparkKirby::SparkPlayer = nullptr;

SparkKirby::SparkKirby()
	: Speed_(350.0f)
	, JumpPower_(1000.f)
	, Gravity_(1500.f)
	, StopTime_(1.f)
	, DownTime_(0.5f)
{

}
SparkKirby::~SparkKirby()
{

}

void SparkKirby::MonsterColCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerCollision->CollisionResult("DefaultMonster", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		SparkPlayer->Off();

		MainPlayer->SetPosition(GetPosition());
		CurSkill_ = KirbySkill::Default;
		MainPlayer->On();
	}

	ChangeState(PlayerState::DamagedStart);
	return;
}

void SparkKirby::AttackColCheck()
{
}

void SparkKirby::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SparkPlayer = this;
}

void SparkKirby::Start()
{
	PlayerCollision = CreateCollision("PlayerHitBox", { 70, 70 });

	// 애니메이션을 하나라도 만들면 애니메이션이 재생된다.
	PlayerAnimationRender = CreateRenderer();
	PlayerAnimationRender->SetPivotType(RenderPivot::BOT);
	PlayerAnimationRender->SetPivot({ 0.f, 210.f });

	// Left
	{
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "Idle_Left", 0, 7, 0.3f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "Down_Left", 8, 15, 0.3f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "Slide_Left", 17, 19, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "Jump_Left", 20, 29, 0.03f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "Walk_Left", 31, 50, 0.03f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "Run_Left", 51, 58, 0.2f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "RunToStop_Left", 59, 60, 0.03f, true);

		// Float
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "Float_Left", 61, 65, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "Float_Left_Loop", 66, 94, 0.02f, true);

		// Exhale
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "Exhale_Left", 95, 96, 0.05f, true);

		// Fall
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "Fall_Left", 97, 105, 0.1f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "FallToBounce_Left", 106, 109, 0.02f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "BounceToIdle_Left", 110, 112, 0.2f, false);

		// Enter
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "Enter_Left", 133, 137, 0.01f, true);

		// Attack
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "AttackStart_Left", 138, 138, 0.05f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Attack.bmp", "Attack_Left", 0, 4, 0.02f, true);
	}


	// Right
	{
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "Idle_Right", 0, 7, 0.3f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "Down_Right", 8, 15, 0.3f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "Slide_Right", 17, 19, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "Jump_Right", 20, 29, 0.03f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "Walk_Right", 31, 50, 0.03f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "Run_Right", 51, 58, 0.2f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "RunToStop_Right", 59, 60, 0.03f, true);

		// Float
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "Float_Right", 61, 65, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "Float_Right_Loop", 66, 94, 0.02f, true);

		// Exhale
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "Exhale_Right", 95, 96, 0.05f, true);

		// Fall
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "Fall_Right", 97, 105, 0.1f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "FallToBounce_Right", 106, 109, 0.02f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "BounceToIdle_Right", 110, 112, 0.2f, false);

		// Enter
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "Enter_Right", 133, 137, 0.01f, true);

		// Attack
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "AttackStart_Right", 138, 138, 0.05f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Attack.bmp", "Attack_Right", 0, 4, 0.02f, true);
	}

	AnimationName_ = "Idle_";
	PlayerAnimationRender->ChangeAnimation("Idle_Right");


	Off();
	SparkPlayer = this;
}

void SparkKirby::Update()
{
	ColMapUpdate();

	DoorPixelCheck();

	DirAnimationCheck();
	PlayerStateUpdate();
	MonsterColCheck();

	DebugModeSwitch();
	DebugKirbySkillChange();

	// 카메라 위치 고정
	CameraFix();

}

void SparkKirby::ChangeState(PlayerState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Walk:
			WalkStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::RunToStop:
			RunToStopStart();
			break;
		case PlayerState::Down:
			DownStart();
			break;
		case PlayerState::Slide:
			SlideStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Float:
			FloatStart();
			break;
		case PlayerState::Fall:
			FallStart();
			break;
		case PlayerState::FallToBounce:
			FallToBounceStart();
			break;
		case PlayerState::BounceToIdle:
			BounceToIdleStart();
			break;
		case PlayerState::Exhausted:
			ExhaustedStart();
			break;
		case PlayerState::AttackStart:
			AttackStartStart();
			break;
		case PlayerState::Attack:
			AttackStart();
			break;
		case PlayerState::AttackEnd:
			AttackEndStart();
			break;
		}
	}

	CurState_ = _State;
}

void SparkKirby::PlayerStateUpdate()
{
	switch (CurState_)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Walk:
		WalkUpdate();
		break;
	case PlayerState::Run:
		RunUpdate();
		break;
	case PlayerState::RunToStop:
		RunToStopUpdate();
		break;
	case PlayerState::Down:
		DownUpdate();
		break;
	case PlayerState::Slide:
		SlideUpdate();
		break;
	case PlayerState::Jump:
		JumpUpdate();
		break;
	case PlayerState::Float:
		FloatUpdate();
		break;
	case PlayerState::Fall:
		FallUpdate();
		break;
	case PlayerState::FallToBounce:
		FallToBounceUpdate();
		break;
	case PlayerState::BounceToIdle:
		BounceToIdleUpdate();
		break;
	case PlayerState::Exhausted:
		ExhaustedUpdate();
		break;
	case PlayerState::AttackStart:
		AttackStartUpdate();
		break;
	case PlayerState::Attack:
		AttackUpdate();
		break;
	case PlayerState::AttackEnd:
		AttackEndUpdate();
		break;
	}
}

void SparkKirby::DirAnimationCheck()
{
	std::string ChangeName;

	PlayerDir CheckDir_ = CurDir_;
	//ChangeDirText_ = "Right";

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		CheckDir_ = PlayerDir::Right;
		ChangeDirText_ = "Right";
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		CheckDir_ = PlayerDir::Left;
		ChangeDirText_ = "Left";
	}

	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		if (CheckDir_ == PlayerDir::Left)
		{
			ChangeDirText_ = "Left";
		}
		else
		{
			ChangeDirText_ = "Right";
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Inhale"))
	{
		if (CheckDir_ == PlayerDir::Left)
		{
			ChangeDirText_ = "Left";
		}
		else
		{
			ChangeDirText_ = "Right";
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("JumpLeft"))
	{
		if (CheckDir_ == PlayerDir::Left)
		{
			ChangeDirText_ = "Left";
		}
		else
		{
			ChangeDirText_ = "Right";
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("JumpRight"))
	{
		if (CheckDir_ == PlayerDir::Left)
		{
			ChangeDirText_ = "Left";
		}
		else
		{
			ChangeDirText_ = "Right";
		}
	}

	if (CheckDir_ != CurDir_)
	{
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
		CurDir_ = CheckDir_;
	}
}


void SparkKirby::AttackStartUpdate()
{
}

void SparkKirby::AttackUpdate()
{
}

void SparkKirby::AttackEndUpdate()
{
}

void SparkKirby::IdleStart()
{
	MoveDir = float4::ZERO;;

	Speed_ = 350.f;

	AnimationName_ = "Idle_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void SparkKirby::WalkStart()
{
	Speed_ = 350.f;

	AnimationName_ = "Walk_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void SparkKirby::RunStart()
{
	Speed_ = 500.f;

	AnimationName_ = "Run_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void SparkKirby::RunToStopStart()
{
	Speed_ = 350.f;
	StopTime_ = 0.3f;

	AnimationName_ = "RunToStop_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void SparkKirby::DownStart()
{
	DownTime_ = 0.5f;
	AnimationName_ = "Down_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);

}

void SparkKirby::SlideStart()
{
	Speed_ = 500.f;
	SlidingTime_ = 1.2f;

	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		MoveDir = float4::LEFT;

	}
	else if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}

	AnimationName_ = "Slide_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);

}

void SparkKirby::JumpStart()
{
	//FallTime_ = 0.8f;
	JumpPower_ = 1000.f;
	Gravity_ = 1800.f;

	// 한 번에 100의 힘으로 위로 간다 
	MoveDir = float4::UP * JumpPower_;

	AnimationName_ = "Jump_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void SparkKirby::FloatStart()
{
	//FallTime_ = 0.8f;
	Speed_ = 3.f;
	Gravity_ = 300.f;

	PlayerAnimationRender->PauseOff();

	AnimationName_ = "Float_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);

}

void SparkKirby::FallStart()
{
	MoveDir = float4::ZERO;;

	AnimationName_ = "Fall_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void SparkKirby::FallToBounceStart()
{
	Gravity_ = 0.0f;

	MoveDir = float4::ZERO;

	AnimationName_ = "FallToBounce_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void SparkKirby::BounceToIdleStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "BounceToIdle_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void SparkKirby::ExhaustedStart()
{
	AnimationName_ = "Exhausted_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void SparkKirby::AttackStartStart()
{
	AnimationName_ = "AttackStart_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void SparkKirby::AttackStart()
{
	AnimationName_ = "Attack_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void SparkKirby::AttackEndStart()
{
	AnimationName_ = "AttackEnd_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}
