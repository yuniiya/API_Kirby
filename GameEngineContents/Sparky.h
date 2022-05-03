#pragma once
#include "Monster.h"

class Sparky : public Monster
{
public:
	// constrcuter destructer
	Sparky();
	~Sparky();

	// delete Function
	Sparky(const Sparky& _Other) = delete;
	Sparky(Sparky&& _Other) noexcept = delete;
	Sparky& operator=(const Sparky& _Other) = delete;
	Sparky& operator=(Sparky&& _Other) noexcept = delete;

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
	void JumpStart() override;
	void SwallowedStart() override;
	void AttackStart() override;
	void DamagedStart() override;

	void IdleUpdate() override;
	void JumpUpdate() override;
	void SwallowedUpdate() override;
	void AttackUpdate() override;
	void DamagedUpdate() override;
};