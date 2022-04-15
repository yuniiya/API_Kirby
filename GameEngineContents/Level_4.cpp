#include "Level_4.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "BackGround.h"
#include "Stage.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "PlayUI.h"

Level_4::Level_4()
{

}
Level_4::~Level_4()
{

}

void Level_4::Loading()
{
	// UI 
	CreateActor<PlayUI>((int)ORDER::UI, "PlayUI");


	// 플레이어 엑터
	{
		Player* Kirby = CreateActor<Player>((int)ORDER::PLAYER, "Player");
		Kirby->SetPosition({ 2900.f, 200.f });
		Kirby->MapScale(3073.f, 768.f);
	}
	

	

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
		Stage* CurStage = CreateActor<Stage>((int)ORDER::STAGE, "Stage");
		CurStage->GetRenderer()->SetImage("Level4.bmp");


		float4 StageActor = {};
		StageActor.x = (CurStage->GetRenderer()->GetImage()->GetScale().Half().x);
		StageActor.y = (CurStage->GetRenderer()->GetImage()->GetScale().Half().y);

		CurStage->GetRenderer()->SetPivot(StageActor);
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
}

void Level_4::LevelChangeStart()
{
	BgmPlayer = GameEngineSound::SoundPlayControl("Play2.mp3");
}

void Level_4::LevelChangeEnd()
{
	BgmPlayer.Stop();
}
