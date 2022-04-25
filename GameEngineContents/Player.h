#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include "Stage.h"

class GameEngineImage;
class GameEngineCollision;

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
	Inhale,
	Full,
	Exhale,
	Swallow,
	Exhausted,
	Attack,
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


protected:
	GameEngineRenderer* PlayerAnimationRender;
	PlayerDir CurDir_;
	PlayerDir InputDir_;
	std::string AnimationName_;
	std::string ChangeDirText_;

	
	GameEngineSoundPlayer BgmPlayer_;

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

	void MovePixelCheck(float _x, float _y);
	void HillPixelCheck();
	int BottomePixelColorCheck(float _y);
	
	
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
	void IdleStart();
	void WalkStart();
	void RunStart();
	void RunToStopStart();
	void DownStart();
	void SlideStart();

	void JumpStart();
	void FallStart();
	void FallToBounceStart();
	void FloatStart();

	void InhaleStart();
	void FullStart();
	void ExhaleStart();
	void SwallowStart();
	void ExhaustedStart();

	void AttackStart();
	void DamagedStart();


	///////////////////////
	void IdleUpdate();
	void WalkUpdate();
	void RunUpdate();
	void RunToStopUpdate();
	void DownUpdate();
	void SlideUpdate();

	void JumpUpdate();
	void FallUpdate();
	void FallToBounceUpdate();

	void FloatUpdate();
	void InhaleUpdate();
	void FullUpdate();
	void ExhaleUpdate();
	void SwallowUpdate();
	void ExhaustedUpdate();

	void AttackUpdate();
	void DamagedUpdate();
	

};
