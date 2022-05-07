#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class Effect_BossStar : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_BossStar();
	~Effect_BossStar();

	// delete Function
	Effect_BossStar(const Effect_BossStar& _Other) = delete;
	Effect_BossStar(Effect_BossStar&& _Other) noexcept = delete;
	Effect_BossStar& operator=(const Effect_BossStar& _Other) = delete;
	Effect_BossStar& operator=(Effect_BossStar&& _Other) noexcept = delete;

protected:
	std::string AnimationName_;

	GameEngineCollision* AttackCollision_;

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;
};
