#include "MetalKirby.h"
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
#include "Effect_Slide.h"
#include "Effect_Star.h"
#include "Effect_Exhale.h"
#include "Effect_ReleaseSkill.h"

MetalKirby* MetalKirby::MetalPlayer = nullptr;
SkillUI* MetalKirby::MetalSkill = nullptr;
SkillName* MetalKirby::MetalName = nullptr;


MetalKirby::MetalKirby()
	: PlayerAnimationRender(nullptr)
	, CurSkill_(KirbySkill::Metal)
	, Speed_(200.f)
	, JumpPower_(500.f)
	, Gravity_(1800.f)
	, StopTime_(1.f)
	, DownTime_(0.5f)
	, SlidingTime_(1.2f)
{

}
MetalKirby::~MetalKirby()
{
	
}

void MetalKirby::MonsterColCheck()
{

}

void MetalKirby::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MetalPlayer = this;
}

void MetalKirby::Start()
{

	PlayerCollision = CreateCollision("MetalCol", { 70, 70 });

	// 애니메이션을 하나라도 만들면 애니메이션이 재생된다.
	PlayerAnimationRender = CreateRenderer();
	PlayerAnimationRender->SetPivotType(RenderPivot::BOT);
	PlayerAnimationRender->SetPivot({ 0.f, 250.f });

	// Walk_Right이미지의 0~9인덱스를 0.1초동안 재생 (true = 루프on)
	//Render->SetPivotType(RenderPivot::BOT);

	// Metal Left
	{
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "Idle_Left", 0, 1, 1.f, true);
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "Down_Left", 2, 3, 1.f, true);
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "Slide_Left", 18, 18, 0.3f, false);
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "Walk_Left", 4, 13, 0.09f, true);

		// Jump
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "Jump_Left", 24, 31, 0.03f, true);

		// Fall
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "Fall_Left", 31, 35, 0.2f, true);
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "FallToBounce_Left", 36, 40, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "BounceToIdle_Left", 30, 30, 0.2f, false);

		// Float
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "Float_Left", 41, 45, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "Float_Left_Loop", 46, 51, 0.1f, true);

		// Exhale
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "Exhale_Left", 52, 52, 0.01f, false);

		// Enter
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "Enter_Left", 20, 23, 0.01f, true);

		// Transform
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "Transform_Left", 53, 53, 0.01f, false);

		// Attack
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "Attack_Left", 55, 61, 0.1f, true);
	}


	// Metal Right
	{
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "Idle_Right", 0, 1, 1.f, true);
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "Down_Right", 2, 3, 1.f, true);
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "Slide_Right", 18, 18, 0.3f, false);
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "Walk_Right", 4, 13, 0.09f, true);

		// Jump
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "Jump_Right", 24, 31, 0.03f, true);

		// Fall
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "Fall_Right", 32, 35, 0.2f, true);
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "FallToBounce_Right", 36, 40, 0.04f, true);
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "BounceToIdle_Right", 30, 30, 0.2f, true);

		// Float
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "Float_Right", 41, 45, 0.02f, true);
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "Float_Right_Loop", 46, 51, 0.1f, true);

		// Exhale
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "Exhale_Right", 52, 52, 0.01f, false);

		// Enter
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "Enter_Right", 20, 23, 0.01f, true);

		// Transform
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "Transform_Right", 53, 53, 0.01f, false);

		// Attack
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "Attack_Right", 55, 61, 0.1f, true);
	}

	AnimationName_ = "Idle_";
	PlayerAnimationRender->ChangeAnimation("Idle_Right");

	Off();
	MetalPlayer = this;

	MetalSkill = GetLevel()->CreateActor<SkillUI>((int)ORDER::UI);
	MetalSkill->GetRenderer()->SetImage("Icon_Metal.bmp");
	MetalSkill->Off();

	MetalName = GetLevel()->CreateActor<SkillName>((int)ORDER::NAMEUI);
	MetalName->GetRenderer()->SetImage("UI_Metal.bmp");
	MetalName->Off();
}

