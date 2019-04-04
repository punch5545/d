#include <Windows.h>
#include <string>
#include <vector>
#include "util.h"
using namespace std;

//LPSTR -> char*
//LPCSTR -> const char*
//LPWSTR -> wchar*
//LPCWSTR -> const wchar*
vector<prevShape> shapes;
LRESULT CALLBACK WndProc
(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
);

int APIENTRY WinMain
(
    HINSTANCE hInstance,
    HINSTANCE prevInstance,
    LPSTR lpszCmdParam,
    int nCmdShow
)
{
    WNDCLASS wndClass;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wndClass.hCursor = LoadIcon(hInstance, IDC_CROSS);
    wndClass.hIcon = LoadIcon(hInstance, IDI_ERROR);
    wndClass.hInstance = hInstance;
    wndClass.lpfnWndProc = static_cast<WNDPROC>(WndProc);
    wndClass.lpszClassName = L"FirstWindow";
    wndClass.lpszMenuName = nullptr;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wndClass);

    HWND hwnd = CreateWindow
    (
        L"FirstWindow",
        L"Hellow, Window",
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        1920,
        1080,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    ShowWindow(hwnd, nCmdShow);

    MSG message;
    ZeroMemory(&message, sizeof(MSG));

    //while (GetMessage(&message, 0, 0, 0))
    //{
    //    TranslateMessage(&message);
    //    DispatchMessage(&message);
    //}

    while (true)
    {
        if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT)
                break;

            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    DestroyWindow(hwnd);
    UnregisterClass(L"FirstWindow", hInstance);

    return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static POINT position;
    static POINT start;
    static POINT end;

	COLORREF black = RGB(0, 0, 0);

	static prevShape pShape;
	static ColorRGBA cBrush;
	static ColorRGBA cPen;
    static bool bClicked = false;
	static bool isBrush = false;
	static char selectPen = 0;
	static char penSize = 1;
	static char selectBrush;
	static char selectShape;
	static bool bBrush = true;

	bool isValied = true;
	isValied &= cBrush.Red >= 0;
	isValied &= cBrush.Red <= 255;
	isValied &= cBrush.Green >= 0;
	isValied &= cBrush.Green <= 255;
	isValied &= cBrush.Blue >= 0;
	isValied &= cBrush.Blue <= 255;

	PAINTSTRUCT ps;
	//Brush
	HBRUSH curBrush;
	HBRUSH oldBrush;

	HPEN curPen;
	HPEN oldPen;

    switch (message)
    {
	case WM_KEYDOWN:
		if (wParam == VK_ADD) // 펜 사이즈 Up
		{
			penSize++;
		}
		else if (wParam == VK_SUBTRACT) // 펜 사이즈 Down
		{
			penSize--;
		}
		else if (wParam == 0x31) // 1. 브러쉬 선택
		{ 
			if (isBrush)
			{
				if (selectBrush < 6)
					selectBrush++;
				else {
					selectBrush = 0;
					isBrush = false;
				}
			}
			else
				isBrush = true;
		}
		else if (wParam == 0x32)// 2. 펜 선택
		{ 
			if (selectPen < 4)
			{
				selectPen++;
				penSize = 1;
			}
			else
				selectPen = 0;
		}
		else if (wParam == 0x33)// 3. 도형 선택
		{ 
			if (selectShape < 3)
				selectShape++;
			else
				selectShape = 0;
		}
		else if (wParam == 0x34) // 4. 색상 변경할 것 선택 (브러쉬, 펜)
		{
			if (bBrush)
				bBrush = false;
			else
				bBrush = true;
		}
		if (wParam == VK_NUMPAD1) // Decrease Red
		{
			if (isValied)
			{
				if (bBrush)
					cBrush.Red--;
				else
					cPen.Red--;
			}
		}
		else if (wParam == VK_NUMPAD4) // Increase Red
		{
			if (isValied)
			{
				if (bBrush)
					cBrush.Red++;
				else
					cPen.Red++;
			}
		}

		if (wParam == VK_NUMPAD2)  // Decrease Green
		{
			if (isValied)
			{
				if (bBrush)
					cBrush.Green--;
				else
					cPen.Green--;
			}
		}
		else if (wParam == VK_NUMPAD5)  // Increase Green
		{
			if (isValied)
			{
				if (bBrush)
					cBrush.Green++;
				else
					cPen.Green++;
			}
		}

		if (wParam == VK_NUMPAD3) // Decrease Blue
		{
			if (isValied)
			{
				if (bBrush)
					cBrush.Blue--;
				else
					cPen.Blue--;
			}
		}
		else if (wParam == VK_NUMPAD6) // Increase Blue
		{
			if (isValied)
			{
				if (bBrush)
					cBrush.Blue++;
				else
					cPen.Blue++;
			}
		}
		break;
#pragma region 메세지박스
    //case WM_LBUTTONDOWN:
    //    MessageBox
    //    (
    //        hwnd,
    //        L"안녕 윈도우!!!",
    //        L"ERROR!!!",
    //        MB_OK
    //    );
    //    break;
#pragma endregion

#pragma region 텍스트
    //case WM_LBUTTONDOWN:
    //{
    //    wstring str = L"마우스 눌림!!";

    //    HDC hdc = GetDC(hwnd); //DC : Device Context
    //    TextOut(hdc, 200, 200, str.c_str(), str.length());
    //    ReleaseDC(hwnd, hdc);
    //}
    //    break;

    //case WM_PAINT:
    //{
    //    wstring str = L"WM_PAINT 메세지 발생!!";

    //    PAINTSTRUCT ps;
    //    HDC hdc = BeginPaint(hwnd, &ps);
    //    TextOut(hdc, 200, 400, str.c_str(), str.length());
    //    EndPaint(hwnd, &ps);
    //}
    //    break;
#pragma endregion

#pragma region 텍스트 움직이기
    //case WM_KEYDOWN:
    //    if (wParam == VK_UP)
    //        position.y -= 10;
    //    else if (wParam == VK_DOWN)
    //        position.y += 10;

    //    if (wParam == VK_LEFT)
    //        position.x -= 10;
    //    else if (wParam == VK_RIGHT)
    //        position.x += 10;

    //    InvalidateRect(hwnd, nullptr, true);
    //    break;

    //case WM_PAINT:
    //{
    //    PAINTSTRUCT ps;
    //    HDC hdc = BeginPaint(hwnd, &ps);
    //    TextOut(hdc, position.x, position.y, L"◎", 1);
    //    EndPaint(hwnd, &ps);
    //}
    //    break;
#pragma endregion

#pragma region 마우스좌표
    //case WM_MOUSEMOVE:
    //    position.x = LOWORD(lParam);
    //    position.y = HIWORD(lParam);
    //    InvalidateRect(hwnd, nullptr, true);
    //    break;

    //case WM_PAINT:
    //{
    //    wstring str = L"";
    //    str += to_wstring(position.x); // 10 -> "10"
    //    str += L", ";
    //    str += to_wstring(position.y);

    //    PAINTSTRUCT ps;
    //    HDC hdc = BeginPaint(hwnd, &ps);
    //    TextOut(hdc, position.x, position.y, str.c_str(), str.length());

    //    //Line
    //    MoveToEx(hdc, 300, 300, nullptr);
    //    LineTo(hdc, 700, 700);

    //    EndPaint(hwnd, &ps);
    //}
    //    break;
#pragma endregion

#pragma region 그림판
    //case WM_LBUTTONDOWN:
    //    position.x = LOWORD(lParam);
    //    position.y = HIWORD(lParam);
    //    bClicked = true;
    //    break;

    //case WM_MOUSEMOVE:
    //    if (bClicked)
    //    {
    //        HDC hdc = GetDC(hwnd);

    //        MoveToEx(hdc, position.x, position.y, nullptr);

    //        position.x = LOWORD(lParam);
    //        position.y = HIWORD(lParam);

    //        LineTo(hdc, position.x, position.y);

    //        ReleaseDC(hwnd, hdc);
    //    }
    //    break;

    //case WM_LBUTTONUP:
    //    bClicked = false;
    //    break;
#pragma endregion

#pragma region 도형 그리기
    //case WM_PAINT:
    //{
    //    PAINTSTRUCT ps;
    //    HDC hdc = BeginPaint(hwnd, &ps);
    //    //Rectangle(hdc, 100, 100, 500, 500);
    //    Ellipse(hdc, 100, 100, 500, 500);
    //    EndPaint(hwnd, &ps);
    //}
    //    break;
#pragma endregion

#pragma region 도형 그림판
    case WM_LBUTTONDOWN:
        start.x = LOWORD(lParam);
        start.y = HIWORD(lParam);
        bClicked = true;
        break;

    case WM_MOUSEMOVE:
        if (bClicked)
        {
            end.x = LOWORD(lParam);
            end.y = HIWORD(lParam);
        }
		pShape = {
		start.x,								// int startX;
		start.y,								// int startY;
		end.x,									// int endX;
		end.y,									// int endY;
		selectShape,							// char shapeType;
		selectBrush,							// char brushType;
		selectPen,								// char penType;
		penSize,								// char penSize;
		isBrush,
		{cBrush.Red, cBrush.Green, cBrush.Blue},// ColorRGBA cBrush;
		{cPen.Red, cPen.Green, cPen.Blue}		// ColorRGBA cPen;
		};
        break;

    case WM_LBUTTONUP:
        bClicked = false;

		shapes.emplace_back(pShape);
		InvalidateRect(hwnd, nullptr, true);
        break;

    case WM_PAINT:
    {
		HDC hdc = BeginPaint(hwnd, &ps);

		for (int i = 0;i<shapes.size();i++)
		{
			switch (shapes[i].shapeType) {
			case 0:
				curPen = CreatePen(shapes[i].penType, shapes[i].penSize, RGB(shapes[i].cPen.Red, shapes[i].cPen.Green, shapes[i].cPen.Blue));
				oldPen = static_cast<HPEN>(SelectObject(hdc, curPen));

				MoveToEx(hdc, shapes[i].startX, shapes[i].startY, nullptr);
				LineTo(hdc, shapes[i].endX, shapes[i].endY);
				break;
			case 1:
				curPen = CreatePen(shapes[i].penType, shapes[i].penSize, RGB(shapes[i].cPen.Red, shapes[i].cPen.Green, shapes[i].cPen.Blue));
				oldPen = static_cast<HPEN>(SelectObject(hdc, curPen));

				if (shapes[i].isBrush)
					curBrush = CreateHatchBrush(shapes[i].brushType, RGB(shapes[i].cBrush.Red, shapes[i].cBrush.Green, shapes[i].cBrush.Blue));
				else
					curBrush = CreateSolidBrush(RGB(shapes[i].cBrush.Red, shapes[i].cBrush.Green, shapes[i].cBrush.Blue));

				oldBrush = static_cast<HBRUSH>(SelectObject(hdc, curBrush));
				Rectangle(hdc, shapes[i].startX, shapes[i].startY, shapes[i].endX, shapes[i].endY);
				break;
			case 2:
				curPen = CreatePen(shapes[i].penType, shapes[i].penSize, RGB(shapes[i].cPen.Red, shapes[i].cPen.Green, shapes[i].cPen.Blue));
				oldPen = static_cast<HPEN>(SelectObject(hdc, curPen));

				if (shapes[i].isBrush)
					curBrush = CreateHatchBrush(shapes[i].brushType, RGB(shapes[i].cBrush.Red, shapes[i].cBrush.Green, shapes[i].cBrush.Blue));
				else
					curBrush = CreateSolidBrush(RGB(shapes[i].cBrush.Red, shapes[i].cBrush.Green, shapes[i].cBrush.Blue));

				oldBrush = static_cast<HBRUSH>(SelectObject(hdc, curBrush));
				Ellipse(hdc, shapes[i].startX, shapes[i].startY, shapes[i].endX, shapes[i].endY);
				break;
			}
		}

		if(isBrush)
			curBrush = CreateHatchBrush(selectBrush, RGB(cBrush.Red, cBrush.Green, cBrush.Blue));
		else
			curBrush = CreateSolidBrush(RGB(cBrush.Red, cBrush.Green, cBrush.Blue));

        oldBrush = static_cast<HBRUSH>(SelectObject(hdc, curBrush));

        //Pen
        curPen = CreatePen(selectPen, penSize, RGB(cPen.Red, cPen.Green, cPen.Blue));
        oldPen = static_cast<HPEN>(SelectObject(hdc, curPen));
		switch (selectShape) {
		case 0:
			MoveToEx(hdc, start.x, start.y, nullptr);
			LineTo(hdc, end.x, end.y);
			break;
		case 1:
			Rectangle(hdc, start.x, start.y, end.x, end.y);
			break;
		case 2:
			Ellipse(hdc, start.x, start.y, end.x, end.y);
			break;
		}
        

        SelectObject(hdc, oldBrush);
        DeleteObject(curBrush);

        SelectObject(hdc, oldPen);
        DeleteObject(curPen);

        EndPaint(hwnd, &ps);

    }
        break;
#pragma endregion

    case WM_CLOSE:
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
