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
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Walk);
		return;
	}
}

void Player::WalkUpdate()
{
	if (false == IsMoveKey())
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	// 점프 
	if (true == GameEngineInput::GetInst()->IsDown("JumpLeft") || true == GameEngineInput::GetInst()->IsDown("JumpRight"))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	DirAnimationCheck();

	MoveDir = float4::ZERO;


	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
		//SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
		//SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);

		// 가속
		// MoveDir += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir = float4::UP;
		//SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir = float4::DOWN;
		//SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	}


	// 미래 위치 -> 이동한다면 이 위치에 도착해있을 것
	float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	// 미래 위치에서 중심점을 발끝으로 내린 위치
	float4 CheckPos = NextPos + float4(0.0f, 25.0f);

	// 플레이어 위치 + N = 플레이어 발 끝 (N에 적절한 값을 넣어서 색 가져올 위치 조정할 수 있다)
	// 충돌맵의 색을 가져와서 
	int Color = MapColImage_->GetImagePixel(CheckPos);
	// 초록색이(땅이) 아니라면 && 카메라 바깥 영역이 아니라면 -> 이동 
	if (RGB(0, 255, 0) != Color && RGB(0, 0, 0) != Color)
	{
		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}
}


void Player::RunUpdate()
{
	// 속력 제한
	if (0.3f <= MoveDir.Len2D())
	{
		MoveDir.Range2D(0.3f);
	}

	// 아무런 키가 눌리지 않으면 점점 감속한다
	if (false == IsMoveKey())
	{
		MoveDir += -MoveDir * GameEngineTime::GetDeltaTime();

		if (0.005f >= MoveDir.Len2D())
		{
			MoveDir = float4::ZERO;
			return;
		}

		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		return;
	}
}

void Player::RunToStopUpdate()
{
}

void Player::DownUpdate()
{
}

void Player::SlideUpdate()
{
}

void Player::JumpUpdate()
{
	SetMove(MoveDir * GameEngineTime::GetDeltaTime());

	// 중력
	MoveDir += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;


	if (true == GameEngineInput::GetInst()->IsPress("JumpLeft"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("JumpRight"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	}

	// 아무런 키가 눌리지 않으면 점점 감속한다
	if (false == IsMoveKey())
	{
		MoveDir += -MoveDir * GameEngineTime::GetDeltaTime();

		if (0.005f >= MoveDir.Len2D())
		{
			MoveDir = float4::ZERO;
			return;
		}

		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		return;
	}

}

void Player::FloatUpdate()
{
}

void Player::FallUpdate()
{
}

void Player::InhaleUpdate()
{
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
	//PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::WalkStart()
{
	AnimationName_ = "Walk_";
	//PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Player::RunStart()
{
}

void Player::RunToStopStart()
{
}

void Player::DownStart()
{
}

void Player::SlideStart()
{
}

void Player::JumpStart()
{
}

void Player::FloatStart()
{
}

void Player::FallStart()
{
}

void Player::InhaleStart()
{
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



