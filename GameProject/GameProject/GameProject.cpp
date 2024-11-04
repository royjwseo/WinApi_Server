// GameProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "GameProject.h"

#define MAX_LOADSTRING 100

int mousePosX;
int mousePosY;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
   // UNREFERENCED_PARAMETER(hPrevInstance);
   // UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
   ::LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
   ::LoadStringW(hInstance, IDC_GAMEPROJECT, szWindowClass, MAX_LOADSTRING);
   
    //1) 윈도우 창 정보 등록(중요 함수)
    MyRegisterClass(hInstance);

    //2) 윈도우 창 생성
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

   // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEPROJECT));
    //단축키로 무언가 제어하는 기능을 없앰 1
    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
       /* if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            //단축키로 무언가 제어하는 기능을 없앰 1
        }*/
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//  
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc; //이벤트 처리를 해당 함수로 해달라는 등록
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = nullptr;// MAKEINTRESOURCEW(IDC_GAMEPROJECT);
    wcex.lpszClassName = L"GameProject";//szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
} // 윈도우 창에 대한 정보를 기입 후 등록하는 단계

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

#define MY_FRAME_BUFFER_WIDTH  800
#define MY_FRAME_BUFFER_HEIGHT 600

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT windowRect = { 0,0,MY_FRAME_BUFFER_WIDTH,MY_FRAME_BUFFER_HEIGHT };
   ::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW,false);

   HWND hWnd = CreateWindowW(L"GameProject", L"Client", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, windowRect.right-windowRect.left, windowRect.bottom-windowRect.top, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: //해당 영역은 윈도우 프로그램 특성상 특정 I/O가 있을 때만 갱신되어 게임과 맞지 않는다. 나중에 바꿔줄것임.
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            //H로 시작하는 윈도우 변수들은 int를 가지고 있는 구조체 형태로 , 운영체제와 상호작용을 위해 커널이
            // 해당 윈도우 창에 대한 식별번호를 알기 위한 핸들을 관리하기 위해 부여받은  int값
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            
            //문자 그리기
            WCHAR buffer[100];
            ::wsprintf(buffer, L"(%d,%d)", mousePosX, mousePosY);
            ::TextOut(hdc, 100, 100, buffer, ::wcslen(buffer));

          // ::TextOut(hdc,100,100,L"TEST",4);

            // 사각형 그리기
            ::Rectangle(hdc, 200, 200, 400, 400);

            //원 그리기
            ::Ellipse(hdc, 200, 200, 400, 400);

            //선
            ::MoveToEx(hdc, 300, 300, nullptr);
            ::LineTo(hdc, 400, 400);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_SIZE:
        break;
    case WM_LBUTTONDOWN:
        break;
    case WM_LBUTTONUP:
        break;
    case WM_RBUTTONDOWN:
        break;
    case WM_RBUTTONUP:
        break;
    case WM_MOUSEMOVE:

        
        // 각각 정수를 받아오는데 아래와 같은 방법으로 구함
        // 마우스 좌표를 16비트 즉 2바이트에 걸쳐 반 기준 아래는 x좌표 저장, 위는 y좌표 저장
        // 그렇게 저장된 값을 빼오는 공식을 매크로로 LOWORD, HIWORD를 통해 가져옴
        // lParam & 0xFFFF;
        // lParam >> 16

        mousePosX=LOWORD(lParam);
        mousePosY=HIWORD(lParam);
        ::InvalidateRect(hWnd, nullptr, TRUE);//이전 내용을 지우고 PAINT를 호출해라.

        break;
    case WM_KEYDOWN:
        break;
    case WM_KEYUP:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
