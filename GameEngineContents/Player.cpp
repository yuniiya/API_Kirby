#include "Player.h"
#include "MetalKirby.h"
#include "IceKirby.h"
#include "SparkKirby.h"

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

#include "Stage.h"
#include "ContentsEnum.h"
#include "Monster.h"
#include "Scarfy.h"
#include "Effect_ReleaseSkill.h"
#include "PlayUI.h"
#include "PlayerHP.h"

Player* Player::MainPlayer = nullptr;
GameEngineSoundPlayer Player::BgmPlayer;
//PlayerHP* PlayerHP::MainHP = nullptr;

Player::Player()
	: MaxHP_(100.f)	// �� ĭ
	, CurHP_(100.f)
	, Speed_(350.0f)
	, AccSpeed_(20.f)
	, JumpPower_(1000.f)
	, Gravity_(1500.f)
	, MapColImage_(nullptr)
	, PlayerCollision(nullptr)
	, PlayerAnimationRender(nullptr)
	, CurState_(PlayerState::Idle)
	, PrevState_(CurState_)
	, MapScaleX_(0.f)
	, MapScaleY_(0.f)
	, MoveDir(float4::ZERO)
	, CurDir_(PlayerDir::Right)
	, RunningTime_(0.1f)
	, StopTime_(1.f)
	, DownTime_(0.5f)
	, InhaleTime_(2.5f)
	, FallTime_(1.5f)
	, IsHit_(false)
	, SlideColTime_(0.5f)
	, SkillName_("")
	, CurSkill_(KirbySkill::Default)
	, SlidingTime_(1.2f)
	, CurSwallowMonster_(SwallowMonsterType::Max)
	, StarEffect_(nullptr)
	, SlideCollision(nullptr)
	, RunEffTime_(0.f)
	, InputDir_(PlayerDir::Max)
	, InhaleEffect_(nullptr)
	, InhaleCollision(nullptr)
	, AttEffect_(nullptr)
	, AttackTime_(0.f)
{

}
Player::~Player()
{

}

void Player::MapScale(float _x, float _y)
{
	MapScaleX_ = _x;
	MapScaleY_ = _y;
}

std::string Player::GetCurrentLevelName()
{
	CurrentLevel = GetLevel()->GetNameCopy();
	return CurrentLevel;
}


bool Player::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveRight") 
		) 
	{
		return false;
	}

	return true;
}

bool Player::IsMoveKeyDown()
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft") ||
		true == GameEngineInput::GetInst()->IsDown("MoveRight")
		)
	{
		return true;
	}

	return false;
}

bool Player::IsJumpKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("JumpLeft") &&
		false == GameEngineInput::GetInst()->IsPress("JumpRight")
		/*false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
		false == GameEngineInput::GetInst()->IsPress("MoveDown")*/
		)
	{
		return false;
	}

	return true;
}

void Player::Move()
{
	MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}

}

void Player::GravityOn()
{
	MoveDir.y += 1.f * GameEngineTime::GetDeltaTime() * Gravity_;
}

void Player::Hit()
{
	if (CurHP_ <= 10.f)
	{
		return;
	}

	CurHP_ -= 10.f;

	PlayerHP::MainHP->SetHP(CurHP_, MaxHP_);

	if (CurSkill_ != KirbySkill::Default)
	{
		switch (CurSkill_)
		{
		case KirbySkill::Ice: 
		{
			IceKirby::IcePlayer->IceKirbyOff();
		}
			break;
		case KirbySkill::Spark:
		{
			SparkKirby::SparkPlayer->SparkKirbyOff();
		}
			break;
		default:
			break;
		}
	}


}


