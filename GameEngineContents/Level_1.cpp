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
#include "Grass.h"
#include "Monster.h"
#include "WaddleDee.h"

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

		// UI 
		PlayUI::MainUI = CreateActor<PlayUI>((int)ORDER::UI, "PlayUI");
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


	// 스테이지
	{
		Stage* CurStage = CreateActor<Stage>((int)ORDER::STAGE);
		CurStage->GetRenderer()->SetImage("Level1.bmp");

		float4 StageActor = {};
		StageActor.x = (CurStage->GetRenderer()->GetImage()->GetScale().Half().x);
		StageActor.y = (CurStage->GetRenderer()->GetImage()->GetScale().Half().y);

		CurStage->GetRenderer()->SetPivot(StageActor);

		// 장애물 콜리전
		//CurStage->CreateCollision("Wall", { 100, 100 }, { 300, 200 });
	}

	// Grass 
	{
		Grass* Grass1 = CreateActor<Grass>((int)ORDER::STAGEACTOR, "Grass1");
		Grass1->SetPosition({ 780.f, 520.f });

		Grass* Grass2 = CreateActor<Grass>((int)ORDER::STAGEACTOR, "Grass2");
		Grass2->SetPosition({ 4858.f, 461.f });


		GameEngineImage* GrassImage = GameEngineImageManager::GetInst()->Find("Grass1-2.bmp");
		GrassImage->CutCount(1, 4);
		Grass* Grass3 = CreateActor<Grass>((int)ORDER::STAGEACTOR, "Grass2");
		GameEngineRenderer* Renderer = Grass3->CreateRenderer("Grass1-2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, {3062.f, 295.f});
		Renderer->CreateAnimation("Grass1-2.bmp", "Grass2", 0, 3, 0.25f, true);
		Renderer->ChangeAnimation("Grass2");

	}

	// 몬스터
	WaddleDee* Waddle = CreateActor<WaddleDee>((int)ORDER::MONSTER, "WaddleDee");

	Waddle->SetPosition({ 500.f,500.f });


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
	//BgmPlayer = GameEngineSound::SoundPlayControl("Play1.mp3");

	Player::MainPlayer->SetPosition({ 100.f, 520.f });
	//Player::MainPlayer->SetPosition({ 1800.f, 420.f });
	//Player::MainPlayer->SetPosition({ 5300.f, 450.f });
	//Player::MainPlayer->SetPosition({ 2600.f, 200.f });
	Player::MainPlayer->MapScale(5753.f, 760.f);
}

void Level_1::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	//BgmPlayer.Stop();

	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		PlayUI::MainUI->NextLevelOn();
	}
}
