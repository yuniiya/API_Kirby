#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineLevel.h> // ������ ���ؼ�
#include "ContentsEnum.h"
#include "Effect_Slide.h"
#include "Effect_RunToStop.h"
#include "Effect_Exhale.h"
#include "Effect_Inhale.h"
#include "Effect_Attack.h"
#include "Effect_Star.h"
#include "Effect_Transform.h"

#include "MetalKirby.h"
#include "IceKirby.h"
#include "SparkKirby.h"

void Player::IdleUpdate()
{
	MonsterColCheck();
	RunningTime_ -= GameEngineTime::GetDeltaTime();

	if (true == IsMoveKey()
		&& RunningTime_ < 0)	
		// ����Ű�� �������� ����
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

	if (true == GameEngineInput::GetInst()->IsPress("Inhale"))
	{
		ChangeState(PlayerState::Inhale);
		return;
	}

	// ���� 
	if (true == IsJumpKey())
	{
		ChangeState(PlayerState::Jump);
		return;
	}	

	HillPixelCheck();
}

void Player::WalkUpdate()
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

	// ���� 
	if (true == IsJumpKey())
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Inhale"))
	{
		ChangeState(PlayerState::Inhale);
		return;
	}

	Move();

	StagePixelCheck(Speed_);

	// ������, �������� 
	//HillPixelCheck();

}

void Player::RunUpdate()
{
	MonsterColCheck();
	if (false == IsMoveKey())
	{
		ChangeState(PlayerState::RunToStop);
		return;
	}

	// ���� 
	if (true == IsJumpKey())
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	Move();
	StagePixelCheck(500.f);

	// �ӷ� ����
	//if (1.f <= MoveDir.Len2D())
	//{
	//	MoveDir.Range2D(1.f);
	//}

	// �ƹ��� Ű�� ������ ������ ���� �����Ѵ�
	//if (false == IsMoveKey())
	//{
	//	MoveDir += -MoveDir * GameEngineTime::GetDeltaTime();

	//	if (0.005f >= MoveDir.Len2D())
	//	{
	//		MoveDir = float4::ZERO;
	//		return;
	//	}

}

void Player::RunToStopUpdate()
{
	MonsterColCheck();
	// �̵� �� �̷� ��ġ �ȼ� üũ
	MoveDir.x += -(MoveDir.x * 3.f) * GameEngineTime::GetDeltaTime();

	float4 CheckPos = GetPosition() + MoveDir * GameEngineTime::GetDeltaTime() * Speed_;
	int Color = MapColImage_->GetImagePixel(CheckPos);

	if (RGB(0, 0, 0) != Color)
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}

	////////////////////////////////////////////////// Stop ���� �ð�
	StopTime_ -= GameEngineTime::GetDeltaTime();

	if (StopTime_ < 0)
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	HillPixelCheck();
}

