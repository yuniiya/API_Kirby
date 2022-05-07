#include "PlayerHP.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
//#include "Player.h"

PlayerHP* PlayerHP::MainHP = nullptr;

PlayerHP::PlayerHP()
	: PlayerHPBar(nullptr)
{

}

PlayerHP::~PlayerHP()
{

}

void PlayerHP::Start()
{
	PlayerHPBar = CreateRenderer("Player_HPBar.bmp");
	PlayerHPBar->SetPivot({ 304.f,740.f });
	PlayerHPBar->CameraEffectOff();
}

void PlayerHP::Update()
{
}