void Player::ChangeState(PlayerState _State)
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
		case PlayerState::FallToBounce:
			FallToBounceStart();
			break;
		case PlayerState::BounceToIdle:
			BounceToIdleStart();
			break;
		case PlayerState::Inhale:
			InhaleStart();
			break;
		case PlayerState::Full:
			FullStart();
			break;
		case PlayerState::FullLoop:
			FullLoopStart();
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
		case PlayerState::AttackStart:
			AttackStartStart();
			break;
		case PlayerState::Attack:
			AttackStart();
			break;
		case PlayerState::AttackEnd:
			AttackEndStart();
			break;
		case PlayerState::DamagedStart:
			DamagedStartStart();
			break;
		case PlayerState::Damaged:
			DamagedStart();
			break;
		case PlayerState::FullToSkill:
			FullToSkillStart();
			break;
		case PlayerState::SwallowToSkill:
			SwallowToSkillStart();
			break;
		case PlayerState::TransformToSkill:
			TransformToSkillStart();
			break;
		}
	}

	CurState_ = _State;
}

void Player::PlayerStateUpdate()
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
	case PlayerState::FallToBounce:
		FallToBounceUpdate();
		break;
	case PlayerState::BounceToIdle:
		BounceToIdleUpdate();
		break;
	case PlayerState::Inhale:
		InhaleUpdate();
		break;
	case PlayerState::Full:
		FullUpdate();
		break;
	case PlayerState::FullLoop:
		FullLoopUpdate();
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
	case PlayerState::AttackStart:
		AttackStartUpdate();
		break;
	case PlayerState::Attack:
		AttackUpdate();
		break;
	case PlayerState::AttackEnd:
		AttackEndUpdate();
		break;
	case PlayerState::DamagedStart:
		DamagedStartUpdate();
		break;
	case PlayerState::Damaged:
		DamagedUpdate();
		break;
	case PlayerState::FullToSkill:
		FullToSkillUpdate();
		break;
	case PlayerState::SwallowToSkill:
		SwallowToSkillUpdate();
		break;
	case PlayerState::TransformToSkill:
		TransformToSkillUpdate();
		break;
	}
}


