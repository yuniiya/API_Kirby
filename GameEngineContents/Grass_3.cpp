#include "Grass_3.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Grass_3::Grass_3()
	: AnimationRenderer_(nullptr)
{

}
Grass_3::~Grass_3()
{

}

void Grass_3::Start()
{
	GameEngineImage* Grass3 = GameEngineImageManager::GetInst()->Find("Grass2-2.bmp");
	Grass3->CutCount(1, 4);

	SetScale(GameEngineWindow::GetScale());

	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->CreateAnimation("Grass2-2.bmp", "Grass2-2", 0, 3, 0.25f, true);

	AnimationRenderer_->ChangeAnimation("Grass2-2");
}

void Grass_3::Update()
{
}


