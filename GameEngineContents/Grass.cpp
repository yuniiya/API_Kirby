#include "Grass.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Grass::Grass()
	: AnimationRenderer_(nullptr)
{

}
Grass::~Grass()
{

}

void Grass::Start()
{

	GameEngineImage* Grass1 = GameEngineImageManager::GetInst()->Find("Grass1-1.bmp");
	Grass1->CutCount(1, 4);
	//GameEngineImage* Grass2 = GameEngineImageManager::GetInst()->Find("Grass1-2.bmp");
	//Grass2->CutCount(1, 4);
	//GameEngineImage* Grass3 = GameEngineImageManager::GetInst()->Find("Grass2-1.bmp");
	//Grass3->CutCount(1, 4);
	//GameEngineImage* Grass4 = GameEngineImageManager::GetInst()->Find("Grass2-2.bmp");
	//Grass4->CutCount(1, 4);
	//GameEngineImage* Grass5 = GameEngineImageManager::GetInst()->Find("Grass2-3.bmp");
	//Grass5->CutCount(1, 4);
	//GameEngineImage* Grass6 = GameEngineImageManager::GetInst()->Find("Grass2-4.bmp");
	//Grass6->CutCount(1, 4);


	SetScale(GameEngineWindow::GetScale());

	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->CreateAnimation("Grass1-1.bmp", "Grass1", 0, 3, 0.25f, true);

	AnimationRenderer_->ChangeAnimation("Grass1");
}

void Grass::Update()
{
}


