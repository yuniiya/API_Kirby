#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>

class GameEngineImage;
class GameEngineCollision;

enum class MonsterState
{
	Idle,
	Walk,
	Attack,
	Damaged,
	Max,
};

enum class MonsterDir
{
	Left,
	Right,
	Max,
};


class Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

protected:
	GameEngineRenderer* MonsterAnimationRenderer;

	MonsterDir CurDir_;
	MonsterDir InputDir_;

	std::string AnimationName_;
	std::string ChangeDirText_;


private:
	float Speed_;

	float4 MoveDir;

	GameEngineCollision* MonsterCollision;

	MonsterState CurState_;

	void StagePixelCheck(float _Speed);

	void Start() override;
	void Update() override;
	void Render() override;

protected:
	void ChangeState(MonsterState _State);
	virtual void MonsterStateUpdate();
	virtual void DirAnimationCheck();

private:
	void IdleStart();
	void WalkStart();
	void AttackStart();
	void DamagedStart();

	void IdleUpdate();
	void WalkUpdate();
	void AttackUpdate();
	void DamagedUpdate();
};
