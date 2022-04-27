#pragma once
#include "Monster.h"

class Kingdedede : public Monster
{
public:
	// constrcuter destructer
	Kingdedede();
	~Kingdedede();

	// delete Function
	Kingdedede(const Kingdedede& _Other) = delete;
	Kingdedede(Kingdedede&& _Other) noexcept = delete;
	Kingdedede& operator=(const Kingdedede& _Other) = delete;
	Kingdedede& operator=(Kingdedede&& _Other) noexcept = delete;

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
	void JumpStart() override;
	void SwallowStart() override;
	void ScreamStart() override;
	void AttackStart() override;
	void DamagedStart() override;

	void IdleUpdate() override;
	void WalkUpdate() override;
	void JumpUpdate() override;
	void SwallowUpdate() override;
	void ScreamUpdate() override;
	void AttackUpdate() override;
	void DamagedUpdate() override;
};