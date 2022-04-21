#pragma once
class BigWaddleDee
{
public:
	// constrcuter destructer
	BigWaddleDee();
	~BigWaddleDee();

	// delete Function
	BigWaddleDee(const BigWaddleDee& _Other) = delete;
	BigWaddleDee(BigWaddleDee&& _Other) noexcept = delete;
	BigWaddleDee& operator=(const BigWaddleDee& _Other) = delete;
	BigWaddleDee& operator=(BigWaddleDee&& _Other) noexcept = delete;

protected:

private:

};
