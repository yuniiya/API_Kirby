#include "BossLevel.h"
#include "Player.h"
#include "MetalKirby.h"
#include "IceKirby.h"
#include "SparkKirby.h"

#include "PlayUI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineActor.h>
#include "BackGround.h"
#include "MapActor.h"
#include "ContentsEnum.h"
#include "Kingdedede.h"

BossLevel::BossLevel()
{

}
BossLevel::~BossLevel()
{

}

void BossLevel::Loading()
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
		MapActor* BackAnimation = CreateActor<MapActor>((int)ORDER::BACKGROUND);
		BackAnimation->SetPosition({512, 384});

		//float4 BackActor = {};
		//BackActor.x = (BackAnimation->GetRenderer()->GetImage()->GetScale().Half().x);
		//BackActor.y = (BackAnimation->GetRenderer()->GetImage()->GetScale().Half().y);

		//BackAnimation->GetRenderer()->SetPivot(BackActor);


		//Stage* CurBack = CreateActor<Stage>((int)ORDER::STAGE);
		/*CurBack->CreateRenderer()->CreateFolderAnimation("BossLevel", "BossLevel", 0, 11, 0.1f, true);
		CurBack = CreateActor<Stage>((int)ORDER::STAGE);
		CurBack->GetRenderer()->CreateFolderAnimation()*/

		//BackRender->CreateRenderer()->CreateFolderAnimation("BossLevel", "BossLevel", 0, 11, 0.1f, true);
		//AnimationRender_->CreateFolderAnimation("BossLevel", "BossLevel", 0, 11, 0.1f, true);
	
	}

	{
		Kingdedede* Boss = CreateActor<Kingdedede>((int)ORDER::MONSTER, "Boss");
		Boss->SetPosition({900.f, 500.f });
	}
}

void BossLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("TitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::GetInst()->IsDown("EndingLevel"))
	{
		GameEngine::GetInst().ChangeLevel("EndingLevel");
	}

	if (true == GameEngineInput::GetInst()->IsDown("NextLevel"))
	{
		GameEngine::GetInst().ChangeLevel("EndingLevel");
	}
}

void BossLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Player::BgmPlayer.Stop();
	Player::BgmPlayer = GameEngineSound::SoundPlayControl("Boss.mp3");

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

void BossLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Player::BgmPlayer.Stop();

	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		MetalKirby::MetalPlayer->NextLevelOn();
		SparkKirby::SparkPlayer->NextLevelOn();
		PlayUI::MainUI->NextLevelOn();
	};
}


