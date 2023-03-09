#pragma once
#include <string>

// 이 클래스는 Actor를 문자열로 구분 짓기 위해 Actor에 이름을 지어주는 역할
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

	// 복사 비용 아끼기 위해 const &
	inline void SetName(const std::string& _Name)
	{
		Name_ = _Name;
	}

	// 외부로 오브젝트 이름 복사
	std::string GetNameCopy()
	{
		return Name_;
	}

	// 아래 쪽 두 개는 string이 그대로 복사되는게 싫을 떄 사용
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
