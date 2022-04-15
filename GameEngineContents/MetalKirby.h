#pragma once
#include "Player.h"

class MetalKirby : public Player
{
public:
	// constrcuter destructer
	MetalKirby();
	~MetalKirby();

	// delete Function
	MetalKirby(const MetalKirby& _Other) = delete;
	MetalKirby(MetalKirby&& _Other) noexcept = delete;
	MetalKirby& operator=(const MetalKirby& _Other) = delete;
	MetalKirby& operator=(MetalKirby&& _Other) noexcept = delete;

protected:

private:

};
