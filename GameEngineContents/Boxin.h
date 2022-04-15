#pragma once
#include "Monster.h"

class Boxin : public Monster
{
public:
	// constrcuter destructer
	Boxin();
	~Boxin();

	// delete Function
	Boxin(const Boxin& _Other) = delete;
	Boxin(Boxin&& _Other) noexcept = delete;
	Boxin& operator=(const Boxin& _Other) = delete;
	Boxin& operator=(Boxin&& _Other) noexcept = delete;

protected:

private:

};