void Player::DownUpdate()
{
	MonsterColCheck();
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

void Player::SlideUpdate()
{
	// ����
	MoveDir += -(MoveDir * 3.f) * GameEngineTime::GetDeltaTime();

	// �� �����δ� �� ����
	{
		float4 CheckPos = GetPosition() + MoveDir * GameEngineTime::GetDeltaTime() * Speed_;

		int Color = MapColImage_->GetImagePixel(CheckPos);
		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}

	// ����: �ִϸ��̼��� ����Ǵ� ���� �ٸ� �������� ����ȵǰ�

	/////////////////////////////////////////////////////////// �����̵� ���� �ð� 
	SlidingTime_ -= GameEngineTime::GetDeltaTime();

	if (SlidingTime_ < 0)
	{
		RunningTime_ = 0;

		PlayerCollision->On();
		ChangeState(PlayerState::Idle);
		return;
	}

	//SlideColTime_ -= GameEngineTime::GetDeltaTime();

	//// �����̵� �ݸ���
	//if (CurDir_ == PlayerDir::Left)
	//{
	//	SlidePos = { -80.f, 10.f };
	//}
	//else
	//{
	//	SlidePos = { 80.f, 10.f };
	//}

	//SlideCollision->SetPivot({ SlidePos });
	//SlideCollision->On();

	//if (SlideColTime_ < 0)
	//{
	//	SlideCollision->Off();
	//}

	// ������, �������� 
	HillPixelCheck();
}

void Player::JumpUpdate()
{
	MonsterColCheck();
	// ���� �̵�
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	float4 YPos = { 0.0f, MoveDir.y };

	// ���� ���� �� ������ Pause
	if (YPos.y = -500.f)
	{
		if (0 == PlayerAnimationRender->CurrentAnimation()->WorldCurrentFrame())
		{
			PlayerAnimationRender->PauseOn();
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{ -300.0f, MoveDir.y };
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{ 300.0f, MoveDir.y };
	}

	// Float
	YPos = { 0.0f, MoveDir.y };
	if (YPos.y >= -300.f)
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
	

	// �߷�
	GravityOn();

	YPos = { 0.0f, MoveDir.y };
	if (YPos.y > -500.f)
	{
		PlayerAnimationRender->PauseOff();
	}
	
	// �翷 + �� üũ 
	MovePixelCheck(20.0f, 20.0f);

	// �ٴڿ� ��Ҵ�
	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
		MakeStarEffect();
		MoveDir = float4::ZERO;
		ChangeState(PlayerState::Idle);
		return;
	}
	//else if (RGB(0, 0, 0) != BottomPixelColorCheck(400.f))
	//{
	//	ChangeState(PlayerState::Fall);
	//	return;
	//}
}

void Player::FloatUpdate()
{
	MonsterColCheck();
	// ���� ����� ��������
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
		PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_ + "_Loop");

		MonsterColCheck();

	}

	// Float���¿��� �̵�
	//MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		{
			std::vector<GameEngineCollision*> ColList;

			if (true == PlayerCollision->CollisionResult("BossHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
			{
				FloatEffSound_.Stop();
				ChangeState(PlayerState::Damaged);
				return;
			}

		}

		MoveDir = float4{-200.f, MoveDir.y};
		PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_ + "_Loop");
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		{
			std::vector<GameEngineCollision*> ColList;

			if (true == PlayerCollision->CollisionResult("BossHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
			{
				FloatEffSound_.Stop();
				ChangeState(PlayerState::Damaged);
				return;
			}

		}

		MoveDir = float4{200.f, MoveDir.y };
		PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_ + "_Loop");
	}
	else if (false == IsMoveKey())
	{
		MoveDir.x = 0.0f;
	}

	// �߷�
	if (false == IsJumpKey())
	{
		MoveDir.y = 100.f;
		SetMove(MoveDir * GameEngineTime::GetDeltaTime());
	}
	else if (true == IsJumpKey())
	{
		MoveDir.y = -200.f;
		SetMove(MoveDir * GameEngineTime::GetDeltaTime());
	}

	// �� �� + �� �ȼ� üũ
	MovePixelCheck(20.0f, 20.0f);

	// Float���·� �ٴڿ� ��Ҵ�
	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
		MoveDir = float4::UP;
		SetMove(MoveDir);
	}
}

void Player::FallUpdate()
{
	MonsterColCheck();
	// ���߿� JumpŰ ������ Float���� ��ȯ 
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

	// ����Ű�� ������ �ش� �������� x �̵�
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{ -200.0f, MoveDir.y };
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{ 200.0f, MoveDir.y };
	}

	// MoveDir.x�� �������� �ʰ� y�� �����Ѵ� 
	MoveDir.y += 1500.f * GameEngineTime::GetDeltaTime();


	// ���� ���� �ʾҴٸ� MoveDir.y�� �����ϸ� �������� 
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

void Player::FallToBounceUpdate()
{
	MonsterColCheck();
	// ����Ű�� ������ �ش� �������� x �̵�
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{ -300.0f, MoveDir.y };
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{ 300.0f, MoveDir.y };
	}

	// ���� ������ ���� �� �� ƨ���
	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
		MoveDir.y = -400.f;
	}

	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	// ƨ������ BounceToIdle�� ��ȯ
	if (RGB(0, 0, 0) != BottomPixelColorCheck(130.f))
	{
		ChangeState(PlayerState::BounceToIdle);
		return;
	}
}

