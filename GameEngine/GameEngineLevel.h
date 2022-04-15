#pragma once
#include <list>
#include <map>
#include <vector>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineActor;
struct ChangeOrderItem
{
	GameEngineActor* TargetObject; // 이녀석을
	int ChangeOrder; // 이렇게 바꿔라.
};


class GameEngine;
class GameEngineActor;
class GameEngineCollision;
class GameEngineRenderer;
class GameEngineLevel : public GameEngineNameObject
{
	// 엔진끼리는 서로 알아도 상관 없다
	friend GameEngine;
	friend GameEngineActor;
	friend GameEngineCollision;
	friend GameEngineRenderer;

public:
	// constrcuter destructer
	GameEngineLevel();
	// 
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0, const std::string& _Name = "")
	{
		// Actor가 몇 개가 있을지 미리 알 수 없으니까 동적할당
		ActorType* NewActor = new ActorType();
		// Actor를 Start하기 위해 Actor로 업캐스팅 필요
		GameEngineActor* StartActor = NewActor;
		NewActor->SetOrder(_Order);
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);

		StartActor->Start();

		// AllActor에서 _Order를 find후 없으면 새로 만들어서 insert
		// 새로운 Actor를 list에 넣어준다 
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		return NewActor;
	}

	inline float4 GetCameraPos()
	{
		return CameraPos_;
	}

	inline void MoveCameraPos(const float4& _Value)
	{
		CameraPos_ += _Value;
	}

	inline void SetCameraPos(const float4& _Value)
	{
		CameraPos_ = _Value;
	}

	template<typename ConvertType>
	ConvertType* FindActor(const std::string& _Name)
	{
		return dynamic_cast<ConvertType*>(FindActor(_Name));
	}

	GameEngineActor* FindActor(const std::string& _Name);

	void RegistActor(const std::string& _Name, GameEngineActor* _Actor);


protected:
	// 시점 함수
	// 만들어지면서 리소스나 액터를 만들때 써라
	virtual void Loading() = 0;
	// 이 레벨이 현재 레벨일때 해야할일을 실행한다.
	virtual void Update() = 0;

	// 추상화되지 않았기 때문에 내용이 없어도 구현부 필요 
	// Start: 현재 레벨->다음 레벨로 이전할 때 현재 레벨이 실행하는 함수
	// End : 현재 레벨->다음 레벨로 이전할 때 이전 레벨이 실행하는 함수
	void ActorLevelChangeStart();
	virtual void LevelChangeStart() {}

	void ActorLevelChangeEnd();
	virtual void LevelChangeEnd() {}

private:
	// 모든 Actor는 map으로 관리 
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	std::map<std::string, GameEngineActor*> RegistActor_;

	std::vector<ChangeOrderItem> ChangeOrderList;

	float4 CameraPos_;

	void ActorUpdate();
	void ActorRender();
	void CollisionDebugRender();
	void ActorRelease();

private:
	std::map<int, std::list<GameEngineRenderer*>> AllRenderer_;

	void AddRenderer(GameEngineRenderer* _Renderer);

	void ChangeUpdateOrder(GameEngineActor* _Actor, int _Oreder);

	void ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder);

private:
	// 삭제는 액터가 하지만 실제 사용은 Level
	// 여기서 함부로 GameEngineCollision*을 delete 하는 일이 있으면 안된다
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision);
};
