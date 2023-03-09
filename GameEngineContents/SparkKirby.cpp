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

#include "Stage.h"
#include "ContentsEnum.h"
#include "Monster.h"
#include "Scarfy.h"
#include "Effect_Slide.h"
#include "Effect_RunToStop.h"
#include "Effect_Star.h"
#include "Effect_Exhale.h"
#include "Effect_ReleaseSkill.h"

SparkKirby* SparkKirby::SparkPlayer = nullptr;
SkillUI* SparkKirby::SparkSkill = nullptr;
SkillName* SparkKirby::SparkName = nullptr;

SparkKirby::SparkKirby()
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
		AttackEffSound_.Stop();
	}
}


void SparkKirby::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SparkPlayer = this;
}

void SparkKirby::Start()
{
	PlayerCollision = CreateCollision("PlayerHitBox", { 70, 70 });
	SparkAttackCollision_ = CreateCollision("SparkAttackCol", { 175.f,175.f });
	SparkAttackCollision_->Off();

	// 애니메이션을 하나라도 만들면 애니메이션이 재생된다.
	PlayerAnimationRender = CreateRenderer();
	PlayerAnimationRender->SetPivotType(RenderPivot::BOT);
	PlayerAnimationRender->SetPivot({ -4.f, 250.f });

	// Left
	{
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkIdle_Left", 0, 7, 0.3f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkDown_Left", 8, 15, 0.3f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkSlide_Left", 17, 19, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkJump_Left", 20, 29, 0.03f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkWalk_Left", 31, 50, 0.033f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkRun_Left", 51, 58, 0.06f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkRunToStop_Left", 59, 59, 0.06f, true);

		// Float
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkFloat_Left", 61, 65, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkFloat_Left_Loop", 66, 90, 0.06f, true);

		// Exhale
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkExhale_Left", 95, 96, 0.05f, true);

		// Fall
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkFall_Left", 97, 105, 0.1f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkFallToBounce_Left", 106, 109, 0.02f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkBounceToIdle_Left", 110, 112, 0.2f, false);

		// Enter
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkEnter_Left", 133, 137, 0.01f, true);

		// Attack
		PlayerAnimationRender->CreateAnimation("Spark_Left.bmp", "SparkAttackStart_Left", 138, 138, 0.05f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Attack.bmp", "SparkAttack_Left", 0, 3, 0.02f, true);
	}


	// Right
	{
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkIdle_Right", 0, 7, 0.3f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkDown_Right", 8, 15, 0.3f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkSlide_Right", 17, 19, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkJump_Right", 20, 29, 0.03f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkWalk_Right", 31, 50, 0.033f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkRun_Right", 51, 58, 0.06f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkRunToStop_Right", 59, 59, 0.09f, true);

		// Float
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkFloat_Right", 61, 65, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkFloat_Right_Loop", 66, 90, 0.06f, true);

		// Exhale
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkExhale_Right", 95, 96, 0.05f, true);

		// Fall
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkFall_Right", 97, 105, 0.1f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkFallToBounce_Right", 106, 109, 0.02f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkBounceToIdle_Right", 110, 112, 0.2f, false);

		// Enter
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkEnter_Right", 133, 137, 0.01f, true);

		// Attack
		PlayerAnimationRender->CreateAnimation("Spark_Right.bmp", "SparkAttackStart_Right", 138, 138, 0.05f, false);
		PlayerAnimationRender->CreateAnimation("Spark_Attack.bmp", "SparkAttack_Right", 0, 3, 0.02f, true);
	}

	SkillName_ = "Spark";
	AnimationName_ = "Idle_";
	ChangeDirText_ = "Right";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);



	Off();
	SparkPlayer = this;

	SparkSkill = GetLevel()->CreateActor<SkillUI>((int)ORDER::UI);
	SparkSkill->GetRenderer()->SetImage("Icon_Spark.bmp");
	SparkSkill->SetPosition({ 67.f, 661.f });
	SparkSkill->Off();

	SparkName = GetLevel()->CreateActor<SkillName>((int)ORDER::NAMEUI);
	SparkName->GetRenderer()->SetImage("UI_Spark.bmp");
	SparkName->Off();

	MainPlayer->InhaleCollision->Off();
}

void SparkKirby::Update()
{
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

		SparkSkill->Off();
		SparkName->Off();

		// 디폴트 커비 On
		MainPlayer->SetPosition(GetPosition());
		CurSkill_ = KirbySkill::Default;
		MainPlayer->On();

		MainPlayer->InhaleCollision->Off();
		Off();
	}
	else if (CurSkill_ != KirbySkill::Spark)
	{
		CurSkill_ = KirbySkill::Spark;
	}

	Player::Update();
}

void SparkKirby::IdleUpdate()
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

void SparkKirby::WalkUpdate()
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

void SparkKirby::AttackStartUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		SparkAttackCollision_->On();

		ChangeState(PlayerState::Attack);
		return;
	}
}

void SparkKirby::AttackUpdate()
{
	if (true == GameEngineInput::GetInst()->IsFree("Attack"))
	{
		AttackEffSound_.Stop();
		AttackEffSoundMid_.Stop();

		SparkAttackCollision_->Off();

		ChangeState(PlayerState::AttackEnd);
		return;
	}
}

void SparkKirby::AttackEndUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void SparkKirby::IdleStart()
{
	MoveDir = float4::ZERO;;

	Speed_ = 350.f;

	AnimationName_ = "Idle_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void SparkKirby::AttackStartStart()
{
	GameEngineSound::SoundPlayOneShot("Spark3.wav");

	AnimationName_ = "AttackStart_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void SparkKirby::AttackStart()
{
	AttackEffSound_.Stop();
	AttackEffSoundMid_.Stop();
	AttackEffSound_ = GameEngineSound::SoundPlayControl("Spark2.wav");
	AttackEffSoundMid_ = GameEngineSound::SoundPlayControl("Spark3.wav");

	AnimationName_ = "Attack_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void SparkKirby::AttackEndStart()
{
	GameEngineSound::SoundPlayOneShot("Spark.wav");

	AnimationName_ = "AttackStart_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}
