#include "BossLevel.h"
#include "Player.h"
#include "PlayUI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineActor.h>
#include "BackGround.h"
#include "MapActor.h"
#include "ContentsEnum.h"

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
	Player::MainPlayer->SetPosition({ 100.f, 500.f });
	Player::MainPlayer->MapScale(1024.f, 768.f);


	BgmPlayer = GameEngineSound::SoundPlayControl("Boss.mp3");
}

void BossLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		PlayUI::MainUI->NextLevelOn();
	}

	BgmPlayer.Stop();
}