void Player::Start()
{
	PlayerCollision = CreateCollision("PlayerHitBox", { 70, 70 });
	InhaleCollision = CreateCollision("InhaleCol", { 100, 100 });
	InhaleCollision->Off();

	//SlideCollision = CreateCollision("SlideCol", { 35, 35 });
	//SlideCollision->Off();

	// �ִϸ��̼��� �ϳ��� ����� �ִϸ��̼��� ����ȴ�.
	PlayerAnimationRender = CreateRenderer();
	PlayerAnimationRender->SetPivotType(RenderPivot::BOT);
	PlayerAnimationRender->SetPivot({ 0.f, 140.f });

	// Walk_Right�̹����� 0~9�ε����� 0.1�ʵ��� ��� (true = ����on)
	//Render->SetPivotType(RenderPivot::BOT);
	//Render->SetPivotType(RenderPivot::BOT);

	// Default Left
	{
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Idle_Left", 0, 1, 1.f, true);
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Down_Left", 2, 3, 1.f, true);
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Slide_Left", 4, 4, 0.3f, false);
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Walk_Left", 6, 15, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Run_Left", 16, 23, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "RunToStop_Left", 24, 24, 0.3f, false);
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "DamagedStart_Left", 70, 70, 0.8f, false);
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Damaged_Left", 70, 78, 0.04f, true);

		// Full
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Full_Loop_Left", 42, 43, 0.5f, true);
		PlayerAnimationRender->CreateAnimation("Default_Att_Left.bmp", "Full_Left", 2, 8, 0.05f, false);			// ����Ʈ �ִ� ver
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "FullWalk_Left", 44, 56, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "FullJump_Left", 57, 63, 0.1f, false);

		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Swallow_Left", 64, 69, 0.05f, false);

		// Attack
		//PlayerAnimationRender->CreateAnimation("Default_Attack_Left.bmp", "AttackStart_Left", 0, 1, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Default_Att_Left.bmp", "AttackStart_Left", 9, 11, 0.05f, true);	// ����Ʈ �ִ� ver
		PlayerAnimationRender->CreateAnimation("Default_Attack_Left.bmp", "Attack_Left", 1, 1, 0.05f, false);
		PlayerAnimationRender->CreateAnimation("Default_Attack_Left.bmp", "AttackEnd_Left", 2, 3, 0.05f, true);

		// Inhale
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Inhale_Left", 30, 37, 0.1f, false);
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Inhale_Left_Loop", 36, 37, 0.1f, true);

		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Exhausted_Left", 38, 40, 0.15f, false);

		// Jump
		PlayerAnimationRender->CreateAnimation("Default_Jump_Left.bmp", "Jump_Left", 0, 8, 0.03f, false);

		// Float
		PlayerAnimationRender->CreateAnimation("Default_Float_Left.bmp", "Float_Left", 0, 4, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Default_Float_Left.bmp", "Float_Left_Loop", 5, 10, 0.1f, true);

		// Exhale
		PlayerAnimationRender->CreateAnimation("Default_Float_Left.bmp", "Exhale_Left", 3, 3, 0.01f, false);

		// Fall
		PlayerAnimationRender->CreateAnimation("Default_Fall_Left.bmp", "Fall_Left", 0, 4, 0.2f, false);
		PlayerAnimationRender->CreateAnimation("Default_Fall_Left.bmp", "FallToBounce_Left", 5, 11, 0.02f, false);
		PlayerAnimationRender->CreateAnimation("Default_Fall_Left.bmp", "BounceToIdle_Left", 12, 12, 0.2f, false);

		//PlayerAnimationRender->CreateAnimation("Default_Enter_Left.bmp", "Enter_Left", 0, 3, 0.15f, false);

	}
	

	// Default Right
	{
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Idle_Right", 0, 1, 1.f, true);
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Down_Right", 2, 3, 1.f, true);
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Slide_Right", 4, 4, 0.3f, false);
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Walk_Right", 6, 15, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Run_Right", 16, 23, 0.07f, true);
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "RunToStop_Right", 24, 24, 0.3f, false);
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "DamagedStart_Right", 70, 70, 0.08f, false);
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Damaged_Right", 71, 78, 0.04f, true);

		// Full
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Full_Loop_Right", 42, 43, 0.5f, true);
		PlayerAnimationRender->CreateAnimation("Default_Att_Right.bmp", "Full_Right", 2, 8, 0.05f, false);			// ����Ʈ �ִ� ver
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "FullWalk_Right", 44, 56, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "FullJump_Right", 57, 63, 0.1f, false);

		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Swallow_Right", 64, 69, 0.05f, false);

		// Attack
		//PlayerAnimationRender->CreateAnimation("Default_Attack_Right.bmp", "AttackStart_Right", 0, 1, 0.5f, true);
		PlayerAnimationRender->CreateAnimation("Default_Att_Right.bmp", "AttackStart_Right", 9, 11, 0.05f, true);	// ����Ʈ �ִ� ver
		PlayerAnimationRender->CreateAnimation("Default_Attack_Right.bmp", "Attack_Right", 1, 1, 0.05f, false);
		PlayerAnimationRender->CreateAnimation("Default_Attack_Right.bmp", "AttackEnd_Right", 2, 3, 0.05f, true);

		// Inhale
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Inhale_Right", 30, 37, 0.1f, false);
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Inhale_Right_Loop", 36, 37, 0.1f, true);

		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Exhausted_Right", 38, 40, 0.15f, false);

		// Jump
		PlayerAnimationRender->CreateAnimation("Default_Jump_Right.bmp", "Jump_Right", 0, 8, 0.03f, false);

		// Float
		PlayerAnimationRender->CreateAnimation("Default_Float_Right.bmp", "Float_Right", 0, 4, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Default_Float_Right.bmp", "Float_Right_Loop", 5, 10, 0.1f, true);

		// Exhale
		PlayerAnimationRender->CreateAnimation("Default_Float_Right.bmp", "Exhale_Right", 3, 3, 0.1f, false);

		// Fall
		PlayerAnimationRender->CreateAnimation("Default_Fall_Right.bmp", "Fall_Right", 0, 4, 0.15f, false);
		PlayerAnimationRender->CreateAnimation("Default_Fall_Right.bmp", "FallToBounce_Right", 5, 11, 0.02f, false);
		PlayerAnimationRender->CreateAnimation("Default_Fall_Right.bmp", "BounceToIdle_Right", 12, 12, 0.2f, false);

		PlayerAnimationRender->CreateAnimation("Default_Enter_Right.bmp", "Enter_Right", 0, 3, 0.15f, false);
	}
	
	AnimationName_ = "Idle_";
	ChangeDirText_ = "Right";
	PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);


	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		// =============== �̵� ===============
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		//GameEngineInput::GetInst()->CreateKey("Run", VK_SPACE);
		// �ι� ��Ÿ : Run
		// Run���¿��� �ݴ� ����Ű : RunToStop

		GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("Down", VK_DOWN);
		// ���� ������ MoveDown: Down
		// Full ���¿��� MoveDown : Swallow

		// =============== ���� ===============
		GameEngineInput::GetInst()->CreateKey("JumpLeft",'A');
		GameEngineInput::GetInst()->CreateKey("JumpRight", 'D');
		// �ι� ��Ÿ�Ѵٸ� A, D : Float
		// �Ʒ� + A, D: Slide

		// =============== ��� ===============
		GameEngineInput::GetInst()->CreateKey("Inhale", 'S');
		// Inhale ���¿��� S : Exhale or Attack
		// Float ���¿��� S : Exhale
		
		// =============== ��ų ===============
		// ���Ƶ��� ��ü�� ��ų�� �����ٸ� W : Copy
		GameEngineInput::GetInst()->CreateKey("Attack", 'W');
		// �ɷ��� ī���� ���¿��� W : ��ų ����

		GameEngineInput::GetInst()->CreateKey("Default", 'Z');
		GameEngineInput::GetInst()->CreateKey("Metal", 'X');
		GameEngineInput::GetInst()->CreateKey("Ice", 'C');
		GameEngineInput::GetInst()->CreateKey("Spark", 'V');

		GameEngineInput::GetInst()->CreateKey("DebugHP", '0');
	}
	
}




