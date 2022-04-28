#pragma once
#include "Player.h"

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
	Inhale,
	Exhale,
	Full,
	FullWalk,
	FullJump,
	Swallow,
	Exhausted,
	Attack,

	Max,
};

enum class PlayerDir
{
	Left,
	Right,
	Down,
	Max,
};

class GameEngineImage;
class GameEngineCollision;

class MetalKirby : public Player
{
public:
	static MetalKirby* MetalPlayer;

	// constrcuter destructer
	MetalKirby();
	~MetalKirby();

	// delete Function
	MetalKirby(const MetalKirby& _Other) = delete;
	MetalKirby(MetalKirby&& _Other) noexcept = delete;
	MetalKirby& operator=(const MetalKirby& _Other) = delete;
	MetalKirby& operator=(MetalKirby&& _Other) noexcept = delete;

	void MapScale(float _x, float _y);

	std::string GetCurrentLevelName()
	{
		CurrentLevel = GetLevel()->GetNameCopy();
		return CurrentLevel;
	}

	void DebugModeSwitch();

//	void DebugKirbySkillChange(KirbySkill _Skill);
//
//protected:
//	KirbySkill CurSkill_;
//
//	void DefaultKirbyUpdate();
//	void MetalKirbyUpdate();
//	void IceKirbyUpdate();
//	void SparkKirbyUpdate();

protected:
	GameEngineRenderer* PlayerAnimationRender;
	PlayerDir CurDir_;
	PlayerDir InputDir_;
	std::string AnimationName_;
	std::string ChangeDirText_;


	void CameraFix();


private:
	float Speed_;
	float AccSpeed_;

	float JumpPower_;
	float JumpMaxHeight_;

	float Gravity_;

	// State 지속 시간
	float RunningTime_;
	float SlidingTime_;
	float StopTime_;
	float DownTime_;
	float InhaleTime_;
	float FallTime_;

	float JumpTimeL_;
	float JumpTimeR_;

	bool LongJump_;

	// 스테이지 관련
	float MapScaleX_;
	float MapScaleY_;

	GameEngineImage* MapColImage_;

	void ColMapUpdate();

	std::string CurrentLevel;

private:
	// 충돌
	GameEngineCollision* PlayerCollision;

	void StagePixelCheck(float _Speed);
	void DoorPixelCheck();
	void DoorCheck(std::string ChangeLevelName_);

	//void DoorCheck();
	void WallCheck();
	void MonsterColCheck();
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


private:
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
	void DirAnimationCheck();

private:
	void IdleStart() override;
	void WalkStart() override;
	void RunStart() override;
	void RunToStopStart() override;
	void DownStart() override;
	void SlideStart() override;

	void JumpStart() override;
	void FallStart() override;
	void FloatStart() override;

	void InhaleStart() override;
	void FullStart() override;
	void FullWalkStart() override;
	void FullJumpStart() override;
	void ExhaleStart() override;
	void SwallowStart() override;
	void ExhaustedStart() override;

	void AttackStart() override;


	///////////////////////
	//void IdleUpdate();
	//void WalkUpdate();
	//void RunUpdate();
	//void RunToStopUpdate();
	//void DownUpdate();
	//void SlideUpdate();

	void JumpUpdate() override;
	void FallUpdate() override;
	//void FloatUpdate();

	//void InhaleUpdate();
	//void FullUpdate();
	//void FullWalkUpdate();
	//void FullJumpUpdate();

	//void ExhaleUpdate();
	//void SwallowUpdate();
	//void ExhaustedUpdate();

	void AttackUpdate() override;


};
