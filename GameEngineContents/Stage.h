#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class Stage : public GameEngineActor
{
public:
	// constrcuter destructer
	Stage();
	~Stage();

	// delete Function
	Stage(const Stage& _Other) = delete;
	Stage(Stage&& _Other) noexcept = delete;
	Stage& operator=(const Stage& _Other) = delete;
	Stage& operator=(Stage&& _Other) noexcept = delete;

	GameEngineRenderer* GetRenderer()
	{
		return Image_;
	};

	
protected:
	void Start() override;
	void Render() override;

private:
	GameEngineRenderer* Image_;
};
