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
		ChangeState(PlayerState::Jump);
		return;
	}

	// 오르막, 내리막길 
	float4 RightDownkPos = GetPosition() + float4{ 0.f,20.f };
	float4 LeftUpPos = GetPosition() + float4{ -20.f,0.f };

	int DownColor = MapColImage_->GetImagePixel(RightDownkPos);
	int UpColor = MapColImage_->GetImagePixel(LeftUpPos);


	float4 XMove = { MoveDir.x, 0.0f };
	float4 YMove = { 0.0f, MoveDir.y };

	if (RGB(0, 0, 0) != DownColor)
	{
		SetMove(float4::DOWN);
	}
	else if (RGB(0, 0, 0) != UpColor)
	{
		SetMove(YMove);
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

	Move();
	StagePixelCheck(Speed_);

	// 오르막, 내리막길 
	HillPixelCheck();
}

void Player::RunUpdate()
{
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

	Move();
	StagePixelCheck(500.f);



	// 오르막, 내리막길 
	HillPixelCheck();

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

}

void Player::RunToStopUpdate()
{
	// 이동 시 미래 위치 픽셀 체크
	MoveDir += -(MoveDir * 3.f) * GameEngineTime::GetDeltaTime();
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

	// 오르막, 내리막길 
	HillPixelCheck();

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

	// 땅 밑으로는 못 가게
	StagePixelCheck(Speed_);

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

void Player::JumpUpdate()
{
	// 위로 이동
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	float4 YPos = { 0.0f, MoveDir.y };

	// 일정 높이 될 때까지 Pause
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
	

	// 중력
	GravityOn();

	YPos = { 0.0f, MoveDir.y };
	if (YPos.y > -500.f)
	{
		PlayerAnimationRender->PauseOff();
	}
	
	// 양옆 + 위 체크 
	MovePixelCheck(20.0f, 20.0f);

	// 바닥에 닿았다
	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
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
	// 공기 내뱉고 내려오기
	if (GameEngineInput::GetInst()->IsDown("Inhale"))
	{
		if (true == IsJumpKey())
		{
			ChangeState(PlayerState::Float);
			return;
		}

		ChangeState(PlayerState::Exhale);
		return;
	}

	if (true == PlayerAnimationRender->IsEndAnimation())
	{
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Loop");
	}

	// Float상태에서 이동
	//MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{-200.f, MoveDir.y};
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Loop");
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{200.f, MoveDir.y };
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Loop");
	}
	else if (false == IsMoveKey())
	{
		MoveDir.x = 0.0f;
	}

	// 중력
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

	// 양 옆 + 위 픽셀 체크
	MovePixelCheck(20.0f, 20.0f);

	// Float상태로 바닥에 닿았다
	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
		MoveDir = float4::UP;
		SetMove(MoveDir);
	}
}

void Player::FallUpdate()
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
	MoveDir.y += 1500.f * GameEngineTime::GetDeltaTime();


	// 땅에 닿지 않았다면 MoveDir.y로 가속하며 떨어진다 
	if (RGB(0, 0, 0) != BottomPixelColorCheck(20.f))
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime());
	}
	else
	{
		ChangeState(PlayerState::FallToBounce);
		return;
	}

}

void Player::FallToBounceUpdate()
{
	// 방향키를 누르면 해당 방향으로 x 이동
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{ -300.0f, MoveDir.y };
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{ 300.0f, MoveDir.y };
	}

	// 땅에 닿으면 위로 한 번 튕긴다
	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
		MoveDir.y = -400.f;
	}

	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	// 튕겼으면 BounceToIdle로 전환
	if (RGB(0, 0, 0) != BottomPixelColorCheck(130.f))
	{
		ChangeState(PlayerState::BounceToIdle);
		return;
	}
}

void Player::BounceToIdleUpdate()
{
	// 방향키를 누르면 해당 방향으로 x 이동
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{ -300.0f, MoveDir.y };
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{ 300.0f, MoveDir.y };
	}

	// MoveDir.x는 움직이지 않고 y만 가속한다 
	MoveDir.y += 1300.f * GameEngineTime::GetDeltaTime();
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	// 땅에 닿으면 Idle로 전환
	if (RGB(0, 0, 0) == BottomPixelColorCheck(20.f))
	{
		MoveDir = float4::ZERO;

		ChangeState(PlayerState::Idle);
		return;
	}
	
}

