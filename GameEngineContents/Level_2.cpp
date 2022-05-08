#include "Level_2.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "BackGround.h"
#include "Stage.h"
#include "Player.h"
#include "MetalKirby.h"
#include "IceKirby.h"
#include "SparkKirby.h"

#include "ContentsEnum.h"
#include "PlayUI.h"
#include "PlayerHP.h"
#include "Grass_2.h"
#include "Grass_3.h"
#include "Grass_4.h"
#include "Grass_5.h"
#include "WaddleDee.h"
#include "BigWaddleDee.h"
#include "Scarfy.h"
#include "Pengy.h"
#include "FadeIn.h"
#include "Effect_DoorStar.h"
#include "Scarfy.h"
#include "Metalun.h"

Level_2::Level_2()
{

}
Level_2::~Level_2()
{

}

void Level_2::Loading()
{
	// UI 
	//CreateActor<PlayUI>((int)ORDER::UI, "PlayUI");


	// 플레이어
	//{
	//	Player* Kirby = CreateActor<Player>((int)ORDER::PLAYER);
	//	Kirby->SetPosition({ 100.f, 490.f });
	//	Kirby->MapScale(5376.f, 768.f);
	//}

	{
		// 백그라운드
		BackGround* CurBack = CreateActor<BackGround>(0);
		CurBack->GetRenderer()->SetImage("Back1.bmp");

		float4 BackActor = {};
		BackActor.x = (CurBack->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (CurBack->GetRenderer()->GetImage()->GetScale().Half().y);

		CurBack->GetRenderer()->SetPivot(BackActor);
	}

	{
		Effect_DoorStar* DoorStar = CreateActor<Effect_DoorStar>((int)ORDER::STAGEACTOR);
		DoorStar->SetPosition({ 5256.f, 325.f });
	}

	{
		Stage* CurStage = CreateActor<Stage>((int)ORDER::STAGE);
		CurStage->GetRenderer()->SetImage("Level2.bmp");


		float4 StageActor = {};
		StageActor.x = (CurStage->GetRenderer()->GetImage()->GetScale().Half().x);
		StageActor.y = (CurStage->GetRenderer()->GetImage()->GetScale().Half().y);

		CurStage->GetRenderer()->SetPivot(StageActor);
	}

	{
		Grass_2* Grass1 = CreateActor<Grass_2>((int)ORDER::STAGEACTOR, "Grass1");
		Grass1->SetPosition({ 355.f, 513.f });

		Grass_3* Grass2 = CreateActor<Grass_3>((int)ORDER::STAGEACTOR, "Grass2");
		Grass2->SetPosition({ 2070.f, 513.f });

		Grass_4* Grass3 = CreateActor<Grass_4>((int)ORDER::STAGEACTOR, "Grass3");
		Grass3->SetPosition({ 4020.f, 514.f });

		Grass_5* Grass4 = CreateActor<Grass_5>((int)ORDER::GRASS, "Grass4");
		Grass4->SetPosition({ 5201.f, 395.f });

	}
	
	// 몬스터
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>((int)ORDER::MONSTER, "WaddleDee");
		Waddle->SetPosition({ 600.f, 450.f });

		BigWaddleDee* BigWaddle = CreateActor<BigWaddleDee>((int)ORDER::MONSTER, "BigWaddleDee");
		BigWaddle->SetPosition({ 1900.f, 500.f });

		Waddle = CreateActor<WaddleDee>((int)ORDER::MONSTER, "WaddleDee");
		Waddle->SetPosition({ 2300.f, 500.f });

		Waddle = CreateActor<WaddleDee>((int)ORDER::MONSTER, "WaddleDee");
		Waddle->SetPosition({ 3600.f, 400.f });


		Metalun* NewMetalun = CreateActor<Metalun>((int)ORDER::MONSTER, "Metalun");
		NewMetalun->SetPosition({ 4800.f, 500.f });


		//Scarfy* scarfy = CreateActor<Scarfy>((int)ORDER::MONSTER, "Scarfy");
		//scarfy->SetPosition({ 500.f, 400.f });

	}
}

void Level_2::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("TitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::GetInst()->IsDown("Level_3"))
	{
		GameEngine::GetInst().ChangeLevel("Level_3");
	}

	if (true == GameEngineInput::GetInst()->IsDown("NextLevel"))
	{
		GameEngine::GetInst().ChangeLevel("Level_3");
	}
}

void Level_2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineSound::SoundPlayOneShot("Enter.wav");


	// 페이드인
	FadeIn* Fade = CreateActor<FadeIn>((int)ORDER::UI);

	{
		Player::MainPlayer->SetPosition({ 100.f, 490.f });
		//Player::MainPlayer->SetPosition({ 5100.f, 490.f });
		//Player::MainPlayer->SetPosition({ 1000.f, 490.f });
		MetalKirby::MetalPlayer->SetPosition({ 100.f, 490.f });
		IceKirby::IcePlayer->SetPosition({ 100.f, 490.f });
		SparkKirby::SparkPlayer->SetPosition({ 100.f, 490.f });

	}

	{
		Player::MainPlayer->MapScale(5376.f, 768.f);
		MetalKirby::MetalPlayer->MapScale(5376.f, 768.f);
		IceKirby::IcePlayer->MapScale(5376.f, 768.f);
		SparkKirby::SparkPlayer->MapScale(5376.f, 768.f);
	}
}

void Level_2::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		MetalKirby::MetalPlayer->NextLevelOn();
		IceKirby::IcePlayer->NextLevelOn();
		SparkKirby::SparkPlayer->NextLevelOn();

		PlayUI::MainUI->NextLevelOn();
		PlayerHP::MainHP->NextLevelOn();

		MetalKirby::MetalSkill->NextLevelOn();
		MetalKirby::MetalName->NextLevelOn();
		IceKirby::IceSkill->NextLevelOn();
		IceKirby::IceName->NextLevelOn();
		SparkKirby::SparkSkill->NextLevelOn();
		SparkKirby::SparkName->NextLevelOn();
	}

}
