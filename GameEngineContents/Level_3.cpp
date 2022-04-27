#include "Level_3.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "BackGround.h"
#include "Stage.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "PlayUI.h"

Level_3::Level_3()
{

}
Level_3::~Level_3()
{

}

void Level_3::Loading()
{
	// UI 
	//CreateActor<PlayUI>((int)ORDER::UI, "PlayUI");


	//{
	//	// 플레이어 엑터
	//	Player* Kirby = CreateActor<Player>((int)ORDER::PLAYER);
	//	Kirby->SetPosition({ 100.f, 490.f });
	//	Kirby->MapScale(5960.f, 768.f);

	//}

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
		Stage* CurStage = CreateActor<Stage>((int)ORDER::STAGE);
		CurStage->GetRenderer()->SetImage("Level3.bmp");


		float4 StageActor = {};
		StageActor.x = (CurStage->GetRenderer()->GetImage()->GetScale().Half().x);
		StageActor.y = (CurStage->GetRenderer()->GetImage()->GetScale().Half().y);

		CurStage->GetRenderer()->SetPivot(StageActor);
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
	Player::MainPlayer->SetPosition({ 100.f, 490.f });
	Player::MainPlayer->MapScale(5960.f, 768.f);
}

void Level_3::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		PlayUI::MainUI->NextLevelOn();
	}
}
