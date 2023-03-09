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
	// �߾ӿ� ��ġ
	SetPosition({ 0,0 });
	SetScale(GameEngineWindow::GetScale());

	Image_ = CreateRenderer();
	Image_->CameraEffectOff();

	// 1. Nintendo 2. Hal_Inc Logo 3. Title 4. �ϴ� Hal_Inc Logo
}

void TitleLogo::Render()
{
	//DebugRectRender();
}
