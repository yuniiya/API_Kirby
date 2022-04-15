#pragma once
#include "Monster.h"

class Kingdedede : public Monster
{
public:
	// constrcuter destructer
	Kingdedede();
	~Kingdedede();

	// delete Function
	Kingdedede(const Kingdedede& _Other) = delete;
	Kingdedede(Kingdedede&& _Other) noexcept = delete;
	Kingdedede& operator=(const Kingdedede& _Other) = delete;
	Kingdedede& operator=(Kingdedede&& _Other) noexcept = delete;

protected:

private:

};
