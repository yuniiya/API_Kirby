#pragma once
#include <string>

// �� Ŭ������ Actor�� ���ڿ��� ���� ���� ���� Actor�� �̸��� �����ִ� ����
class GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineNameObject();
	~GameEngineNameObject();

	// delete Function
	GameEngineNameObject(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject(GameEngineNameObject&& _Other) noexcept = delete;
	GameEngineNameObject& operator=(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject& operator=(GameEngineNameObject&& _Other) noexcept = delete;

	// ���� ��� �Ƴ��� ���� const &
	inline void SetName(const std::string& _Name)
	{
		Name_ = _Name;
	}

	// �ܺη� ������Ʈ �̸� ����
	std::string GetNameCopy()
	{
		return Name_;
	}

	// �Ʒ� �� �� ���� string�� �״�� ����Ǵ°� ���� �� ���
	const std::string& GetNameConstRef()
	{
		return Name_;
	}

	const char* GetNameConstPtr()
	{
		return Name_.c_str();
	}

protected:

private:
	std::string Name_;

};
