#include "Water.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>


Water::Water()
	: AnimationRenderer_(nullptr)
{

}
Water::~Water()
{
}

void Water::Start()
{
	GameEngineImage* Water1 = GameEngineImageManager::GetInst()->Find("Water3-1.bmp");
	Water1->CutCount(1, 4);


	SetScale(GameEngineWindow::GetScale());

	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->CreateAnimation("Water3-1.bmp", "Water3", 0, 3, 0.16f, true);
	AnimationRenderer_->ChangeAnimation("Water3");
}

void Water::Update()
{
}


