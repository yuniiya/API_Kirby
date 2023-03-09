#include "SkillName.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

SkillName::SkillName()
	: Renderer(nullptr)
{

}
SkillName::~SkillName()
{

}

void SkillName::Start()
{
	SetPosition({ 70.f, 740.f });
	SetScale(GameEngineWindow::GetScale());

	Renderer = CreateRenderer();
	Renderer->CameraEffectOff();
}

void SkillName::Update()
{

}
