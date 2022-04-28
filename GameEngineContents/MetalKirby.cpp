#include "MetalKirby.h"
#include "Player.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineLevel.h>

#include "Bullet.h"
#include "Stage.h"
#include "ContentsEnum.h"
#include "Monster.h"
#include "Scarfy.h"

MetalKirby* MetalKirby::MetalPlayer = nullptr;

MetalKirby::MetalKirby()
	: PlayerAnimationRender(nullptr)
	, CurSkill_(KirbySkill::Metal)
{

}
MetalKirby::~MetalKirby()
{

}

//void MetalKirby::ColMapUpdate()
//{
//	std::string CurrentLevel = GetLevel()->GetNameCopy();
//
//	if (nullptr == MapColImage_)
//		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level1_ColMap.bmp");
//
//
//	if ("Level_1" == CurrentLevel)
//	{
//		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level1_ColMap.bmp");
//	}
//	else if ("Level_2" == CurrentLevel)
//	{
//		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level2_ColMap.bmp");
//		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level2_CDebugolMap.bmp");
//	}
//	else if ("Level_3" == CurrentLevel)
//	{
//		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level3_ColMap.bmp");
//	}
//	else if ("Level_4" == CurrentLevel)
//	{
//		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level4_ColMap.bmp");
//	}
//	else if ("TitleLevel" == CurrentLevel)
//	{
//		MapColImage_ = GameEngineImageManager::GetInst()->Find("Title_ColMap.bmp");
//	}
//	else if ("BossRoomLevel" == CurrentLevel)
//	{
//		MapColImage_ = GameEngineImageManager::GetInst()->Find("BossRoom_ColMap.bmp");
//	}
//	else if ("BossLevel" == CurrentLevel)
//	{
//		MapColImage_ = GameEngineImageManager::GetInst()->Find("BossLevel_ColMap.bmp");
//	}
//	else
//		return;
//}

//void MetalKirby::StagePixelCheck(float _Speed)
//{
//}
//
//void MetalKirby::DoorPixelCheck()
//{
//}
//
//void MetalKirby::DoorCheck(std::string ChangeLevelName_)
//{
//}
//
//void MetalKirby::WallCheck()
//{
//}
//
//void MetalKirby::MonsterColCheck()
//{
//}
//
//void MetalKirby::SwallowColCheck()
//{
//}
//
//void MetalKirby::AttackColCheck()
//{
//}
//
//void MetalKirby::MovePixelCheck(float _x, float _y)
//{
//}
//
//void MetalKirby::HillPixelCheck()
//{
//}
//
//int MetalKirby::BottomPixelColorCheck(float _y)
//{
//	return 0;
//}

