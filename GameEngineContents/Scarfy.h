#pragma once
#include "Monster.h"

class Scarfy : public Monster
{
public:
	// constrcuter destructer
	Scarfy();
	~Scarfy();

	// delete Function
	Scarfy(const Scarfy& _Other) = delete;
	Scarfy(Scarfy&& _Other) noexcept = delete;
	Scarfy& operator=(const Scarfy& _Other) = delete;
	Scarfy& operator=(Scarfy&& _Other) noexcept = delete;

protected:

private:

};
