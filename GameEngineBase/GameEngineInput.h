#pragma once
#include <Windows.h>
#include <map>
#include <string>

class GameEngineInput
{
private:

	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down_; // 최초로 키를 눌렀을때
		bool Press_; // 계속 누르는중
		bool Up_; // 막 뗐을때
		bool Free_; // 안누르고 있을때.

		float Time_;
		int Key_; // 이키가 눌렸다면,, 

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key_);
		}

		void Update(float _DeltaTime);

		void Reset()
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}

		// 생성자 주석걸어두기
		//GameEngineKey(int _Key) 
		//	: Key_(_Key)
		//	, Down_(false)
		//	, Press_(false)
		//	, Up_(false)
		//	, Free_(true)
		//{
		//}
	};

private:
	static GameEngineInput* Inst_;

public:
	static GameEngineInput* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

public:
	// time을 외부에서 따로 받아서 사용하도록 해서 EngineTime에 종속되지 않도록 함
	// 0.0f = 기본값 (시간을 안 넣으면 0)
	void Update(float _DeltaTime = 0.0f);
	void CreateKey(const std::string& _Name, int _Key);

	float GetTime(const std::string& _Name);	// 이 키가 얼마동안 눌렸는지 
	bool IsDown(const std::string& _Name);
	bool IsUp(const std::string& _Name);
	bool IsPress(const std::string& _Name);
	bool IsFree(const std::string& _Name);
	bool IsKey(const std::string& _Name);

protected:

private:
	std::map<std::string, GameEngineKey> AllInputKey_;

	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;
};

