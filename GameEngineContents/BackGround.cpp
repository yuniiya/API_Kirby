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

	// ���� �̹����� ���������� �� �� �����ϱ� ����д� �� �׶��� �ʿ��� ������ ���
	Image_ = CreateRenderer();
	Image_->CameraEffectOff();

}

void BackGround::Render()
{
}


