#include "MapActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

MapActor::MapActor()
	: BackAnimationRenderer_(nullptr)
{

}
MapActor::~MapActor()
{

}

void MapActor::Start()
{
	SetPosition({ 0,0 });
	SetScale(GameEngineWindow::GetScale());

	BackAnimationRenderer_ = CreateRenderer();
	BackAnimationRenderer_->CreateFolderAnimation("BossLevel", "BossLevel", 0, 11, 0.017f, true);
	BackAnimationRenderer_->ChangeAnimation("BossLevel");
}

void MapActor::Update()
{
}


