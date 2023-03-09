#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;

class Water_2 : public GameEngineActor
{
public:
	// constrcuter destructer
	Water_2();
	~Water_2();

	// delete Function
	Water_2(const Water_2& _Other) = delete;
	Water_2(Water_2&& _Other) noexcept = delete;
	Water_2& operator=(const Water_2& _Other) = delete;
	Water_2& operator=(Water_2&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;
};
