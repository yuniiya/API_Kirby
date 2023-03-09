#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;

class Grass_1 : public GameEngineActor
{
public:
	// constrcuter destructer
	Grass_1();
	~Grass_1();

	// delete Function
	Grass_1(const Grass_1& _Other) = delete;
	Grass_1(Grass_1&& _Other) noexcept = delete;
	Grass_1& operator=(const Grass_1& _Other) = delete;
	Grass_1& operator=(Grass_1&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;

};
