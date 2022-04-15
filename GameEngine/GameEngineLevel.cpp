#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCollision.h"
#include "GameEngineRenderer.h"
#include <GameEngineBase/GameEngineDebug.h>


GameEngineLevel::GameEngineLevel()
	: CameraPos_(float4::ZERO)
{

}
GameEngineLevel::~GameEngineLevel()
{
	// Level에서 Actor를 생성헀으니까 삭제도 Level에서
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		// list삭제
		std::list<GameEngineActor*>& Group = GroupStart->second;

		std::list<GameEngineActor*>::iterator StartActor = Group.begin();
		std::list<GameEngineActor*>::iterator EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			if (nullptr == (*StartActor))
			{
				continue;
			}
			delete (*StartActor);
			(*StartActor) = nullptr;
		}
	}
}

void GameEngineLevel::ActorUpdate()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;


	GroupStart = AllActor_.begin();
	GroupEnd = AllActor_.end();

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			(*StartActor)->ReleaseUpdate();
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}

			(*StartActor)->Update();
		}
	}
}

void GameEngineLevel::ActorLevelChangeStart() {

	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;

		GroupStart = AllActor_.begin();
		GroupEnd = AllActor_.end();

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			StartActor = Group.begin();
			EndActor = Group.end();


			for (; StartActor != EndActor; ++StartActor)
			{
				if (false == (*StartActor)->IsUpdate())
				{
					continue;
				}

				(*StartActor)->LevelChangeStart();
			}
		}
	}
}

GameEngineActor* GameEngineLevel::FindActor(const std::string& _Name)
{
	std::map<std::string, GameEngineActor*>::iterator FindIter = RegistActor_.find(_Name);

	if (RegistActor_.end() == FindIter)
	{
		return nullptr;
	}

	return FindIter->second;
}

void GameEngineLevel::RegistActor(const std::string& _Name, GameEngineActor* _Actor)
{
	if (RegistActor_.end() != RegistActor_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 이름으로 또 등록하려고 했습니다.");
	}

	RegistActor_.insert(std::map<std::string, GameEngineActor*>::value_type(_Name, _Actor));
}

void GameEngineLevel::ActorLevelChangeEnd() {
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;

		GroupStart = AllActor_.begin();
		GroupEnd = AllActor_.end();

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			StartActor = Group.begin();
			EndActor = Group.end();


			for (; StartActor != EndActor; ++StartActor)
			{
				if (false == (*StartActor)->IsUpdate())
				{
					continue;
				}

				(*StartActor)->LevelChangeEnd();
			}
		}
	}
}


void GameEngineLevel::ActorRender()
{
	// 랜더러 랜더
	{
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStart = AllRenderer_.begin();
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEnd = AllRenderer_.end();

		std::list<GameEngineRenderer*>::iterator StartRenderer;
		std::list<GameEngineRenderer*>::iterator EndRenderer;

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineRenderer*>& Group = GroupStart->second;
			StartRenderer = Group.begin();
			EndRenderer = Group.end();
			for (; StartRenderer != EndRenderer; ++StartRenderer)
			{
				if (false == (*StartRenderer)->IsUpdate())
				{
					continue;
				}

				(*StartRenderer)->Render();
			}
		}
	}

	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;

		GroupStart = AllActor_.begin();
		GroupEnd = AllActor_.end();

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			StartActor = Group.begin();
			EndActor = Group.end();


			for (; StartActor != EndActor; ++StartActor)
			{
				if (false == (*StartActor)->IsUpdate())
				{
					continue;
				}

				(*StartActor)->Render();
			}
		}
	}
}

void GameEngineLevel::CollisionDebugRender()
{
	std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupStart = AllCollision_.begin();
	std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupEnd = AllCollision_.end();

	std::list<GameEngineCollision*>::iterator StartCollision;
	std::list<GameEngineCollision*>::iterator EndCollision;

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineCollision*>& Group = GroupStart->second;
		StartCollision = Group.begin();
		EndCollision = Group.end();
		for (; StartCollision != EndCollision; ++StartCollision)
		{
			if (false == (*StartCollision)->IsUpdate())
			{
				continue;
			}

			(*StartCollision)->DebugRender();
		}
	}

}



void GameEngineLevel::ActorRelease()
{
	{
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStart = AllRenderer_.begin();
		std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEnd = AllRenderer_.end();

		std::list<GameEngineRenderer*>::iterator StartRenderer;
		std::list<GameEngineRenderer*>::iterator EndRenderer;


		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineRenderer*>& Group = GroupStart->second;
			StartRenderer = Group.begin();
			EndRenderer = Group.end();
			for (; StartRenderer != EndRenderer; )
			{
				if (false == (*StartRenderer)->IsDeath())
				{
					++StartRenderer;
					continue;
				}

				StartRenderer = Group.erase(StartRenderer);
			}
		}
	}

	// 콜리전은 레벨에서도 관리하고 있으므로 파괴된 콜리전있는지 먼저 체크
	{
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupStart = AllCollision_.begin();
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupEnd = AllCollision_.end();

		std::list<GameEngineCollision*>::iterator StartCollision;
		std::list<GameEngineCollision*>::iterator EndCollision;


		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineCollision*>& Group = GroupStart->second;
			StartCollision = Group.begin();
			EndCollision = Group.end();
			for (; StartCollision != EndCollision; )
			{
				// 죽은 애가 아니면 -> 넘어간다
				if (false == (*StartCollision)->IsDeath())
				{
					++StartCollision;
					continue;
				}

				// 죽은 애다 -> 콜리전 그룹에서 삭제 (delete는 엑터의 몫)
				StartCollision = Group.erase(StartCollision);
			}
		}

	}

	// 액터의 삭제
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;

		GroupStart = AllActor_.begin();
		GroupEnd = AllActor_.end();

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			StartActor = Group.begin();
			EndActor = Group.end();
			for (; StartActor != EndActor; )
			{
				if (true == (*StartActor)->IsDeath())
				{
					delete* StartActor;
					StartActor = Group.erase(StartActor);
					continue;
				}

				// 엑터가 살아있다 -> 파괴된 콜리전/렌더러가 있는지 Release로 체크
				// 삭제가 안됐다면 콜리전이나 랜더러를 확인해본다.
				(*StartActor)->Release();

				++StartActor;
			}
		}
	}

}

void GameEngineLevel::AddRenderer(GameEngineRenderer* _Renderer)
{
	// 찾아서 없으면 만드는 것까지.
	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}


void GameEngineLevel::ChangeUpdateOrder(GameEngineActor* _Actor, int _NewOreder)
{
	if (_Actor->GetOrder() == _NewOreder)
	{
		return;
	}
	ChangeOrderList.push_back({ _Actor ,_NewOreder });
}

void GameEngineLevel::ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder)
{
	AllRenderer_[_Renderer->GetOrder()].remove(_Renderer);

	// Order초기화 
	_Renderer->GameEngineUpdateObject::SetOrder(_NewOrder);

	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);

}

void GameEngineLevel::AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision)
{
	// 찾아서 없으면 만드는 것까지
	AllCollision_[_GroupName].push_back(_Collision);
}