void Player::BounceToIdleUpdate()
{
	MonsterColCheck();
	// ����Ű�� ������ �ش� �������� x �̵�
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{ -300.0f, MoveDir.y };
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{ 300.0f, MoveDir.y };
	}

	// MoveDir.x�� �������� �ʰ� y�� �����Ѵ� 
	MoveDir.y += 1300.f * GameEngineTime::GetDeltaTime();
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	// ���� ������ Idle�� ��ȯ
	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
		MakeStarEffect();
		MoveDir = float4::ZERO;
		ChangeState(PlayerState::Idle);
		return;
	}
	
}

void Player::InhaleUpdate()
{
	if (true == GameEngineInput::GetInst()->IsPress("Inhale"))
	{
		if (CurDir_ == PlayerDir::Left)
		{
			InhalePos.x = -90.f;
			
		}
		else
		{
			InhalePos.x = 90.f;
		}

		InhaleCollision->SetPivot({ InhalePos });
		InhaleCollision->On();

		InhaleColCheck();
	}


	InhaleTime_ -= GameEngineTime::GetDeltaTime();

	if (PlayerAnimationRender->IsEndAnimation())
	{
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Loop");
	}
	
	// 2.5�� �� Exhausted
	if (InhaleTime_ <= 0)
	{
		InhaleEffect_->Death();
		InhaleEffSound_.Stop();

		InhaleCollision->Off();
		ChangeState(PlayerState::Exhausted);
		return;
	}

	// Ű���� �� ���� �� -> Idle
	if(GameEngineInput::GetInst()->IsUp("Inhale"))
	{
		InhaleEffect_->Death();
		InhaleEffSound_.Stop();

		InhaleCollision->Off();
		ChangeState(PlayerState::Idle);
		return;
	}

	// �ȱ�
	if (true == IsMoveKey())
	{
		InhaleEffect_->Death();
		InhaleEffSound_.Stop();

		InhaleCollision->Off();
		ChangeState(PlayerState::Walk);
		return;
	}

	// ����
	if (true == IsJumpKey())
	{
		InhaleEffect_->Death();
		InhaleEffSound_.Stop();

		InhaleCollision->Off();
		ChangeState(PlayerState::Jump);
		return;
	}
}

void Player::FullUpdate()
{
	//InhaleCollision->Off();

	if (PlayerAnimationRender->IsEndAnimation())
	{
		ChangeState(PlayerState::FullLoop);
		return;
	}

}

void Player::FullLoopUpdate()
{
	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		if (CurSwallowMonster_ == SwallowMonsterType::Max)
		{
			ChangeState(PlayerState::Swallow);
			return;
		}
		else
		{
			ChangeState(PlayerState::SwallowToSkill);
			return;
		}

	}

	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::FullWalk);
		return;
	}

	if (true == IsJumpKey())
	{
		ChangeState(PlayerState::FullJump);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Attack"))
	{
		ChangeState(PlayerState::AttackStart);
		return;
	}
}


void Player::FullWalkUpdate()
{
	MonsterColCheck();
	RunningTime_ = 0.1f;

	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		if (CurSwallowMonster_ == SwallowMonsterType::Max)
		{
			ChangeState(PlayerState::Swallow);
			return;
		}
		else
		{
			ChangeState(PlayerState::SwallowToSkill);
			return;
		}
	}

	if (false == IsMoveKey())
	{
		ChangeState(PlayerState::FullLoop);
		return;
	}

	// ���� 
	if (true == IsJumpKey())
	{
		ChangeState(PlayerState::FullJump);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Attack"))
	{
		ChangeState(PlayerState::AttackStart);
		return;
	}

	Move();
	StagePixelCheck(Speed_);

	// ������, �������� 
	//HillPixelCheck();
}

