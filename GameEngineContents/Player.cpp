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

#include "Bullet.h"
#include "Stage.h"
#include "ContentsEnum.h"
#include "Monster.h"
#include "Scarfy.h"


Player* Player::MainPlayer = nullptr;
GameEngineSoundPlayer Player::BgmPlayer;

Player::Player()
	: Speed_(350.0f)
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
	//, CurSkill_(KirbySkill::Default)

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


bool Player::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveRight") 
		/*false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
		false == GameEngineInput::GetInst()->IsPress("MoveDown")*/
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
	}
}


void Player::Start()
{
	PlayerCollision = CreateCollision("PlayerHitBox", { 70, 70 });
	InhaleCollision = CreateCollision("InhaleCol", { 100, 100 });
	InhaleCollision->Off();

	// 애니메이션을 하나라도 만들면 애니메이션이 재생된다.
	PlayerAnimationRender = CreateRenderer();
	PlayerAnimationRender->SetPivotType(RenderPivot::BOT);
	PlayerAnimationRender->SetPivot({ 0.f, 140.f });

	// Walk_Right이미지의 0~9인덱스를 0.1초동안 재생 (true = 루프on)
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
		PlayerAnimationRender->CreateAnimation("Default_Att_Left.bmp", "Full_Left", 2, 8, 0.05f, false);			// 이펙트 있는 ver
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "FullWalk_Left", 44, 56, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "FullJump_Left", 57, 63, 0.1f, false);

		PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Swallow_Left", 64, 69, 0.05f, false);

		// Attack
		//PlayerAnimationRender->CreateAnimation("Default_Attack_Left.bmp", "AttackStart_Left", 0, 1, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Default_Att_Left.bmp", "AttackStart_Left", 9, 11, 0.05f, true);	// 이펙트 있는 ver
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
		PlayerAnimationRender->CreateAnimation("Default_Att_Right.bmp", "Full_Right", 2, 8, 0.05f, false);			// 이펙트 있는 ver
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "FullWalk_Right", 44, 56, 0.05f, true);
		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "FullJump_Right", 57, 63, 0.1f, false);

		PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Swallow_Right", 64, 69, 0.05f, false);

		// Attack
		//PlayerAnimationRender->CreateAnimation("Default_Attack_Right.bmp", "AttackStart_Right", 0, 1, 0.5f, true);
		PlayerAnimationRender->CreateAnimation("Default_Att_Right.bmp", "AttackStart_Right", 9, 11, 0.05f, true);	// 이펙트 있는 ver
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
	}
	
	AnimationName_ = "Idle_";
	PlayerAnimationRender->ChangeAnimation("Idle_Right");


	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		// =============== 이동 ===============
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		//GameEngineInput::GetInst()->CreateKey("Run", VK_SPACE);
		// 두번 연타 : Run
		// Run상태에서 반대 방향키 : RunToStop

		GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("Down", VK_DOWN);
		// 지형 위에서 MoveDown: Down
		// Full 상태에서 MoveDown : Swallow

		// =============== 점프 ===============
		GameEngineInput::GetInst()->CreateKey("JumpLeft",'A');
		GameEngineInput::GetInst()->CreateKey("JumpRight", 'D');
		// 두번 연타한다면 A, D : Float
		// 아래 + A, D: Slide

		// =============== 흡수 ===============
		GameEngineInput::GetInst()->CreateKey("Inhale", 'S');
		// Inhale 상태에서 S : Exhale or Attack
		// Float 상태에서 S : Exhale
		
		// =============== 스킬 ===============
		// 빨아들인 물체가 스킬을 가졌다면 W : Copy
		GameEngineInput::GetInst()->CreateKey("Attack", 'W');
		// 능력을 카피한 상태에서 W : 스킬 해제

		GameEngineInput::GetInst()->CreateKey("Default", 'Z');
		GameEngineInput::GetInst()->CreateKey("Metal", 'X');
		GameEngineInput::GetInst()->CreateKey("Ice", 'C');
		GameEngineInput::GetInst()->CreateKey("Spark", 'V');
	}
	
}




void Player::Update()
{
	// 충돌 맵
	ColMapUpdate();

	// 지형 충돌, 문 스테이지 이동 체크
	//StagePixelCheck();
	DoorPixelCheck();

	DirAnimationCheck();
	PlayerStateUpdate();
	//MonsterColCheck();

	DebugModeSwitch();
	//DebugKirbySkillChange(CurSkill_);

	// 카메라 위치 고정
	CameraFix();

	//WallCheck();

	DebugKirbySkillChange();
}

void Player::Render()
{
	//DebugRectRender();
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

// 충돌 -> 파괴
void Player::WallCheck()
{
	// 그때그때 벡터를 만들어서 할지 or 멤버 변수로 두고 한 번에 클리어할지
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerCollision->CollisionResult("Wall", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			// (엑터 제외한) 콜리전만 파괴 
			ColList[i]->Death();
		}
	}
}

void Player::MonsterColCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerCollision->CollisionResult("DefaultMonster", ColList, CollisionType::Rect, CollisionType::Rect))
	{
	/*	for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();
		}*/

		ChangeState(PlayerState::DamagedStart);
		return;
		
	}
}