void MetalKirby::Update()
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


	if (true == GameEngineInput::GetInst()->IsDown("SkillRelease"))
	{
		// 스킬 해제 사운드
		GameEngineSound::SoundPlayOneShot("Release1.wav");

		{
			Effect_ReleaseSkill* Effect = GetLevel()->CreateActor<Effect_ReleaseSkill>((int)ORDER::EFFECT);

			if (CurDir_ == PlayerDir::Right)
			{
				Effect->SetPosition(GetPosition());
				Effect->SetDir(EffectDir::Right);

			}
			else if (CurDir_ == PlayerDir::Left)
			{
				Effect->SetPosition(GetPosition());
				Effect->SetDir(EffectDir::Left);
			}
		}

		Off();
		MetalSkill->Off();
		MetalName->Off();

		// 디폴트 커비 On
		MainPlayer->SetPosition(GetPosition());
		CurSkill_ = KirbySkill::Default;
		MainPlayer->On();
	}
}

void MetalKirby::ChangeState(PlayerState _State)
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
		case PlayerState::Exhale:
			ExhaleStart();
			break;
		case PlayerState::Exhausted:
			ExhaustedStart();
			break;
		case PlayerState::Attack:
			AttackStart();
			break;
		}
	}

	CurState_ = _State;
}

void MetalKirby::PlayerStateUpdate()
{
	switch (CurState_)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Walk:
		WalkUpdate();
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
	case PlayerState::Exhale:
		ExhaleUpdate();
		break;
	case PlayerState::Attack:
		AttackUpdate();
		break;
	}
}

void MetalKirby::DirAnimationCheck()
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

	if (true == GameEngineInput::GetInst()->IsPress("Attack"))
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

void MetalKirby::IdleUpdate()
{
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Walk);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		ChangeState(PlayerState::Down);
		return;
	}

	// 점프 
	if (true == IsJumpKey())
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	HillPixelCheck();
}

void MetalKirby::WalkUpdate()
{
	if (false == IsMoveKey())
	{
		EffectSound_.Stop();
		ChangeState(PlayerState::Idle);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Down"))
	{
		EffectSound_.Stop();
		ChangeState(PlayerState::Down);
		return;
	}

	// 점프 
	if (true == IsJumpKey())
	{
		EffectSound_.Stop();
		ChangeState(PlayerState::Jump);
		return;
	}

	MoveDir = float4::ZERO;

	Move();

	StagePixelCheck(Speed_);
}

void MetalKirby::DownUpdate()
{
	if (true == GameEngineInput::GetInst()->IsFree("Down"))
	{
		ChangeState(PlayerState::Idle);
		return;
	}


	DownTime_ -= GameEngineTime::GetDeltaTime();


	if (true == IsMoveKey()
		&& DownTime_ > 0)
	{
		ChangeState(PlayerState::Slide);
		return;
	}
}

void MetalKirby::SlideUpdate()
{
	// 감속
	MoveDir += -(MoveDir * 3.f) * GameEngineTime::GetDeltaTime();

	// 땅 밑으로는 못 가게
	{
		float4 CheckPos = GetPosition() + MoveDir * GameEngineTime::GetDeltaTime() * Speed_;

		int Color = MapColImage_->GetImagePixel(CheckPos);
		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}

	// 문제: 애니메이션이 재생되는 동안 다른 방향으로 변경안되게

	/////////////////////////////////////////////////////////// 슬라이딩 지속 시간 
	SlidingTime_ -= GameEngineTime::GetDeltaTime();

	if (SlidingTime_ < 0)
	{
		RunningTime_ = 0;

		ChangeState(PlayerState::Idle);
		return;
	}

	// 오르막, 내리막길 
	HillPixelCheck();
}

void MetalKirby::JumpUpdate()
{
	// 위로 이동
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	float4 YPos = { 0.0f, MoveDir.y };

	// 일정 높이 될 때까지 Pause
	if (YPos.y = -200.f)
	{
		if (24 == PlayerAnimationRender->CurrentAnimation()->WorldCurrentFrame())
		{
			PlayerAnimationRender->PauseOn();
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{ -200.0f, MoveDir.y };
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{ 200.0f, MoveDir.y };
	}

	// Float
	YPos = { 0.0f, MoveDir.y };
	if (YPos.y >= -100.f)
	{
		if (GameEngineInput::GetInst()->IsDown("JumpRight"))
		{
			ChangeState(PlayerState::Float);
			return;
		}
		else if (GameEngineInput::GetInst()->IsDown("JumpLeft"))
		{
			ChangeState(PlayerState::Float);
			return;
		}
	}


	// 중력
	MoveDir.y += 1.f * GameEngineTime::GetDeltaTime() * Gravity_;

	YPos = { 0.0f, MoveDir.y };
	if (YPos.y > -200.f)
	{
		PlayerAnimationRender->PauseOff();

		//if (31 == PlayerAnimationRender->CurrentAnimation()->WorldCurrentFrame())
		//{
		//	PlayerAnimationRender->PauseOn();
		//}
	}

	// 양옆 + 위 체크 
	MovePixelCheck(20.0f, 20.0f);

	// 바닥에 닿았다
	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
		MakeStarEffect();
		GameEngineSound::SoundPlayOneShot("Metal1.wav");
		MoveDir = float4::ZERO;
		ChangeState(PlayerState::Idle);
		return;
	}
}

void MetalKirby::FallUpdate()
{
	// 도중에 Jump키 누르면 Float으로 전환 
	if (GameEngineInput::GetInst()->IsPress("JumpLeft"))
	{
		ChangeState(PlayerState::Float);
		return;
	}
	else if (GameEngineInput::GetInst()->IsPress("JumpRight"))
	{
		ChangeState(PlayerState::Float);
		return;
	}

	// 방향키를 누르면 해당 방향으로 x 이동
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{ -200.0f, MoveDir.y };
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{ 200.0f, MoveDir.y };
	}

	// MoveDir.x는 움직이지 않고 y만 가속한다 
	MoveDir.y += 2000.f * GameEngineTime::GetDeltaTime();


	// 땅에 닿지 않았다면 MoveDir.y로 가속하며 떨어진다 
	if (RGB(0, 0, 0) != BottomPixelColorCheck(20.f))
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime());
	}
	else
	{
		MakeStarEffect();
		ChangeState(PlayerState::FallToBounce);
		return;
	}

}

