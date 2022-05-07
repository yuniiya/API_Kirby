#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;

class Effect_Transform : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_Transform();
	~Effect_Transform();

	// delete Function
	Effect_Transform(const Effect_Transform& _Other) = delete;
	Effect_Transform(Effect_Transform&& _Other) noexcept = delete;
	Effect_Transform& operator=(const Effect_Transform& _Other) = delete;
	Effect_Transform& operator=(Effect_Transform&& _Other) noexcept = delete;

public:
	std::string AnimationName_;
	std::string ChangeDirText_;

public:

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;

};