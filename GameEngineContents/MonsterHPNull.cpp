#include "MonsterHPNull.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

MonsterHPNull::MonsterHPNull()
	: MonsterHPBar(nullptr)
{

}
MonsterHPNull::~MonsterHPNull()
{

}

void MonsterHPNull::Start()
{
	MonsterHPBar = CreateRenderer("Monster_HP_Null.bmp");
	MonsterHPBar->SetPivot({ 780.f,740.f });
	MonsterHPBar->CameraEffectOff();
}

void MonsterHPNull::Update()
{
}




