#include "PlayerHP.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Player.h"

PlayerHP* PlayerHP::MainHP = nullptr;
GameEngineRenderer* PlayerHP::PlayerHPBar = nullptr;

PlayerHP::PlayerHP()
	: OriginalScale_(270.f)
{

}

PlayerHP::~PlayerHP()
{

}

void PlayerHP::SetHP(float _CurHP, float _MaxHP)
{
	float ratio = _CurHP / _MaxHP;

	if(_CurHP < 10.f)
	{
		return;
	}

	if (_CurHP > 100.f)
	{
		return;
	}

	PrevScale_ = PlayerHPBar->GetScale().x;
	PlayerHPBar->SetScale({ OriginalScale_ * ratio, PlayerHPBar->GetScale().y });
	PlayerHPBar->SetPivot({ PlayerHPBar->GetPivot().x - (PrevScale_ - PlayerHPBar->GetScale().x) / 2.f, PlayerHPBar->GetPivot().y });
}

void PlayerHP::Start()
{
	PlayerHPBar = CreateRenderer();
	PlayerHPBar->SetPivot({ 304.f,740.f });
	PlayerHPBar->CameraEffectOff();

	PlayerHPBar->SetImage("Player_HPBar.bmp");
	PlayerHPBar->SetScale({ PlayerHPBar->GetScale() });
}

void PlayerHP::Update()
{
}




