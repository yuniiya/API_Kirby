#include "Bullet.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Bullet::Bullet()
	: Time()
{

}
Bullet::~Bullet()
{

}

void Bullet::Start()
{
	//CreateRendererToScale("BulletStar.bmp", GetScale(), RenderPivot::CENTER, float4(0.0f, 100.0f));

	//GameEngineRenderer* Bullet = CreateRenderer("BulletStar.bmp");
	//Bullet->SetTransColor(RGB(207, 176, 255));
	//Bullet->SetIndex(0);

	GameEngineRenderer* Bullet = CreateRenderer();
	Bullet->SetTransColor(RGB(207, 176, 255));

	Bullet->CreateAnimation("BulletStar.bmp", "Bullet", 0, 4, 0.1f, true);
	Bullet->ChangeAnimation("Bullet");


	Death(1.0f);
}

void Bullet::Update()
{

	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 500.0f);
}