void Player::Update()
{
	// �浹 ��
	ColMapUpdate();

	// ���� �浹, �� �������� �̵� üũ
	//StagePixelCheck();
	DoorPixelCheck();
	//DoorCheck();

	DirAnimationCheck();
	PlayerStateUpdate();
	//MonsterColCheck();

	DebugModeSwitch();

	// ī�޶� ��ġ ����
	CameraFix();

	//DebugKirbySkillChange();
	DebugHP();

}

void Player::Render()
{
	if (true == GetLevel()->GetIsDebug())
	{
		std::string CurSkillStr = "";
		std::string CurAnimationStr = "";
		std::string CurSkillType = "";
		std::string CurSwallowMonster = "";

		if (SkillName_ == "")
		{
			CurSkillStr = "SkillName : None";
		}
		else
		{
			CurSkillStr = "SkillName : " + SkillName_;
		}

		CurAnimationStr = "AnimationName : " + AnimationName_;

		if (CurSkill_ == KirbySkill::Ice)
		{
			CurSkillType = "CurSkill : Ice";
		}
		else if (CurSkill_ == KirbySkill::Metal)
		{
			CurSkillType = "CurSkill : Metal";
		}
		else if (CurSkill_ == KirbySkill::Spark)
		{
			CurSkillType = "CurSkill : Spark";
		}
		else
		{
			CurSkillType = "CurSkill : Default";
		}

		if (CurSwallowMonster_ == SwallowMonsterType::Ice)
		{
			CurSwallowMonster = "CurSwallowMonster : Ice";
		}
		else if (CurSwallowMonster_ == SwallowMonsterType::Metal)
		{
			CurSwallowMonster = "CurSwallowMonster : Metal";
		}
		else if (CurSwallowMonster_ == SwallowMonsterType::Spark)
		{
			CurSwallowMonster = "CurSwallowMonster : Spark";
		}
		else
		{
			CurSwallowMonster = "CurSwallowMonster : Default";
		}


		SetBkMode(GameEngine::BackBufferDC(), OPAQUE);
		SetTextColor(GameEngine::BackBufferDC(), RGB(0, 0, 0));
		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix(), GetCameraEffectPosition().iy() - 120, CurSkillStr.c_str(), static_cast<int>(CurSkillStr.length()));
		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix(), GetCameraEffectPosition().iy() - 100, CurAnimationStr.c_str(), static_cast<int>(CurAnimationStr.length()));
		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix(), GetCameraEffectPosition().iy() - 80, CurSkillType.c_str(), static_cast<int>(CurSkillType.length()));
		TextOut(GameEngine::BackBufferDC(), GetCameraEffectPosition().ix(), GetCameraEffectPosition().iy() - 60, CurSwallowMonster.c_str(), static_cast<int>(CurSwallowMonster.length()));

	}
}

