#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineImage;
class GameEngineCollision;
class MapActor : public GameEngineActor
{
public:
	// constrcuter destructer
	MapActor();
	~MapActor();

	// delete Function
	MapActor(const MapActor& _Other) = delete;
	MapActor(MapActor&& _Other) noexcept = delete;
	MapActor& operator=(const MapActor& _Other) = delete;
	MapActor& operator=(MapActor&& _Other) noexcept = delete;

	GameEngineRenderer* GetRenderer()
	{
		return BackAnimationRenderer_;
	};

protected:

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* BackAnimationRenderer_;
};
