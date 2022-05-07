#include "Level_4.h"
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
#include "Water_1.h"
#include "Water_2.h"
#include "FadeIn.h"
#include "Effect_DoorStar.h"
#include "GameEngine/GameEngineCollision.h"

Level_4::Level_4()
{

}
Level_4::~Level_4()
{

}

void Level_4::Loading()
{
	// 백그라운드 엑터
	{
		BackGround* CurBack = CreateActor<BackGround>((int)ORDER::BACKGROUND, "BackGround");
		CurBack->GetRenderer()->SetImage("Back3.bmp");

		float4 BackActor = {};
		BackActor.x = (CurBack->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (CurBack->GetRenderer()->GetImage()->GetScale().Half().y);

		CurBack->GetRenderer()->SetPivot(BackActor);
	}

	{
		Effect_DoorStar* DoorStar = CreateActor<Effect_DoorStar>((int)ORDER::STAGEACTOR);
		DoorStar->SetPosition({ 2856.f, 265.f });
	}

	{
		Stage* CurStage = CreateActor<Stage>((int)ORDER::STAGE, "Stage");
		CurStage->GetRenderer()->SetImage("Level4.bmp");


		float4 StageActor = {};
		StageActor.x = (CurStage->GetRenderer()->GetImage()->GetScale().Half().x);
		StageActor.y = (CurStage->GetRenderer()->GetImage()->GetScale().Half().y);

		CurStage->GetRenderer()->SetPivot(StageActor);


		// 강에 IceBreath닿으면 얼음 생성 
		//GameEngineCollision* WaterCol = CurStage->CreateCollision("Water1", { 690.f, 205.f }, { 1216.f, 535.f });

		//std::vector<GameEngineCollision*> ColList;

		//if (true == WaterCol->CollisionResult("IceBreathCol", ColList, CollisionType::Rect, CollisionType::Rect))
		//{
		//	
		//}
		//
		//CurStage->CreateCollision("Water2", { 560.f, 215.f }, { 2400.f, 522.f });
	}

	{
		Water_1* Water1 = CreateActor<Water_1>((int)ORDER::GRASS);
		Water1->SetPosition({ 1215.f, 432.f });

		Water_2* Water2 = CreateActor<Water_2>((int)ORDER::GRASS);
		Water2->SetPosition({ 2400.f, 433.f });
	}


}

void Level_4::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("TitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::GetInst()->IsDown("BossRoomLevel"))
	{
		GameEngine::GetInst().ChangeLevel("BossRoomLevel");
	}

	if (true == GameEngineInput::GetInst()->IsDown("NextLevel"))
	{
		GameEngine::GetInst().ChangeLevel("BossRoomLevel");
	}
}

void Level_4::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineSound::SoundPlayOneShot("Enter.wav");

	FadeIn* Fade = CreateActor<FadeIn>((int)ORDER::UI);

	//Player::BgmPlayer.Stop();
	Player::BgmPlayer = GameEngineSound::SoundPlayControl("Play2.mp3");

	{
		//Player::MainPlayer->SetPosition({ 100.f, 440.f });
		Player::MainPlayer->SetPosition({ 2700.f, 440.f });
		MetalKirby::MetalPlayer->SetPosition({ 100.f, 440.f });
		IceKirby::IcePlayer->SetPosition({ 100.f, 440.f });
		SparkKirby::SparkPlayer->SetPosition({ 100.f, 440.f });
	}
	
	{
		Player::MainPlayer->MapScale(3073.f, 768.f);
		MetalKirby::MetalPlayer->MapScale(3073.f, 768.f);
		IceKirby::IcePlayer->MapScale(3073.f, 768.f);
		SparkKirby::SparkPlayer->MapScale(3073.f, 768.f);
	}
	
}

void Level_4::LevelChangeEnd(GameEngineLevel* _NextLevel)
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
