#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include "Stage.h"
#include "Effect_Attack.h"
#include "Effect_Star.h"
#include "Effect_Inhale.h"
#include "PlayUI.h"
//#include "PlayerHP.h"

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
	FullLoop,
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

	FullToSkill,
	SwallowToSkill,
	TransformToSkill,

	Max,
};

enum class SwallowMonsterType 
{
	Metal,
	Ice,
	Spark,

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
	//static PlayerHP* MainHP;

	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void MapScale(float _x, float _y);

	std::string GetCurrentLevelName();

	void DebugModeSwitch();

	//void DebugKirbySkillChange(KirbySkill _Skill);
	void DebugKirbySkillChange();

	void DebugHP();

protected:
	KirbySkill CurSkill_;
	SwallowMonsterType CurSwallowMonster_;

	void DefaultKirbyUpdate();
	void MetalKirbyUpdate();
	void IceKirbyUpdate();
	void SparkKirbyUpdate();

protected:
	GameEngineRenderer* PlayerAnimationRender;
	PlayerDir CurDir_;
	PlayerDir InputDir_;
	std::string SkillName_;
	std::string AnimationName_;
	std::string ChangeDirText_;
	
	void CameraFix();

protected:
	Effect_Attack* AttEffect_;
	Effect_Star* StarEffect_;
	Effect_Inhale* InhaleEffect_;

	GameEngineSoundPlayer FloatEffSound_;
	GameEngineSoundPlayer InhaleEffSound_;
	GameEngineSoundPlayer DamagedEffSound_;

protected:
	void MakeStarEffect();

	void PlayerHPUpdate();

protected:
	float CurHP_;
	float MaxHP_;

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

	// Effect
	float RunEffTime_;
	float AttackTime_;

	float SlideColTime_;


	// 스테이지 관련
	float MapScaleX_;
	float MapScaleY_;

	GameEngineImage* MapColImage_;

	void ColMapUpdate();

	std::string CurrentLevel;

public:
	GameEngineCollision* InhaleCollision;

protected:
	// 충돌
	GameEngineCollision* PlayerCollision;

	GameEngineCollision* SlideCollision;

	float4 InhalePos;
	float4 SlidePos;

	void StagePixelCheck(float _Speed);
	void DoorPixelCheck();
	void DoorCheck(std::string ChangeLevelName_);

	void WallCheck();
	virtual void MonsterColCheck();
	void InhaleColCheck();

	void MovePixelCheck(float _x, float _y);
	void HillPixelCheck();
	int BottomPixelColorCheck(float _y);
	
	
protected:
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

	bool IsHit_;
	virtual void Hit();


protected:
	virtual void ChangeState(PlayerState _State);
	virtual void PlayerStateUpdate();
	virtual void DirAnimationCheck();
	void SkillRelease();

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

	void InhaleStart();
	void FullStart();
	void FullLoopStart();
	void FullWalkStart();
	void FullJumpStart();
	virtual void ExhaleStart();
	void SwallowStart();
	void ExhaustedStart();

	virtual void AttackStartStart();
	virtual void AttackStart();
	virtual void AttackEndStart();
	virtual void DamagedStartStart();
	virtual void DamagedStart();

	void FullToSkillStart();
	void SwallowToSkillStart();
	void TransformToSkillStart();

	/////////////////////// Update
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

	void InhaleUpdate();
	void FullUpdate();
	void FullLoopUpdate();
	void FullWalkUpdate();
	void FullJumpUpdate();
	virtual void ExhaleUpdate();
	void SwallowUpdate();
	void ExhaustedUpdate();

	virtual void AttackStartUpdate();
	virtual void AttackUpdate();
	virtual void AttackEndUpdate();
	virtual void DamagedStartUpdate();
	virtual void DamagedUpdate();

	void FullToSkillUpdate();
	void SwallowToSkillUpdate();
	void TransformToSkillUpdate();

};
