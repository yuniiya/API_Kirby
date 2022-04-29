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

BossRoomLevel::BossRoomLevel()
{

}
BossRoomLevel::~BossRoomLevel()
{

}

void BossRoomLevel::Loading()
{
	// UI 
	//CreateActor<PlayUI>((int)ORDER::UI, "PlayUI");

	//{
	//	Player* Kirby = CreateActor<Player>((int)ORDER::PLAYER);
	//	Kirby->SetPosition({ 100.f, 500.f });
	//	Kirby->MapScale(1024.f, 768.f);
	//}

	// 백그라운드 엑터
	{
		BackGround* CurBack = CreateActor<BackGround>((int)ORDER::BACKGROUND);
		CurBack->GetRenderer()->SetImage("BossRoomLevel.bmp");

		float4 BackActor = {};
		BackActor.x = (CurBack->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (CurBack->GetRenderer()->GetImage()->GetScale().Half().y);

		CurBack->GetRenderer()->SetPivot(BackActor);
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
	Player::BgmPlayer.Stop();
	Player::BgmPlayer = GameEngineSound::SoundPlayControl("BossRoom.mp3");

	{
		Player::MainPlayer->SetPosition({ 100.f, 500.f });
		MetalKirby::MetalPlayer->SetPosition({ 100.f, 500.f });
		SparkKirby::SparkPlayer->SetPosition({ 100.f, 500.f });
	}
	
	{
		Player::MainPlayer->MapScale(1024.f, 768.f);
		MetalKirby::MetalPlayer->MapScale(1024.f, 768.f);
		SparkKirby::SparkPlayer->MapScale(1024.f, 768.f);
	}
	
}

void BossRoomLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		MetalKirby::MetalPlayer->NextLevelOn();
		SparkKirby::SparkPlayer->NextLevelOn();
		PlayUI::MainUI->NextLevelOn();
	}
}
