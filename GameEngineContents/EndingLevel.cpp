#include "EndingLevel.h"
#include "Player.h"
#include "PlayUI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "BackGround.h"
#include "ContentsEnum.h"

EndingLevel::EndingLevel()
{

}
EndingLevel::~EndingLevel()
{

}

void EndingLevel::Loading()
{
	// UI 
	//CreateActor<PlayUI>((int)ORDER::UI, "PlayUI");


	//// 플레이어 엑터
	//Player* Kirby = CreateActor<Player>((int)ORDER::PLAYER);
	//Kirby->SetPosition({ 100.f, 500.f });
	//Kirby->MapScale(1024.f, 768.f);

	// 백그라운드 엑터
	{
		BackGround* CurBack = CreateActor<BackGround>(0);
		CurBack->GetRenderer()->SetImage("EndingLevel.bmp");

		float4 BackActor = {};
		BackActor.x = (CurBack->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (CurBack->GetRenderer()->GetImage()->GetScale().Half().y);

		CurBack->GetRenderer()->SetPivot(BackActor);
	}
}

void EndingLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("TitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}
}

void EndingLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer->SetPosition({ 100.f, 500.f });
	Player::MainPlayer->MapScale(1024.f, 768.f);


	GameEngineSound::SoundPlayOneShot("Ending.mp3");
}

void EndingLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		PlayUI::MainUI->NextLevelOn();
	}
}


