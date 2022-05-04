#pragma once
#include "Player.h"

class GameEngineImage;
class GameEngineCollision;

class IceKirby : public Player
{
public:
	static IceKirby* IcePlayer;

	// constrcuter destructer
	IceKirby();
	~IceKirby();

	// delete Function
	IceKirby(const IceKirby& _Other) = delete;
	IceKirby(IceKirby&& _Other) noexcept = delete;
	IceKirby& operator=(const IceKirby& _Other) = delete;
	IceKirby& operator=(IceKirby&& _Other) noexcept = delete;

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

private:
	float Speed_;
	float JumpPower_;

	float Gravity_;

	// State 지속 시간
	float SlidingTime_;
	float StopTime_;
	float DownTime_;


private:
	//GameEngineCollision* PlayerCollision;


	void MonsterColCheck() override;
	//void AttackColCheck();

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