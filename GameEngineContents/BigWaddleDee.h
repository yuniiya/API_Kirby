#pragma once
#include "Monster.h"

class BigWaddleDee : public Monster
{
public:
	// constrcuter destructer
	BigWaddleDee();
	~BigWaddleDee();

	// delete Function
	BigWaddleDee(const BigWaddleDee& _Other) = delete;
	BigWaddleDee(BigWaddleDee&& _Other) noexcept = delete;
	BigWaddleDee& operator=(const BigWaddleDee& _Other) = delete;
	BigWaddleDee& operator=(BigWaddleDee&& _Other) noexcept = delete;

private:
	//float Speed_;

protected:
	GameEngineRenderer* AnimationRender;

	GameEngineCollision* MonsterCollision;

private:
	void ChangeState(MonsterState _State) override;
	void MonsterStateUpdate() override;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	void WalkStart() override;
	void SwallowedStart() override;
	void DamagedStart() override;

	void WalkUpdate() override;
	void SwallowedUpdate() override;
	void DamagedUpdate() override;
};

