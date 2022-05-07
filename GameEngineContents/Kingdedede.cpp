#include "Kingdedede.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>

Kingdedede::Kingdedede()
	: Speed_(80.f)
{
	CurState_ = MonsterState::Max;
	MoveDir = float4::LEFT;
}

Kingdedede::~Kingdedede()
{

}

void Kingdedede::ChangeState(MonsterState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case MonsterState::Idle:
			IdleStart();
			break;
		case MonsterState::Walk:
			WalkStart();
			break;
		case MonsterState::Jump:
			JumpStart();
			break;
		case MonsterState::Swallow:
			SwallowStart();
			break;
		case MonsterState::Scream:
			ScreamStart();
			break;
		case MonsterState::Attack:
			AttackStart();
			break;
		case MonsterState::Damaged:
			DamagedStart();
			break;
		}
	}

	CurState_ = _State;
}

void Kingdedede::MonsterStateUpdate()
{
	switch (CurState_)
	{
	case MonsterState::Idle:
		IdleUpdate();
		break;
	case MonsterState::Walk:
		WalkUpdate();
		break;
	case MonsterState::Jump:
		JumpUpdate();
		break;
	case MonsterState::Swallow:
		SwallowUpdate();
		break;
	case MonsterState::Scream:
		ScreamUpdate();
		break;
	case MonsterState::Attack:
		AttackUpdate();
		break;
	case MonsterState::Damaged:
		DamagedUpdate();
		break;
	}
}

void Kingdedede::Start()
{
	// 히트 박스
	MonsterCollision = CreateCollision("BossHitBox", { 70, 70 });


	AnimationRender = CreateRenderer();
	AnimationRender->SetPivotType(RenderPivot::CENTER);
	AnimationRender->SetPivot({ 0.f, 35.f });

	// Boss - Left
	//AnimationRender->CreateAnimation("Boss_Left.bmp", "Idle_Left", 0, 3, 0.5f, true);
	AnimationRender->CreateAnimation("King_Left.bmp", "Idle_Left", 0, 3, 0.5f, true);
	//AnimationRender->CreateAnimation("Pengy_Left.bmp", "Walk_Left", 1, 2, 0.1f, true);
	//AnimationRender->CreateAnimation("Pengy_Left.bmp", "Swallow_Left", 7, 7, 0.1f, false);
	//AnimationRender->CreateAnimation("Pengy_Left.bmp", "Attack_Left", 3, 5, 0.1f, true);
	//AnimationRender->CreateAnimation("Pengy_Left.bmp", "Damaged_Left", 7, 7, 0.1f, false);

	// Boss - Right
	//AnimationRender->CreateAnimation("Boss_Right.bmp", "Idle_Right", 0, 3, 0.5f, true);
	AnimationRender->CreateAnimation("King_Right.bmp", "Idle_Right", 0, 3, 0.5f, true);
	//AnimationRender->CreateAnimation("Pengy_Right.bmp", "Walk_Right", 1, 2, 0.1f, true);
	//AnimationRender->CreateAnimation("Pengy_Right.bmp", "Swallowe_Left", 7, 7, 0.1f, false);
	//AnimationRender->CreateAnimation("Pengy_Right.bmp", "Attack_Right", 3, 5, 0.1f, true);
	//AnimationRender->CreateAnimation("Pengy_Right.bmp", "Damaged_Right", 7, 7, 0.1f, false);

	AnimationName_ = "Idle_";
	ChangeDirText_ = "Left";
	ChangeState(MonsterState::Idle);
}

void Kingdedede::Update()
{
	ColMapUpdate();

	//DirAnimationCheck();
	MonsterStateUpdate();

	// 항상 땅에 붙어있도록 체크
	GroundPixelCheck();
}

void Kingdedede::Render()
{
}


void Kingdedede::IdleUpdate()
{

}

void Kingdedede::WalkUpdate()
{
	if (RGB(0, 0, 0) == BottomPixelColorCheck(30.f))
	{
		WallPixelCheck(30.f, Speed_);
	}

}

void Kingdedede::JumpUpdate()
{
}

void Kingdedede::SwallowUpdate()
{
}

void Kingdedede::ScreamUpdate()
{
}

void Kingdedede::AttackUpdate()
{
}

void Kingdedede::DamagedUpdate()
{
}

void Kingdedede::IdleStart()
{
	AnimationName_ = "Idle_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::WalkStart()
{
	AnimationName_ = "Walk_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::JumpStart()
{
	AnimationName_ = "Jump_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::SwallowStart()
{
	AnimationName_ = "Swallow_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::ScreamStart()
{
	AnimationName_ = "Scream_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::AttackStart()
{
	AnimationName_ = "Attack_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::DamagedStart()
{
	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Kingdedede::WallPixelCheck(float _x, float _Speed)
{
	// 벽에 부딫히면 반대 방향으로 전환

	MonsterDir CheckDir_ = CurDir_;

	float4 LeftCheck = GetPosition() + float4{ -_x, 0.0f };
	float4 RightCheck = GetPosition() + float4{ _x, 0.0f };

	int LeftColor = MapColImage_->GetImagePixel(LeftCheck);
	int RightColor = MapColImage_->GetImagePixel(RightCheck);

	if (CurDir_ == MonsterDir::Left)
	{
		if (RGB(0, 0, 0) == LeftColor)
		{
			CurDir_ = MonsterDir::Right;
			ChangeDirText_ = "Right";
			AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
			MoveDir.x = 1.f;
		}
		else
		{
			MoveDir.x = -1.f;
		}
	}


	if (CurDir_ == MonsterDir::Right)
	{

		if (RGB(0, 0, 0) == RightColor)
		{
			CurDir_ = MonsterDir::Left;
			ChangeDirText_ = "Left";
			AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
			MoveDir.x = -1.f;
		}
		else
		{
			MoveDir.x = 1.f;
		}
	}

	SetMove(MoveDir * GameEngineTime::GetDeltaTime() * _Speed);
}

void Kingdedede::MonsterColCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == MonsterCollision->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			// (엑터 제외한) 콜리전만 파괴 
			ColList[i]->Death();
		}
	}
}
