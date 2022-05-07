#pragma once
#include <GameEngine/GameEngineActor.h>

class SkillName : public GameEngineActor
{
public:
	// constrcuter destructer
	SkillName();
	~SkillName();

	// delete Function
	SkillName(const SkillName& _Other) = delete;
	SkillName(SkillName&& _Other) noexcept = delete;
	SkillName& operator=(const SkillName& _Other) = delete;
	SkillName& operator=(SkillName&& _Other) noexcept = delete;

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