void Player::InhaleColCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PlayerCollision->CollisionResult("DefaultMonster", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		/*	for (size_t i = 0; i < ColList.size(); i++)
			{
				ColList[i]->GetActor()->Death();
			}*/

		InhaleEffSound_.Stop();
		ChangeState(PlayerState::Full);
		return;

	}
}

void Player::AttackColCheck()
{
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
		PlayerAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText_);
		CurDir_ = CheckDir_;
	}

}


void Player::CameraFix()
{
	// 커비를 중심에 둔다 
	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

	// 카메라가 범위를 벗어나면 위치를 0,0으로 맞춘다
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
	// 땅 밑으로 못 가게
	float4 CheckPos = GetPosition() + MoveDir * GameEngineTime::GetDeltaTime() * _Speed;

	int Color = MapColImage_->GetImagePixel(CheckPos);
	if (RGB(0, 0, 0) != Color)
	{
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
	// 오르막, 내리막길 
	float4 CheckPos = float4::DOWN;
	float4 LeftUpPos = float4::UP;

	int DownColor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 20.0f } + CheckPos);
	int LeftColor = MapColImage_->GetImagePixel(GetPosition() + float4{ -20.0f, 0.0f } + CheckPos);

	if (RGB(0, 0, 0) != DownColor)
	{
		// 땅에 닿아있는 동안은 계속 내려준다
		while (RGB(0, 0, 0) == DownColor)
		{
			CheckPos += float4::DOWN;
			DownColor = MapColImage_->GetImagePixel(GetPosition() + CheckPos);
		}
		SetMove(CheckPos);
	}
	else if (RGB(0, 0, 0) == LeftColor)
	{
		while (RGB(0, 0, 0) != LeftColor)
		{
			LeftUpPos += float4::UP;
			LeftColor = MapColImage_->GetImagePixel(GetPosition() + CheckPos);
		}
		SetMove(LeftUpPos);
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
	// 다음 맵으로 이동
	if ("Level_1" == GetCurrentLevelName())
		DoorCheck("Level_2");
	else if ("Level_2" == GetCurrentLevelName())
		DoorCheck("Level_3");
	else if ("Level_3" == GetCurrentLevelName())
		DoorCheck("Level_4");
	else if ("Level_4" == GetCurrentLevelName())
		DoorCheck("BossRoomLevel");
	else if ("BossRoomLevel" == GetCurrentLevelName())
		DoorCheck("BossLevel");

}

void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
}

//////////////////////////////////////////////////////////////////////// 디버그용
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
		DefaultKirbyUpdate();
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

void Player::DefaultKirbyUpdate()
{
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

	MainPlayer->SetPosition(GetPosition());
	CurSkill_ = KirbySkill::Default;
	MainPlayer->On();
}

void Player::MetalKirbyUpdate()
{
	if (CurSkill_ == KirbySkill::Metal)
	{
		return;
	}

	if (CurSkill_ == KirbySkill::Default)
	{
		MainPlayer->Off();
	}
	else if (CurSkill_ == KirbySkill::Ice)
	{
		IceKirby::IcePlayer->Off();
	}
	else if (CurSkill_ == KirbySkill::Spark)
	{
		SparkKirby::SparkPlayer->Off();
	}

	MetalKirby::MetalPlayer->SetPosition(GetPosition());
	CurSkill_ = KirbySkill::Metal;
	MetalKirby::MetalPlayer->On();
}

void Player::IceKirbyUpdate()
{
	if (CurSkill_ == KirbySkill::Ice)
	{
		return;
	}

	if (CurSkill_ == KirbySkill::Default)
	{
		MainPlayer->Off();
	}
	else if (CurSkill_ == KirbySkill::Metal)
	{
		MetalKirby::MetalPlayer->Off();
	}
	else if (CurSkill_ == KirbySkill::Spark)
	{
		SparkKirby::SparkPlayer->Off();
	}

	IceKirby::IcePlayer->SetPosition(GetPosition());
	CurSkill_ = KirbySkill::Ice;
	IceKirby::IcePlayer->On();
}

void Player::SparkKirbyUpdate()
{
	if (CurSkill_ == KirbySkill::Spark)
	{
		return;
	}

	if (CurSkill_ == KirbySkill::Default)
	{
		MainPlayer->Off();
	}
	else if (CurSkill_ == KirbySkill::Metal)
	{
		MetalKirby::MetalPlayer->Off();
	}
	else if (CurSkill_ == KirbySkill::Ice)
	{
		IceKirby::IcePlayer->Off();
	}

	SparkKirby::SparkPlayer->SetPosition(GetPosition());
	CurSkill_ = KirbySkill::Spark;
	SparkKirby::SparkPlayer->On();
}



// 충돌 -> 다음 스테이지로 이동
//void Player::DoorCheck()
//{
//
//	if (true == PlayerCollision->CollisionCheck("Door", CollisionType::Rect, CollisionType::Rect))
//	{
//		// if (true == GameEngineInput::GetInst()->IsDown("Down"))
//		GameEngine::GetInst().ChangeLevel("Level_2");
//	}
//}
