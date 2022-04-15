#include "TitleLogo.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>


TitleLogo::TitleLogo()
{

}
TitleLogo::~TitleLogo()
{

}

void TitleLogo::Start()
{
	// 중앙에 위치
	SetPosition({ 0,0 });
	SetScale(GameEngineWindow::GetScale());

	Image_ = CreateRenderer();
	Image_->CameraEffectOff();

	// 1. Nintendo 2. Hal_Inc Logo 3. Title 4. 하단 Hal_Inc Logo
}

void TitleLogo::Render()
{
	//DebugRectRender();
}
