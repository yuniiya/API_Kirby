#pragma once
#include "Player.h"

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

	//void MapScale(float _x, float _y);

	std::string GetCurrentLevelName()
	{
		CurrentLevel = GetLevel()->GetNameCopy();
		return CurrentLevel;
	}

	//void DebugModeSwitch();

	//void DebugKirbySkillChange(KirbySkill _Skill);

protected:
	KirbySkill CurSkill_;

	//void DefaultKirbyUpdate();
	//void MetalKirbyUpdate();
	//void IceKirbyUpdate();
	//void SparkKirbyUpdate();

protected:
	GameEngineRenderer* PlayerAnimationRender;
	//PlayerDir CurDir_;
	//PlayerDir InputDir_;
	//std::string AnimationName_;
	//std::string ChangeDirText_;


	//void CameraFix();


private:
	float Speed_;
	float JumpPower_;

	float Gravity_;

	// State 지속 시간
	float SlidingTime_;
	float StopTime_;
	float DownTime_;

	// 스테이지 관련
	//float MapScaleX_;
	//float MapScaleY_;

	//GameEngineImage* MapColImage_;

	//void ColMapUpdate();

	//std::string CurrentLevel;

private:
	// 충돌
	//GameEngineCollision* PlayerCollision;
	//void DoorCheck(std::string ChangeLevelName_);


	void MonsterColCheck() override;

	//void SwallowColCheck();
	//void AttackColCheck();

private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void Start() override;
	void Update() override;

private:
	//float4 MoveDir;
	//PlayerState CurState_;
	//PlayerState PrevState_;

	//bool IsMoveKey();
	//bool IsMoveKeyDown();
	//bool IsJumpKey();

	//void Move();
	//void GravityOn();


protected:
	void ChangeState(PlayerState _State);
	void PlayerStateUpdate();
	void DirAnimationCheck() override;

private:
	void IdleStart() override;
	void WalkStart() override;
	void DownStart() override;
	void SlideStart() override;

	void JumpStart() override;
	void FallStart() override;
	void FallToBounceStart() override;
	void BounceToIdleStart() override;
	void FloatStart() override;

	void ExhaleStart() override;
	void AttackStart() override;


	///////////////////////
	void IdleUpdate() override;
	void WalkUpdate() override;
	void DownUpdate() override;
	void SlideUpdate() override;

	void JumpUpdate() override;
	void FallUpdate() override;
	void FallToBounceUpdate() override;
	void BounceToIdleUpdate() override;
	void FloatUpdate() override;

	void ExhaleUpdate() override;
	void AttackUpdate() override;


};
