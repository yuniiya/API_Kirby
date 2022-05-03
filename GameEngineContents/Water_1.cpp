#include "Water_1.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Water_1::Water_1() 
	: AnimationRenderer_(nullptr)
{

}
Water_1::~Water_1()
{

}

void Water_1::Start()
{
	GameEngineImage* Water2 = GameEngineImageManager::GetInst()->Find("Water4-1.bmp");
	Water2->CutCount(1, 4);

	SetScale(GameEngineWindow::GetScale());

	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->CreateAnimation("Water4-1.bmp", "Water4-1", 0, 3, 0.14f, true);

	AnimationRenderer_->ChangeAnimation("Water4-1");
}

void Water_1::Update()
{
}

