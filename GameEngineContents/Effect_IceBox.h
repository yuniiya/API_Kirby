#pragma once
class Effect_IceBox
{
public:
	// constrcuter destructer
	Effect_IceBox();
	~Effect_IceBox();

	// delete Function
	Effect_IceBox(const Effect_IceBox& _Other) = delete;
	Effect_IceBox(Effect_IceBox&& _Other) noexcept = delete;
	Effect_IceBox& operator=(const Effect_IceBox& _Other) = delete;
	Effect_IceBox& operator=(Effect_IceBox&& _Other) noexcept = delete;

protected:

private:

};
