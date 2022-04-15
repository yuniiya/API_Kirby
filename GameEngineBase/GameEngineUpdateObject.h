#pragma once
#include <string>
#include "GameEngineTime.h"


class GameEngineUpdateObject
{
public:
	// constrcuter destructer
	GameEngineUpdateObject();
	~GameEngineUpdateObject();

	// delete Function
	GameEngineUpdateObject(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject(GameEngineUpdateObject&& _Other) noexcept = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject& operator=(GameEngineUpdateObject&& _Other) noexcept = delete;


	inline void On()
	{
		IsUpdate_ = true;
	}

	inline void Off()
	{
		IsUpdate_ = false;
	}

	// 살아있는 애만 업데이트 
	inline virtual bool IsUpdate()
	{
		return IsUpdate_ && false == IsDeath_;
	}

	inline virtual bool IsDeath()
	{
		return IsDeath_;
	}

	inline void Death()
	{
		IsDeath_ = true;
	}

	// Death의 시간을 정해줬을 때만 유효하게 도는 업데이트
	void ReleaseUpdate()
	{
		if (false == IsReleaseUpdate_)
		{
			return;
		}

		DeathTime_ -= GameEngineTime::GetDeltaTime();

		if (0.0f >= DeathTime_)
		{
			IsDeath_ = true;
		}
	}

	inline void Death(float _Time)
	{
		IsReleaseUpdate_ = true;
		DeathTime_ = _Time;
	}

	inline int GetOrder()
	{
		return Order_;
	}

	// 렌더러 만들 때 Order초기화
	virtual inline void SetOrder(int _Order)
	{
		Order_ = _Order;
	}


private:
	int Order_;
	bool IsReleaseUpdate_;
	float DeathTime_;

	bool IsUpdate_;
	bool IsDeath_;

};