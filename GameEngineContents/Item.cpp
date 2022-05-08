#include "Item.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "GameEngine//GameEngineCollision.h"
#include "GameEngineBase//GameEngineSound.h"
//#include "Player.h"

Item::Item()
	: Image_(nullptr)
	, IsSound(false)
{

}
Item::~Item()
{

}

void Item::Start()
{
	Collision_ = CreateCollision("Item1", { 50.f, 50.f });

	// 1. 작은 보물상자 / 큰 보물상자 
	// 2. 체리 토마토 삼각김밥 푸딩
	// 3. 보스트로피
	//SetPosition({ 0,0 });
	SetScale(GameEngineWindow::GetScale());

	// 무슨 이미지를 렌더링할지 알 수 없으니까 비워둔다 백 그라운드 필요한 곳에서 사용
	Image_ = CreateRenderer();
	Image_->CameraEffectOff();
}

void Item::Update()
{
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == Collision_->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			IsSound = true;
		}
	}

	if (true == IsSound)
	{
		GameEngineSound::SoundPlayOneShot("Item1.wav");
	}

}



