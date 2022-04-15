#include "Stage.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>


Stage::Stage()
	: Image_(nullptr)
{

}
Stage::~Stage()
{

}

void Stage::Start()
{
	SetPosition({0, 0});
	SetScale(GameEngineWindow::GetScale());

	Image_ = CreateRenderer();
}

void Stage::Render()
{
}


