#include "Grass_2.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Grass_2::Grass_2()
	: AnimationRenderer_(nullptr)
{

}
Grass_2::~Grass_2()
{

}

void Grass_2::Start()
{
	GameEngineImage* Grass3 = GameEngineImageManager::GetInst()->Find("Grass2-1.bmp");
	Grass3->CutCount(1, 4);

	SetScale(GameEngineWindow::GetScale());

	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->CreateAnimation("Grass2-1.bmp", "Grass2-1", 0, 3, 0.25f, true);

	AnimationRenderer_->ChangeAnimation("Grass2-1");
}

void Grass_2::Update()
{
}
