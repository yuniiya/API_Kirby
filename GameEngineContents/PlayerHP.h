#pragma once
class PlayerHP
{
public:
	// constrcuter destructer
	PlayerHP();
	~PlayerHP();

	// delete Function
	PlayerHP(const PlayerHP& _Other) = delete;
	PlayerHP(PlayerHP&& _Other) noexcept = delete;
	PlayerHP& operator=(const PlayerHP& _Other) = delete;
	PlayerHP& operator=(PlayerHP&& _Other) noexcept = delete;

protected:

private:

};
