#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;

class Item : public GameEngineActor
{
public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

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