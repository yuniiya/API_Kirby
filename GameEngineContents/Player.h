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
	Inhale,
	Full,
	Exhale,
	Swallow,
	Attack,
	Damaged,
	
	Max,
};

enum class PlayerDir
{
	Left,
	Right,
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


	//inline Stage* GetStage()
	//{
	//	return CurStage_;
	//	GetLevel()->
	//}

	void MapScale(float _x, float _y);

	std::string GetCurrentLevelName()
	{
		CurrentLevel = GetLevel()->GetNameCopy();
		return CurrentLevel;
	}

	void DebugModeSwitch()
	{
		GetLevel()->IsDebugModeSwitch();
	}


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
	float Gravity_;
	float AccGravity_;

	float RunningTime_;
	float SlidingTime_;
	float StopTime_;
	float DownTime_;

	float MapScaleX_;
	float MapScaleY_;

	float4 MoveDir;

	GameEngineImage* MapColImage_;

	GameEngineCollision* PlayerCollision;

	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void ColMapUpdate();

	void StagePixelCheck(float _Speed);
	void DoorPixelCheck();
	void DoorCheck(std::string ChangeLevelName_);

	//void DoorCheck();
	void WallCheck();


	std::string CurrentLevel;
	



private:
	PlayerState CurState_;
	GameEngineRenderer* Render1;

	bool IsMoveKey();
	bool IsMoveKeyDown();
	bool IsJumpKey();
	//void KeyMove();

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
	void FloatStart();
	void InhaleStart();
	void FullStart();
	void ExhaleStart();
	void SwallowStart();
	void AttackStart();
	void DamagedStart();


	void IdleUpdate();
	void WalkUpdate();
	void RunUpdate();
	void RunToStopUpdate();
	void DownUpdate();
	void SlideUpdate();

	void JumpUpdate();
	void FallUpdate();
	void FloatUpdate();
	void InhaleUpdate();
	void FullUpdate();
	void ExhaleUpdate();
	void SwallowUpdate();
	void AttackUpdate();
	void DamagedUpdate();
	

};
