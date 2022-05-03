#pragma once
#include "Monster.h"

class Pengy : public Monster
{
public:
	// constrcuter destructer
	Pengy();
	~Pengy();

	// delete Function
	Pengy(const Pengy& _Other) = delete;
	Pengy(Pengy&& _Other) noexcept = delete;
	Pengy& operator=(const Pengy& _Other) = delete;
	Pengy& operator=(Pengy&& _Other) noexcept = delete;

private:
	float Speed_;

protected:
	GameEngineRenderer* AnimationRender;

	GameEngineCollision* MonsterCollision;

private:
	void ChangeState(MonsterState _State) override;
	void MonsterStateUpdate() override;

protected:
	void WallPixelCheck(float _x, float _Speed);
	void MonsterColCheck();

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	void IdleStart() override;
	void WalkStart() override;
	void SwallowedStart() override;
	void AttackStart() override;

	void IdleUpdate() override;
	void WalkUpdate() override;
	void SwallowedUpdate() override;
	void AttackUpdate() override;
};