#include "Fade.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "GameEngine//GameEngineImage.h"


Fade::Fade()
	: Renderer_(nullptr)
	, Alpha_(0)
	, FadeEnd_(false)
{

}
Fade::~Fade()
{

}

void Fade::Start()
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

	// 처음에는 완전히 투명
	Renderer_->SetAlpha(0);
}

void Fade::Update()
{
	// 서서히 알파값을 올려준다 -> 페이드 아웃
	Alpha_ += 35.f * (GameEngineTime::GetDeltaTime() * 20);
	Renderer_->SetAlpha(static_cast<unsigned int>(Alpha_));

	if (Alpha_ > 255)
	{
		FadeEnd_ = true;
		Renderer_->SetAlpha(0);
	}

}
