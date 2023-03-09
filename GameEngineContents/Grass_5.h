#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;

class Grass_5 : public GameEngineActor
{
public:
	// constrcuter destructer
	Grass_5();
	~Grass_5();

	// delete Function
	Grass_5(const Grass_5& _Other) = delete;
	Grass_5(Grass_5&& _Other) noexcept = delete;
	Grass_5& operator=(const Grass_5& _Other) = delete;
	Grass_5& operator=(Grass_5&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;

};