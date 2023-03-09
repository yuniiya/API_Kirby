#include "Water_2.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Water_2::Water_2()
{

}
Water_2::~Water_2()
{

}

void Water_2::Start()
{
	GameEngineImage* Water3 = GameEngineImageManager::GetInst()->Find("Water4-2.bmp");
	Water3->CutCount(1, 4);

	SetScale(GameEngineWindow::GetScale());

	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->CreateAnimation("Water4-2.bmp", "Water4-2", 0, 3, 0.16f, true);

	AnimationRenderer_->ChangeAnimation("Water4-2");
}

void Water_2::Update()
{
}

