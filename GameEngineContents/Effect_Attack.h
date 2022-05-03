#pragma once
class Effect_Attack
{
public:
	// constrcuter destructer
	Effect_Attack();
	~Effect_Attack();

	// delete Function
	Effect_Attack(const Effect_Attack& _Other) = delete;
	Effect_Attack(Effect_Attack&& _Other) noexcept = delete;
	Effect_Attack& operator=(const Effect_Attack& _Other) = delete;
	Effect_Attack& operator=(Effect_Attack&& _Other) noexcept = delete;

protected:

private:

};
