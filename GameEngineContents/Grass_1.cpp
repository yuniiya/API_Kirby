#include "Grass_1.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Grass_1::Grass_1()
{

}
Grass_1::~Grass_1()
{

}

void Grass_1::Start()
{
	GameEngineImage* Grass2 = GameEngineImageManager::GetInst()->Find("Grass1-2.bmp");
	Grass2->CutCount(1, 4);

	SetScale(GameEngineWindow::GetScale());

	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->CreateAnimation("Grass1-2.bmp", "Grass1-2", 0, 3, 0.25f, true);

	AnimationRenderer_->ChangeAnimation("Grass1-2");
}

void Grass_1::Update()
{
}
