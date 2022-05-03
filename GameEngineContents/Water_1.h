#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;

class Water_1 : public GameEngineActor
{
public:
	// constrcuter destructer
	Water_1();
	~Water_1();

	// delete Function
	Water_1(const Water_1& _Other) = delete;
	Water_1(Water_1&& _Other) noexcept = delete;
	Water_1& operator=(const Water_1& _Other) = delete;
	Water_1& operator=(Water_1&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;
};
