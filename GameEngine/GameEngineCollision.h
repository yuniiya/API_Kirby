#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
#include <map>
#include <vector>

class GameEngineImage;
class GameEngineCollision : public GameEngineActorSubObject
{
	friend GameEngineActor;
	
public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	inline void SetPivot(const float4& _Pos)
	{
		Pivot_ = _Pos;
	}

	inline void SetScale(const float4& _Scale)
	{
		Scale_ = _Scale;
	}

	// 엑터 좌표를 기준으로 설정한 충돌체의 진짜 위치
	inline float4 GetCollisionPos()
	{
		return GetActor()->GetPosition() + Pivot_;
	}

	// 사각형 충돌체 좌표
	inline GameEngineRect GetRect()
	{
		return GameEngineRect(GetActor()->GetPosition() + Pivot_, Scale_);
	}

	// 충돌한 대상이 있는지 체크 -> 존재하면 true 
	bool CollisionCheck(
		const std::string& _TargetGroup,
		CollisionType _This = CollisionType::Circle,
		CollisionType _Target = CollisionType::Circle
	);

	// 충돌했다 = true -> 파괴
	bool CollisionResult(
		const std::string& _TargetGroup,
		std::vector<GameEngineCollision*>& _ColResult,	// 넣어준 값으로 충돌체 리스트(vector) 채워서 줄게
		CollisionType _This = CollisionType::Circle,
		CollisionType _Target = CollisionType::Circle
	);

	void DebugRender();

private:
	friend class FrameAnimation;

	// 엑터의 중심에서 Pivot만큼 떨어진 위치를 중심으로 충돌체를 그린다
	float4 Pivot_;
	float4 Scale_;

};
