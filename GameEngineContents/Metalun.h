#pragma once
#include "Monster.h"

class Metalun : public Monster
{
public:
	// constrcuter destructer
	Metalun();
	~Metalun();

	// delete Function
	Metalun(const Metalun& _Other) = delete;
	Metalun(Metalun&& _Other) noexcept = delete;
	Metalun& operator=(const Metalun& _Other) = delete;
	Metalun& operator=(Metalun&& _Other) noexcept = delete;

protected:

private:

};
