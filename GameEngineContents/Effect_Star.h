#pragma once
class Effect_Star
{
public:
	// constrcuter destructer
	Effect_Star();
	~Effect_Star();

	// delete Function
	Effect_Star(const Effect_Star& _Other) = delete;
	Effect_Star(Effect_Star&& _Other) noexcept = delete;
	Effect_Star& operator=(const Effect_Star& _Other) = delete;
	Effect_Star& operator=(Effect_Star&& _Other) noexcept = delete;

protected:

private:

};
