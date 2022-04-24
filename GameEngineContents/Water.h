#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;

class Water : public GameEngineActor
{
public:
	// constrcuter destructer
	Water();
	~Water();

	// delete Function
	Water(const Water& _Other) = delete;
	Water(Water&& _Other) noexcept = delete;
	Water& operator=(const Water& _Other) = delete;
	Water& operator=(Water&& _Other) noexcept = delete;

	GameEngineRenderer* GetRenderer()
	{
		return AnimationRenderer_;
	};

protected:

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;
};
