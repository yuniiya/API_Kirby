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


	// 점프 키 누른지 0.03이상이면 LongJump
	//if (GameEngineInput::GetInst()->GetTime("JumpRight") >= 0.03f)
	//{
	//	LongJump_ = true;
	//}
	//else if (GameEngineInput::GetInst()->GetTime("JumpRight") < 0.005f)
	//{
	//	LongJump_ = false;
	//}
	//	

	// 점프 
	if (true == IsJumpKey())
	{
		//if (true == LongJump_)
		//{
		//	JumpPower_ = 1000.f;
		//	Gravity_ = 1800.f;
		//}
		//else if (false == LongJump_)
		//{
		//	JumpPower_ = 500.f;
		//	Gravity_ = 900.f;
		//}

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

	Move();
	StagePixelCheck(Speed_);

	// 오르막, 내리막길 
	float4 RightDownkPos = GetPosition() + float4{ 0.f,20.f };
	float4 LeftUpPos = GetPosition() + float4{ -20.f,0.f };

	int DownColor = MapColImage_->GetImagePixel(RightDownkPos);
	int UpColor = MapColImage_->GetImagePixel(LeftUpPos);


	float4 XMove = { MoveDir.x, 0.0f };
	float4 YMove = { 0.0f, MoveDir.y - 1.f };

	if (RGB(0, 0, 0) != DownColor)
	{
		SetMove(float4::DOWN);
	}
	else if (RGB(0, 0, 0) != UpColor)
	{
		SetMove(YMove);
	}
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
	float4 RightDownkPos = GetPosition() + float4{ 0.f,20.f };
	float4 LeftUpPos = GetPosition() + float4{ -20.f,0.f };

	int DownColor = MapColImage_->GetImagePixel(RightDownkPos);
	int UpColor = MapColImage_->GetImagePixel(LeftUpPos);


	float4 XMove = { MoveDir.x, 0.0f };
	float4 YMove = { 0.0f, MoveDir.y - 1.f };

	if (RGB(0, 0, 0) != DownColor)
	{
		SetMove(float4::DOWN);
	}
	else if (RGB(0, 0, 0) != UpColor)
	{
		SetMove(YMove);
	}


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
	float4 RightDownkPos = GetPosition() + float4{ 0.f,20.f };
	float4 LeftUpPos = GetPosition() + float4{ -20.f,0.f };

	int DownColor = MapColImage_->GetImagePixel(RightDownkPos);
	int UpColor = MapColImage_->GetImagePixel(LeftUpPos);

	float4 XMove = { MoveDir.x, 0.0f };
	float4 YMove = { 0.0f, MoveDir.y - 1.f };

	if (RGB(0, 0, 0) != DownColor)
	{ 
		SetMove(float4::DOWN);
	}
	else if (RGB(0, 0, 0) != UpColor)
	{
		SetMove(YMove);
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
	float4 RightDownkPos = GetPosition() + float4{ 0.f,20.f };
	float4 LeftUpPos = GetPosition() + float4{ -20.f,0.f };

	int RightDownColor = MapColImage_->GetImagePixel(RightDownkPos);
	int LeftUpColor = MapColImage_->GetImagePixel(LeftUpPos);


	float4 XMove = { MoveDir.x, 0.0f };
	float4 YMove = { 0.0f, MoveDir.y - 1.f };

	if (RGB(0, 0, 0) != RightDownColor)
	{
		SetMove(float4::DOWN);
	}
	else if (RGB(0, 0, 0) != LeftUpColor)
	{
		SetMove(YMove);
	}
}

void Player::JumpUpdate()
{
	// 위로 이동
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	float4 XPos = { MoveDir.x, 0.0f };
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
		MoveDir += float4::LEFT;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir += float4::RIGHT;
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
	float4 CheckPos = GetPosition() + float4{0, 20.f};
	int Color = MapColImage_->GetImagePixel(CheckPos);


	float4 CheckPos2 = GetPosition() + float4{ 0, 180.f };
	int Color2 = MapColImage_->GetImagePixel(CheckPos2);

	if (RGB(0, 0, 0) == Color)
	{
		MoveDir = float4::ZERO;
		ChangeState(PlayerState::Idle);
		return;
	}
	else if (RGB(0, 0, 0) != Color2)
	{
		FallTime_ -= GameEngineTime::GetDeltaTime();
		if (FallTime_ <= 0.f)
		{
			ChangeState(PlayerState::Fall);
			return;
		}
	}


	
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
	// 공기 내뱉고 내려오기
	if (GameEngineInput::GetInst()->IsDown("Inhale"))
	{
		ChangeState(PlayerState::Exhale);
		return;
	}

	if (PlayerAnimationRender->IsEndAnimation())
	{
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Loop");
	}

	// Float상태에서 이동
	MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4{-0.8f, 0.f};
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Loop");
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4{0.8f, 0.f};
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_ + "_Loop");
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir = float4{ 0.f, -0.8f};
	}

	// 중력
	if (false == IsJumpKey())
	{
		GravityOn();
		SetMove(MoveDir);
	}
	else if (true == IsJumpKey())
	{
		MoveDir.y = -0.5f;
		SetMove(MoveDir);
	}

	// 양 옆 + 위 픽셀 체크
	MovePixelCheck(20.0f, 20.0f);

	// Float상태로 바닥에 닿았다
	float4 CheckPos = GetPosition() + float4{ 0, 20.f };

	int Color = MapColImage_->GetImagePixel(CheckPos);
	if (RGB(0, 0, 0) == Color)
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


	// 아래로 떨어진다
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());


	float4 XPos = { MoveDir.x, 0.0f };
	float4 YPos = { 0.0f, MoveDir.y };

	// 발이 땅을 향하는 애니메이션 재생
	if (1 == PlayerAnimationRender->CurrentAnimation()->WorldCurrentFrame())
	{
		if (YPos.y >= 150.f)
		{
			PlayerAnimationRender->PauseOn();
			YPos = { 0.0f, MoveDir.y };
		}
	}

	// 땅에 가까워지면 머리가 땅을 향하는 애니메이션 재생
	float4 StageCheckPos = GetPosition() + float4{ 0, 200.f };
	int StageColor = MapColImage_->GetImagePixel(StageCheckPos);
	if (RGB(0, 0, 0) == StageColor)
	{
		PlayerAnimationRender->PauseOff();

	}

	// 땅에 닿기 전 까지는 4번째 애니메이션에서 Pause
	if (4 == PlayerAnimationRender->CurrentAnimation()->WorldCurrentFrame())
	{
		PlayerAnimationRender->PauseOn();
		StageCheckPos = {0.0f, 0.0f};
	}

	// 땅에 닿으면 Pause 해제 후 한 번 튕긴다
	StageCheckPos = GetPosition() + float4{ 0, 20.f };
	StageColor = MapColImage_->GetImagePixel(StageCheckPos);
	if (RGB(0, 0, 0) == StageColor)
	{
		MoveDir = float4{ MoveDir.x, -1.f } * 400.f;
		SetMove(MoveDir * GameEngineTime::GetDeltaTime());
		Gravity_ = 1200.f;
		
	}

	GravityOn();

	// 튕긴다
	if (Gravity_ >= 1200.f)
	{
		PlayerAnimationRender->PauseOff();
	}


	// 튕긴 후 다시 땅에 착지 => Idle
	StageCheckPos = GetPosition() + float4{ 0, 40.f };
	StageColor = MapColImage_->GetImagePixel(StageCheckPos);
	if (RGB(0, 0, 0) == StageColor
		&& PlayerAnimationRender->IsEndAnimation())
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

