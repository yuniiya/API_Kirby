#pragma once
#include "Player.h"

class FighterKirby : public Player
{
public:
	// constrcuter destructer
	FighterKirby();
	~FighterKirby();

	// delete Function
	FighterKirby(const FighterKirby& _Other) = delete;
	FighterKirby(FighterKirby&& _Other) noexcept = delete;
	FighterKirby& operator=(const FighterKirby& _Other) = delete;
	FighterKirby& operator=(FighterKirby&& _Other) noexcept = delete;

protected:

private:

};
