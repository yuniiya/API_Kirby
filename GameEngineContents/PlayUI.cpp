#include "PlayUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Player.h"

PlayUI* PlayUI::MainUI = nullptr;

PlayUI::PlayUI()
{

}
PlayUI::~PlayUI()
{

}

void PlayUI::Start()
{
	//// 액터를 화면 중간에 놓는다.
	//{
	//	float4 Pos = GameEngineWindow::GetScale().Half();
	//	SetPosition(Pos);
	//}


	GameEngineRenderer* PlayerHP = CreateRenderer("Player_HP_Null.bmp");
	PlayerHP->SetPivot({ 305.f,740.f });
	PlayerHP->CameraEffectOff();

	//GameEngineRenderer* PlayerHPBar = CreateRenderer("Player_HPBar.bmp");
	//PlayerHPBar->SetPivot({ 304.f,740.f });
	//PlayerHPBar->CameraEffectOff();
	//PlayerHPBar->SetPivot({294.f, 740.f});
	//PlayerHPBar->SetScale({ 250.f, 30.f });

	GameEngineRenderer* LifeUI = CreateRenderer("LifeUI.bmp");
	LifeUI->SetPivot({ 257.f,686.f });
	LifeUI->CameraEffectOff();

	GameEngineRenderer* SkillUI = CreateRenderer("Skill_Normal.bmp");
	SkillUI->SetPivot({ 70.f,740.f });
	SkillUI->CameraEffectOff();
	
	//GameEngineRenderer* MonsterHP = CreateRenderer(".bmp");
}

void PlayUI::Update()
{

}



