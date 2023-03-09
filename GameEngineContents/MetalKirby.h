#pragma once
#include "Player.h"
#include "SkillUI.h"
#include "SkillName.h"

class GameEngineImage;
class GameEngineCollision;

class MetalKirby : public Player
{
public:
	static MetalKirby* MetalPlayer;
	static SkillUI* MetalSkill;
	static SkillName* MetalName;

	// constrcuter destructer
	MetalKirby();
	~MetalKirby();

	// delete Function
	MetalKirby(const MetalKirby& _Other) = delete;
	MetalKirby(MetalKirby&& _Other) noexcept = delete;
	MetalKirby& operator=(const MetalKirby& _Other) = delete;
	MetalKirby& operator=(MetalKirby&& _Other) noexcept = delete;

protected:
	
	GameEngineSoundPlayer EffectSound_;


private:
	float Speed_;
	float JumpPower_;

	float Gravity_;

	// State 지속 시간
	float SlidingTime_;
	float StopTime_;
	float DownTime_;

private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void Start() override;
	void Update() override;


private:
	void IdleStart() override;
	void WalkStart() override;
	void SlideStart() override;

	void JumpStart() override;
	void FallToBounceStart() override;
	void FloatStart() override;

	void AttackStart() override;


	///////////////////////
	void IdleUpdate() override;
	void WalkUpdate() override;

	void JumpUpdate() override;
	void FallUpdate() override;
	void FallToBounceUpdate() override;
	void BounceToIdleUpdate() override;
	void FloatUpdate() override;

	void ExhaleUpdate() override;
	void AttackUpdate() override;


};
