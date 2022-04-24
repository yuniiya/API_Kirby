#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;

class Grass : public GameEngineActor
{
public:
	// constrcuter destructer
	Grass();
	~Grass();

	// delete Function
	Grass(const Grass& _Other) = delete;
	Grass(Grass&& _Other) noexcept = delete;
	Grass& operator=(const Grass& _Other) = delete;
	Grass& operator=(Grass&& _Other) noexcept = delete;

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
