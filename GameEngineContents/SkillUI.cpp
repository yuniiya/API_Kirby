#include "SkillUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

SkillUI* SkillUI::MainSkillUI = nullptr;

SkillUI::SkillUI()
	: Renderer(nullptr)
{

}
SkillUI::~SkillUI()
{

}

void SkillUI::Start()
{
	SetPosition({ 67.f, 669.f });
	SetScale(GameEngineWindow::GetScale());

	Renderer = CreateRenderer();
	Renderer->CameraEffectOff();
}

void SkillUI::Update()
{

}