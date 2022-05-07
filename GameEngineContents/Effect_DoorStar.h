#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class Effect_DoorStar : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_DoorStar();
	~Effect_DoorStar();

	// delete Function
	Effect_DoorStar(const Effect_DoorStar& _Other) = delete;
	Effect_DoorStar(Effect_DoorStar&& _Other) noexcept = delete;
	Effect_DoorStar& operator=(const Effect_DoorStar& _Other) = delete;
	Effect_DoorStar& operator=(Effect_DoorStar&& _Other) noexcept = delete;

protected:
	std::string AnimationName_;

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;
};
