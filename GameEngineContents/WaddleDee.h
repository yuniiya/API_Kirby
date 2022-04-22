#pragma once
#include "Monster.h"

class WaddleDee : public Monster
{
public:
	// constrcuter destructer
	WaddleDee();
	~WaddleDee();

	// delete Function
	WaddleDee(const WaddleDee& _Other) = delete;
	WaddleDee(WaddleDee&& _Other) noexcept = delete;
	WaddleDee& operator=(const WaddleDee& _Other) = delete;
	WaddleDee& operator=(WaddleDee&& _Other) noexcept = delete;

protected:
	GameEngineRenderer* AnimationRender;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	void WalkStart();
	void DamagedStart();

	void WalkUpdate();
	void DamagedUpdate();
};
