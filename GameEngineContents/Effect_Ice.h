#pragma once
class Effect_Ice
{
public:
	// constrcuter destructer
	Effect_Ice();
	~Effect_Ice();

	// delete Function
	Effect_Ice(const Effect_Ice& _Other) = delete;
	Effect_Ice(Effect_Ice&& _Other) noexcept = delete;
	Effect_Ice& operator=(const Effect_Ice& _Other) = delete;
	Effect_Ice& operator=(Effect_Ice&& _Other) noexcept = delete;

protected:

private:

};
