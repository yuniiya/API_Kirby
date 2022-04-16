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
		ChangeState(PlayerState::Walk);
		return;
	} 
	else	if (true == IsMoveKey()
		&& RunningTime_ > 0)
	{
		ChangeState(PlayerState::Run);
		return;
	}


	
	if (true == GameEngineInput::GetInst()->IsDown("Down"))
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

	MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}


	float4 CheckLeftPos = GetPosition() + float4(-20.f, 0.f);
	float4 CheckRightPos = GetPosition() + float4(20.f, 0.f);

	int ColorLeft = MapColImage_->GetImagePixel(CheckLeftPos);
	int ColorRight = MapColImage_->GetImagePixel(CheckRightPos);

	if (RGB(0, 255, 0) != ColorLeft && RGB(0, 255, 0) != ColorRight && RGB(0, 0, 0) != ColorLeft)
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}

	// SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//StagePixelCheck();
}


void Player::RunUpdate()
{
	//DirAnimationCheck();

	if (false == IsMoveKey())
	{
		ChangeState(PlayerState::RunToStop);
		return;
	}

	MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}

	float4 CheckLeftPos = GetPosition() + float4(-20.f, 0.f);
	float4 CheckRightPos = GetPosition() + float4(20.f, 0.f);

	int ColorLeft = MapColImage_->GetImagePixel(CheckLeftPos);
	int ColorRight = MapColImage_->GetImagePixel(CheckRightPos);

	if (RGB(0, 255, 0) != ColorLeft && RGB(0, 255, 0) != ColorRight && RGB(0, 0, 0) != ColorLeft)
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
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

	//	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	//	return;
	//}
}

void Player::RunToStopUpdate()
{
	if (true == PlayerAnimationRender->IsEndAnimation())
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


	RunningTime_ = 0.5f;

	if (true == IsMoveKey() && RunningTime_ > 0)
	{
		ChangeState(PlayerState::Slide);
		return;
	}
}

void Player::SlideUpdate()
{
	if (true == GameEngineInput::GetInst()->IsFree("Down"))
	{
		ChangeState(PlayerState::Idle);
		return;
	}

}

void Player::JumpUpdate()
{
	if (false == IsMoveKey())
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	//SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	//// 중력
	//MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;


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

	//	if (0.005f >= MoveDir.Len2D())
	//	{
	//		MoveDir = float4::ZERO;
	//		return;
	//	}

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
	AnimationName_ = "RunToStop_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::DownStart()
{
	AnimationName_ = "Down_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);

}

void Player::SlideStart()
{
	AnimationName_ = "Slide_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);

	//if (ChangeDirText_ == "Right")
	//	MoveDir += float4::RIGHT;
	//else
	//	MoveDir += float4::LEFT;
}

void Player::JumpStart()
{
	AnimationName_ = "Jump_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::FloatStart()
{
	AnimationName_ = "Float_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::FallStart()
{
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



