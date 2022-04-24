#include "Level_2.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "BackGround.h"
#include "Stage.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "PlayUI.h"
#include "Grass.h"

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
		Stage* CurStage = CreateActor<Stage>((int)ORDER::STAGE);
		CurStage->GetRenderer()->SetImage("Level2.bmp");


		float4 StageActor = {};
		StageActor.x = (CurStage->GetRenderer()->GetImage()->GetScale().Half().x);
		StageActor.y = (CurStage->GetRenderer()->GetImage()->GetScale().Half().y);

		CurStage->GetRenderer()->SetPivot(StageActor);
	}

	{
		GameEngineImage* GrassImage = GameEngineImageManager::GetInst()->Find("Grass2-1.bmp");
		GrassImage->CutCount(1, 4);
		Grass* Grass1 = CreateActor<Grass>((int)ORDER::STAGEACTOR, "Grass1");
		GameEngineRenderer* Renderer = Grass1->CreateRenderer("Grass2-1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, { 355.f, 513.f });
		Renderer->CreateAnimation("Grass2-1.bmp", "Grass1", 0, 3, 0.25f, true);
		Renderer->ChangeAnimation("Grass1");

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
	Player::MainPlayer->SetPosition({ 100.f, 490.f });
	Player::MainPlayer->MapScale(5376.f, 768.f);

	BgmPlayer = GameEngineSound::SoundPlayControl("Play1.mp3");
}

void Level_2::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		PlayUI::MainUI->NextLevelOn();
	}

	BgmPlayer.Stop();
}
