#include "PlayerHP.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Player.h"

PlayerHP* PlayerHP::MainHP = nullptr;
GameEngineRenderer* PlayerHP::PlayerHPBar = nullptr;

PlayerHP::PlayerHP()
{

}

PlayerHP::~PlayerHP()
{

}

void PlayerHP::SetHP(float _CurHP, float _MaxHP)
{
	float ratio = _CurHP / _MaxHP;

	if(_CurHP == 10.f)
	{
		return;
	}

	if (_CurHP == 100.f)
	{
		return;
	}

	PlayerHPBar->SetScale({ 270.f * ratio, PlayerHPBar->GetScale().y });

	if (ratio == 0.9f)
	{
		PlayerHPBar->SetPivot({ 291.f, 740.f });
	}
	else if (ratio == 0.8f)
	{
		PlayerHPBar->SetPivot({ 277.f, 740.f });
	}
	else if (ratio == 0.7f)
	{
		PlayerHPBar->SetPivot({ 264.f, 740.f });
	}  
	else if (ratio == 0.6f)
	{
		PlayerHPBar->SetPivot({ 250.f, 740.f });
	}
	else if (ratio == 0.5f)
	{
		PlayerHPBar->SetPivot({ 237.f, 740.f });
	}
	else if (_CurHP == 40.f)
	{
		PlayerHPBar->SetPivot({ 223.f, 740.f });
	}
	else if (_CurHP == 30.f)
	{
		PlayerHPBar->SetPivot({ 210.f, 740.f });
	}
	else if (_CurHP == 20.f)
	{
		PlayerHPBar->SetPivot({ 196.f, 740.f });
	}



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




