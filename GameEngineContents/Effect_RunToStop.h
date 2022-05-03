#pragma once
class Effect_RunToStop
{
public:
	// constrcuter destructer
	Effect_RunToStop();
	~Effect_RunToStop();

	// delete Function
	Effect_RunToStop(const Effect_RunToStop& _Other) = delete;
	Effect_RunToStop(Effect_RunToStop&& _Other) noexcept = delete;
	Effect_RunToStop& operator=(const Effect_RunToStop& _Other) = delete;
	Effect_RunToStop& operator=(Effect_RunToStop&& _Other) noexcept = delete;

protected:

private:

};
