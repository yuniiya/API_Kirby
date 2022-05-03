#pragma once
class Effect_Exhale
{
public:
	// constrcuter destructer
	Effect_Exhale();
	~Effect_Exhale();

	// delete Function
	Effect_Exhale(const Effect_Exhale& _Other) = delete;
	Effect_Exhale(Effect_Exhale&& _Other) noexcept = delete;
	Effect_Exhale& operator=(const Effect_Exhale& _Other) = delete;
	Effect_Exhale& operator=(Effect_Exhale&& _Other) noexcept = delete;

protected:

private:

};
