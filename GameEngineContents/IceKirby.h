#pragma once
#include "Player.h"

class IceKirby : public Player
{
public:
	// constrcuter destructer
	IceKirby();
	~IceKirby();

	// delete Function
	IceKirby(const IceKirby& _Other) = delete;
	IceKirby(IceKirby&& _Other) noexcept = delete;
	IceKirby& operator=(const IceKirby& _Other) = delete;
	IceKirby& operator=(IceKirby&& _Other) noexcept = delete;

protected:

private:

};