void MetalKirby::FallToBounceUpdate()
{
	// 방향키를 누르면 해당 방향으로 x 이동
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{ -100.0f, MoveDir.y };
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{ 100.0f, MoveDir.y };
	}

	// 땅에 닿으면 위로 한 번 튕긴다
	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
		MoveDir.y = -50.f;
	}

	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	// 튕겼으면 BounceToIdle로 전환
	if (RGB(0, 0, 0) != BottomPixelColorCheck(35.f))
	{
		ChangeState(PlayerState::BounceToIdle);
		return;
	}
}

void MetalKirby::BounceToIdleUpdate()
{
	// 방향키를 누르면 해당 방향으로 x 이동
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{ -200.0f, MoveDir.y };
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{ 200.0f, MoveDir.y };
	}

	// MoveDir.x는 움직이지 않고 y만 가속한다 
	MoveDir.y += 2000.f * GameEngineTime::GetDeltaTime();
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	// 땅에 닿으면 Idle로 전환
	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
		MakeStarEffect();

		MoveDir = float4::ZERO;
		ChangeState(PlayerState::Idle);
		return;
	}
}

void MetalKirby::FloatUpdate()
{
	// 공기 내뱉고 내려오기
	if (GameEngineInput::GetInst()->IsDown("Inhale"))
	{
		if (true == IsJumpKey())
		{
			ChangeState(PlayerState::Float);
			return;
		}

		FloatEffSound_.Stop();
		ChangeState(PlayerState::Exhale);
		return;
	}

	if (true == PlayerAnimationRender->IsEndAnimation())
	{
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Loop");
	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{ -200.f, MoveDir.y };
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Loop");
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{ 200.f, MoveDir.y };
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Loop");
	}
	else if (false == IsMoveKey())
	{
		MoveDir.x = 0.0f;
	}

	// 중력
	if (false == IsJumpKey())
	{
		MoveDir.y = 200.f;
		SetMove(MoveDir * GameEngineTime::GetDeltaTime());
	}
	else if (true == IsJumpKey())
	{
		MoveDir.y = -100.f;
		SetMove(MoveDir * GameEngineTime::GetDeltaTime());
	}

	// 양 옆 + 위 픽셀 체크
	MovePixelCheck(20.0f, 20.0f);

	// Float상태로 바닥에 닿았다
	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
		MoveDir = float4::UP;
		SetMove(MoveDir);
	}
}

void MetalKirby::ExhaleUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		// 땅이랑 너무 가깝다 -> Idle
		if (RGB(0, 0, 0) == BottomPixelColorCheck(100.f))
		{
			MoveDir = float4::ZERO;

			MakeStarEffect();
			ChangeState(PlayerState::Idle);
			return;
		}


		// 땅에서 일정한 거리 떨어져 있으면 Fall로 전환
		MoveDir.y += 900.f * GameEngineTime::GetDeltaTime();
		SetMove(MoveDir * GameEngineTime::GetDeltaTime());

		ChangeState(PlayerState::Fall);
		return;
	}

}

