#include "MonsterHP.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

MonsterHP::MonsterHP()
	: MonsterHPBar(nullptr)
{

}
MonsterHP::~MonsterHP()
{

}

void MonsterHP::Start()
{
	MonsterHPBar = CreateRenderer("Monster_HPBar.bmp");
	MonsterHPBar->SetPivot({ 780.f,740.f });
	MonsterHPBar->CameraEffectOff();
}

void MonsterHP::Update()
{
}