void Player::ColMapUpdate()
{
	std::string CurrentLevel = GetLevel()->GetNameCopy();

	if (nullptr == MapColImage_)
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level1_ColMap.bmp");


	if ("Level_1" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level1_ColMap.bmp");
	}
	else if ("Level_2" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level2_ColMap.bmp");
	}
	else if ("Level_3" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level3_ColMap.bmp");
	}
	else if ("Level_4" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Level4_ColMap.bmp");
	}
	else if ("TitleLevel" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("Title_ColMap.bmp");
	}
	else if ("BossRoomLevel" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("BossRoom_ColMap.bmp");
	}
	else if ("BossLevel" == CurrentLevel)
	{
		MapColImage_ = GameEngineImageManager::GetInst()->Find("BossLevel_ColMap.bmp");
	}
	else
		return;

}

// �浹 -> �ı�
void Player::WallCheck()
{
	// �׶��׶� ���͸� ���� ���� or ��� ������ �ΰ� �� ���� Ŭ��������
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerCollision->CollisionResult("Wall", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			// (���� ������) �ݸ����� �ı� 
			ColList[i]->Death();
		}
	}
}

void Player::MonsterColCheck()
{
	// ����Ʈ ����
	{	
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("DefaultMonster", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			FloatEffSound_.Stop();

			IsHit_ = true;

			ChangeState(PlayerState::Damaged);
			return;
		}
	}

	// Skilled
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("MetalunCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			IsHit_ = true;

			FloatEffSound_.Stop();
			DamagedEffSound_.Stop();

			ChangeState(PlayerState::Damaged);
			return;
		}
	}

	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("PengyCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			IsHit_ = true;

			FloatEffSound_.Stop();
			ChangeState(PlayerState::Damaged);
			return;
		}
	}

	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("IceBreathCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			IsHit_ = true;

			FloatEffSound_.Stop();
			ChangeState(PlayerState::Damaged);
			return;
		}
	}

	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("SparkyCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			IsHit_ = true;

			DamagedEffSound_.Stop();
			FloatEffSound_.Stop();
			ChangeState(PlayerState::Damaged);
			return;
		}
	}


	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("SparkyAttackCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			IsHit_ = true;

			FloatEffSound_.Stop();
			ChangeState(PlayerState::Damaged);
			return;
		}

	}

	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("BossHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			IsHit_ = true;

			FloatEffSound_.Stop();

			ChangeState(PlayerState::Damaged);
			return;

		}

	}

	////////////////////////////////////////////////////////////////////////////////////// ������
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("Item1", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			CurHP_ += 10.f;
			PlayerHP::MainHP->SetHP(CurHP_, MaxHP_);


			for (size_t i = 0; i < ColList.size(); i++)
			{
				ColList[i]->GetActor()->Death();
			}
		}
	}

	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("Item2", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			CurHP_ += 10.f;
			PlayerHP::MainHP->SetHP(CurHP_, MaxHP_);

			for (size_t i = 0; i < ColList.size(); i++)
			{
				ColList[i]->GetActor()->Death();
			}
		}
	}
}

void Player::InhaleColCheck()
{
	// ����Ʈ ����
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("DefaultMonster", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			InhaleEffect_->Death();
			InhaleEffSound_.Stop();

			ChangeState(PlayerState::Full);
			return;
		}
	}

	// Skilled
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("MetalunCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			InhaleEffect_->Death();
			InhaleEffSound_.Stop();

			CurSwallowMonster_ = SwallowMonsterType::Metal;
			ChangeState(PlayerState::FullToSkill);
			return;
		}
	}

	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("PengyCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			InhaleEffect_->Death();
			InhaleEffSound_.Stop();

			CurSwallowMonster_ = SwallowMonsterType::Ice;
			ChangeState(PlayerState::FullToSkill);
			return;
		}
	}

	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("SparkyCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			InhaleEffect_->Death();
			InhaleEffSound_.Stop();

			CurSwallowMonster_ = SwallowMonsterType::Spark;
			ChangeState(PlayerState::FullToSkill);
			return;
		}
	}

	// Boss Star -> �Ծ ���� ����
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision->CollisionResult("BossStarCol", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			InhaleEffect_->Death();
			InhaleEffSound_.Stop();

			ChangeState(PlayerState::Full);
			return;
		}
	}

}


