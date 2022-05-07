#pragma once
#include <GameEngine/GameEngineActor.h>

class SkillUI : public GameEngineActor
{
public:
	static SkillUI* MainSkillUI;

	// constrcuter destructer
	SkillUI();
	~SkillUI();

	// delete Function
	SkillUI(const SkillUI& _Other) = delete;
	SkillUI(SkillUI&& _Other) noexcept = delete;
	SkillUI& operator=(const SkillUI& _Other) = delete;
	SkillUI& operator=(SkillUI&& _Other) noexcept = delete;

public:
	GameEngineRenderer* GetRenderer()
	{
		return Renderer;
	}


protected:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* Renderer;
};
