#pragma once
class MonsterHP
{
public:
	// constrcuter destructer
	MonsterHP();
	~MonsterHP();

	// delete Function
	MonsterHP(const MonsterHP& _Other) = delete;
	MonsterHP(MonsterHP&& _Other) noexcept = delete;
	MonsterHP& operator=(const MonsterHP& _Other) = delete;
	MonsterHP& operator=(MonsterHP&& _Other) noexcept = delete;

protected:

private:

};
