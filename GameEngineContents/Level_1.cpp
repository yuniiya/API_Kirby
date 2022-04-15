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
#include "ContentsEnum.h"
#include "PlayUI.h"

Level_1::Level_1()
{

}
Level_1::~Level_1()
{
}

void Level_1::Loading()
{
	

	// UI 
	CreateActor<PlayUI>((int)ORDER::UI, "PlayUI");


	// 플레이어 엑터
	Player* Kirby = CreateActor<Player>((int)ORDER::PLAYER, "Player");
	Kirby->SetPosition({100.f, 300.f});
	Kirby->MapScale(5753.f, 768.f);

	 // 백그라운드 엑터
	{
		BackGround* CurBack = CreateActor<BackGround>((int)ORDER::BACKGROUND);
		CurBack->GetRenderer()->SetImage("Back1.bmp");

		float4 BackActor = {};
		BackActor.x = (CurBack->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (CurBack->GetRenderer()->GetImage()->GetScale().Half().y);

		CurBack->GetRenderer()->SetPivot(BackActor);
	}

	
	// 스테이지
	{
		Stage* CurStage = CreateActor<Stage>((int)ORDER::STAGE);
		CurStage->GetRenderer()->SetImage("Level1.bmp");

		float4 StageActor = {};
		StageActor.x = (CurStage->GetRenderer()->GetImage()->GetScale().Half().x);
		StageActor.y = (CurStage->GetRenderer()->GetImage()->GetScale().Half().y);

		CurStage->GetRenderer()->SetPivot(StageActor);


		CurStage->CreateCollision("Door", { 100, 100 }, { 500, 200 });

		// 장애물 콜리전
		//CurStage->CreateCollision("Wall", { 100, 100 }, { 300, 200 });
	}
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
}

void Level_1::LevelChangeStart()
{
	//BgmPlayer = GameEngineSound::SoundPlayControl("Play1.mp3");
}

void Level_1::LevelChangeEnd()
{
	//BgmPlayer.Stop();
}
