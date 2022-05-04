#include "Effect_Attack.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>

Effect_Attack::Effect_Attack()
	: AnimationRenderer_(nullptr)
	, AttackCollision_(nullptr)
	, MapColImage_(nullptr)
	, Dir_(EffectDir::Right)
{

}
Effect_Attack::~Effect_Attack()
{

}

void Effect_Attack::ColMapUpdate()
{
	std::string CurrentLevel = GetLevel()->GetNameCopy();

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

void Effect_Attack::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 220.f });

	AttackCollision_ = CreateCollision("AttackCol", { 70.f, 70.f }, {});


	AnimationRenderer_->CreateAnimation("Effect.bmp", "Attack_", 6, 7, 0.1f, true);
	AnimationRenderer_->CreateAnimation("Effect.bmp", "Attack_End", 15, 19, 0.08f, false);

	AnimationName_ = "Attack_";
	//ChangeDirText_ = "Left";
	//AnimationRenderer_->ChangeAnimation("Slide_Left");


	//Death(1.f);
}

void Effect_Attack::Update()
{
	ColMapUpdate();

	float4 LeftCheck = GetPosition() + float4{ -30.f, 0.0f };
	float4 RightCheck = GetPosition() + float4{30.f, 0.0f };

	int LeftColor = MapColImage_->GetImagePixel(LeftCheck);
	int RightColor = MapColImage_->GetImagePixel(RightCheck);

	// 왼쪽 벽에 닿았다 -> EndEff으로 바꾼다
	if (RGB(0, 0, 0) == LeftColor)
	{
		MoveDir = float4::ZERO;
		AnimationRenderer_->ChangeAnimation("Attack_End");

		if (AnimationRenderer_->IsEndAnimation())
		{
			Death();
		}
	}
	else if(RGB(0,0,0) == RightColor)	
	{
		MoveDir = float4::ZERO;
		AnimationRenderer_->ChangeAnimation("Attack_End");

		if (AnimationRenderer_->IsEndAnimation())
		{
			Death();
		}
	}
	else
	{
		// 벽에 닿지 않았다 -> Attack 애니메이션 계속 재생
		AnimationRenderer_->ChangeAnimation(AnimationName_);

		if (Dir_ == EffectDir::Right)
		{
			MoveDir.x = 2.f;
		}
		else
		{
			MoveDir.x = -2.f;
		}
	}

	SetMove(MoveDir);


	////////////////////////////////////// 충돌 체크
	{
		std::vector<GameEngineCollision*> ColList;
		if (true == AttackCollision_->CollisionCheck("DefaultMonster", CollisionType::Rect, CollisionType::Rect))
		{
			MoveDir = float4::ZERO;

			//AnimationRenderer_->ChangeAnimation("Attack_End");

			if (AnimationRenderer_->IsEndAnimation())
			{
				Death();
			}
		}
	}

}



