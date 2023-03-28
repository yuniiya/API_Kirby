#pragma once
#include "Player.h"
#include "SkillUI.h"
#include "SkillName.h"

class GameEngineImage;
class GameEngineCollision;

class SparkKirby : public Player
{
public:
	static SparkKirby* SparkPlayer;
	static SkillUI* SparkSkill;
	static SkillName* SparkName;

	// constrcuter destructer
	SparkKirby();
	~SparkKirby();

	// delete Function
	SparkKirby(const SparkKirby& _Other) = delete;
	SparkKirby(SparkKirby&& _Other) noexcept = delete;
	SparkKirby& operator=(const SparkKirby& _Other) = delete;
	SparkKirby& operator=(SparkKirby&& _Other) noexcept = delete;

	void SparkKirbyOff();

protected:

	GameEngineSoundPlayer AttackEffSound_;
	GameEngineSoundPlayer AttackEffSoundMid_;

private:
	// Ãæµ¹
	GameEngineCollision* SparkAttackCollision_;

	void MonsterColCheck() override;

private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void Start() override;
	void Update() override;


protected:
	void IdleStart() override;
	void AttackStartStart() override;
	void AttackStart() override;
	void AttackEndStart() override;

	/////////////////////////////////
	void IdleUpdate() override;
	void WalkUpdate() override;
	void AttackStartUpdate() override;
	void AttackUpdate() override;
	void AttackEndUpdate() override;

};