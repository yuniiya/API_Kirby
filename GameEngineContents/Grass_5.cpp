#include "Grass_5.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Grass_5::Grass_5()
	: AnimationRenderer_(nullptr)
{

}
Grass_5::~Grass_5()
{

}

void Grass_5::Start()
{
	GameEngineImage* Grass3 = GameEngineImageManager::GetInst()->Find("Grass2-4.bmp");
	Grass3->CutCount(1, 4);

	SetScale(GameEngineWindow::GetScale());

	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->CreateAnimation("Grass2-4.bmp", "Grass2-4", 0, 3, 0.25f, true);

	AnimationRenderer_->ChangeAnimation("Grass2-4");
}

void Grass_5::Update()
{
}

