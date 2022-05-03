#pragma once
class Effect_Inhale
{
public:
	// constrcuter destructer
	Effect_Inhale();
	~Effect_Inhale();

	// delete Function
	Effect_Inhale(const Effect_Inhale& _Other) = delete;
	Effect_Inhale(Effect_Inhale&& _Other) noexcept = delete;
	Effect_Inhale& operator=(const Effect_Inhale& _Other) = delete;
	Effect_Inhale& operator=(Effect_Inhale&& _Other) noexcept = delete;

protected:

private:

};
