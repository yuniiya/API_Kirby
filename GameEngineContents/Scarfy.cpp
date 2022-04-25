#include "Scarfy.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>

Scarfy::Scarfy()
{
	CurState_ = MonsterState::Max;
	MoveDir = float4::LEFT;
}
Scarfy::~Scarfy()
{

}

void Scarfy::ChangeState(MonsterState _State)
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
		case MonsterState::Damaged:
			DamagedStart();
			break;
		}
	}

	CurState_ = _State;
}

void Scarfy::MonsterStateUpdate()
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
	case MonsterState::Damaged:
		DamagedUpdate();
		break;
	}
}

void Scarfy::Start()
{
	// 히트 박스
	MonsterCollision = CreateCollision("ScarfyHitBox", { 50, 50 });

	AnimationRender = CreateRenderer();
	AnimationRender->SetPivotType(RenderPivot::CENTER);
	AnimationRender->SetPivot({ 0.f, 35.f });

	// Scarfy - Left
	MonsterAnimationRenderer->CreateAnimation("Scarfy_Left.bmp", "Scarfy_Idle_Left", 0, 2, 0.1f, true);
	MonsterAnimationRenderer->CreateAnimation("Scarfy_Left.bmp", "Scarfy_Damaged_Left", 3, 3, 0.1f, false);

	// Scarfy - Right
	MonsterAnimationRenderer->CreateAnimation("Scarfy_Right.bmp", "Scarfy_Idle_Right", 0, 2, 0.1f, true);
	MonsterAnimationRenderer->CreateAnimation("Scarfy_Right.bmp", "Scarfy_Damaged_Right", 3, 3, 0.1f, false);

	AnimationName_ = "Idle_";
	ChangeDirText_ = "Left";
	ChangeState(MonsterState::Idle);
}

void Scarfy::Update()
{
	ColMapUpdate();

	DirAnimationCheck();
	MonsterStateUpdate();

	// 항상 땅에 붙어있도록 체크
	GroundPixelCheck();
}

void Scarfy::Render()
{
}

void Scarfy::IdleUpdate()
{
}

void Scarfy::SwallowedUpdate()
{
}

void Scarfy::DamagedUpdate()
{
}

void Scarfy::IdleStart()
{
	Speed_ = 10.0f;
	AnimationName_ = "Idle_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Scarfy::SwallowedStart()
{
	AnimationName_ = "Swallowed_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Scarfy::DamagedStart()
{
	AnimationName_ = "Damaged_";
	AnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