void MetalKirby::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void MetalKirby::Start()
{
	//SetScale({ 1000, 1000 });

	PlayerCollision = CreateCollision("PlayerHitBox", { 70, 70 });

	// 애니메이션을 하나라도 만들면 애니메이션이 재생된다.
	PlayerAnimationRender = CreateRenderer();
	PlayerAnimationRender->SetPivotType(RenderPivot::BOT);
	PlayerAnimationRender->SetPivot({ 0.f, 210.f });

	// Walk_Right이미지의 0~9인덱스를 0.1초동안 재생 (true = 루프on)
	//Render->SetPivotType(RenderPivot::BOT);

	// Default Left
	{
		PlayerAnimationRender->CreateAnimation("Metal_Left.bmp", "Idle_Left", 0, 1, 1.f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Down_Left", 2, 3, 1.f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Slide_Left", 4, 4, 0.3f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Walk_Left", 6, 15, 0.07f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Run_Left", 16, 23, 0.07f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "RunToStop_Left", 24, 24, 0.3f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "DamagedStart_Left", 70, 70, 0.08f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Damaged_Left", 71, 78, 0.04f, true);

	//	// Full
	//	//PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Full_Left", 42, 43, 1.f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Att_Left.bmp", "Full_Left", 2, 8, 0.05f, true);			// 이펙트 있는 ver
	//	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "FullWalk_Left", 44, 56, 0.07f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "FullJump_Left", 57, 63, 0.03f, true);

	//	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Swallow_Left", 64, 69, 0.5f, true);

	//	// Attack
	//	//PlayerAnimationRender->CreateAnimation("Default_Attack_Leftt.bmp", "AttackStart_Leftt", 0, 1, 0.05f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Att_Left.bmp", "AttackStart_Left", 9, 11, 0.05f, true);	// 이펙트 있는 ver
	//	PlayerAnimationRender->CreateAnimation("Default_Attack_Left.bmp", "Attack_Left", 1, 1, 0.05f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Attack_Left.bmp", "AttackEnd_Left", 2, 3, 0.05f, true);

	//	// Inhale
	//	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Inhale_Left", 30, 37, 0.1f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Inhale_Left_Loop", 36, 37, 0.1f, true);

	//	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Exhausted_Left", 38, 40, 0.15f, false);

	//	// Jump
	//	PlayerAnimationRender->CreateAnimation("Default_Jump_Left.bmp", "Jump_Left", 0, 8, 0.03f, false);

	//	// Float
	//	PlayerAnimationRender->CreateAnimation("Default_Float_Left.bmp", "Float_Left", 0, 4, 0.05f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Float_Left.bmp", "Float_Left_Loop", 5, 10, 0.1f, true);

	//	// Exhale
	//	PlayerAnimationRender->CreateAnimation("Default_Float_Left.bmp", "Exhale_Left", 3, 3, 0.01f, false);

	//	// Fall
	//	PlayerAnimationRender->CreateAnimation("Default_Fall_Left.bmp", "Fall_Left", 0, 4, 0.2f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Fall_Left.bmp", "FallToBounce_Left", 5, 11, 0.02f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Fall_Left.bmp", "BounceToIdle_Left", 12, 12, 0.2f, false);

	}


	//// Default Right
	//{
		PlayerAnimationRender->CreateAnimation("Metal_Right.bmp", "Idle_Right", 0, 1, 1.f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Down_Right", 2, 3, 1.f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Slide_Right", 4, 4, 0.3f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Walk_Right", 6, 15, 0.07f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Run_Right", 16, 23, 0.07f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "RunToStop_Right", 24, 24, 0.3f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "DamagedStart_Right", 70, 70, 0.08f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Damaged_Right", 71, 78, 0.04f, true);

	//	// Full
	//	//PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Full_Right", 42, 43, 1.f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Att_Right.bmp", "Full_Right", 2, 8, 0.05f, true);			// 이펙트 있는 ver
	//	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "FullWalk_Right", 44, 56, 0.07f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "FullJump_Right", 57, 63, 0.03f, true);

	//	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Swallow_Right", 64, 69, 0.5f, true);

	//	// Attack
	//	//PlayerAnimationRender->CreateAnimation("Default_Attack_Right.bmp", "AttackStart_Right", 0, 1, 0.05f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Att_Right.bmp", "AttackStart_Right", 9, 11, 0.05f, true);	// 이펙트 있는 ver
	//	PlayerAnimationRender->CreateAnimation("Default_Attack_Right.bmp", "Attack_Right", 1, 1, 0.05f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Attack_Right.bmp", "AttackEnd_Right", 2, 3, 0.05f, true);

	//	// Inhale
	//	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Inhale_Right", 30, 37, 0.1f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Inhale_Right_Loop", 36, 37, 0.1f, true);

	//	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Exhausted_Right", 38, 40, 0.15f, false);

	//	// Jump
	//	PlayerAnimationRender->CreateAnimation("Default_Jump_Right.bmp", "Jump_Right", 0, 8, 0.03f, false);

	//	// Float
	//	PlayerAnimationRender->CreateAnimation("Default_Float_Right.bmp", "Float_Right", 0, 4, 0.05f, true);
	//	PlayerAnimationRender->CreateAnimation("Default_Float_Right.bmp", "Float_Right_Loop", 5, 10, 0.1f, true);

	//	// Exhale
	//	PlayerAnimationRender->CreateAnimation("Default_Float_Right.bmp", "Exhale_Right", 3, 3, 0.1f, false);

	//	// Fall
	//	PlayerAnimationRender->CreateAnimation("Default_Fall_Right.bmp", "Fall_Right", 0, 4, 0.15f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Fall_Right.bmp", "FallToBounce_Right", 5, 11, 0.02f, false);
	//	PlayerAnimationRender->CreateAnimation("Default_Fall_Right.bmp", "BounceToIdle_Right", 12, 12, 0.2f, false);
	//}

	AnimationName_ = "Idle_";
	//ChangeDirText_ = "Left";
	PlayerAnimationRender->ChangeAnimation("Idle_Right");
	//ChangeState(PlayerState::Idle);

	Off();
	MetalPlayer = this;
}

void MetalKirby::Update()
{
	ColMapUpdate();

	//DoorPixelCheck();

	DirAnimationCheck();
	PlayerStateUpdate();
	MonsterColCheck();

	DebugModeSwitch();
	//DebugKirbySkillChange(CurSkill_);
	DebugKirbySkillChange();

	// 카메라 위치 고정
	CameraFix();

}

void MetalKirby::Render()
{
}

//bool MetalKirby::IsMoveKey()
//{
//	return false;
//}
//
//bool MetalKirby::IsMoveKeyDown()
//{
//	return false;
//}
//
//bool MetalKirby::IsJumpKey()
//{
//	return false;
//}
//
//void MetalKirby::Move()
//{
//}
//
//void MetalKirby::GravityOn()
//{
//}

void MetalKirby::ChangeState(PlayerState _State)
{

	if (CurState_ != _State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Walk:
			WalkStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::RunToStop:
			RunToStopStart();
			break;
		case PlayerState::Down:
			DownStart();
			break;
		case PlayerState::Slide:
			SlideStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Float:
			FloatStart();
			break;
		case PlayerState::Fall:
			FallStart();
			break; 
		case PlayerState::Inhale:
			InhaleStart();
			break;
		case PlayerState::Full:
			FullStart();
			break;
		case PlayerState::FullWalk:
			FullWalkStart();
			break;
		case PlayerState::FullJump:
			FullJumpStart();
			break;
		case PlayerState::Exhale:
			ExhaleStart();
			break;
		case PlayerState::Swallow:
			SwallowStart();
			break;
		case PlayerState::Exhausted:
			ExhaustedStart();
			break;
		case PlayerState::Attack:
			AttackStart();
			break;
		}
	}

	CurState_ = _State;
}

void MetalKirby::PlayerStateUpdate()
{
	switch (CurState_)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Walk:
		WalkUpdate();
		break;
	case PlayerState::Run:
		RunUpdate();
		break;
	case PlayerState::RunToStop:
		RunToStopUpdate();
		break;
	case PlayerState::Down:
		DownUpdate();
		break;
	case PlayerState::Slide:
		SlideUpdate();
		break;
	case PlayerState::Jump:
		JumpUpdate();
		break;
	case PlayerState::Float:
		FloatUpdate();
		break;
	case PlayerState::Fall:
		FallUpdate();
		break;
	case PlayerState::Inhale:
		InhaleUpdate();
		break;
	case PlayerState::Full:
		FullUpdate();
		break;
	case PlayerState::FullWalk:
		FullWalkUpdate();
		break;
	case PlayerState::FullJump:
		FullJumpUpdate();
		break;
	case PlayerState::Exhale:
		ExhaleUpdate();
		break;
	case PlayerState::Swallow:
		SwallowUpdate();
		break;
	case PlayerState::Exhausted:
		ExhaustedUpdate();
		break;
	case PlayerState::Attack:
		AttackUpdate();
		break;
	}
}

