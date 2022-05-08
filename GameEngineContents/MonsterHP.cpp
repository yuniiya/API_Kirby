#include "MonsterHP.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Kingdedede.h"

MonsterHP* MonsterHP::MainBossHP = nullptr;
GameEngineRenderer* MonsterHP::MonsterHPBar = nullptr;


MonsterHP::MonsterHP()
	//: MonsterHPBar(nullptr)
{

}
MonsterHP::~MonsterHP()
{

}

void MonsterHP::SetHP(float _CurHP, float _MaxHP)
{
	float ratio = _CurHP / _MaxHP;

	MonsterHPBar->SetScale({ 211.f * ratio, MonsterHPBar->GetScale().y });
	
	if (ratio == 0.8f)
	{
		MonsterHPBar->SetPivot({ 759.f, 740.f });
	}
	else if (ratio == 0.6f)
	{
		MonsterHPBar->SetPivot({ 738.f, 740.f });
	}
	else if (ratio == 0.4f)
	{
		MonsterHPBar->SetPivot({ 717.f, 740.f });
	}
	else if (ratio == 0.2f)
	{
		MonsterHPBar->SetPivot({ 696.f, 740.f });
	}	


	//MainBossHP->GetRenderer()->SetScale({ MonsterHPBar->GetScale().x * 0.8f, MonsterHPBar->GetScale().y });

}

void MonsterHP::Start()
{
	MonsterHPBar = CreateRenderer();
	MonsterHPBar->SetPivot({ 780.f,740.f });
	MonsterHPBar->CameraEffectOff();

	MonsterHPBar->SetImage("Monster_HPBar.bmp");
	MonsterHPBar->SetScale({ MonsterHPBar->GetScale()});

	//MainBossHP->CreateRenderer();
	//MainBossHP->GetRenderer()->SetImage("Monster_HPBar.bmp");
	//MainBossHP->GetRenderer()->SetPivot({ 780.f, 740.f });
	//MonsterHPBar->CameraEffectOff();

	//MonsterHPBar->SetImage("Monster_HPBar.bmp");
}

void MonsterHP::Update()
{
	MainBossHP = this;
}

