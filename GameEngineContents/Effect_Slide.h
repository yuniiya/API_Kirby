#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;

class Effect_Slide : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_Slide();
	~Effect_Slide();

	// delete Function
	Effect_Slide(const Effect_Slide& _Other) = delete;
	Effect_Slide(Effect_Slide&& _Other) noexcept = delete;
	Effect_Slide& operator=(const Effect_Slide& _Other) = delete;
	Effect_Slide& operator=(Effect_Slide&& _Other) noexcept = delete;

public:


protected:
	void DirAnimationCheck();

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;

};