void Player::DirAnimationCheck()
{
	std::string ChangeName;

	PlayerDir CheckDir_ = CurDir_;
	//ChangeDirText_ = "Right";

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		CheckDir_ = PlayerDir::Right;
		ChangeDirText_ = "Right";
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		CheckDir_ = PlayerDir::Left;
		ChangeDirText_ = "Left";
	}

	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		if (CheckDir_ == PlayerDir::Left)
		{
			ChangeDirText_ = "Left";
		}
		else 
		{
			ChangeDirText_ = "Right";
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("Inhale"))
	{	
		if (CheckDir_ == PlayerDir::Left)
		{
			ChangeDirText_ = "Left";
		}
		else
		{
			ChangeDirText_ = "Right";
		}
	}


	if (true == GameEngineInput::GetInst()->IsPress("JumpLeft"))
	{
		if (CheckDir_ == PlayerDir::Left)
		{
			ChangeDirText_ = "Left";
		}
		else
		{
			ChangeDirText_ = "Right";
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("JumpRight"))
	{
		if (CheckDir_ == PlayerDir::Left)
		{
			ChangeDirText_ = "Left";
		}
		else
		{
			ChangeDirText_ = "Right";
		}
	}

	if (CheckDir_ != CurDir_)
	{
		PlayerAnimationRender->ChangeAnimation(SkillName_ + AnimationName_ + ChangeDirText_);
		CurDir_ = CheckDir_;
	}

}

void Player::SkillRelease()
{
	// ��ų ���� ����
	GameEngineSound::SoundPlayOneShot("Release1.wav");
	CurSwallowMonster_ = SwallowMonsterType::Max;

	Effect_ReleaseSkill* Effect = GetLevel()->CreateActor<Effect_ReleaseSkill>((int)ORDER::EFFECT);

	if (CurDir_ == PlayerDir::Right)
	{
		Effect->SetPosition(GetPosition());
		Effect->SetDir(EffectDir::Right);

	}
	else if (CurDir_ == PlayerDir::Left)
	{
		Effect->SetPosition(GetPosition());
		Effect->SetDir(EffectDir::Left);
	}
}


void Player::CameraFix()
{
	// Ŀ�� �߽ɿ� �д� 
	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

	// ī�޶� ������ ����� ��ġ�� 0,0���� �����
	if (0 > GetLevel()->GetCameraPos().x)
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.x = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (0 > GetLevel()->GetCameraPos().y)
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

	float CameraRectX = 1024;
	float CameraRectY = 768;

	//GetStage()->GetScale().ix();

	if (MapScaleX_ <= GetLevel()->GetCameraPos().x + CameraRectX)
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.x = GetLevel()->GetCameraPos().x - (GetLevel()->GetCameraPos().x + CameraRectX - MapScaleX_);;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

	if (MapScaleY_ <= (GetLevel()->GetCameraPos().y + CameraRectY))
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = GetLevel()->GetCameraPos().y - (GetLevel()->GetCameraPos().y + CameraRectY - MapScaleY_);
		GetLevel()->SetCameraPos(CurCameraPos);
	}
}

void Player::MakeStarEffect()
{
	StarEffect_ = GetLevel()->CreateActor<Effect_Star>((int)ORDER::EFFECT);

	if (CurDir_ == PlayerDir::Right)
	{
		StarEffect_->SetPosition(GetPosition() + float4{ -30.f, 0.f });
	}
	else if (CurDir_ == PlayerDir::Left)
	{
		StarEffect_->SetPosition(GetPosition() + float4{ 30.f, 0.f });
	}
}