void MetalKirby::AttackUpdate()
{
	PlayerAnimationRender->PauseOn();

	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		GameEngineSound::SoundPlayOneShot("MetalAttack3.wav");
		ChangeState(PlayerState::Idle);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		PlayerAnimationRender->PauseOff();

		MoveDir.x = -0.5f;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		PlayerAnimationRender->PauseOff();

		MoveDir.x = 0.5f;
	}
	else if (false == IsMoveKey())
	{
		MoveDir.x = 0.0f;
	}

	SetMove(MoveDir);

	MovePixelCheck(20.0f, 20.0f);

	///////////////////////////////////////// 문제: 내리막길에서 속도 빨라지게
	// 오르막, 내리막길 
	float4 CheckPos = { MoveDir.x, 1.f };
	//float4 LeftUpPos = float4::UP;

	int DownColor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 20.0f } + CheckPos);

	if (RGB(0, 0, 0) != DownColor)
	{
		// 땅에 닿아있는 동안은 계속 내려준다
		while (RGB(0, 0, 0) == DownColor)
		{
			CheckPos.y += 1.f;
			DownColor = MapColImage_->GetImagePixel(GetPosition() + CheckPos);
		}

		SetMove(CheckPos);
	}
}

void MetalKirby::IdleStart()
{
	PlayerAnimationRender->PauseOff();
	MoveDir = float4::ZERO;;

	AnimationName_ = "Idle_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void MetalKirby::WalkStart()
{
	//GameEngineSound::SoundPlayOneShot("Metal1.wav");
	EffectSound_.Stop();
	EffectSound_ = GameEngineSound::SoundPlayControl("Metal1.wav");

	//EffectSound_ = GameEngineSound::SoundPlayOneShot("Metal1.wav", -1);


	Speed_ = 150.f;

	AnimationName_ = "Walk_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void MetalKirby::DownStart()
{
	DownTime_ = 0.5f;

	AnimationName_ = "Down_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void MetalKirby::SlideStart()
{
	{
		Effect_Slide* Effect = GetLevel()->CreateActor<Effect_Slide>((int)ORDER::EFFECT);

		if (CurDir_ == PlayerDir::Right)
		{
			Effect->SetPosition(GetPosition() + float4{ -45.f, 40.f });
			Effect->SetDir(EffectDir::Right);

		}
		else if (CurDir_ == PlayerDir::Left)
		{
			Effect->SetPosition(GetPosition() + float4{ 45.f, 40.f });
			Effect->SetDir(EffectDir::Left);
		}
	}
	GameEngineSound::SoundPlayOneShot("Slide.wav");

	Speed_ = 400.f;
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

void MetalKirby::JumpStart()
{
	GameEngineSound::SoundPlayOneShot("Jump.wav");

	MoveDir = float4::UP * JumpPower_;
	Gravity_ = 2000.f;

	AnimationName_ = "Jump_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void MetalKirby::FallStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "Fall_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void MetalKirby::FallToBounceStart()
{
	GameEngineSound::SoundPlayOneShot("Metal1.wav");

	Gravity_ = 0.0f;
	MoveDir = float4::ZERO;

	AnimationName_ = "FallToBounce_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void MetalKirby::BounceToIdleStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "BounceToIdle_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void MetalKirby::FloatStart()
{
	FloatEffSound_.Stop();
	FloatEffSound_ = GameEngineSound::SoundPlayControl("Float.wav");

	Speed_ = 3.f;
	Gravity_ = 500.f;

	PlayerAnimationRender->PauseOff();

	AnimationName_ = "Float_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void MetalKirby::ExhaleStart()
{
	{
		Effect_Exhale* Effect = GetLevel()->CreateActor<Effect_Exhale>((int)ORDER::EFFECT);

		if (CurDir_ == PlayerDir::Right)
		{
			Effect->SetPosition(GetPosition() + float4{ 80.f, 55.f });
			Effect->SetDir(EffectDir::Right);

		}
		else if (CurDir_ == PlayerDir::Left)
		{
			Effect->SetPosition(GetPosition() + float4{ -80.f, 55.f });
			Effect->SetDir(EffectDir::Left);
		}
	}
	GameEngineSound::SoundPlayOneShot("Exhale.wav");

	AnimationName_ = "Exhale_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void MetalKirby::AttackStart()
{
	GameEngineSound::SoundPlayOneShot("MetalAttack3.wav");

	AnimationName_ = "Attack_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}