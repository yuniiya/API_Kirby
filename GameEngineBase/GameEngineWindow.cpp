#include "GameEngineWindow.h"
#include "GameEngineDebug.h"

// 필요하기 때문에 전역변수로 
// (조작할 윈도우의 핸들, 메세지, )
LRESULT CALLBACK MessageProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        // 윈도우를 종료하고 모든 
        GameEngineWindow::GetInst().Off();
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_CLOSE:
    {
        GameEngineWindow::GetInst().Off();
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();
// 시작하자마자 만들고 리턴 

GameEngineWindow::GameEngineWindow()
    : hInst_(nullptr)   // 프로세스
    , hWnd_(nullptr)    // 윈도우
    , WindowOn_(true)
    , HDC_(nullptr)
    , Scale_{}
{
}

GameEngineWindow::~GameEngineWindow()
{
    // 핸들은 사용했으면 해제해줘야 한다
    if (nullptr != HDC_)
    {
        ReleaseDC(hWnd_, HDC_);
        HDC_ = nullptr;
    }

    if (nullptr != hWnd_)
    {
        DestroyWindow(hWnd_);
        hWnd_ = nullptr;
    }
}

void GameEngineWindow::Off()
{
    WindowOn_ = false;
}

void GameEngineWindow::RegClass(HINSTANCE _hInst)
{
    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MessageProcess;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;                         // 외부에서 인자로 받아와서 사용 
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowClass";
    wcex.hIconSm = nullptr;

    RegisterClassExA(&wcex);
}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string& _Title)
{
    // 방어 코드 -> 프로세스 핸들이 이미 있으면 리턴  
    if (nullptr != hInst_)
    {
        MsgBoxAssert("윈도우를 2번 띄우려고 했습니다");
        return;
    }

    Title_ = _Title;

    // 프로세스 등록은 한 번만 실행 (클래스)
    hInst_ = _hInst;
    RegClass(_hInst);

    // 윈도우 생성 (객체)
    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", Title_.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    HDC_ = GetDC(hWnd_);

    if (!hWnd_)
    {
        return;
    }
}

// 윈도우 띄워주는 부분
void GameEngineWindow::ShowGameWindow()
{
    // 방어 코드 -> 윈도우 핸들이 비어있으면 리턴 
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("메인 윈도우가 만들어지지 않았습니다. 화면에 출력할 수 없습니다. ");
        return;
    }

    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}

// 메세지를 기다리며 윈도우 유지
// main쪽의 GameLoop함수가 전달될 곳 
void GameEngineWindow::MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)())
{
    // 여기까지 들어왔다면 윈도우는 준비된 상황
    // 루프를 돌기 전 준비할게 있다면 _Init으로 준비해달라
    if (nullptr != _InitFunction)
    {
        _InitFunction();
    }

    MSG msg;


    while (WindowOn_)
    {
        if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // 윈도우 메세지를 처리한 뒤 게임로직이 처리된다
        if (nullptr == _LoopFunction)
        {
            continue;
            // 아래 쪽의_LoopFunction; 구문 실행되지 않고 넘어감 
        }

        _LoopFunction();
    }
}

void GameEngineWindow::SetWindowScaleAndPosition(float4 _Pos, float4 _Scale)
{
    // 윈도우 작업영역 -> EngineWindow에서 크기를 float으로 했으니까 int형변환해서 사용
    RECT Rc = { 0, 0, _Scale.ix(), _Scale.iy() };

    // 메뉴바를 제외한 윈도우의 작업영역 크기를 얻어온다
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    Scale_ = _Scale;

    // 얻어온 작업영역의 크기를 기반으로 윈도우 사이즈를 설정한다 
    SetWindowPos(hWnd_, nullptr
        , _Pos.ix(), _Pos.iy()
        , Rc.right - Rc.left
        , Rc.bottom - Rc.top        // y는 위로 갈수록 작아지니까 B - T
        , SWP_NOZORDER);
}

