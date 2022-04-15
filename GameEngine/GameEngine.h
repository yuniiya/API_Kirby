#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>

class GameEngineImage;
// 전방선언 이유 -> Loading함수 protected로 남겨두고 + 동시에 여기서 쓰기 위해서 
class GameEngineLevel;
class GameEngine
{
public:
	// constrcuter destructer
	GameEngine();
	~GameEngine();

	// delete Function
	GameEngine(const GameEngine& _Other) = delete;
	GameEngine(GameEngine&& _Other) noexcept = delete;
	GameEngine& operator=(const GameEngine& _Other) = delete;
	GameEngine& operator=(GameEngine&& _Other) noexcept = delete;

	static inline GameEngineImage* BackBufferImage()
	{
		return BackBufferImage_;
	}

	static HDC BackBufferDC();

	// virtual : 가상함수 테이블 생성
	// = 0 : 상속받는 쪽에서 반드시 이 함수 만들어야 한다
	// 이 쪽 클래스는 이제 추상 클래스 -> 클래스를 묶는 역할
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;

	template<typename GameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		// 받은 게임을 기반으로 엔진이 만들어진다 
		GameType UserGame;
		UserContents_ = &UserGame;

		// 받아둔 엔진을 이용해서 윈도우 띄우기 (Init, Loop, End)
		WindowCreate();
		EngineEnd();
	}

	// 엔진 시작과 거의 동시에 만들어진다 -> 다른 곳에서 엔진을 편하게 쓰기 위한 함수 
	static GameEngine& GetInst()
	{
		// 엔진이 없다?
		if (nullptr == UserContents_)
		{
			MsgBoxAssert("GEngine ERROR Engine Is Not Start");
		}

		return *UserContents_;
	}

	void ChangeLevel(const std::string& _Name);

protected:
	template<typename LevelType>
	void CreateLevel(const std::string& _Name)
	{
		LevelType* NewLevel = new LevelType();
		NewLevel->SetName(_Name);
		GameEngineLevel* Level = NewLevel;	// 업캐스팅
		Level->Loading();					// Level단계의 Loading은 한 번만 
		AllLevel_.insert(std::make_pair(_Name, NewLevel));
	}

private:
	// 레벨을 map으로 관리 
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngine* UserContents_;

	static GameEngineImage* WindowMainImage_; // 진짜로 출력되는 이미지 
	static GameEngineImage* BackBufferImage_;	

	static void WindowCreate();
	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();
};
