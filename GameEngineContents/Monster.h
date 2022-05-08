#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>

class GameEngineImage;
class GameEngineCollision;

enum class MonsterState
{
	Idle,
	Walk,
	Jump,
	JumpDown,
	Attack,
	Swallowed,
	Damaged,
	DamagedByMetal,
	Swallow,
	Scream,
	Dead,

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
	int HP_;

	bool IsHit_;
	virtual void Hit() {};

protected:
	GameEngineRenderer* MonsterAnimationRenderer;

	MonsterDir CurDir_;
	MonsterDir InputDir_;

	std::string AnimationName_;
	std::string ChangeDirText_;

protected:
	float Speed_;
	float Gravity_;

	float4 MoveDir;

	MonsterState CurState_;

	void GravityOn();

	void StagePixelCheck(float _Speed);
	//void WallPixelCheck(float _x, float _Speed);
	void GroundPixelCheck();

	int BottomPixelColorCheck(float _y);

protected:
	// 스테이지 관련
	float MapScaleX_;
	float MapScaleY_;

	GameEngineImage* MapColImage_;

	void ColMapUpdate();

	std::string CurrentLevel;


protected:
	virtual void Start();
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	virtual void ChangeState(MonsterState _State);
	virtual void MonsterStateUpdate();
	virtual void DirAnimationCheck();

protected:
	virtual void IdleStart() {};
	virtual void WalkStart() {};
	virtual void JumpStart() {};
	virtual void SwallowedStart() {};

	virtual void AttackStart() {};
	virtual void DamagedStart() {};
	virtual void DamagedByMetalStart() {};

	// Boss전용
	virtual void SwallowStart() {};
	virtual void ScreamStart() {};
	virtual void DeadStart() {};

	//////////////////////////////////////////


	virtual void IdleUpdate() {};
	virtual void WalkUpdate() {};
	virtual void JumpUpdate() {};
	virtual void SwallowedUpdate() {};

	virtual void AttackUpdate() {};
	virtual void DamagedUpdate() {};
	virtual void DamagedByMetalUpdate() {};

	// Boss전용
	virtual void SwallowUpdate() {};
	virtual void ScreamUpdate() {};
	virtual void DeadUpdate() {};
};
