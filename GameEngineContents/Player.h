#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include "Stage.h"

class GameEngineImage;
class GameEngineCollision;

enum class KirbySkill
{
	Default,
	Metal,
	Ice,
	Spark,

	Max,
};

enum class PlayerState
{
	Idle,
	Walk,
	Run,
	RunToStop,
	Down,
	Slide,
	Jump,
	Float,
	Fall,
	FallToBounce,
	BounceToIdle,
	Inhale,
	Full,
	FullWalk,
	FullJump,
	Exhale,
	Swallow,
	Exhausted,
	AttackStart,
	Attack,
	AttackEnd,
	DamagedStart,
	Damaged,
	
	Max,
};

enum class PlayerDir
{
	Left,
	Right,
	Down, 
	Max,
};


class Player : public GameEngineActor
{
public:
	static Player* MainPlayer;
	static GameEngineSoundPlayer BgmPlayer;

	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void MapScale(float _x, float _y);

	std::string GetCurrentLevelName()
	{
		CurrentLevel = GetLevel()->GetNameCopy();
		return CurrentLevel;
	}

	void DebugModeSwitch();

	//void DebugKirbySkillChange(KirbySkill _Skill);
	void DebugKirbySkillChange();

protected:
	KirbySkill CurSkill_;

	void DefaultKirbyUpdate();
	void MetalKirbyUpdate();
	void IceKirbyUpdate();
	void SparkKirbyUpdate();

protected:
	GameEngineRenderer* PlayerAnimationRender;
	PlayerDir CurDir_;
	PlayerDir InputDir_;
	std::string AnimationName_;
	std::string ChangeDirText_;
	

	void CameraFix();


protected:
	float Speed_;
	float AccSpeed_;

	float JumpPower_;
	float Gravity_;

	// State 지속 시간
	float RunningTime_;
	float SlidingTime_;
	float StopTime_;
	float DownTime_;
	float InhaleTime_;
	float FallTime_;


	// 스테이지 관련
	float MapScaleX_;
	float MapScaleY_;

	GameEngineImage* MapColImage_;

	void ColMapUpdate();

	std::string CurrentLevel;

protected:
	// 충돌
	GameEngineCollision* PlayerCollision;

	void StagePixelCheck(float _Speed);
	void DoorPixelCheck();
	void DoorCheck(std::string ChangeLevelName_);

	//void DoorCheck();
	void WallCheck();
	virtual void MonsterColCheck();
	void SwallowColCheck();
	void AttackColCheck();

	void MovePixelCheck(float _x, float _y);
	void HillPixelCheck();
	int BottomPixelColorCheck(float _y);
	
	
private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void Start() override;
	void Update() override;
	void Render() override;


protected:
	float4 MoveDir;
	PlayerState CurState_;
	PlayerState PrevState_;

	bool IsMoveKey();
	bool IsMoveKeyDown();
	bool IsJumpKey();

	void Move();
	void GravityOn();


protected:
	void ChangeState(PlayerState _State);
	void PlayerStateUpdate();
	virtual void DirAnimationCheck();

protected:
	virtual void IdleStart();
	virtual void WalkStart();
	virtual void RunStart();
	virtual void RunToStopStart();
	virtual void DownStart();
	virtual void SlideStart();

	virtual void JumpStart();
	virtual void FallStart();
	virtual void FallToBounceStart();
	virtual void BounceToIdleStart();
	virtual void FloatStart();

	virtual void InhaleStart();
	virtual void FullStart();
	virtual void FullWalkStart();
	virtual void FullJumpStart();
	virtual void ExhaleStart();
	virtual void SwallowStart();
	virtual void ExhaustedStart();

	virtual void AttackStartStart();
	virtual void AttackStart();
	virtual void AttackEndStart();
	virtual void DamagedStartStart();
	virtual void DamagedStart();


	///////////////////////
	virtual void IdleUpdate();
	virtual void WalkUpdate();
	virtual void RunUpdate();
	virtual void RunToStopUpdate();
	virtual void DownUpdate();
	virtual void SlideUpdate();

	virtual void JumpUpdate();
	virtual void FallUpdate();
	virtual void FallToBounceUpdate();
	virtual void BounceToIdleUpdate();
	virtual void FloatUpdate();

	virtual void InhaleUpdate();
	virtual void FullUpdate();
	virtual void FullWalkUpdate();
	virtual void FullJumpUpdate();

	virtual void ExhaleUpdate();
	virtual void SwallowUpdate();
	virtual void ExhaustedUpdate();

	virtual void AttackStartUpdate();
	virtual void AttackUpdate();
	virtual void AttackEndUpdate();
	virtual void DamagedStartUpdate();
	virtual void DamagedUpdate();
	

};
