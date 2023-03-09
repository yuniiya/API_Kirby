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

	// 1. ���� �������� / ū �������� 
	// 2. ü�� �丶�� �ﰢ��� Ǫ��
	// 3. ����Ʈ����
	//SetPosition({ 0,0 });
	SetScale(GameEngineWindow::GetScale());

	// ���� �̹����� ���������� �� �� �����ϱ� ����д� �� �׶��� �ʿ��� ������ ���
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
		GameEngineSound::SoundPlayOneShot("Item2.wav");
	}

}



