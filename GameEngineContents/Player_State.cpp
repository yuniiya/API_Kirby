#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서
#include "Bullet.h" // 총알을 만들고 싶다.

void Player::IdleUpdate()
{
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

	if (true == GameEngineInput::GetInst()->IsPress("Inhale"))
	{
		ChangeState(PlayerState::Inhale);
		return;
	}

	// 점프 
	if (true == IsJumpKey())
	{
		//JumpTimeR_ = GameEngineInput::GetInst()->GetTime("JumpRight");
		//JumpTimeL_ = GameEngineInput::GetInst()->GetTime("JumpLeft");

		ChangeState(PlayerState::Jump);
		return;
	}
}

void Player::WalkUpdate()
{
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

	
	// 달리기


	// 점프 
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

	StagePixelCheck(Speed_);

	float4 RightDownkPos = GetPosition() + float4{ 0,20 };
	float4 LeftUpPos = GetPosition() + float4{ -20,0 };

	int DownColor = MapColImage_->GetImagePixel(RightDownkPos);
	int UpColor = MapColImage_->GetImagePixel(LeftUpPos);

	if (RGB(0, 0, 0) != DownColor)
	{
		SetMove(float4::DOWN);
	}
	else if (RGB(0, 0, 0) != UpColor)
	{
		SetMove(float4::UP);
	}
}


void Player::RunUpdate()
{
	//DirAnimationCheck();

	if (false == IsMoveKey())
	{
		ChangeState(PlayerState::RunToStop);
		return;
	}

	// 점프 
	if (true == IsJumpKey())
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	StagePixelCheck(500.f);
	



	// 속력 제한
	//if (1.f <= MoveDir.Len2D())
	//{
	//	MoveDir.Range2D(1.f);
	//}

	// 아무런 키가 눌리지 않으면 점점 감속한다
	//if (false == IsMoveKey())
	//{
	//	MoveDir += -MoveDir * GameEngineTime::GetDeltaTime();

	//	if (0.005f >= MoveDir.Len2D())
	//	{
	//		MoveDir = float4::ZERO;
	//		return;
	//	}

	//	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//	return;
	//}
}

void Player::RunToStopUpdate()
{
	MoveDir += -(MoveDir * 4.5f) * GameEngineTime::GetDeltaTime();
	float4 CheckPos = GetPosition() + MoveDir * GameEngineTime::GetDeltaTime() * Speed_;
	int Color = MapColImage_->GetImagePixel(CheckPos);

	if (RGB(0, 0, 0) != Color)
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}

	////////////////////////////////////////////////// Stop 지속 시간
	StopTime_ -= GameEngineTime::GetDeltaTime();

	if (StopTime_ < 0)
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::DownUpdate()
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

void Player::SlideUpdate()
{

	// 감속
	MoveDir += -(MoveDir * 3.f) * GameEngineTime::GetDeltaTime();
	//SetMove(MoveDir);


	float4 CheckPos = GetPosition() + MoveDir * GameEngineTime::GetDeltaTime() * Speed_;
	int Color = MapColImage_->GetImagePixel(CheckPos);

	if (RGB(0, 0, 0) != Color)
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
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
}

void Player::JumpUpdate()
{
	// 위로 이동
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	// ============ 일정 높이가 될 때까지 PauseOn
	//if (0 == PlayerAnimationRender->CurrentAnimation()->WorldCurrentFrame())
	//{
	//	PlayerAnimationRender->PauseOn();

	//}

	

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir += float4::LEFT;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir += float4::RIGHT;
	}

	// Float

	// 중력
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * Gravity_;
	
	int BottomCheck = MapColImage_->GetImagePixel(GetPosition() + float4{0, 20});
	int UpCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ 0, -100 });
	int LeftCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ -20, 0 });
	int RightCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ 20, 0 });

	// 땅에 닿았다
	if (RGB(0, 0, 0) == BottomCheck)
	{
		MoveDir = float4::ZERO;

		ChangeState(PlayerState::Idle);
		return;
	}

	if (RGB(0, 0, 0) == UpCheck)
	{
		MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * Gravity_;
	}

	//StagePixelCheck(Speed_);
	
	//if (true == GameEngineInput::GetInst()->IsPress("JumpLeft"))
	//{
	//	SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	//}
	//if (true == GameEngineInput::GetInst()->IsPress("JumpRight"))
	//{
	//	SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	//}

	//// 아무런 키가 눌리지 않으면 점점 감속한다
	//if (false == IsMoveKey())
	//{
	//	MoveDir += -MoveDir * GameEngineTime::GetDeltaTime();

		//if (0.005f >= MoveDir.Len2D())
		//{
		//	MoveDir = float4::ZERO;
		//	return;
		//}

	//	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//	return;
	//}

	//if (true == GameEngineInput::GetInst()->IsDown("Inhale"))
	//{
	//	ChangeState(PlayerState::Inhale);
	//	return;
	//}

}

void Player::FloatUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Loop");
	}
}

void Player::FallUpdate()
{
}

void Player::InhaleUpdate()
{
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Walk);
		return;
	}

	if (true == IsJumpKey())
	{
		ChangeState(PlayerState::Jump);
		return;
	}
}

void Player::FullUpdate()
{
}

void Player::ExhaleUpdate()
{
}

void Player::SwallowUpdate()
{
}

void Player::AttackUpdate()
{

}

void Player::DamagedUpdate()
{
}




//////////////////////////////////////// State

void Player::IdleStart()
{
	// 애니메이션이 바뀐다.

	AnimationName_ = "Idle_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::WalkStart()
{
	AnimationName_ = "Walk_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::RunStart()
{
	AnimationName_ = "Run_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::RunToStopStart()
{
	StopTime_ = 0.3f;
	AnimationName_ = "RunToStop_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::DownStart()
{
	DownTime_ = 0.5f;
	AnimationName_ = "Down_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);

}

void Player::SlideStart()
{
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

void Player::JumpStart()
{
	// 한 번에 100의 힘으로 위로 간다 
	MoveDir = float4::UP * JumpPower_;
	
	AnimationName_ = "Jump_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);


	//if (JumpTimeL_ <= 0.0025f)
	//{
	//	JumpPower_ = 500.f;
	//	Gravity_ = 800.f;
	//}
	//if (JumpTimeR_ <= 0.003f)
	//{
	//	JumpPower_ = 500.f;
	//	Gravity_ = 800.f;
	//}
	//else if (JumpTimeL_ >= 0.027f)
	//{
	//	JumpPower_ = 1000.f;
	//	Gravity_ = 1500.f;
	//}
	//else if (JumpTimeR_ >= 0.03f)
	//{
	//	JumpPower_ = 1000.f;
	//	Gravity_ = 1500.f;
	//}
}

void Player::FloatStart()
{
	AnimationName_ = "Float_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::FallStart()
{
	AnimationName_ = "Fall_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::InhaleStart()
{
	AnimationName_ = "Inhale_";
	//PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);

	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Loop");
}

void Player::FullStart()
{
}

void Player::ExhaleStart()
{
}

void Player::SwallowStart()
{
}

void Player::AttackStart()
{

}

void Player::DamagedStart()
{
}



