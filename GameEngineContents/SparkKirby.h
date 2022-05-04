#pragma once
#include "Player.h"

class GameEngineImage;
class GameEngineCollision;

class SparkKirby : public Player
{
public:
	static SparkKirby* SparkPlayer;

	// constrcuter destructer
	SparkKirby();
	~SparkKirby();

	// delete Function
	SparkKirby(const SparkKirby& _Other) = delete;
	SparkKirby(SparkKirby&& _Other) noexcept = delete;
	SparkKirby& operator=(const SparkKirby& _Other) = delete;
	SparkKirby& operator=(SparkKirby&& _Other) noexcept = delete;

	std::string GetCurrentLevelName()
	{
		CurrentLevel = GetLevel()->GetNameCopy();
		return CurrentLevel;
	}

protected:
	KirbySkill CurSkill_;

protected:
	GameEngineRenderer* PlayerAnimationRender;

	GameEngineSoundPlayer FloatEffSound_;
	GameEngineSoundPlayer AttackEffSound_;
	GameEngineSoundPlayer AttackEffSoundMid_;

private:
	float Speed_;
	float JumpPower_;

	float Gravity_;

	// State 지속 시간
	float SlidingTime_;
	float StopTime_;
	float DownTime_;

private:
	// 충돌
	GameEngineCollision* SparkAttackCollision_;


	void MonsterColCheck() override;

	//void SwallowColCheck();
	void AttackColCheck();

private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void Start() override;
	void Update() override;

protected:
	void ChangeState(PlayerState _State);
	void PlayerStateUpdate();
	void DirAnimationCheck() override;

protected:
	void IdleStart() override;
	void WalkStart() override;
	void RunStart() override;
	void RunToStopStart() override;
	void DownStart() override;
	void SlideStart() override;

	void JumpStart() override;
	void FallStart() override;
	void FallToBounceStart() override;
	void BounceToIdleStart() override;
	void FloatStart() override;
	void ExhaleStart() override;

	void AttackStartStart() override;
	void AttackStart() override;
	void AttackEndStart() override;


	/////////////////////////////////
	void IdleUpdate() override;
	void WalkUpdate() override;
	void RunUpdate() override;
	void RunToStopUpdate() override;
	void DownUpdate() override;
	void SlideUpdate() override;

	void JumpUpdate() override;
	void FallUpdate() override;
	void FallToBounceUpdate() override;
	void BounceToIdleUpdate() override;
	void FloatUpdate();
	void ExhaleUpdate() override;


	void AttackStartUpdate() override;
	void AttackUpdate() override;
	void AttackEndUpdate() override;

};