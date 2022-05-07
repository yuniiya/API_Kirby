#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;
class Fade : public GameEngineActor
{
public:
	// constrcuter destructer
	Fade();
	~Fade();

	// delete Function
	Fade(const Fade& _Other) = delete;
	Fade(Fade&& _Other) noexcept = delete;
	Fade& operator=(const Fade& _Other) = delete;
	Fade& operator=(Fade&& _Other) noexcept = delete;

protected:
	float Alpha_;

	bool FadeEnd_;

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* Renderer_;
};