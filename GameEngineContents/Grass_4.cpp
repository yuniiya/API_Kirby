#include "Grass_4.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Grass_4::Grass_4()
	: AnimationRenderer_(nullptr)
{

}
Grass_4::~Grass_4()
{

}

void Grass_4::Start()
{
	GameEngineImage* Grass3 = GameEngineImageManager::GetInst()->Find("Grass2-3.bmp");
	Grass3->CutCount(1, 4);

	SetScale(GameEngineWindow::GetScale());

	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->CreateAnimation("Grass2-3.bmp", "Grass2-3", 0, 3, 0.25f, true);

	AnimationRenderer_->ChangeAnimation("Grass2-3");
}

void Grass_4::Update()
{
}

