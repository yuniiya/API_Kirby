#pragma once
#include "Monster.h"

class Snooter : public Monster
{
public:
	// constrcuter destructer
	Snooter();
	~Snooter();

	// delete Function
	Snooter(const Snooter& _Other) = delete;
	Snooter(Snooter&& _Other) noexcept = delete;
	Snooter& operator=(const Snooter& _Other) = delete;
	Snooter& operator=(Snooter&& _Other) noexcept = delete;

protected:

private:

};
