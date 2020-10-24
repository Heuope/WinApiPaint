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
HWND BrushWide;
HWND Text;

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
	RedColor = CreateWindow(
		L"EDIT",
		L"0",
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		0, 50, 35, 30, hWnd, NULL, nullptr, nullptr
	);
	GreenColor = CreateWindow(
		L"EDIT",
		L"0",
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		30, 50, 35, 30, hWnd, NULL, nullptr, nullptr
	);
	BlueColor = CreateWindow(
		L"EDIT",
		L"0",
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		60, 50, 35, 30, hWnd, NULL, nullptr, nullptr
	);
	BrushWide = CreateWindow(
		L"EDIT",
		L"1",
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		60, 80, 35, 30, hWnd, NULL, nullptr, nullptr
	);
	HWND hButtonLine = CreateWindow(
		L"BUTTON",
		L"/",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 130, 30, 30, hWnd, reinterpret_cast<HMENU>(5), nullptr, nullptr
	);
	HWND hButtonRect = CreateWindow(
		L"BUTTON",
		L"▆",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		60, 130, 30, 30, hWnd, reinterpret_cast<HMENU>(6), nullptr, nullptr
	);
	HWND hButtonCurve = CreateWindow(
		L"BUTTON",
		L"/\\",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		30, 130, 30, 30, hWnd, reinterpret_cast<HMENU>(10), nullptr, nullptr
	);
	HWND hButtonPolygon = CreateWindow(
		L"BUTTON",
		L"★",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 160, 30, 30, hWnd, reinterpret_cast<HMENU>(11), nullptr, nullptr
	);
	HWND hButtonElipse = CreateWindow(
		L"BUTTON",
		L"o",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		30, 160, 30, 30, hWnd, reinterpret_cast<HMENU>(12), nullptr, nullptr
	);
	HWND hButtonText = CreateWindow(
		L"BUTTON",
		L"T",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		60, 160, 30, 30, hWnd, reinterpret_cast<HMENU>(13), nullptr, nullptr
	);
	Text = CreateWindow(
		L"EDIT",
		L"",
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		0, 190, 100, 100, hWnd, reinterpret_cast<HMENU>(14), nullptr, nullptr
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

int MapWide(int wide)
{
	if (wide < 0)
		return 0;
	if (wide > 20)
		return 20;
	return wide;
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

int GetBrushWide()
{
	LPTSTR pBuffer = new TCHAR[128];
	GetWindowText(BrushWide, pBuffer, 20);

	return MapWide(CastChar(pBuffer));
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
	rect.top = 80;
	rect.left = 0;
	rect.bottom = 110;
	rect.right = 60;

	HBRUSH hBrush1 = CreateSolidBrush(RGB(r, g, b));

	FillRect(GetDC(hWnd), &rect, hBrush1);

	return RGB(r, g, b);
}

int GetLength(const LPTSTR a)
{
	for (int i = 0; i < 1024; i++)
	{
		if (a[i] == '\0')
			return i;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HFONT hFont;
	RECT rect;
	HBRUSH hBrush;
	HPEN hPen;
	POINT pt;

	static COLORREF color = RGB(0, 0, 0);
	static bool isDraw = false;
	static int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;
	static int shape = 0, curveCount = 0, polyCount = 0;
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
		case WM_RBUTTONDOWN:
		{
			if (shape == 2)
			{
				memset(curveLine, 0, sizeof(POINT) * 256);
				curveCount = 0;
			}
			if (shape == 3)
			{
				memset(poly, 0, sizeof(POINT) * 256);
				polyCount = 0;
			}
		}
		break;
		case WM_LBUTTONDOWN:
		{
			HDC hdc = GetDC(hWnd);
			X1 = GET_X_LPARAM(lParam);
			Y1 = GET_Y_LPARAM(lParam);
			X2 = GET_X_LPARAM(lParam);
			Y2 = GET_Y_LPARAM(lParam);
			isDraw = true;

			if (shape == 2)
			{
				if (curveCount > 255)
				{
					curveCount--;
				}
				curveLine[curveCount].x = GET_X_LPARAM(lParam);
				curveLine[curveCount].y = GET_Y_LPARAM(lParam);
				curveCount++;
				HPEN hPen2 = CreatePen(PS_SOLID, GetBrushWide(), color);
				SelectObject(hdc, hPen2);
				for (int i = 0; i < curveCount - 1; i++)
				{
					Line(hdc, curveLine[i].x, curveLine[i].y, curveLine[i + 1].x, curveLine[i + 1].y);
				}
				DeleteObject(hPen2);
			}
			if (shape == 3)
			{
				if (polyCount > 255)
				{
					polyCount--;
				}
				poly[polyCount].x = GET_X_LPARAM(lParam);
				poly[polyCount].y = GET_Y_LPARAM(lParam);
				polyCount++;
				HBRUSH hBrush = CreateSolidBrush(color);
				SelectObject(hdc, hBrush);
				Polygon(hdc, poly, polyCount);
				DeleteObject(hBrush);
			}
			if (shape == 5)
			{
				LPTSTR pBuffer = new TCHAR[128];
				GetWindowText(Text, pBuffer, 128);
				RECT rt = { X1, Y1, X2 + 30, Y2 + 30 };
				DrawText(GetDC(hWnd), pBuffer, GetLength(pBuffer), &rt, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
			}
		}
		break;
		case WM_LBUTTONUP:
		{
			isDraw = false;
			HDC hdc = GetDC(hWnd);
			switch (shape)
			{
				case 0:
				{
					HPEN hPen2 = CreatePen(PS_SOLID, GetBrushWide(), color);
					SelectObject(hdc, hPen2);

					Line(hdc, X1, Y1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

					DeleteObject(hPen2);
				}
			break;
			}
		}
		break;
		case WM_MOUSEMOVE:
		{
			if (isDraw)
			{
				HDC hdc = GetDC(hWnd);
				switch (shape)
				{
					case 1:
					{
						rect.top = Y1;
						rect.left = X1;
						rect.right = X2;
						rect.bottom = Y2;
						HBRUSH hBrush1 = CreateSolidBrush(color);
						FillRect(hdc, &rect, hBrush1);
						DeleteObject(hBrush1);

						X2 = GET_X_LPARAM(lParam);
						Y2 = GET_Y_LPARAM(lParam);

						rect.top = Y1;
						rect.left = X1;
						rect.right = X2;
						rect.bottom = Y2;
						HBRUSH hBrush2 = CreateSolidBrush(color);
						FillRect(hdc, &rect, hBrush2);
						DeleteObject(hBrush2);
					}
				break;
					case 4:
					{
						HPEN hPen2 = CreatePen(PS_NULL, GetBrushWide(), color);
						SelectObject(hdc, hPen2);
						Ellipse(hdc, X1, Y1, X2, Y2);
						DeleteObject(hPen2);

						X2 = GET_X_LPARAM(lParam);
						Y2 = GET_Y_LPARAM(lParam);

						HBRUSH hBrush2 = CreateSolidBrush(color);
						SelectObject(hdc, hBrush2);
						Ellipse(hdc, X1, Y1, X2, Y2);
						DeleteObject(hBrush2);
					}
				break;
				default:
					break;
				}
			}
		}
		break;
		case WM_DESTROY:
		{
			PostQuitMessage(EXIT_SUCCESS);
		}
		break;

		default:
		{
			return(DefWindowProc(hWnd, message, wParam, lParam));
		}
	}
	return 0;
}