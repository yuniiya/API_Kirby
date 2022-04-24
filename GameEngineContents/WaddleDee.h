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

private:
	//float Speed_;

protected:
	GameEngineRenderer* AnimationRender;

private:
	void ChangeState(MonsterState _State) override;
	void MonsterStateUpdate() override;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	void WalkStart() override;
	void DamagedStart() override;

	void WalkUpdate() override;
	void DamagedUpdate() override;
};
