#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <Windows.h>
#include <windowsx.h>
#include <string>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND RedColor;
HWND GreenColor;
HWND BlueColor;
HWND TestColor;

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	return LineTo(hdc, x2, y2);
}

int CALLBACK  wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"MyAppClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
	{
		return EXIT_FAILURE;
	}


	if (hwnd = CreateWindow(wc.lpszClassName, L"Paint", WS_OVERLAPPEDWINDOW, 0, 0, 1920, 1080, nullptr, nullptr, wc.hInstance, nullptr);
		hwnd == INVALID_HANDLE_VALUE)
	{
		return EXIT_FAILURE;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int> (msg.wParam);
}

void CreateButtons(HWND hEdit, HWND hWnd)
{
	HWND hChangeColor = CreateWindow(
		L"BUTTON",
		L"Change color",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 100, 50, hWnd, reinterpret_cast<HMENU>(0), nullptr, nullptr
	);
	HWND hButtonLine = CreateWindow(
		L"BUTTON",
		L"Line",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 300, 100, 50, hWnd, reinterpret_cast<HMENU>(5), nullptr, nullptr
	);
	HWND hButtonRect = CreateWindow(
		L"BUTTON",
		L"Rectangle",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 350, 100, 50, hWnd, reinterpret_cast<HMENU>(6), nullptr, nullptr
	);
	HWND hLineSizeS = CreateWindow(
		L"Button",
		L"Small",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 800, 100, 50, hWnd, reinterpret_cast<HMENU>(7), nullptr, nullptr
	);
	HWND hLineSizeM = CreateWindow(
		L"Button",
		L"Medium",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 850, 100, 50, hWnd, reinterpret_cast<HMENU>(8), nullptr, nullptr
	);
	HWND hLineSizeL = CreateWindow(
		L"Button",
		L"Large",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 900, 100, 50, hWnd, reinterpret_cast<HMENU>(9), nullptr, nullptr
	);
	HWND hButtonCurve = CreateWindow(
		L"BUTTON",
		L"Curve",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 400, 100, 50, hWnd, reinterpret_cast<HMENU>(10), nullptr, nullptr
	);
	HWND hButtonPolygon = CreateWindow(
		L"BUTTON",
		L"Polygon",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 450, 100, 50, hWnd, reinterpret_cast<HMENU>(11), nullptr, nullptr
	);
	HWND hButtonElipse = CreateWindow(
		L"BUTTON",
		L"Elipse",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 500, 100, 50, hWnd, reinterpret_cast<HMENU>(12), nullptr, nullptr
	);
	HWND hButtonText = CreateWindow(
		L"BUTTON",
		L"Text",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 550, 100, 50, hWnd, reinterpret_cast<HMENU>(13), nullptr, nullptr
	);
	HWND text = CreateWindow(
		L"EDIT",
		L"Text",
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		0, 600, 100, 50, hWnd, reinterpret_cast<HMENU>(14), nullptr, nullptr
	);
	RedColor = CreateWindow(
		L"EDIT",
		L"0",
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		0, 650, 30, 30, hWnd, reinterpret_cast<HMENU>(15), nullptr, nullptr
	);
	GreenColor = CreateWindow(
		L"EDIT",
		L"0",
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		30, 650, 30, 30, hWnd, reinterpret_cast<HMENU>(16), nullptr, nullptr
	);
	BlueColor = CreateWindow(
		L"EDIT",
		L"0",
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		60, 650, 30, 30, hWnd, reinterpret_cast<HMENU>(17), nullptr, nullptr
	);
}

int MapColor(int color)
{
	if (color < 0)
		return 0;
	if (color > 255)
		return 255;
	return color;
}

int CastChar(LPTSTR str)
{
	char* a = new char[20];
	for (int i = 0; i < 20; i++)
	{
		a[i] = str[i];
	}
	return MapColor(atoi(a));
}

COLORREF ChangeColor(HWND hWnd)
{
	COLORREF color;
	LPTSTR pBuffer;
	pBuffer = new TCHAR[128];

	GetWindowText(RedColor, pBuffer, 20);
	int r = CastChar(pBuffer);

	GetWindowText(GreenColor, pBuffer, 20);
	int g = CastChar(pBuffer);

	GetWindowText(BlueColor, pBuffer, 20);
	int b = CastChar(pBuffer);
			
	RECT rect;
	rect.top = 50;
	rect.bottom = 100;
	rect.left = 0;
	rect.right = 100;

	HBRUSH hBrush1 = CreateSolidBrush(RGB(r, g, b));

	FillRect(GetDC(hWnd), &rect, hBrush1);

	return RGB(r, g, b);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	LOGFONT lf;
	HFONT hFont;
	RECT rect;
	HBRUSH hBrush;
	HPEN hPen;
	POINT pt;

	static COLORREF color = RGB(0, 0, 0);
	static bool isDraw = false;
	static int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;
	static int shape = 0, line = 1, curveCount = 0, polyCount = 0;
	static POINT curveLine[256];
	static POINT poly[256];
	static wchar_t text[256];
	static HWND hEdit;

	if (message == WM_CREATE)
	{
		CreateButtons(hEdit, hWnd);
	}	

	switch (message)
	{	
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case 0:
					color = ChangeColor(hWnd);
					break;
				case 5:
					shape = 0;
					break;
				case 6:
					shape = 1;
					break;
				case 7:
					line = 1;
					break;
				case 8:
					line = 5;
					break;
				case 9:
					line = 10;
					break;
				case 10:
					shape = 2;
					break;
				case 11:
					shape = 3;
					break;
				case 12:
					shape = 4;
					break;
				case 13:
					shape = 5;
					break;
				default:
					break;
			}			
		}
		break;				
		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
		}
		return 0;

		default:
		{
			return(DefWindowProc(hWnd, message, wParam, lParam));
		}
	}
	return 0;
}