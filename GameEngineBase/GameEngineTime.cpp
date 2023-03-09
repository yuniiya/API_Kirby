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
	// ������� �� ī��Ʈ
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&PrevCount_));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));
	// ���� ī��Ʈ���� ���� �� ������ �̸�ŭ�� ���ڴ�
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&SecondCount_));

	// ���� �� �ٽ� ���
	Update();
}

void GameEngineTime::Update()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));
	RealDeltaTime_ = (static_cast<double>(CurrentCount_) - static_cast<double>(PrevCount_)) / static_cast<double>(SecondCount_);
	PrevCount_ = CurrentCount_;
	DeltaTime_ = static_cast<float>(RealDeltaTime_);
}