void Player::FullJumpUpdate()
{
	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		if (CurSwallowMonster_ == SwallowMonsterType::Max)
		{
			ChangeState(PlayerState::Swallow);
			return;
		}
		else
		{
			ChangeState(PlayerState::SwallowToSkill);
			return;
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Attack"))
	{
		ChangeState(PlayerState::AttackStart);
		return;
	}

	MonsterColCheck();
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	float4 YPos = { 0.0f, MoveDir.y };

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{ -300.0f, MoveDir.y };
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{ 300.0f, MoveDir.y };
	}

	// �߷�
	GravityOn();

	// �翷 + �� üũ 
	MovePixelCheck(20.0f, 20.0f);

	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
		MakeStarEffect();
		MoveDir = float4::ZERO;
		ChangeState(PlayerState::FullLoop);
		return;
	}
}

void Player::ExhaleUpdate()
{
	MonsterColCheck();
	if (PlayerAnimationRender->IsEndAnimation())
	{
		// ���̶� �ʹ� ������ -> Idle
		if (RGB(0, 0, 0) == BottomPixelColorCheck(150.f))
		{
			MakeStarEffect();
			MoveDir = float4::ZERO;

			ChangeState(PlayerState::Idle);
			return;
		}


		// ������ ������ �Ÿ� ������ ������ Fall�� ��ȯ
		MoveDir.y += 900.f * GameEngineTime::GetDeltaTime();
		SetMove(MoveDir * GameEngineTime::GetDeltaTime());

		ChangeState(PlayerState::Fall);
		return;
	}	
}

void Player::SwallowUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::ExhaustedUpdate()
{
	MonsterColCheck();
	if (PlayerAnimationRender->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::AttackStartUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		ChangeState(PlayerState::Attack);
		return;
	}
}

void Player::AttackUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		ChangeState(PlayerState::AttackEnd);
		return;
	}
}

void Player::AttackEndUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::DamagedStartUpdate()
{
	if (CurDir_ == PlayerDir::Right)
	{
		MoveDir.x = -0.5f;
	}
	else if (CurDir_ == PlayerDir::Left)
	{
		MoveDir.x = 0.5f;
	}

	MoveDir.y += 1.f * GameEngineTime::GetDeltaTime() * 10.f;
	SetMove(MoveDir);

	StagePixelCheck(Speed_);


	if (PlayerAnimationRender->IsEndAnimation())
	{
		ChangeState(PlayerState::Damaged);
		return;
	}
}

void Player::DamagedUpdate()
{

	if (CurDir_ == PlayerDir::Right)
	{
		MoveDir.x = -0.8f;
	}
	else if (CurDir_ == PlayerDir::Left)
	{
		MoveDir.x = 0.8f;
	}
	
	int LeftCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ -20.f, 0.f });
	int RightCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ 20.f, 0.f });

	float4 Pos = MoveDir;

	if (RGB(0, 0, 0) == LeftCheck)
	{
		MoveDir.x = 1.f;
	}
	else if (RGB(0, 0, 0) == RightCheck)
	{
		MoveDir.x = -1.f;
	}
	
	MoveDir.y += 1.f * GameEngineTime::GetDeltaTime() * 10.f;
	SetMove(MoveDir);

	if (PlayerAnimationRender->IsEndAnimation())
	{
		//DamagedEffSound_.Stop();
		IsHit_ = false;
		ChangeState(PlayerState::Idle);
		return;
	}


	StagePixelCheck(Speed_);
}


void Player::FullToSkillUpdate()
{
	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		ChangeState(PlayerState::SwallowToSkill);
		return;
	}

	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::FullWalk);
		return;
	}

	if (true == IsJumpKey())
	{
		ChangeState(PlayerState::FullJump);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Attack"))
	{
		ChangeState(PlayerState::AttackStart);
		return;
	}
}

void Player::SwallowToSkillUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		ChangeState(PlayerState::TransformToSkill);
		return;
	}
}

void Player::TransformToSkillUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		CurSwallowMonster_ = SwallowMonsterType::Max;
		ChangeState(PlayerState::Idle);
		return;
	}
}

//////////////////////////////////////// State

