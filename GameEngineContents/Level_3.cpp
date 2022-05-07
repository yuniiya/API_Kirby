#include "Level_3.h"
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
#include "Water.h"
#include "FadeIn.h"
#include "Effect_DoorStar.h"

Level_3::Level_3()
{

}
Level_3::~Level_3()
{

}

void Level_3::Loading()
{
	// 백그라운드 엑터
	{
		BackGround * CurBack = CreateActor<BackGround>(0);
		CurBack->GetRenderer()->SetImage("Back1.bmp");

		float4 BackActor = {};
		BackActor.x = (CurBack->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (CurBack->GetRenderer()->GetImage()->GetScale().Half().y);

		CurBack->GetRenderer()->SetPivot(BackActor);
	}

	{
		Effect_DoorStar* DoorStar = CreateActor<Effect_DoorStar>((int)ORDER::STAGEACTOR);
		DoorStar->SetPosition({ 5776.f, 165.f });
	}

	{
		Stage* CurStage = CreateActor<Stage>((int)ORDER::STAGE);
		CurStage->GetRenderer()->SetImage("Level3.bmp");


		float4 StageActor = {};
		StageActor.x = (CurStage->GetRenderer()->GetImage()->GetScale().Half().x);
		StageActor.y = (CurStage->GetRenderer()->GetImage()->GetScale().Half().y);

		CurStage->GetRenderer()->SetPivot(StageActor);
	}

	{
		Water* Water1 = CreateActor<Water>((int)ORDER::STAGEACTOR);
		Water1->SetPosition({ 2734.f, 425.f });
	}
}

void Level_3::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("TitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::GetInst()->IsDown("Level_4"))
	{
		GameEngine::GetInst().ChangeLevel("Level_4");
	}

	if (true == GameEngineInput::GetInst()->IsDown("NextLevel"))
	{
		GameEngine::GetInst().ChangeLevel("Level_4");
	}

}

void Level_3::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineSound::SoundPlayOneShot("Enter.wav");

	FadeIn* Fade = CreateActor<FadeIn>((int)ORDER::UI);

	{
		Player::MainPlayer->SetPosition({ 100.f, 490.f });
		//Player::MainPlayer->SetPosition({ 2700.f, 490.f });
		//Player::MainPlayer->SetPosition({ 5600.f, 490.f });
		MetalKirby::MetalPlayer->SetPosition({ 100.f, 490.f });
		IceKirby::IcePlayer->SetPosition({ 100.f, 490.f });
		SparkKirby::SparkPlayer->SetPosition({ 100.f, 490.f });
	}
	
	{
		Player::MainPlayer->MapScale(5960.f, 768.f);
		MetalKirby::MetalPlayer->MapScale(5960.f, 768.f);
		IceKirby::IcePlayer->MapScale(5960.f, 768.f);
		SparkKirby::SparkPlayer->MapScale(5960.f, 768.f);
	}
	
}

void Level_3::LevelChangeEnd(GameEngineLevel* _NextLevel)
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