void Player::PlayerHPUpdate()
{

	/*if (PlayerHP_ = 90)
	{
		HP.PlayerHPBar->SetPivot({ 294.f, 740.f });
		HP.PlayerHPBar->SetScale({250.f, 30.f});
	}*/
}

void Player::DoorCheck(std::string ChangeLevelName_)
{
	int Color = MapColImage_->GetImagePixel(GetPosition());

	if (RGB(0, 0, 255) == Color && true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{
		GameEngine::GetInst().ChangeLevel(ChangeLevelName_);
	}	
}

void Player::StagePixelCheck(float _Speed)
{
	float4 DownPos = GetPosition() + float4{ 0.0f, 15.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;
	float4 LeftPos = GetPosition() + float4{ -15.f, 0.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;
	float4 RightPos = GetPosition() + float4{ 15.f, 0.f } + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;

	int DownColor = MapColImage_->GetImagePixel(DownPos);
	int LeftColor = MapColImage_->GetImagePixel(LeftPos);
	int RightColor = MapColImage_->GetImagePixel(RightPos);

	if (RGB(0, 0, 0) != DownColor
		&& RGB(0, 0, 0) != RightColor
		&& RGB(0, 0, 0) != LeftColor)						// 1-1) �ߺ��� ���� ���� ���� �ƴ� ���� �� �� �ִ�
	{
		if (RGB(0, 0, 0) != BottomPixelColorCheck(20.f))	// 1-2) ���ٰ� ���� ���� �ȴ�Ҿ� �׷��� 1�ȼ� ������
		{
			MoveDir.y = 1.f;
		}

		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * _Speed);
	}
	else if (RGB(0, 0, 0) == DownColor)				// 2-1) �ߺ��� ���� ���� ���� ������ �׷� 1�ȼ� �÷���
	{
		MoveDir.y = -1.f;

		SetMove(MoveDir * GameEngineTime::GetDeltaTime() * _Speed);
	}
}

void Player::MovePixelCheck(float _x, float _y)
{
	int UpCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ 0.f, -_y });
	int LeftCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ -_x, 0.f });
	int RightCheck = MapColImage_->GetImagePixel(GetPosition() + float4{ _x, 0.f });

	float4 Pos = MoveDir;

	if (RGB(0, 0, 0) == UpCheck)
	{
		//MoveDir = float4{ 0.0f, _y + 0.1f};
		MoveDir = float4{ 0.0f, 1.f };
		SetMove(MoveDir);
	}
	else if (RGB(0, 0, 0) == LeftCheck)
	{
		//MoveDir = float4{ _x + 0.1f, 0.0f };
		MoveDir = float4{ 1.f, 0.0f };
		SetMove(MoveDir);
	}
	else if (RGB(0, 0, 0) == RightCheck)
	{
		//MoveDir = float4{ -_x - 0.1f, 0.0f };
		MoveDir = float4{ -1.f, 0.0f };
		SetMove(MoveDir);
	}
}

void Player::HillPixelCheck()
{
	float4 CheckPos = float4::DOWN;
	float4 LeftUpPos = float4::UP;
	float4 RightUpPos = float4::UP;

	int DownColor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 20.0f } + CheckPos);
	int LeftColor = MapColImage_->GetImagePixel(GetPosition() + float4{ -20.0f, 0.0f } + CheckPos);
	int RightColor = MapColImage_->GetImagePixel(GetPosition() + float4{ 20.0f, 0.0f } + RightUpPos);

	if (RGB(0, 0, 0) != DownColor)
	{
		// ���� ����ִ� ������ ��� �����ش�
		while (RGB(0, 0, 0) == DownColor)
		{
			CheckPos += float4::DOWN;
			DownColor = MapColImage_->GetImagePixel(GetPosition() + CheckPos);
		}
		SetMove(CheckPos);
	}
	else if (RGB(0, 0, 0) == LeftColor)	// ���ʾ��� ���̶�� ���� �ƴ� ������ �÷��ش�
	{
		while (RGB(0, 0, 0) != LeftColor)
		{
			LeftUpPos += float4::UP;
			LeftColor = MapColImage_->GetImagePixel(GetPosition() + CheckPos);
		}
		SetMove(LeftUpPos);
	}
	else if (RGB(0, 0, 0) == RightColor)
	{
		while (RGB(0, 0, 0) != RightColor)
		{
			RightUpPos += float4::UP;
			RightColor = MapColImage_->GetImagePixel(GetPosition() + RightUpPos);
		}
		SetMove(RightUpPos);
	}
}

