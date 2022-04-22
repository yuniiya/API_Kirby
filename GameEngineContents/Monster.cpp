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

	// Default Left
	{
		// Waddle
		MonsterAnimationRenderer->CreateAnimation("WaddleDee_Left", "Waddle_Walk_Left", 0, 4, 0.8f, true);
		MonsterAnimationRenderer->CreateAnimation("WaddleDee_Left", "Waddle_Swallowed_Left", 8, 8, 0.8f, false);
		MonsterAnimationRenderer->CreateAnimation("WaddleDee_Left", "Waddle_Damaged_Left", 9, 9, 0.8f, false);

		// Big Waddle
		MonsterAnimationRenderer->CreateAnimation("BigWaddleDee_Right", "BigWaddle_Walk_Right", 0, 4, 0.8f, true);
		MonsterAnimationRenderer->CreateAnimation("BigWaddleDee_Right", "BigWaddle_Swallowed_Right", 5, 5, 0.8f, false);
		MonsterAnimationRenderer->CreateAnimation("BigWaddleDee_Right", "BigWaddle_Damaged_Right", 6, 6, 0.8f, false);

		// Snooter
		MonsterAnimationRenderer->CreateAnimation("Snooter_Left", "Snooter_Idle_Left", 8, 11, 0.5f, true);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Left", "Snooter_Walk_Left", 0, 3, 0.5f, false);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Left", "Snooter_Swallow_Left", 4, 6, 0.5f, false);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Left", "Snooter_Swallow_Left2", 9, 9, 0.5f, false);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Left", "Snooter_Swallow_Left3", 8, 8, 0.5f, false);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Left", "Snooter_Swallow_Left4", 7, 8, 0.1f, false);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Left", "Snooter_Attack_Left", 10, 17, 0.1f, false);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Left", "Snooter_Damaged_Left", 18, 18, 0.1f, false);

		// Scarfy
		MonsterAnimationRenderer->CreateAnimation("Scarfy_Left", "Scarfy_Idle_Left", 0, 2, 0.1f, true);
		MonsterAnimationRenderer->CreateAnimation("Scarfy_Left", "Scarfy_Damaged_Left", 3, 3, 0.1f, false);
	}

	// Skilled Left
	{
		// Pengy
		MonsterAnimationRenderer->CreateAnimation("Pengy_Left", "Pengy_Idle_Left", 0, 0, 0.1f, false);
		MonsterAnimationRenderer->CreateAnimation("Pengy_Left", "Pengy_Walk_Left", 1, 2, 0.1f, true);
		MonsterAnimationRenderer->CreateAnimation("Pengy_Left", "Pengy_Attack_Left", 3, 5, 0.1f, true);
		MonsterAnimationRenderer->CreateAnimation("Pengy_Left", "Pengy_Damaged_Left", 7, 7, 0.1f, false);
		
		// Metalun

		// Boxin

		// Boss
	}




	// Default Right
	{
		// Waddle
		MonsterAnimationRenderer->CreateAnimation("WaddleDee_Left", "Waddle_Walk_Left", 0, 4, 0.8f, true);
		MonsterAnimationRenderer->CreateAnimation("WaddleDee_Left", "Waddle_Swallowed_Left", 5, 5, 0.8f, false);
		MonsterAnimationRenderer->CreateAnimation("WaddleDee_Left", "Waddle_Damaged_Left", 6, 6, 0.8f, false);

		// Big Waddle
		MonsterAnimationRenderer->CreateAnimation("BigWaddleDee_Right", "BigWaddle_Walk_Right", 0, 4, 0.8f, true);
		MonsterAnimationRenderer->CreateAnimation("BigWaddleDee_Right", "BigWaddle_Swallowed_Right", 8, 8, 0.8f, false);
		MonsterAnimationRenderer->CreateAnimation("BigWaddleDee_Right", "BigWaddle_Damaged_Right", 9, 9, 0.8f, false);

		// Snooter
		MonsterAnimationRenderer->CreateAnimation("Snooter_Right", "Snooter_Idle_Right", 8, 11, 0.5f, true);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Right", "Snooter_Walk_Right", 0, 3, 0.5f, true);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Right", "Snooter_Swallow_Right", 4, 6, 0.5f, false);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Right", "Snooter_Swallow_Right2", 9, 9, 0.5f, false);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Right", "Snooter_Swallow_Right3", 8, 8, 0.5f, false);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Right", "Snooter_Swallow_Right4", 7, 8, 0.1f, false);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Right", "Snooter_Attack_Right", 10, 17, 0.1f, false);
		MonsterAnimationRenderer->CreateAnimation("Snooter_Right", "Snooter_Damaged_Right", 18, 18, 0.1f, false);

		// Scarfy
		MonsterAnimationRenderer->CreateAnimation("Scarfy_Right", "Scarfy_Idle_Right", 0, 2, 0.1f, true);
		MonsterAnimationRenderer->CreateAnimation("Scarfy_Right", "Scarfy_Damaged_Right", 3, 3, 0.1f, false);
	}

	// Skilled Right
	{
		// Pengy
		MonsterAnimationRenderer->CreateAnimation("Pengy_Right", "Pengy_Idle_Right", 0, 0, 0.1f, false);
		MonsterAnimationRenderer->CreateAnimation("Pengy_Right", "Pengy_Walk_Right", 1, 2, 0.1f, true);
		MonsterAnimationRenderer->CreateAnimation("Pengy_Right", "Pengy_Attack_Right", 3, 5, 0.1f, true);
		MonsterAnimationRenderer->CreateAnimation("Pengy_Right", "Pengy_Damaged_Right", 7, 7, 0.1f, false);

		// Metalun

		// Boxin

		// Boss
	}
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
