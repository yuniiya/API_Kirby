#include "Effect_BigIceBox.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase//GameEngineTime.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineLevel.h>
#include "Effect_IceBoxEnd.h"


Effect_BigIceBox::Effect_BigIceBox()
	: AnimationRenderer_(nullptr)
	, IceTime_(4.f)
	, IsSlide(false)
	, IsCrack(false)
	, IsSlideSound(false)
{

}

Effect_BigIceBox::~Effect_BigIceBox()
{

}

void Effect_BigIceBox::SlideOn()
{
	float4 PlayerPos = IceKirby::IcePlayer->GetPosition();
	//float4 PrevPlayerPos = PlayerPos;

	//if (PrevPlayerPos.x != PlayerPos.x)
	//{
	//	PlayerPos = PrevPlayerPos;
	//}

	if (PlayerPos.x < GetPosition().x)
	{
		MoveDir.x = 2.f;
	}
	else if (PlayerPos.x > GetPosition().x)
	{
		MoveDir.x = -2.f;
	}

	SetMove(MoveDir);
}

void Effect_BigIceBox::CrackOn()
{
	//GameEngineSound::SoundPlayOneShot("IceCrack.wav");

	Death();

	Effect_IceBoxEnd* Effect = GetLevel()->CreateActor<Effect_IceBoxEnd>((int)ORDER::EFFECT);
	Effect->SetPosition(GetPosition());
}

void Effect_BigIceBox::PlaySlideSound()
{
	GameEngineSound::SoundPlayOneShot("IcePush2.wav");
}

void Effect_BigIceBox::CollisionCheck()
{
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == IceCollision_->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			IsSlide = true;
		}
	}

	{
		std::vector<GameEngineCollision*> ColList;

		if (true == IceCollision_->CollisionResult("DefaultMonster", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			IsCrack = true;
		}
	}

}

void Effect_BigIceBox::ColMapUpdate()
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

void Effect_BigIceBox::Start()
{
	IceCollision_ = CreateCollision("IceBoxCol", { 80, 80 });

	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 210.f });

	AnimationRenderer_->CreateAnimation("Effect.bmp", "IceBox_", 50, 50, 0.1f, false);

	AnimationName_ = "IceBox_";

	GameEngineSound::SoundPlayOneShot("Ice2.wav");
	//Death(0.8f);
}

void Effect_BigIceBox::Update()
{
	AnimationRenderer_->ChangeAnimation(AnimationName_);

	ColMapUpdate();
	CollisionCheck();

	if (true == IsSlide)
	{
		SlideOn();

		IsSlideSound = true;
	}

	//if (true == IsSlideSound)
	//{
	//	GameEngineSound::SoundPlayOneShot("IcePush2.wav");
	//}

	if (true == IsCrack)
	{
		CrackOn();
	}

	float4 LeftCheck = GetPosition() + float4{ -30.f, 0.0f };
	float4 RightCheck = GetPosition() + float4{ 30.f, 0.0f };

	int LeftColor = MapColImage_->GetImagePixel(LeftCheck);
	int RightColor = MapColImage_->GetImagePixel(RightCheck);

	// ���� ���� ��Ҵ� -> EndEff���� �ٲ۴�
	if (RGB(0, 0, 0) == LeftColor
		|| RGB(0, 0, 0) == RightColor)
	{
		Death();

		Effect_IceBoxEnd* Effect = GetLevel()->CreateActor<Effect_IceBoxEnd>((int)ORDER::EFFECT);
		Effect->SetPosition(GetPosition());
	}


	/////////// ���ӽð� + ���� ����� �� ����Ʈ
	IceTime_ -= GameEngineTime::GetDeltaTime();

	if (IceTime_ < 0)
	{
		Death();

		Effect_IceBoxEnd* Effect = GetLevel()->CreateActor<Effect_IceBoxEnd>((int)ORDER::EFFECT);
		Effect->SetPosition(GetPosition());
	}
}


