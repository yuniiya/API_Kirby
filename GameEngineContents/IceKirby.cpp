#include "IceKirby.h"
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

#include "Stage.h"
#include "ContentsEnum.h"
#include "Monster.h"
#include "Scarfy.h"
#include "Effect_Slide.h"
#include "Effect_RunToStop.h"
#include "Effect_Star.h"
#include "Effect_IceBreath.h"
#include "Effect_IceBox.h"
#include "Effect_Exhale.h"
#include "Effect_ReleaseSkill.h"


IceKirby* IceKirby::IcePlayer = nullptr;
SkillUI* IceKirby::IceSkill = nullptr;
SkillName* IceKirby::IceName = nullptr;

IceKirby::IceKirby()
{

}
IceKirby::~IceKirby()
{

}

void IceKirby::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	IcePlayer = this;
}

void IceKirby::Start()
{
	//SetScale({ 1000, 1000 });

	PlayerCollision = CreateCollision("PlayerHitBox", { 70, 70 });

	// 애니메이션을 하나라도 만들면 애니메이션이 재생된다.
	PlayerAnimationRender = CreateRenderer();
	PlayerAnimationRender->SetPivotType(RenderPivot::BOT);
	PlayerAnimationRender->SetPivot({ -4.f, 250.f });

	// Walk_Right이미지의 0~9인덱스를 0.1초동안 재생 (true = 루프on)
	//Render->SetPivotType(RenderPivot::BOT);

	// Left
	{
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceIdle_Left", 0, 1, 1.f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceDown_Left", 2, 3, 1.f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceSlide_Left", 4, 4, 0.3f, false);
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceJump_Left", 6, 14, 0.03f, false);
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceWalk_Left", 15, 24, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceRun_Left", 25, 32, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceRunToStop_Left", 33, 33, 0.3f, false);

		// Float
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceFloat_Left", 34, 38, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceFloat_Left_Loop", 39, 54, 0.08f, true);

		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceExhale_Left", 57, 57, 0.1f, false);

		// Fall
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceFall_Left", 59, 63, 0.2f, false);
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceFallToBounce_Left", 64, 68, 0.02f, false);
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceBounceToIdle_Left", 69, 72, 0.2f, false);

		// Attack
		//PlayerAnimationRender->CreateAnimation("Default_Attack_Left.bmp", "AttackStart_Left", 0, 1, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceAttackStart_Left", 93, 98, 0.06f, false);
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceAttack_Left", 99, 100, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Left.bmp", "IceAttackEnd_Left", 101, 102, 0.05f, false);
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Damaged_Left", 70, 78, 0.04f, true);

	}


	// Right
	{
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceIdle_Right", 0, 1, 1.f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceDown_Right", 2, 3, 1.f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceSlide_Right", 4, 4, 0.3f, false);
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceJump_Right", 6, 14, 0.03f, false);
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceWalk_Right", 15, 24, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceRun_Right", 25, 32, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceRunToStop_Right", 33, 33, 0.3f, false);

		// Float
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceFloat_Right", 34, 38, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceFloat_Right_Loop", 39, 54, 0.08f, true);

		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceExhale_Right", 57, 57, 0.1f, false);

		// Fall
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceFall_Right", 59, 63, 0.2f, false);
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceFallToBounce_Right", 64, 68, 0.02f, false);
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceBounceToIdle_Right", 69, 72, 0.2f, false);

		// Attack
		//PlayerAnimationRender->CreateAnimation("Default_Attack_Left.bmp", "AttackStart_Left", 0, 1, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceAttackStart_Right", 93, 98, 0.06f, false);
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceAttack_Right", 99, 100, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Ice_Right.bmp", "IceAttackEnd_Right", 101, 102, 0.05f, false);
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Damaged_Right", 71, 78, 0.04f, true);
	}
	
	SkillName_ = "Ice";
	AnimationName_ = "Idle_";
	ChangeDirText_ = "Right";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ +  ChangeDirText_);

	Off();
	IcePlayer = this;

	IceSkill = GetLevel()->CreateActor<SkillUI>((int)ORDER::UI);
	IceSkill->GetRenderer()->SetImage("Icon_Ice.bmp");
	IceSkill->SetPosition({ 67.f, 665.f });
	IceSkill->Off();

	IceName = GetLevel()->CreateActor<SkillName>((int)ORDER::NAMEUI);
	IceName->GetRenderer()->SetImage("UI_Ice.bmp");
	IceName->Off();
}

void IceKirby::Update()
{
	Player::Update();
	if (true == GameEngineInput::GetInst()->IsDown("SkillRelease"))
	{
		SkillRelease();
		IceKirbyOff();
	}
	else if(CurSkill_ != KirbySkill::Ice)
	{
		CurSkill_ = KirbySkill::Ice;
	}

}

void IceKirby::IceKirbyOff()
{
	IceSkill->Off();
	IceName->Off();

	// 디폴트 커비 On
	MainPlayer->SetPosition(GetPosition());
	MainPlayer->On();

	MainPlayer->InhaleCollision->Off();
	Off();
}


void IceKirby::IdleUpdate()
{
	MonsterColCheck();
	RunningTime_ -= GameEngineTime::GetDeltaTime();

	if (true == IsMoveKey()
		&& RunningTime_ < 0)
		// 연속키를 누른적이 없사
	{
		InputDir_ = CurDir_;

		ChangeState(PlayerState::Walk);
		return;
	}
	else if (true == IsMoveKey()
		&& RunningTime_ > 0)
	{
		if (InputDir_ == CurDir_)
		{
			ChangeState(PlayerState::Run);
			return;
		}
		else
		{
			ChangeState(PlayerState::Walk);
			return;
		}

	}

	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		ChangeState(PlayerState::Down);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Attack"))
	{
		ChangeState(PlayerState::AttackStart);
		return;
	}

	// 점프 
	if (true == IsJumpKey())
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	// 오르막, 내리막길 
	HillPixelCheck();

}

void IceKirby::WalkUpdate()
{
	MonsterColCheck();
	RunningTime_ = 0.1f;

	if (false == IsMoveKey())
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Down"))
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

	if (true == GameEngineInput::GetInst()->IsPress("Attack"))
	{
		ChangeState(PlayerState::AttackStart);
		return;
	}

	Move();
	StagePixelCheck(Speed_);
}

void IceKirby::AttackUpdate()
{
	if (true == GameEngineInput::GetInst()->IsFree("Attack"))
	{
		AttackEffSound_.Stop();
		ChangeState(PlayerState::AttackEnd);
		return;
	}
}

void IceKirby::AttackEndUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		IceBreath_->Death();
		ChangeState(PlayerState::Idle);
		return;
	}
}


void IceKirby::IdleStart()
{
	MoveDir = float4::ZERO;;

	Speed_ = 350.f;

	AnimationName_ = "Idle_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void IceKirby::AttackStart()
{
	{
		IceBreath_ = GetLevel()->CreateActor<Effect_IceBreath>((int)ORDER::EFFECT);

		if (CurDir_ == PlayerDir::Right)
		{
			IceBreath_->SetPosition(GetPosition() + float4{ 155.f, 10.f });
			IceBreath_->SetDir(EffectDir::Right);

		}
		else if (CurDir_ == PlayerDir::Left)
		{
			IceBreath_->SetPosition(GetPosition() + float4{ -155.f, 10.f });
			IceBreath_->SetDir(EffectDir::Left);
		}
	}
	
	AttackEffSound_.Stop();
	AttackEffSound_ = GameEngineSound::SoundPlayControl("IceBreath3.wav");

	AnimationName_ = "Attack_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}



