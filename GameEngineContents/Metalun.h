#pragma once
#include "Monster.h"

class Metalun : public Monster
{
public:
	// constrcuter destructer
	Metalun();
	~Metalun();

	// delete Function
	Metalun(const Metalun& _Other) = delete;
	Metalun(Metalun&& _Other) noexcept = delete;
	Metalun& operator=(const Metalun& _Other) = delete;
	Metalun& operator=(Metalun&& _Other) noexcept = delete;

private:
	float Speed_;
	
	float DamagedTime_;

protected:
	GameEngineRenderer* AnimationRender;

	GameEngineCollision* MonsterCollision;

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
	void WalkStart() override;
	void SwallowedStart() override;
	void DamagedStart() override;

	void IdleUpdate() override;
	void WalkUpdate() override;
	void SwallowedUpdate() override;
	void DamagedUpdate() override;
};