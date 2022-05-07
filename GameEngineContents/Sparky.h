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

	float DamagedTime_;
	float AttReadyTime_;
	float AttackTime_;
	float JumpTime_;
	float JumpDownTime_;

	int HitCount_;
	bool IsHit;

protected:
	void Hit();

protected:
	GameEngineRenderer* AnimationRender;

	GameEngineCollision* MonsterCollision;
	GameEngineCollision* AttackCollision;

	GameEngineSoundPlayer AttackEffSound_;
	GameEngineSoundPlayer JumpEffSound_;

private:
	void ChangeState(MonsterState _State) override;
	void MonsterStateUpdate() override;
	void DirCheck();

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
	void JumpDownStart();
	void SwallowedStart() override;
	void AttackStart() override;
	void DamagedStart() override;

	void IdleUpdate() override;
	void JumpUpdate() override;
	void JumpDownUpdate();
	void SwallowedUpdate() override;
	void AttackUpdate() override;
	void DamagedUpdate() override;
};