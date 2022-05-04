#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_IceBox : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_IceBox();
	~Effect_IceBox();

	// delete Function
	Effect_IceBox(const Effect_IceBox& _Other) = delete;
	Effect_IceBox(Effect_IceBox&& _Other) noexcept = delete;
	Effect_IceBox& operator=(const Effect_IceBox& _Other) = delete;
	Effect_IceBox& operator=(Effect_IceBox&& _Other) noexcept = delete;

public:
	//PlayerDir CurDir_;
	EffectDir Dir_;


	std::string AnimationName_;
	std::string ChangeDirText_;

public:
	void SetDir(EffectDir _Dir)
	{
		Dir_ = _Dir;
	}

private:
	void Start() override;
	void Update() override;

private:
	GameEngineRenderer* AnimationRenderer_;

};