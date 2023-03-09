#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;

class Grass_2 : public GameEngineActor
{
public:
	// constrcuter destructer
	Grass_2();
	~Grass_2();

	// delete Function
	Grass_2(const Grass_2& _Other) = delete;
	Grass_2(Grass_2&& _Other) noexcept = delete;
	Grass_2& operator=(const Grass_2& _Other) = delete;
	Grass_2& operator=(Grass_2&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;

};

