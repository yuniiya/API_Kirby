#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineImage;
class GameEngineCollision;

class Effect_IceBoxEnd : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_IceBoxEnd();
	~Effect_IceBoxEnd();

	// delete Function
	Effect_IceBoxEnd(const Effect_IceBoxEnd& _Other) = delete;
	Effect_IceBoxEnd(Effect_IceBoxEnd&& _Other) noexcept = delete;
	Effect_IceBoxEnd& operator=(const Effect_IceBoxEnd& _Other) = delete;
	Effect_IceBoxEnd& operator=(Effect_IceBoxEnd&& _Other) noexcept = delete;

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
