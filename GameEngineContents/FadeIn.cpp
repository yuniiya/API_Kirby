#include "FadeIn.h"

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "GameEngine//GameEngineImage.h"


FadeIn::FadeIn()
	: Renderer_(nullptr)
	, Alpha_(255)
	, FadeEnd_(false)
{

}
FadeIn::~FadeIn()
{

}

void FadeIn::Start()
{
	SetPosition({ 0,0 });
	SetScale(GameEngineWindow::GetScale());

	Renderer_ = CreateRenderer();
	//Renderer_->SetImage("FadeOut2.bmp");
	Renderer_->SetImage("Fade.bmp");

	float4 Actor = {};
	Actor.x = (Renderer_->GetImage()->GetScale().Half().x);
	Actor.y = (Renderer_->GetImage()->GetScale().Half().y - 8.f);

	Renderer_->SetPivot(Actor);

	// 처음에는 완전히 흰색
	Renderer_->SetAlpha(255);
}

void FadeIn::Update()
{
	// 서서히 알파값을 줄여준다 -> 페이드인 
	Alpha_ -= 35.f * (GameEngineTime::GetDeltaTime() * 20);
	Renderer_->SetAlpha(static_cast<unsigned int>(Alpha_));

	if (Alpha_ <= 0)
	{
		FadeEnd_ = true;
		Renderer_->SetAlpha(0);
	}

}