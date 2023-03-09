#include "Effect_BossStar.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "GameEngine/GameEngineCollision.h"
#include "Player.h"

Effect_BossStar::Effect_BossStar()
	: AnimationRenderer_(nullptr)
{

}
Effect_BossStar::~Effect_BossStar()
{

}

void Effect_BossStar::Start()
{
	AttackCollision_ = CreateCollision("BossStarCol", {70.f, 70.f});

	AnimationRenderer_ = CreateRenderer();
	AnimationRenderer_->SetPivotType(RenderPivot::BOT);
	AnimationRenderer_->SetPivot({ 0.f, 220.f });

	AnimationRenderer_->CreateAnimation("Default_Att_Right.bmp", "BossStar_", 23, 26, 0.1f, true);
	//AnimationRenderer_->CreateAnimation("Effect_BossStar.bmp", "BossStar_", 20, 26, 0.15f, true);
	//AnimationRenderer_->CreateAnimation("Effect.bmp", "DoorStar_", 6, 7, 0.8f, true);

	AnimationName_ = "BossStar_";

	Death(3.f);
}

void Effect_BossStar::Update()
{
	AnimationRenderer_->ChangeAnimation(AnimationName_);

	// 삼켜지고 있는 중이면 Death로 처리
	if (10.0f >= std::abs(GetPosition().x - Player::MainPlayer->GetPosition().x))
	{
		Death();
	}

	{
		std::vector<GameEngineCollision*> ColList;
		if (true == AttackCollision_->CollisionCheck("InhaleCol", CollisionType::Rect, CollisionType::Rect))
		{
			float4 PlayerPos = Player::MainPlayer->GetPosition();
			float4 Pos = GetPosition();

			// 플레이어가 몬스터 왼쪽에 있다
			if (PlayerPos.x < Pos.x)
			{
				MoveDir.x -= 3.f * GameEngineTime::GetDeltaTime();
			}
			else if (PlayerPos.x > Pos.x)
			{
				// 몬스터 오른쪽에 있다
				MoveDir.x += 3.f * GameEngineTime::GetDeltaTime();
			}

			SetMove(MoveDir);

		}
	}

}
