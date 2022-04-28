#pragma once
#include "Player.h"

class SparkKirby : public Player
{
public:
	static SparkKirby* SparkPlayer;

	// constrcuter destructer
	SparkKirby();
	~SparkKirby();

	// delete Function
	SparkKirby(const SparkKirby& _Other) = delete;
	SparkKirby(SparkKirby&& _Other) noexcept = delete;
	SparkKirby& operator=(const SparkKirby& _Other) = delete;
	SparkKirby& operator=(SparkKirby&& _Other) noexcept = delete;

protected:

private:

};
