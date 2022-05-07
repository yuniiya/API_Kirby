#include "BossRoomLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include "BackGround.h"
#include "Stage.h"
#include "Player.h"
#include "MetalKirby.h"
#include "IceKirby.h"
#include "SparkKirby.h"

#include "ContentsEnum.h"
#include "PlayUI.h"
#include "PlayerHP.h"
#include "FadeIn.h"
#include "Effect_DoorStar.h"

BossRoomLevel::BossRoomLevel()
{

}
BossRoomLevel::~BossRoomLevel()
{

}

void BossRoomLevel::Loading()
{
	// 백그라운드 엑터
	{
		BackGround* CurBack = CreateActor<BackGround>((int)ORDER::BACKGROUND);
		CurBack->GetRenderer()->SetImage("BossRoomLevel.bmp");

		float4 BackActor = {};
		BackActor.x = (CurBack->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (CurBack->GetRenderer()->GetImage()->GetScale().Half().y);

		CurBack->GetRenderer()->SetPivot(BackActor);
	}

	{
		Effect_DoorStar* DoorStar = CreateActor<Effect_DoorStar>((int)ORDER::STAGEACTOR);
		DoorStar->SetPosition({ 545.f, 510.f });
	}

}

void BossRoomLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("TitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::GetInst()->IsDown("BossLevel"))
	{
		GameEngine::GetInst().ChangeLevel("BossLevel");
	}

	if (true == GameEngineInput::GetInst()->IsDown("NextLevel"))
	{
		GameEngine::GetInst().ChangeLevel("BossLevel");
	}
}

void BossRoomLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	// 페이드인
	FadeIn* Fade = CreateActor<FadeIn>((int)ORDER::UI);

	Player::BgmPlayer.Stop();
	Player::BgmPlayer = GameEngineSound::SoundPlayControl("BossRoom.mp3");

	{
		Player::MainPlayer->SetPosition({ 100.f, 500.f });
		MetalKirby::MetalPlayer->SetPosition({ 100.f, 500.f });
		IceKirby::IcePlayer->SetPosition({ 100.f, 500.f });
		SparkKirby::SparkPlayer->SetPosition({ 100.f, 500.f });
	}
	
	{
		Player::MainPlayer->MapScale(1024.f, 768.f);
		MetalKirby::MetalPlayer->MapScale(1024.f, 768.f);
		IceKirby::IcePlayer->MapScale(1024.f, 768.f);
		SparkKirby::SparkPlayer->MapScale(1024.f, 768.f);
	}
	
}

void BossRoomLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		MetalKirby::MetalPlayer->NextLevelOn();
		IceKirby::IcePlayer->NextLevelOn();
		SparkKirby::SparkPlayer->NextLevelOn();

		PlayUI::MainUI->NextLevelOn();
		PlayerHP::MainHP->NextLevelOn();
	}
}
