#pragma once
#include "Monster.h"

class Scarfy : public Monster
{
public:
	// constrcuter destructer
	Scarfy();
	~Scarfy();

	// delete Function
	Scarfy(const Scarfy& _Other) = delete;
	Scarfy(Scarfy&& _Other) noexcept = delete;
	Scarfy& operator=(const Scarfy& _Other) = delete;
	Scarfy& operator=(Scarfy&& _Other) noexcept = delete;

private:
	float Speed_;
	float DamagedTime_;

public:

protected:
	GameEngineRenderer* AnimationRender;

	GameEngineCollision* MonsterCollision;

private:
	void ChangeState(MonsterState _State) override;
	void MonsterStateUpdate() override;

	void DirCheck();

protected:
	void MonsterColCheck();

private:
	MonsterDir CurDir_;
	MonsterDir InputDir_;

	std::string AnimationName_;
	std::string ChangeDirText_;

protected:
	void Start() override;
	void Update() override;
	void Render() override;


private:
	void IdleStart() override;
	void JumpStart() override;
	void SwallowedStart() override;
	void DamagedStart() override;
	void DamagedByMetalStart() override;

	void IdleUpdate() override;
	void JumpUpdate() override;
	void SwallowedUpdate() override;
	void DamagedUpdate() override;
	void DamagedByMetalUpdate() override;
};