void Player::ExhaleUpdate()
{
	if (PlayerAnimationRender->IsEndAnimation())
	{
		ChangeState(PlayerState::Fall);
		return;
	}
	
	
}

void Player::SwallowUpdate()
{
}

void Player::ExhaustedUpdate()
{
	ChangeState(PlayerState::Idle);
	return;

	//if (PlayerAnimationRender->IsEndAnimation())
	//{
	//	
	//}
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
	Speed_ = 350.f;

	/*JumpPower_ = 1000.f;
	Gravity_ = 1800.f;*/
	
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
	FallTime_ = 0.8f;
	JumpPower_ = 1000.f;
	Gravity_ = 1800.f;

	// 한 번에 100의 힘으로 위로 간다 
	MoveDir = float4::UP * JumpPower_;
	
	AnimationName_ = "Jump_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::FloatStart()
{
	FallTime_ = 0.8f;
	Speed_ = 5.f;
	Gravity_ = 100.f;

	AnimationName_ = "Float_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
	
}

void Player::FallStart()
{
	Gravity_ = 500.f;

	MoveDir = float4::DOWN * Gravity_;

	AnimationName_ = "Fall_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::InhaleStart()
{
	InhaleTime_ = 2.5f;

	AnimationName_ = "Inhale_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::FullStart()
{
}

void Player::ExhaleStart()
{
	AnimationName_ = "Exhale_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::SwallowStart()
{
}

void Player::ExhaustedStart()
{
	AnimationName_ = "Exhausted_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::AttackStart()
{

}

void Player::DamagedStart()
{
}



