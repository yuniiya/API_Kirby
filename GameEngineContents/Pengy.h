#pragma once
#include "Monster.h"

class Pengy : public Monster
{
public:
	// constrcuter destructer
	Pengy();
	~Pengy();

	// delete Function
	Pengy(const Pengy& _Other) = delete;
	Pengy(Pengy&& _Other) noexcept = delete;
	Pengy& operator=(const Pengy& _Other) = delete;
	Pengy& operator=(Pengy&& _Other) noexcept = delete;

protected:

private:

};
