#pragma once
#include "Monster.h"
#include "Effect_AttackEnd.h"

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
	float Speed_;
	float DamagedTime_;

public:

protected:
	GameEngineRenderer* AnimationRender;

	GameEngineCollision* MonsterCollision;

	Effect_AttackEnd* AttackEffect_;

private:
	void ChangeState(MonsterState _State) override;
	void MonsterStateUpdate() override;

protected:
	void WallPixelCheck(float _x, float _Speed);
	void MonsterColCheck();
	void InhaleColCheck();

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	void WalkStart() override;
	void SwallowedStart() override;
	void DamagedStart() override;
	void IcedStart();

	void WalkUpdate() override;
	void SwallowedUpdate() override;
	void DamagedUpdate() override;
	void IcedUpdate();
};
