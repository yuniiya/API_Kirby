#include "Windows.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/Kirby.h>

//Kirby kirby;
//
//// �ؽ��� �� ������Ʈ �ε�, �غ�
//void GameInit()
//{
//    kirby.GameInit();
//}
//
//// ���� ����
//void GameLoop()
//{
//    kirby.GameLoop();
//}

int __stdcall WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ char* lpCmdLine,                // ���� �Ķ���� : ���ڸ� �����ؼ� �ȿ� ���ڸ� ä�� �� �ִ� 
    _In_ int       nCmdShow)
{
    // �޸� �� üũ 
    //GameEngineDebug::LeakCheckOn();

    //// ���μ��� ������ �޸� ���� 
    //GameEngineWindow::Destroy();

    //kirby.GameEnd();

    GameEngine::Start<Kirby>();
}

