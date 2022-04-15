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

Level_2::Level_2()
{

}
Level_2::~Level_2()
{

}

void Level_2::Loading()
{
	// UI 
	CreateActor<PlayUI>((int)ORDER::UI, "PlayUI");

	// 렌더러로 이미지 추가 

	// 플레이어
	{
		Player* Kirby = CreateActor<Player>((int)ORDER::PLAYER);
		Kirby->SetPosition({ 5200.f, 200.f });
		Kirby->MapScale(5376.f, 768.f);
	}

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

}

void Level_2::LevelChangeStart()
{
	BgmPlayer = GameEngineSound::SoundPlayControl("Play1.mp3");
}

void Level_2::LevelChangeEnd()
{
	BgmPlayer.Stop();
}
