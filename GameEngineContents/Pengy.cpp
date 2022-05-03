#include "Pengy.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>

Pengy::Pengy()
	: Speed_(80.f)
{
	CurState_ = MonsterState::Max;
	MoveDir = float4::LEFT;
}

Pengy::~Pengy()
{

}

void Pengy::ChangeState(MonsterState _State)
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
		case MonsterState::Swallowed:
			SwallowedStart();
			break;
		case MonsterState::Attack:
			AttackStart();
			break;
		}
	}

	CurState_ = _State;
}

void Pengy::MonsterStateUpdate()
{
	switch (CurState_)
	{
	case MonsterState::Idle:
		IdleUpdate();
		break;
	case MonsterState::Walk:
		WalkUpdate();
		break;
	case MonsterState::Swallowed:
		SwallowedUpdate();
		break;
	case MonsterState::Attack:
		AttackUpdate();
		break;
	}
}

void Pengy::Start()
{
	// 히트 박스
	MonsterCollision = CreateCollision("PengyCol", { 70, 70 });


	AnimationRender = CreateRenderer();
	AnimationRender->SetPivotType(RenderPivot::CENTER);
	AnimationRender->SetPivot({ 0.f, 35.f });

	// Pengy - Left
	AnimationRender->CreateAnimation("Pengy_Left.bmp", "Idle_Left", 0, 0, 0.1f, false);
	AnimationRender->CreateAnimation("Pengy_Left.bmp", "Walk_Left", 1, 2, 0.1f, true);
	//AnimationRender->CreateAnimation("Pengy_Left.bmp", "Swallowed_Left", 7, 7, 0.1f, false);
	AnimationRender->CreateAnimation("Pengy_Left.bmp", "Attack_Left", 3, 5, 0.1f, true);
	AnimationRender->CreateAnimation("Pengy_Left.bmp", "Damaged_Left", 7, 7, 0.1f, false);

	// Pengy _ Right
	AnimationRender->CreateAnimation("Pengy_Right.bmp", "Idle_Right", 0, 0, 0.1f, false);
	AnimationRender->CreateAnimation("Pengy_Right.bmp", "Walk_Right", 1, 2, 0.1f, true);
	//AnimationRender->CreateAnimation("Pengy_Right.bmp", "Swallowed_Left", 7, 7, 0.1f, false);
	AnimationRender->CreateAnimation("Pengy_Right.bmp", "Attack_Right", 3, 5, 0.1f, true);
	AnimationRender->CreateAnimation("Pengy_Right.bmp", "Damaged_Right", 7, 7, 0.1f, false);

	AnimationName_ = "Idle_";
	ChangeDirText_ = "Left";
	ChangeState(MonsterState::Idle);
}

void Pengy::Update()
{
	ColMapUpdate();

	//DirAnimationCheck();
	MonsterStateUpdate();

	// 항상 땅에 붙어있도록 체크
	GroundPixelCheck();
}

void Pengy::Render()
{
}


void Pengy::IdleUpdate()
{

}

void Pengy::WalkUpdate()
{
	if (RGB(0, 0, 0) == BottomPixelColorCheck(30.f))
	{
		WallPixelCheck(30.f, Speed_);
	}

}

void Pengy::SwallowedUpdate()
{
}

void Pengy::AttackUpdate()
{
}

void Pengy::IdleStart()
{
	AnimationName_ = "Idle_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Pengy::WalkStart()
{
	Speed_ = 50.0f;
	AnimationName_ = "Walk_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Pengy::SwallowedStart()
{
	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Pengy::AttackStart()
{
	AnimationName_ = "Attack_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Pengy::WallPixelCheck(float _x, float _Speed)
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

void Pengy::MonsterColCheck()
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

	std::vector<GameEngineCollision*> SwallowColList;

	if (true == MonsterCollision->CollisionResult("InhaleCol", SwallowColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < SwallowColList.size(); i++)
		{
			// (엑터 제외한) 콜리전만 파괴 

			ChangeState(MonsterState::Swallowed);
			return;
		}

	}
}