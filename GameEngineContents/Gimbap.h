#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;

class Gimbap : public GameEngineActor
{
public:
	// constrcuter destructer
	Gimbap();
	~Gimbap();

	// delete Function
	Gimbap(const Gimbap& _Other) = delete;
	Gimbap(Gimbap&& _Other) noexcept = delete;
	Gimbap& operator=(const Gimbap& _Other) = delete;
	Gimbap& operator=(Gimbap&& _Other) noexcept = delete;

public:
	GameEngineRenderer* GetRenderer()
	{
		return Image_;
	}

	bool IsSound;

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* Image_;

	GameEngineCollision* Collision_;
};