int Player::BottomPixelColorCheck(float _y)
{
	float4 CheckPos = GetPosition() + float4{0.0f, _y};
	int Color = MapColImage_->GetImagePixel(CheckPos);

	return Color;
}

void Player::DoorPixelCheck()
{
	// ���� ������ �̵�
	if ("Level_1" == GetCurrentLevelName())
		DoorCheck("Level_2");
	else if ("Level_2" == GetCurrentLevelName())
		DoorCheck("Level_3");
	else if ("Level_3" == GetCurrentLevelName())
		DoorCheck("BossRoomLevel");
	else if ("BossRoomLevel" == GetCurrentLevelName())
		DoorCheck("BossLevel");

	//else if ("Level_3" == GetCurrentLevelName())
	//	DoorCheck("Level_4");
}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;

}

//////////////////////////////////////////////////////////////////////// ����׿�
void Player::DebugModeSwitch()
{
	if (true == GameEngineInput::GetInst()->IsDown("DebugMode"))
	{
		GetLevel()->IsDebugModeSwitch();
	}
}

void Player::DebugKirbySkillChange()
{
	if (true == GameEngineInput::GetInst()->IsDown("Default"))
	{
		//DefaultKirbyUpdate();
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Metal"))
	{
		MetalKirbyUpdate();
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Ice"))
	{
		IceKirbyUpdate();
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Spark"))
	{
		SparkKirbyUpdate();
	}
}

void Player::DebugHP()
{
	if (true == GameEngineInput::GetInst()->IsDown("DebugHP"))
	{
		Hit();
	}
}

void Player::DefaultKirbyUpdate()
{
	SkillName_ = "";

	if (CurSkill_ == KirbySkill::Default)
	{
		return;
	}

	if (CurSkill_ == KirbySkill::Metal)
	{
		MetalKirby::MetalPlayer->Off();
	}
	else if (CurSkill_ == KirbySkill::Ice)
	{
		IceKirby::IcePlayer->Off();
	}
	else if (CurSkill_ == KirbySkill::Spark)
	{
		SparkKirby::SparkPlayer->Off();
	}

	// ��ų ���� ����
	GameEngineSound::SoundPlayOneShot("Release1.wav");

	{
		Effect_ReleaseSkill* Effect = GetLevel()->CreateActor<Effect_ReleaseSkill>((int)ORDER::EFFECT);

		if (CurDir_ == PlayerDir::Right)
		{
			Effect->SetPosition(GetPosition());
			Effect->SetDir(EffectDir::Right);

		}
		else if (CurDir_ == PlayerDir::Left)
		{
			Effect->SetPosition(GetPosition());
			Effect->SetDir(EffectDir::Left);
		}
	}

	MainPlayer->SetPosition(GetPosition());
	CurSkill_ = KirbySkill::Default;
	MainPlayer->On();
}

void Player::MetalKirbyUpdate()
{
	if (CurSkill_ != KirbySkill::Default)
	{
		return;
	}

	CurSkill_ = KirbySkill::Metal;
	CurSwallowMonster_ = SwallowMonsterType::Metal;
	ChangeState(PlayerState::SwallowToSkill);
	return;
}

void Player::IceKirbyUpdate()
{
	if (CurSkill_ != KirbySkill::Default)
	{
		return;
	}

	CurSkill_ = KirbySkill::Ice;
	CurSwallowMonster_ = SwallowMonsterType::Ice;
	ChangeState(PlayerState::SwallowToSkill);
	return;
}

void Player::SparkKirbyUpdate()
{
	if (CurSkill_ != KirbySkill::Default)
	{
		return;
	}

	CurSkill_ = KirbySkill::Spark;
	CurSwallowMonster_ = SwallowMonsterType::Spark;
	ChangeState(PlayerState::SwallowToSkill);
	return;
}


