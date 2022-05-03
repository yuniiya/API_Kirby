#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;

class Grass_4 : public GameEngineActor
{
public:
	// constrcuter destructer
	Grass_4();
	~Grass_4();

	// delete Function
	Grass_4(const Grass_4& _Other) = delete;
	Grass_4(Grass_4&& _Other) noexcept = delete;
	Grass_4& operator=(const Grass_4& _Other) = delete;
	Grass_4& operator=(Grass_4&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;

};