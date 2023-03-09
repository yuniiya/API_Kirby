#include "BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

BackGround::BackGround()
	: Image_(nullptr)
{

}
BackGround::~BackGround()
{

}

void BackGround::Start()
{
	SetPosition({ 0,0 });
	SetScale(GameEngineWindow::GetScale());

	// 무슨 이미지를 렌더링할지 알 수 없으니까 비워둔다 백 그라운드 필요한 곳에서 사용
	Image_ = CreateRenderer();
	Image_->CameraEffectOff();

}

void BackGround::Render()
{
}


