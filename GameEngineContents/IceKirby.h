#pragma once
#include "Player.h"
#include "Effect_IceBreath.h"
#include "SkillUI.h"
#include "SkillName.h"

class GameEngineImage;
class GameEngineCollision;

class IceKirby : public Player
{
public:
	static IceKirby* IcePlayer;
	static SkillUI* IceSkill;
	static SkillName* IceName;

	// constrcuter destructer
	IceKirby();
	~IceKirby();

	// delete Function
	IceKirby(const IceKirby& _Other) = delete;
	IceKirby(IceKirby&& _Other) noexcept = delete;
	IceKirby& operator=(const IceKirby& _Other) = delete;
	IceKirby& operator=(IceKirby&& _Other) noexcept = delete;

	void IceKirbyOff();


protected:
	GameEngineSoundPlayer AttackEffSound_;

private:
	// Effect
	Effect_IceBreath* IceBreath_;

private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void Start() override;
	void Update() override;

protected:
	void IdleStart() override;
	void AttackStart() override;


	/////////////////////////////////
	void IdleUpdate() override;
	void WalkUpdate() override;
	void AttackUpdate() override;
	void AttackEndUpdate() override;

};