void Player::IdleStart()
{
	CurSkill_ = KirbySkill::Default;
	SkillName_ = "";
	PrevState_ = PlayerState::Idle;

	RunEffTime_ = 1.f;
	MoveDir = float4::ZERO;;

	Speed_ = 350.f;
	
	AnimationName_ = "Idle_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::WalkStart()
{
	Speed_ = 350.f;

	AnimationName_ = "Walk_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::RunStart()
{
	{
		Effect_Slide* Effect = GetLevel()->CreateActor<Effect_Slide>((int)ORDER::EFFECT);

		if (CurDir_ == PlayerDir::Right)
		{
			Effect->SetPosition(GetPosition() + float4{ -40.f, 40.f });
			Effect->SetDir(EffectDir::Right);
			
		}
		else if (CurDir_ == PlayerDir::Left)
		{
			Effect->SetPosition(GetPosition() + float4{ 40.f, 40.f });
			Effect->SetDir(EffectDir::Left);
		}
	}

	GameEngineSound::SoundPlayOneShot("Slide.wav");

	Speed_ = 500.f;

	AnimationName_ = "Run_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::RunToStopStart()
{
	{
		Effect_RunToStop* Effect = GetLevel()->CreateActor<Effect_RunToStop>((int)ORDER::EFFECT);

		if (CurDir_ == PlayerDir::Right)
		{
			Effect->SetPosition(GetPosition() + float4{ -40.f, 50.f });
			Effect->SetDir(EffectDir::Right);

		}
		else if (CurDir_ == PlayerDir::Left)
		{
			Effect->SetPosition(GetPosition() + float4{ 40.f, 50.f });
			Effect->SetDir(EffectDir::Left);
		}
	}

	GameEngineSound::SoundPlayOneShot("RunToStop.wav");

	Speed_ = 350.f;
	StopTime_ = 0.3f;

	AnimationName_ = "RunToStop_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::DownStart()
{
	DownTime_ = 0.5f;
	AnimationName_ = "Down_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);

}

void Player::SlideStart()
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

	Speed_ = 500.f;
	SlidingTime_ = 1.2f;
	SlideColTime_ = 0.5f;

	PlayerCollision->Off();

	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		MoveDir = float4::LEFT;

	}
	else if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}

	AnimationName_ = "Slide_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);

}

void Player::JumpStart()
{
	GameEngineSound::SoundPlayOneShot("Jump.wav");

	//FallTime_ = 0.8f;
	JumpPower_ = 1000.f;
	Gravity_ = 1800.f;

	// �� ���� 100�� ������ ���� ���� 
	MoveDir = float4::UP * JumpPower_;
	
	AnimationName_ = "Jump_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::FloatStart()
{
	FloatEffSound_.Stop();
	FloatEffSound_ = GameEngineSound::SoundPlayControl("Float.wav");

	//FallTime_ = 0.8f;
	Speed_ = 3.f;
	Gravity_ = 300.f;

	PlayerAnimationRender->PauseOff();

	AnimationName_ = "Float_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
	
}

void Player::FallStart()
{
	MoveDir = float4::ZERO;;

	AnimationName_ = "Fall_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::FallToBounceStart()
{
	GameEngineSound::SoundPlayOneShot("Jump.wav");

	Gravity_ = 0.0f;

	MoveDir = float4::ZERO;
	
	AnimationName_ = "FallToBounce_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::BounceToIdleStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "BounceToIdle_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::InhaleStart()
{
	{
		InhaleEffect_ = GetLevel()->CreateActor<Effect_Inhale>((int)ORDER::EFFECT);

		if (CurDir_ == PlayerDir::Right)
		{
			InhaleEffect_->SetPosition(GetPosition() + float4{ 90.f, 50.f });
			InhaleEffect_->SetDir(EffectDir::Right);

		}
		else if (CurDir_ == PlayerDir::Left)
		{
			InhaleEffect_->SetPosition(GetPosition() + float4{ -90.f, 50.f });
			InhaleEffect_->SetDir(EffectDir::Left);
		}
	}

	InhaleEffSound_.Stop();
	InhaleEffSound_ = GameEngineSound::SoundPlayControl("Inhale.wav");

	InhaleTime_ = 2.f;

	AnimationName_ = "Inhale_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::FullStart()
{
	GameEngineSound::SoundPlayOneShot("Full.wav");

	AnimationName_ = "Full_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::FullLoopStart()
{
	InhaleCollision->Off();

	AnimationName_ = "Full_Loop_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::FullWalkStart()
{
	AnimationName_ = "FullWalk_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::FullJumpStart()
{
	GameEngineSound::SoundPlayOneShot("Jump.wav");

	JumpPower_ = 1000.f;
	Gravity_ = 1800.f;

	// �� ���� 100�� ������ ���� ���� 
	MoveDir = float4::UP * JumpPower_;

	AnimationName_ = "FullJump_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::ExhaleStart()
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

	MoveDir = float4::ZERO;

	AnimationName_ = "Exhale_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::SwallowStart()
{
	GameEngineSound::SoundPlayOneShot("Swallow.wav");

	AnimationName_ = "Swallow_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::ExhaustedStart()
{
	AnimationName_ = "Exhausted_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::AttackStartStart()
{
	AnimationName_ = "AttackStart_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::AttackStart()
{
	{
		AttEffect_ = GetLevel()->CreateActor<Effect_Attack>((int)ORDER::EFFECT);

		if (CurDir_ == PlayerDir::Right)
		{
			AttEffect_->SetPosition(GetPosition() + float4{ 30.f, 10.f });
			AttEffect_->SetDir(EffectDir::Right);

		}
		else if (CurDir_ == PlayerDir::Left)
		{
			AttEffect_->SetPosition(GetPosition() + float4{ -80.f, 10.f });
			AttEffect_->SetDir(EffectDir::Left);
		}
	}

	GameEngineSound::SoundPlayOneShot("Attack.wav");

	AnimationName_ = "Attack_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::AttackEndStart()
{
	AnimationName_ = "AttackEnd_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::DamagedStartStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "DamagedStart_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::DamagedStart()
{
	if (true == IsHit_)
	{
		Hit();
	}


	PrevState_ = PlayerState::Damaged;

	DamagedEffSound_.Stop();
	GameEngineSound::SoundPlayOneShot("Damaged2.wav");

	MoveDir = float4::ZERO;

	AnimationName_ = "Damaged_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}


void Player::FullToSkillStart()
{
	GameEngineSound::SoundPlayOneShot("Full.wav");

	AnimationName_ = "Full_";
	PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
}

void Player::SwallowToSkillStart()
{
	GameEngineSound::SoundPlayOneShot("Swallow.wav");

	{
		Effect_Transform* Effect = GetLevel()->CreateActor<Effect_Transform>((int)ORDER::EFFECT);
		Effect->SetPosition(GetPosition());
	}

	AnimationName_ = "Swallow_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::TransformToSkillStart()
{
	GameEngineSound::SoundPlayOneShot("Transform.wav");
	MainPlayer->Off();

	switch (CurSwallowMonster_)
	{
	case SwallowMonsterType::Metal:
	{
		MetalKirby::MetalPlayer->SetPosition(GetPosition());
		CurSkill_ = KirbySkill::Metal;
		SkillName_ = "Metal";

		MetalKirby::MetalPlayer->On();
		MetalKirby::MetalSkill->On();
		MetalKirby::MetalName->On();
	}
		break;
	case SwallowMonsterType::Ice:
	{
		IceKirby::IcePlayer->SetPosition(GetPosition());
		CurSkill_ = KirbySkill::Ice;
		SkillName_ = "Ice";

		IceKirby::IcePlayer->On();
		IceKirby::IceSkill->On();
		IceKirby::IceName->On();
	}
		break;
	case SwallowMonsterType::Spark:
	{
		SparkKirby::SparkPlayer->SetPosition(GetPosition());
		CurSkill_ = KirbySkill::Spark;
		SkillName_ = "Spark";

		SparkKirby::SparkPlayer->On();
		SparkKirby::SparkSkill->On();
		SparkKirby::SparkName->On();
	}
		break;
	case SwallowMonsterType::Max:
		break;
	default:
		break;
	}

}
