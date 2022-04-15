#pragma once
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineEnum.h"
#include <list>

class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineActor : public GameEngineNameObject, public GameEngineUpdateObject
{
// ========================
// AcotrBase
// ========================
private:
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	inline GameEngineLevel* GetLevel()
	{
		return Level_;
	}

	// 카메라에 영향받은 위치 
	inline float4 GetCameraEffectPosition()
	{
		return Position_ - GetLevel()->GetCameraPos();
	}

	inline float4 GetPosition()
	{
		return Position_;
	}

	inline float4 GetScale()
	{
		return Scale_;
	}

	inline void SetMove(float4 _Value)
	{
		Position_ += _Value;
	}

	inline void SetPosition(float4 _Value)
	{
		Position_ = _Value;
	}

	inline void SetScale(float4 _Value)
	{
		Scale_ = _Value;
	}


protected:
	virtual void Start() = 0;
	virtual void Update() {}
	virtual void Render() {}

	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd() {}

	void Release();

	void DebugRectRender();

	void LevelRegist(std::string _RegistName = "");

private:
	GameEngineLevel* Level_;
	float4 Position_;
	float4 Scale_;
	
	// private로 둔 이유: 자식 프로젝트에서 Level을 재세팅할 수 없도록
	// -> Actor는 반드시 Level이 세팅되어 있는 상태에서 동작해야 한다 
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

// ========================
// Render
// ========================
public:
	// 센터에서 그린다 (PivotPos: 그린 뒤 수정 값)
	// 이미지가 없어도 렌더링 가능
	GameEngineRenderer* CreateRenderer(int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER, const float4 & _PivotPos = {0,0});

	// 가장 빠를겁니다.
	// 디폴트 인자는 선언에서만 지정 가능합니다.
	GameEngineRenderer* CreateRenderer(const std::string& _Image, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = {0,0});

	GameEngineRenderer* CreateRendererToScale(const std::string& _Image, const float4& _Scale, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX) ,RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });

private:
	// list내부 렌더링될 이미지 리스트 순회
	std::list<GameEngineRenderer*>::iterator StartRenderIter;
	std::list<GameEngineRenderer*>::iterator EndRenderIter;

	std::list<GameEngineRenderer*> RenderList_;


	////////////////////////////////////////////////////////// Collision

public:
	GameEngineCollision* CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot = { 0, 0 });

private:
	// 이터레이터
	std::list<GameEngineCollision*> CollisionList_;
};


