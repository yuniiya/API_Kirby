#include "Monster.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>

Monster::Monster()
	: Speed_(100.f)
{

}
Monster::~Monster()
{

}

void Monster::ChangeState(MonsterState _State)
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

void Monster::MonsterStateUpdate()
{
	if (CurState_ != CurState_)
	{
		switch (CurState_)
		{
		case MonsterState::Idle:
			IdleUpdate();
			break;
		case MonsterState::Walk:
			WalkUpdate();
			break;
		case MonsterState::Attack:
			AttackUpdate();
			break;
		case MonsterState::Damaged:
			DamagedUpdate();
			break;
		}
	}
}


void Monster::Start()
{
	MonsterAnimationRenderer = CreateRenderer();
	MonsterAnimationRenderer->SetPivotType(RenderPivot::BOT);
	MonsterAnimationRenderer->SetPivot({ 0.f, 140.f });
}

void Monster::Update()
{
}

void Monster::Render()
{
}

void Monster::StagePixelCheck(float _Speed)
{
}


void Monster::DirAnimationCheck()
{
}

void Monster::IdleStart()
{
}

void Monster::WalkStart()
{
}

void Monster::AttackStart()
{
}

void Monster::DamagedStart()
{
}

void Monster::IdleUpdate()
{
}

void Monster::WalkUpdate()
{
}

void Monster::AttackUpdate()
{
}

void Monster::DamagedUpdate()
{
}
