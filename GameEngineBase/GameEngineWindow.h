#pragma once
#include <Windows.h>
#include <string>
#include "GameEngineMath.h"
#include "GameEngineDebug.h"

class GameEngineWindow
{
private:
	// static -> 데이터 영역에 메모리가 올라가니까 일반 지역변수와 달리 계속 살아 있는다
	// 따라서 함수 내에서 호출될 경우, 함수가 호출될 때 마다 초기화되지 않고 데이터를 계속 쌓을 수 있다 
	static GameEngineWindow* Inst_;

public:
	// staitc 함수 : 특정 객체에 종속되지 않고 클래스 자체와 연관이 있는 함수
	// staitc 변수만 사용할 수 있다 (클래스의 멤버 변수는 특정 객체에 종속되어있기 때문에)
	inline static GameEngineWindow& GetInst()
	{
		return *Inst_;
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
	void RegClass(HINSTANCE _hInst);
	void CreateGameWindow(HINSTANCE _hInst, const std::string& _Title);
	void ShowGameWindow();
	void MessageLoop(void(_InitFunction)(), void(*_LoopFunction)());

	void SetWindowScaleAndPosition(float4 _Pos, float4 _Scale);

	void Off();

	static inline HDC GetHDC()
	{
		return Inst_->HDC_;
	}

	static inline float4 GetScale()
	{
		return Inst_->Scale_;
	}

protected:

private:
	std::string Title_;
	bool WindowOn_;
	HINSTANCE hInst_;
	HWND hWnd_;
	HDC HDC_;
	float4 Scale_;
	

	// constrcuter destructer
	// 싱글톤 --> 생성자를 private으로 
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

};