void MetalKirby::IdleStart()
{
	AnimationName_ = "Idle_";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void MetalKirby::WalkStart()
{
}

void MetalKirby::RunStart()
{
}

void MetalKirby::RunToStopStart()
{
}

void MetalKirby::DownStart()
{
}

void MetalKirby::SlideStart()
{
}

void MetalKirby::JumpStart()
{
}

void MetalKirby::FallStart()
{
}

void MetalKirby::FloatStart()
{
}

void MetalKirby::InhaleStart()
{
}

void MetalKirby::FullStart()
{
}

void MetalKirby::FullWalkStart()
{
}

void MetalKirby::FullJumpStart()
{
}

void MetalKirby::ExhaleStart()
{
}

void MetalKirby::SwallowStart()
{
}

void MetalKirby::ExhaustedStart()
{
}

void MetalKirby::AttackStart()
{
}

void MetalKirby::IdleUpdate()
{
}

void MetalKirby::WalkUpdate()
{
}

void MetalKirby::RunUpdate()
{
}

void MetalKirby::RunToStopUpdate()
{
}

void MetalKirby::DownUpdate()
{
}

void MetalKirby::SlideUpdate()
{
}

void MetalKirby::JumpUpdate()
{
}

void MetalKirby::FallUpdate()
{
}

void MetalKirby::FloatUpdate()
{
}

void MetalKirby::InhaleUpdate()
{
}

void MetalKirby::FullUpdate()
{
}

void MetalKirby::FullWalkUpdate()
{
}

void MetalKirby::FullJumpUpdate()
{
}

void MetalKirby::ExhaleUpdate()
{
}

void MetalKirby::SwallowUpdate()
{
}

void MetalKirby::ExhaustedUpdate()
{
}

void MetalKirby::AttackUpdate()
{
}
