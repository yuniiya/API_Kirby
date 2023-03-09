#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;

class Grass_3 : public GameEngineActor
{
public:
	// constrcuter destructer
	Grass_3();
	~Grass_3();

	// delete Function
	Grass_3(const Grass_3& _Other) = delete;
	Grass_3(Grass_3&& _Other) noexcept = delete;
	Grass_3& operator=(const Grass_3& _Other) = delete;
	Grass_3& operator=(Grass_3&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;

};