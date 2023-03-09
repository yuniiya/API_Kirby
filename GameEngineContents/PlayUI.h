#pragma once
#include <GameEngine/GameEngineActor.h>

class PlayUI : public GameEngineActor
{
public:
	static PlayUI* MainUI;

	// constrcuter destructer
	PlayUI();
	~PlayUI();

	// delete Function
	PlayUI(const PlayUI& _Other) = delete;
	PlayUI(PlayUI&& _Other) noexcept = delete;
	PlayUI& operator=(const PlayUI& _Other) = delete;
	PlayUI& operator=(PlayUI&& _Other) noexcept = delete;

	//GameEngineRenderer* GetRenderer()
	//{
	//	return Image_;
	//}

protected:
	void Start() override;
	void Update() override;

private:
	//GameEngineRenderer* Image_;
};
