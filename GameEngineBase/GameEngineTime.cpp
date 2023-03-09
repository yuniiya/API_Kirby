#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime* GameEngineTime::Inst_ = new GameEngineTime();

GameEngineTime::GameEngineTime()
	: SecondCount_()
	, CurrentCount_()
	, PrevCount_()
	, DeltaTime_(0.f)
	, RealDeltaTime_(0.f)
{

}
GameEngineTime::~GameEngineTime()
{

}

void GameEngineTime::Reset()
{
	// 현재까지 센 카운트
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&PrevCount_));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));
	// 현재 카운트에서 리셋 후 언제나 이만큼만 세겠다
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&SecondCount_));

	// 리셋 후 다시 계산
	Update();
}

void GameEngineTime::Update()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));
	RealDeltaTime_ = (static_cast<double>(CurrentCount_) - static_cast<double>(PrevCount_)) / static_cast<double>(SecondCount_);
	PrevCount_ = CurrentCount_;
	DeltaTime_ = static_cast<float>(RealDeltaTime_);
}
