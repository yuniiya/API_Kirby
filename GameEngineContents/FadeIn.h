#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;
class FadeIn : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeIn();
	~FadeIn();

	// delete Function
	FadeIn(const FadeIn& _Other) = delete;
	FadeIn(FadeIn&& _Other) noexcept = delete;
	FadeIn& operator=(const FadeIn& _Other) = delete;
	FadeIn& operator=(FadeIn&& _Other) noexcept = delete;

protected:
	float Alpha_;

	bool FadeEnd_;

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* Renderer_;
};