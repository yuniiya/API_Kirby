#include "TitleLevel.h"
#include "TitleLogo.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSound.h>

#include "BackGround.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "PlayUI.h"

TitleLevel::TitleLevel()
{

}
TitleLevel::~TitleLevel()
{

}

void TitleLevel::Loading()
{
	// 백그라운드 엑터
	{
		BackGround* CurBack = CreateActor<BackGround>((int)ORDER::BACKGROUND, "Title_Back");
		CurBack->GetRenderer()->SetImage("Title_Back.bmp");

		float4 BackActor = {};
		BackActor.x = (CurBack->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (CurBack->GetRenderer()->GetImage()->GetScale().Half().y);

		CurBack->GetRenderer()->SetPivot(BackActor);
	}

	// 스테이지
	{
		Stage* CurStage = CreateActor<Stage>((int)ORDER::STAGE);
		CurStage->GetRenderer()->SetImage("Title_Stage.bmp");

		float4 StageActor = {};
		StageActor.x = (CurStage->GetRenderer()->GetImage()->GetScale().Half().x);
		StageActor.y = (CurStage->GetRenderer()->GetImage()->GetScale().Half().y);

		CurStage->GetRenderer()->SetPivot(StageActor);
	}
	
	{
		// map에 insert와 find를 동시에 
		// 배경이 로고보다 먼저 그려지기 때문에 배경 = 0
		TitleLogo* Title = CreateActor<TitleLogo>((int)ORDER::UI, "TitleLogo");
		Title->GetRenderer()->SetImage("TitleLogo.bmp");

		float4 TitleActor = {};
		TitleActor.x = (Title->GetRenderer()->GetImage()->GetScale().Half().x);
		TitleActor.y = (Title->GetRenderer()->GetImage()->GetScale().Half().y);

		Title->GetRenderer()->SetPivot(TitleActor);


		TitleLogo* TitleBot = CreateActor<TitleLogo>((int)ORDER::UI, "TitleBot");
		TitleBot->GetRenderer()->SetImage("TitleLogo_Bot.bmp");
		TitleBot->GetRenderer()->SetPivot({512, 690});
	}



	//{
	//	Player* Kirby = CreateActor<Player>((int)ORDER::PLAYER);
	//	Kirby->SetPosition({ 100.f, 100.f });
	//	Kirby->MapScale(1024.f, 768.f);
	//}
	
}

void TitleLevel::Update()
{
	// 레벨 체인지 
	if (true == GameEngineInput::GetInst()->IsDown("NextLevel"))
	{
		GameEngine::GetInst().ChangeLevel("Level_1");
	}

	if (true == GameEngineInput::GetInst()->IsDown("Level_1"))
	{
		GameEngine::GetInst().ChangeLevel("Level_1");
	}

	if (true == GameEngineInput::GetInst()->IsDown("Level_2"))
	{
		GameEngine::GetInst().ChangeLevel("Level_2");
	}

	if (true == GameEngineInput::GetInst()->IsDown("Level_3"))
	{
		GameEngine::GetInst().ChangeLevel("Level_3");
	}

	if (true == GameEngineInput::GetInst()->IsDown("Level_4"))
	{
		GameEngine::GetInst().ChangeLevel("Level_4");
	}

	if (true == GameEngineInput::GetInst()->IsDown("BossRoomLevel"))
	{
		GameEngine::GetInst().ChangeLevel("BossRoomLevel");
	}

	if (true == GameEngineInput::GetInst()->IsDown("BossLevel"))
	{
		GameEngine::GetInst().ChangeLevel("BossLevel");
	}

	if (true == GameEngineInput::GetInst()->IsDown("EndingLevel"))
	{
		GameEngine::GetInst().ChangeLevel("EndingLevel");
	}
}

void TitleLevel::LevelChangeStart()
{
	BgmPlayer = GameEngineSound::SoundPlayControl("TitleBGM.mp3");
}

void TitleLevel::LevelChangeEnd()
{
	BgmPlayer.Stop();
}


