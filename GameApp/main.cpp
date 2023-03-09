#include "Windows.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/Kirby.h>

//Kirby kirby;
//
//// 텍스쳐 및 오브젝트 로딩, 준비
//void GameInit()
//{
//    kirby.GameInit();
//}
//
//// 게임 실행
//void GameLoop()
//{
//    kirby.GameLoop();
//}

int __stdcall WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ char* lpCmdLine,                // 메인 파라미터 : 문자를 전달해서 안에 문자를 채울 수 있다 
    _In_ int       nCmdShow)
{
    // 메모리 릭 체크 
    //GameEngineDebug::LeakCheckOn();

    //// 프로세스 끝나면 메모리 해제 
    //GameEngineWindow::Destroy();

    //kirby.GameEnd();

    GameEngine::Start<Kirby>();
}

