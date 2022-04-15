#include "GameEngine.h"
#include "GameEngineBase/GameEngineWindow.h"
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSound.h>

// static변수니까 초기화 필요 
std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
GameEngineLevel* GameEngine::NextLevel_ = nullptr;
GameEngine* GameEngine::UserContents_ = nullptr;
GameEngineImage* GameEngine::BackBufferImage_ = nullptr;
GameEngineImage* GameEngine::WindowMainImage_ = nullptr;


GameEngine::GameEngine()
{

}
GameEngine::~GameEngine()
{
}

HDC GameEngine::BackBufferDC()
{
    return BackBufferImage_->ImageDC();
}

void GameEngine::GameInit()
{
}

void GameEngine::GameLoop()
{
}

void GameEngine::GameEnd()
{
}

void GameEngine::WindowCreate()
{
    // 윈도우가 만들어지면서 윈도우 크기만한 HBITMAP이 만들어진다 -> 윈도우에서 보게되는 비트맵
    GameEngineWindow::GetInst().CreateGameWindow(nullptr, "Kirby"); 
    GameEngineWindow::GetInst().ShowGameWindow();
    GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}

void GameEngine::EngineInit()
{
    // 윈도우가 만들어져야 윈도우의 크기를 기반으로 동일한 크기의 백 버퍼를 만들 수 있는데
    // 여기서 윈도우 크기가 결정된다
    UserContents_->GameInit();

    
    WindowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMain", GameEngineWindow::GetHDC());
  
    // 백버퍼 생성
    BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());
}

void GameEngine::EngineLoop()
{
    GameEngineTime::GetInst()->Update();

    // 1. 엔진수준에서 매 프레임마다 체크 
    UserContents_->GameLoop();

    // 다음 레벨이 있다
    if (nullptr != NextLevel_)
    {
        // 현재 레벨이 있으면 -> 현재 레벨 End
        if (nullptr != CurrentLevel_)
        {
            CurrentLevel_->ActorLevelChangeEnd();
            CurrentLevel_->LevelChangeEnd();
        }
        
        // 현재 레벨 = 다음 레벨이 된다
        CurrentLevel_ = NextLevel_;

        // 다음 레벨(현재 레벨)이 있으면 -> 다음 레벨 Start
        if (nullptr != CurrentLevel_)
        {
            CurrentLevel_->LevelChangeStart();
            CurrentLevel_->ActorLevelChangeStart();
        }

        NextLevel_ = nullptr;

        // 레벨 로딩이 끝난 후를 0으로 보고 그 때 부터 시간 체크
        GameEngineTime::GetInst()->Reset();

        Rectangle(WindowMainImage_->ImageDC(), 0, 0, WindowMainImage_->GetScale().ix(), WindowMainImage_->GetScale().iy());
        Rectangle(BackBufferImage_->ImageDC(), 0, 0, BackBufferImage_->GetScale().ix(), BackBufferImage_->GetScale().iy());
    }

    if (nullptr == CurrentLevel_)
    {
        MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
    }


    GameEngineSound::Update();
    // 모든애들 업데이트 전에 Key업데이트
    GameEngineInput::GetInst()->Update(GameEngineTime::GetInst()->GetDeltaTime());

    // 2. 레벨 수준에서 체크 
    CurrentLevel_->Update();
    CurrentLevel_->ActorUpdate();
    CurrentLevel_->ActorRender();

    // 콜리전 
    //CurrentLevel_->CollisionDebugRender(); 

    // 백 버퍼 이미지를 메인 윈도우로 복사
    WindowMainImage_->BitCopy(BackBufferImage_);

    // Death있는지 체크하고 삭제 
    CurrentLevel_->ActorRelease();
}

void GameEngine::EngineEnd()
{
    UserContents_->GameEnd();

    std::map<std::string, GameEngineLevel*>::iterator StartIter = AllLevel_.begin();
    std::map<std::string, GameEngineLevel*>::iterator EndIter = AllLevel_.end();

    for (; StartIter != EndIter; ++StartIter)
    {
        if (nullptr == StartIter->second)
        {
            continue;
        }
        
        delete StartIter->second;
    }

    GameEngineSound::AllResourcesDestroy();
    GameEngineImageManager::Destroy();

    GameEngineInput::Destroy();
    GameEngineTime::Destroy();
    GameEngineWindow::Destroy();
}


void GameEngine::ChangeLevel(const std::string& _Name)
{
    // ChangeLevel에서 해당 레벨있는지 조사 후, 있으면 NextLevel로 지정된다
    // -> 한 번 루프 도는 동안 현재 레벨은 유지되어야 하기 때문
    std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Name);

    if (AllLevel_.end() == FindIter)
    {
        MsgBoxAssert("Level Find Error");
        return;
    }

    NextLevel_ = FindIter->second;
}
