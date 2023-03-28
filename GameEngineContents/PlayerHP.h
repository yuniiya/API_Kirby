#pragma once
#include <GameEngine/GameEngineActor.h>

class PlayerHP : public GameEngineActor
{
public:
	static PlayerHP* MainHP;

	// constrcuter destructer
	PlayerHP();
	~PlayerHP();

	// delete Function
	PlayerHP(const PlayerHP& _Other) = delete;
	PlayerHP(PlayerHP&& _Other) noexcept = delete;
	PlayerHP& operator=(const PlayerHP& _Other) = delete;
	PlayerHP& operator=(PlayerHP&& _Other) noexcept = delete;

public:
	void SetHP(float _CurHP, float _MaxHP);

	static GameEngineRenderer* GetRenderer()
	{
		return PlayerHPBar;
	}

private:
	static GameEngineRenderer* PlayerHPBar;
	float OriginalScale_;
	float PrevScale_;

protected:
	void Start() override;
	void Update() override;
};
