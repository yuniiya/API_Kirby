#include "Level_1.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>
#include "BackGround.h"
#include "Stage.h"
#include "Player.h"
#include "MetalKirby.h"
#include "IceKirby.h"
#include "SparkKirby.h"

#include "ContentsEnum.h"
#include "PlayUI.h"
#include "PlayerHP.h"
#include "Grass.h"
#include "Grass_1.h"
#include "Monster.h"
#include "WaddleDee.h"
#include "BigWaddleDee.h"
#include "Scarfy.h"
#include "Metalun.h"
#include "Sparky.h"
#include "Fade.h"
#include "FadeIn.h"
#include "Effect_DoorStar.h"

Level_1::Level_1()
{

}
Level_1::~Level_1()
{
}

void Level_1::Loading()
{

	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)ORDER::PLAYER, "Player");
		MetalKirby::MetalPlayer = CreateActor<MetalKirby>((int)ORDER::PLAYER, "MetalKirby");
		IceKirby::IcePlayer = CreateActor<IceKirby>((int)ORDER::PLAYER, "IceKirby");
		SparkKirby::SparkPlayer = CreateActor<SparkKirby>((int)ORDER::PLAYER, "SparkKirby");

		// UI 
		PlayUI::MainUI = CreateActor<PlayUI>((int)ORDER::UI, "PlayUI");
		PlayerHP::MainHP = CreateActor<PlayerHP>((int)ORDER::UI);
		//SkillUI::MainSkillUI = CreateActor<SkillUI>((int)ORDER::UI);
	}

	// 백그라운드 엑터
	{
		BackGround* CurBack = CreateActor<BackGround>((int)ORDER::BACKGROUND);
		CurBack->GetRenderer()->SetImage("Back1.bmp");

		float4 BackActor = {};
		BackActor.x = (CurBack->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (CurBack->GetRenderer()->GetImage()->GetScale().Half().y);

		CurBack->GetRenderer()->SetPivot(BackActor);
	}

	{
		Effect_DoorStar* DoorStar = CreateActor<Effect_DoorStar>((int)ORDER::STAGEACTOR);
		DoorStar->SetPosition({ 5594.f, 385.f });
	}


	// 스테이지
	{
		Stage* CurStage = CreateActor<Stage>((int)ORDER::STAGE);
		CurStage->GetRenderer()->SetImage("Level1.bmp");

		float4 StageActor = {};
		StageActor.x = (CurStage->GetRenderer()->GetImage()->GetScale().Half().x);
		StageActor.y = (CurStage->GetRenderer()->GetImage()->GetScale().Half().y);

		CurStage->GetRenderer()->SetPivot(StageActor);

		// 장애물 콜리전
		//CurStage->CreateCollision("Door", { 100.f, 100.f }, { 5595.f, 400.f });
	}

	// Grass 
	{
		Grass* Grass1 = CreateActor<Grass>((int)ORDER::STAGEACTOR, "Grass1");
		Grass1->SetPosition({ 780.f, 520.f });

		Grass* Grass2 = CreateActor<Grass>((int)ORDER::STAGEACTOR, "Grass2");
		Grass2->SetPosition({ 4858.f, 461.f });
		
		Grass_1* Grass3 = CreateActor<Grass_1>((int)ORDER::STAGEACTOR, "Grass3");
		Grass3->SetPosition({3062.f, 295.f});

	} //{3062.f, 295.f}

	// 몬스터
	{
		//WaddleDee* Waddle = CreateActor<WaddleDee>((int)ORDER::MONSTER, "WaddleDee");
		//Waddle->SetPosition({ 700.f, 400.f }); 

		//Waddle = CreateActor<WaddleDee>((int)ORDER::MONSTER, "WaddleDee");
		//Waddle->SetPosition({ 400.f, 400.f });


		WaddleDee* Waddle = CreateActor<WaddleDee>((int)ORDER::MONSTER, "WaddleDee");
		Waddle->SetPosition({ 1500.f, 400.f });

		//Waddle = CreateActor<WaddleDee>((int)ORDER::MONSTER, "WaddleDee");
		//Waddle->SetPosition({ 5200.f, 400.f });

		BigWaddleDee* BigWaddle = CreateActor<BigWaddleDee>((int)ORDER::MONSTER, "BigWaddleDee");
		BigWaddle->SetPosition({ 2700.f, 400.f });


		Scarfy* scarfy = CreateActor<Scarfy>((int)ORDER::MONSTER, "Scarfy");
		scarfy->SetPosition({1300.f, 300.f});
	}
	

	//{
	//	Metalun* NewMetalun = CreateActor<Metalun>((int)ORDER::MONSTER, "Metalun");
	//	NewMetalun->SetPosition({ 4200.f, 300.f });

	//	NewMetalun = CreateActor<Metalun>((int)ORDER::MONSTER, "Metalun");
	//	NewMetalun->SetPosition({ 700.f, 300.f });


	//	Sparky* NewSparky = CreateActor<Sparky>((int)ORDER::MONSTER, "Sparky");
	//	NewSparky->SetPosition({ 300.f, 300.f });
	//}

	

}

void Level_1::Update()
{
	// 레벨 체인지 
	if (true == GameEngineInput::GetInst()->IsDown("TitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::GetInst()->IsDown("Level_2"))
	{
		GameEngine::GetInst().ChangeLevel("Level_2");
	}

	if (true == GameEngineInput::GetInst()->IsDown("NextLevel"))
	{
		GameEngine::GetInst().ChangeLevel("Level_2");
	}
}

void Level_1::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	// 페이드인
	FadeIn* Fade = CreateActor<FadeIn>((int)ORDER::UI);

	{
		Player::MainPlayer->SetPosition({ 100.f, 520.f });
		//Player::MainPlayer->SetPosition({ 1800.f, 420.f });
		//Player::MainPlayer->SetPosition({ 5300.f, 450.f });
		//Player::MainPlayer->SetPosition({ 2900.f, 200.f });

		MetalKirby::MetalPlayer->SetPosition({ 100.f, 520.f });
		//MetalKirby::MetalPlayer->SetPosition({ 2800.f, 200.f });

		IceKirby::IcePlayer->SetPosition({ 100.f, 520.f });

		SparkKirby::SparkPlayer->SetPosition({ 100.f, 520.f });
	}


	{
		Player::MainPlayer->MapScale(5753.f, 760.f);
		MetalKirby::MetalPlayer->MapScale(5753.f, 760.f);
		IceKirby::IcePlayer->MapScale(5753.f, 760.f);
		SparkKirby::SparkPlayer->MapScale(5753.f, 760.f);
	}
	
}

void Level_1::LevelChangeEnd(GameEngineLevel* _NextLevel)
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
