#include "Effect_ReleaseSkill.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Effect_ReleaseSkill::Effect_ReleaseSkill()
	: AnimationRenderer_(nullptr)
	, AttackCollision_(nullptr)
	, MapColImage_(nullptr)
	, Dir_(EffectDir::Right)
{

}
Effect_ReleaseSkill::~Effect_ReleaseSkill()
{

}

void Effect_ReleaseSkill::ColMapUpdate()
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

void Effect_ReleaseSkill::Start()
{
	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 220.f });

	AnimationRenderer_->CreateAnimation("Effect.bmp", "ReleaseSkil_", 6, 7, 0.08f, true);

	AnimationName_ = "ReleaseSkil_";

	Death(0.4f);
}

void Effect_ReleaseSkill::Update()
{
	ColMapUpdate();

	if (Dir_ == EffectDir::Right)
	{
		MoveDir = float4{-150.f, -400.f};
		SetMove(MoveDir * GameEngineTime::GetDeltaTime());
	}
	else
	{
		MoveDir = float4{ 150.f, -400.f };
		SetMove(MoveDir * GameEngineTime::GetDeltaTime());
	}

	AnimationRenderer_->ChangeAnimation(AnimationName_);

	//float4 DownCheck = GetPosition() + float4{ 0.f, 30.0f };
	//float4 LeftCheck = GetPosition() + float4{ -30.f, 0.0f };
	//float4 RightCheck = GetPosition() + float4{ 30.f, 0.0f };

	//int DownColor = MapColImage_->GetImagePixel(DownCheck);
	//int LeftColor = MapColImage_->GetImagePixel(LeftCheck);
	//int RightColor = MapColImage_->GetImagePixel(RightCheck);

	//if (RGB(0, 0, 0) == LeftColor)
	//{

	//}
	//else if (RGB(0, 0, 0) == RightColor)
	//{

	//}
	//else
	//{
	//	// 벽에 닿지 않았다 -> Attack 애니메이션 계속 재생
	//	AnimationRenderer_->ChangeAnimation(AnimationName_);

	//	if (Dir_ == EffectDir::Right)
	//	{
	//		MoveDir.x = 2.f;
	//	}
	//	else
	//	{
	//		MoveDir.x = -2.f;
	//	}
	//}

	//SetMove(MoveDir);
}