void Player::InhaleUpdate()
{
	InhaleTime_ -= GameEngineTime::GetDeltaTime();

	if (PlayerAnimationRender->IsEndAnimation())
	{
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Loop");
	}
	
	// 2.5초 후 Exhausted
	if (InhaleTime_ <= 0)
	{
		ChangeState(PlayerState::Exhausted);
		return;
	}

	// 키에서 손 뗐을 때 -> Idle
	if(GameEngineInput::GetInst()->IsUp("Inhale"))
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	// 걷기
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Walk);
		return;
	}

	// 점프
	if (true == IsJumpKey())
	{
		ChangeState(PlayerState::Jump);
		return;
	}
}

void Player::FullUpdate()
{
}

void Player::FullWalkUpdate()
{
}

void Player::FullJumpUpdate()
{
}

void Player::ExhaleUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		// 땅이랑 너무 가깝다 -> Idle
		if (RGB(0, 0, 0) == BottomPixelColorCheck(150.f))
		{
			MoveDir = float4::ZERO;

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

void Player::SwallowUpdate()
{
}

void Player::ExhaustedUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

void Player::AttackStartUpdate()
{
}

void Player::AttackUpdate()
{

}

void Player::AttackEndUpdate()
{
}

void Player::DamagedStartUpdate()
{
	//PlayerAnimationRender->PauseOn();

	//float Time = 0.0f;

	//Time += GameEngineTime::GetDeltaTime();

	//if (1.f >= Time)
	//{
	//	ChangeState(PlayerState::Damaged);
	//	return;
	//}

	if (CurDir_ == PlayerDir::Right)
	{
		MoveDir.x = -0.5f;
	}
	else if (CurDir_ == PlayerDir::Left)
	{
		MoveDir.x = 0.5f;
	}

	SetMove(MoveDir);


	ChangeState(PlayerState::Damaged);
	return;

	//if (1.8f <= GetAccTime())
	//{
	//	ReSetAccTime();

	//	ChangeState(PlayerState::Damaged);
	//	return;
	//}

	
}

void Player::DamagedUpdate()
{
	//PlayerAnimationRender->PauseOff();

	if (CurDir_ == PlayerDir::Right)
	{
		MoveDir.x = -1.2f;
	}
	else if (CurDir_ == PlayerDir::Left)
	{
		MoveDir.x = 1.2f;
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

	SetMove(MoveDir);

	if (PlayerAnimationRender->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}




//////////////////////////////////////// State

void Player::IdleStart()
{
	MoveDir = float4::ZERO;;

	Speed_ = 350.f;
	
	AnimationName_ = "Idle_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::WalkStart()
{
	Speed_ = 350.f;

	AnimationName_ = "Walk_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::RunStart()
{
	Speed_ = 500.f;

	AnimationName_ = "Run_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::RunToStopStart()
{
	Speed_ = 350.f;
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

void Player::JumpStart()
{
	//FallTime_ = 0.8f;
	JumpPower_ = 1000.f;
	Gravity_ = 1800.f;

	// 한 번에 100의 힘으로 위로 간다 
	MoveDir = float4::UP * JumpPower_;
	
	AnimationName_ = "Jump_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::FloatStart()
{
	//FallTime_ = 0.8f;
	Speed_ = 3.f;
	Gravity_ = 300.f;

	PlayerAnimationRender->PauseOff();

	AnimationName_ = "Float_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
	
}

void Player::FallStart()
{
	MoveDir = float4::ZERO;;

	AnimationName_ = "Fall_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::FallToBounceStart()
{
	Gravity_ = 0.0f;

	MoveDir = float4::ZERO;
	
	AnimationName_ = "FallToBounce_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::BounceToIdleStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "BounceToIdle_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::InhaleStart()
{
	InhaleTime_ = 2.f;

	AnimationName_ = "Inhale_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::FullStart()
{
	AnimationName_ = "Full_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::FullWalkStart()
{
	AnimationName_ = "FullWalk_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::FullJumpStart()
{
	AnimationName_ = "FullJump_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::ExhaleStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "Exhale_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::SwallowStart()
{
	AnimationName_ = "Swallow_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::ExhaustedStart()
{
	AnimationName_ = "Exhausted_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::AttackStartStart()
{
	AnimationName_ = "AttackStart_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::AttackStart()
{
	AnimationName_ = "Attack_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::AttackEndStart()
{
	AnimationName_ = "AttackEnd_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::DamagedStartStart()
{
	MoveDir = float4::ZERO;

	AnimationName_ = "DamagedStart_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::DamagedStart()
{
	AnimationName_ = "Damaged_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}



