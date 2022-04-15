#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include <GameEngine/GameEngineLevel.h>
#include "Bullet.h"
#include "Stage.h"
#include "ContentsEnum.h"

Player* Player::MainPlayer = nullptr;

Player::Player()
	: Speed_(500.0f)
	, Gravity_(100.0f)
	, MapColImage_(nullptr)
	, AccGravity_(100.f)
	, PlayerCollision(nullptr)
	, PlayerAnimationRender(nullptr)
	, CurState_(PlayerState::Idle)
	, Render1(nullptr)
	, MapScaleX_(0.f)
	, MapScaleY_(0.f)
	, MoveDir(float4::ZERO)
	, CurDir_(PlayerDir::Right)
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
		false == GameEngineInput::GetInst()->IsPress("MoveRight") &&
		false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
		false == GameEngineInput::GetInst()->IsPress("MoveDown")
		) 
	{
		return false;
	}

	return true;
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
		case PlayerState::Inhale:
			InhaleStart();
			break;
		case PlayerState::Full:
			FullStart();
			break;
		case PlayerState::Exhale:
			ExhaleStart();
			break;
		case PlayerState::Swallow:
			SwallowStart();
			break;
		case PlayerState::Attack:
			AttackStart();
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
	case PlayerState::Inhale:
		InhaleUpdate();
		break;
	case PlayerState::Full:
		FullUpdate();
		break;
	case PlayerState::Exhale:
		ExhaleUpdate();
		break;
	case PlayerState::Swallow:
		SwallowUpdate();
		break;
	case PlayerState::Attack:
		AttackUpdate();
		break;
	case PlayerState::Damaged:
		DamagedUpdate();
		break;
	}
}


void Player::Start()
{
	//SetScale({ 1000, 1000 });

	PlayerCollision = CreateCollision("PlayerHitBox", { 100, 100 });

	// 애니메이션을 하나라도 만들면 애니메이션이 재생된다.
	PlayerAnimationRender = CreateRenderer();
	PlayerAnimationRender->SetPivotType(RenderPivot::BOT);
	PlayerAnimationRender->SetPivot({ 0.f, 140.f });
	//PlayerAnimationRender = CreateRendererToScale("Test.bmp",{100, 1000});
	//PlayerAnimationRender = CreateRendererToScale("1_Right.bmp", {128, 128}, static_cast<int>(ORDER::PLAYER), RenderPivot::BOT);

	// Walk_Right이미지의 0~9인덱스를 0.1초동안 재생 (true = 루프on)
	//Render->SetPivotType(RenderPivot::BOT);
	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Idle_Left", 0, 1, 1.f, true);
	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Down_Left", 2, 3, 5.f, false);
	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Slide_Left", 4, 5, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Walk_Left", 6, 15, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Run_Left", 16, 23, 1.f, true);
	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "RunToStop_Left", 24, 24, 0.5f, true);
	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Float_Left", 29, 25, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("Default_Left.bmp", "Inhale_Left", 30, 37, 0.1f, true);

	//PlayerAnimationRender->CreateAnimation("Default_Jump_Left.bmp", "Jump_Left", 0, 9, 0.1f, true);



	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Idle_Right", 0, 1, 1.f, true);
	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Down_Right", 2, 3, 5.f, false);
	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Slide_Right", 4, 5, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Walk_Right", 6, 15, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Run_Right", 16, 23, 1.f, true);
	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "RunToStop_Right", 24, 24, 0.5f, true);
	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Float_Right", 29, 25, 0.1f, true);
	PlayerAnimationRender->CreateAnimation("Default_Right.bmp", "Inhale_Right", 30, 37, 0.1f, true);

	//PlayerAnimationRender->CreateAnimation("Default_Jump_Right.bmp", "Jump_Right", 0, 9, 0.1f, true);

	AnimationName_ = "Idle_";
	PlayerAnimationRender->ChangeAnimation("Idle_Right");



	//CreateRendererToScale("Walk.bmp", GetScale(), RenderPivot::CENTER, float4(0.0f, 170.0f));
	//AnimationName = "Walk_Right";
	//CurDir_ = PlayerDir::Right;



	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		// =============== 이동 ===============
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Run", VK_SPACE);
		// 두번 연타 : Run
		// Run상태에서 반대 방향키 : RunToStop

		GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MoveDown", VK_DOWN);
		// 지형 위에서 MoveDown: Down
		// Full 상태에서 MoveDown : Swallow

		// =============== 점프 ===============
		//GameEngineInput::GetInst()->CreateKey("JumpLeft",'A');
		//GameEngineInput::GetInst()->CreateKey("JumpRight", 'D');
		// 두번 연타한다면 A, D : Float
		// 아래 + A, D: Slide

		// =============== 흡수 ===============
		GameEngineInput::GetInst()->CreateKey("Inhale", 'S');
		// Inhale 상태에서 S : Exhale or Attack
		// Float 상태에서 S : Exhale
		
		// =============== 스킬 ===============
		// 빨아들인 물체가 스킬을 가졌다면 W : Copy
		//GameEngineInput::GetInst()->CreateKey("Copy", 'W');
		GameEngineInput::GetInst()->CreateKey("Down", 'W');
		// 능력을 카피한 상태에서 W : 스킬 해제
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

	// 카메라 위치 고정
	CameraFix();


	//WallCheck();



	// ============================================== 가속 
	//AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;
	//// 땅에 닿았다면
	//if (RGB(0, 0, 0) == Color)
	//{
	//	AccGravity_ = 0.0f;
	//}
	//SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);


	//if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	//{
	//	Bullet* Ptr = GetLevel()->CreateActor<Bullet>();
	//	// 총알이 내 위치에서 만들어진다
	//	Ptr->SetPosition(GetPosition());
	//}
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

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
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

	if (RGB(0, 0, 255) == Color && true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		GameEngine::GetInst().ChangeLevel(ChangeLevelName_);
	}
}

void Player::StagePixelCheck()
{
	// 땅 밑으로 못 가게
	MoveDir = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir = float4::RIGHT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir = float4::UP;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir = float4::DOWN;
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

void Player::LevelChangeStart()
{
	MainPlayer = this;
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
