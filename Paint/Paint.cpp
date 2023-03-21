// Paint.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Paint.h"
#include "commdlg.h"
#include "CommCtrl.h"
#include "Capture.h"
#include "Menu.h"
#include "Math.h"
#define MAX_LOADSTRING 100

void Cursor();
int isLBut = 0;
int isEraser = 0;
HCURSOR hCursCircle;
HCURSOR hCursArrow;

int cur_size;
HWND hwnd_ed_size;
HWND hwnd_sp_size;
int cur_red;
HWND hwnd_ed_red;
HWND hwnd_sp_red;
int cur_green;
HWND hwnd_ed_green;
HWND hwnd_sp_green;
int cur_blue;
HWND hwnd_ed_blue;
HWND hwnd_sp_blue;



typedef struct {
	int r;
	int g;
	int b;
}myColor;
typedef struct {
	myColor color;
	int size;
}myPen;
myPen pen;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр

WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINT));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PAINT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{

	case WM_CREATE:
	{
		hCursArrow = LoadCursor(NULL, IDC_ARROW);
		Cursor();
		create_win_ctrl(hWnd, 0, 0, 50, 15, &hwnd_ed_size, &hwnd_sp_size, &cur_size, ED_SIZE, SP_SIZE);
		create_win_ctrl(hWnd, 50, 0, 50, 15, &hwnd_ed_red, &hwnd_sp_red, &cur_red, ED_RED, SP_RED);
		create_win_ctrl(hWnd, 100, 0, 50, 15, &hwnd_ed_green, &hwnd_sp_green, &cur_green, ED_GREEN, SP_GREEN);
		create_win_ctrl(hWnd, 150, 0, 50, 15, &hwnd_ed_blue, &hwnd_sp_blue, &cur_blue, ED_BLUE, SP_BLUE);
		HMENU hMenuBar = CreateMenu();
		AppendMenuW(hMenuBar, MF_STRING, NULL, L"SIZE");
		AppendMenuW(hMenuBar, MF_STRING, NULL, L"    RED");
		AppendMenuW(hMenuBar, MF_STRING, NULL, L"    GREEN");
		AppendMenuW(hMenuBar, MF_STRING, NULL, L"  BLUE");
		AppendMenuW(hMenuBar, MF_STRING, 15, L"  PEN");
		AppendMenuW(hMenuBar, MF_STRING, 2, L"     ERASER");
		AppendMenuW(hMenuBar, MF_STRING, 1, L"               SAVE");
		SetMenu(hWnd, hMenuBar);
	}
	break;
	//case WM_SETCURSOR:			
	//	//SetCursor(hCurs1);		
	//	SetCursor(hCurs);
	//	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		if (HIWORD(wParam) == EN_CHANGE) {
			char s[50];
			if (LOWORD(wParam) == ED_SIZE) {
				GetWindowTextA(hwnd_ed_size, s, sizeof(s));
				cur_size = (unsigned char)(atoi(s));
				pen.size = cur_size;
			}
			else if (LOWORD(wParam) == ED_RED) {
				GetWindowTextA(hwnd_ed_red, s, sizeof(s));
				cur_red = (unsigned char)(atoi(s));
				pen.color.r = cur_red;
			}
			else if (LOWORD(wParam) == ED_GREEN) {
				GetWindowTextA(hwnd_ed_green, s, sizeof(s));
				cur_green = (unsigned char)(atoi(s));
				pen.color.g = cur_green;
			}
			else if (LOWORD(wParam) == ED_BLUE) {
				GetWindowTextA(hwnd_ed_blue, s, sizeof(s));
				cur_blue = (unsigned char)(atoi(s));
				pen.color.b = cur_blue;
			}
			//Cursor(cur_size);
		}
		switch (wmId)
		{
		case 1:
			CaptureAnImage(hWnd);
			InvalidateRect(hWnd, NULL, NULL);
			break;
		case 2:
			isEraser = 1;
			break;
		case 15:
			isEraser = 0;
			break;
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
	case WM_VSCROLL:
	{
		if ((HWND)(lParam) == hwnd_sp_size
			&& LOWORD(wParam) == SB_ENDSCROLL) {
			char s[50]; HDC hdc;
			GetWindowTextA(hwnd_ed_size, s, sizeof(s));

			return 0;
		}
	}
	break;
	case  WM_ERASEBKGND:
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...winapi 
		HBRUSH Brush;
		HPEN hPen;
		if (isEraser == 1) {
			Brush = CreateSolidBrush(RGB(255, 255, 255));
			hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		}
		else {
			Brush = CreateSolidBrush(RGB(pen.color.r, pen.color.g, pen.color.b));
			hPen = CreatePen(PS_SOLID, 1, RGB(pen.color.r, pen.color.g, pen.color.b));
		}
		HBRUSH WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
		HPEN BlackPen = CreatePen(1, 1, RGB(0, 0, 0));
		RECT rc;
		GetClientRect(hWnd, &rc);


		if (isLBut == 1) {
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(hWnd, &p);
			SelectObject(hdc, Brush);
			Ellipse(hdc, p.x - pen.size, p.y - pen.size, p.x + pen.size, p.y + pen.size);
			SelectObject(hdc, hPen);
			Ellipse(hdc, p.x - pen.size, p.y - pen.size, p.x + pen.size, p.y + pen.size);
			SelectObject(hdc, WhiteBrush);
			Rectangle(hdc, 200, 0, rc.right, 16);
			SelectObject(hdc, BlackPen);
			Rectangle(hdc, 200, 0, rc.right, 16);
		}




		DeleteObject(Brush);
		DeleteObject(hPen);
		DeleteObject(WhiteBrush);
		DeleteObject(BlackPen);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		isLBut = 1;
		InvalidateRect(hWnd, NULL, NULL);
		break;
	case WM_LBUTTONUP:
		isLBut = 0;
		InvalidateRect(hWnd, NULL, NULL);
		break;


	case  WM_MOUSEMOVE: {
		if (isLBut == 1) {
			InvalidateRect(hWnd, NULL, NULL);
		}
		SetClassLongPtr(hWnd, (GCLP_HCURSOR), (LONG)hCursCircle);
		//InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
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





void Cursor() {
//	//if (r < 5) return;
//	//BYTE** AND = (BYTE**)calloc(r * 2, sizeof(BYTE*));
//	BYTE** AND = (BYTE**)malloc(r * 2 * sizeof(BYTE*));
//	for (int i = 0; i < r * 2; i++)
//	{
//		//BYTE* AND = (BYTE*)calloc(r * 2, sizeof(BYTE));
//		 AND[i] = (BYTE*)malloc(r * 2 * sizeof(BYTE));
//	}
//	for (int i = 0; i < r * 2; i++)
//	{
//		for (int j = 0; j < r * 2; j++) {
//			AND[i][j] = 1;
//		}
//	}
//
//	int X1 = r - 1;
//	int Y1 = r - 1;
//	int x = 0;
//	int y = r - 1;
//	int delta = 1 - 2 * (r - 1);
//	int error = 0;
//	while (y >= x) {
//		AND[X1 + x][Y1 + y] = 0;
//		AND[X1 + x][Y1 - y] = 0;
//
//		AND[X1 - x][Y1 + y] = 0;
//
//		AND[X1 - x][Y1 - y] = 0;
//
//		AND[X1 + y][Y1 + x] = 0;
//
//		AND[X1 + y][Y1 - x] = 0;
//
//		AND[X1 - y][Y1 + x] = 0;
//
//		AND[X1 - y][Y1 - x] = 0;
//
//		error = 2 * (delta + y) - 1;
//		if ((delta < 0) && (error <= 0)) {
//			delta += 2 * ++x + 1;
//			continue;
//		}
//		if ((delta > 0) && (error > 0)) {
//			delta -= 2 * --y + 1;
//			continue;
//
//		}
//		delta += 2 * (++x - --y);
//	}
//
//	BYTE* mas = (BYTE*)calloc(r * 2*4, sizeof(BYTE));
//
//	for (int i = 0; i < r * 2; i++)
//	{
//		for (int j = 0; j < 4; j++) {
//			for (int k = 0; k < 8; k++) {
//				mas[i * 4 + j] += AND[i][k + j * 8] * pow(2, 7 - k);
//			}
//		}
//	}
//
//	BYTE* XORmaskCursor = (BYTE*)calloc(r * 2*4, sizeof(BYTE));
//	hCurs = CreateCursor(hInst,   // app. instance 
//		r,                // horizontal position of hot spot 
//		r,                 // vertical position of hot spot 
//		r*2,                // cursor width 
//		r*2,                // cursor height 
//		mas,     // AND mask 
//		XORmaskCursor);   // XOR mask 
//
//	free(XORmaskCursor);
//	/*for (int i = 0; i < r*2; i++)
//	{
//		free(mas[i]);
//	}*/
//	free(mas);
//}
	






//if (r < 1) return;
	//BYTE AND[100][100];

	//for (int i = 0; i < 100; i++)
	//{
	//	for (int j = 0; j < 100; j++) {
	//		AND[i][j] = 1;
	//	}

	//}
	//int X1 = r - 1;
	//int Y1 = r - 1;
	//int x = 0;
	//int y = r - 1;
	//int delta = 1 - 2 * (r - 1);
	//int error = 0;
	//while (y >= x) {
	//	AND[X1 + x][Y1 + y] = 0;
	//	AND[X1 + x][Y1 - y] = 0;

	//	AND[X1 - x][Y1 + y] = 0;

	//	AND[X1 - x][Y1 - y] = 0;

	//	AND[X1 + y][Y1 + x] = 0;

	//	AND[X1 + y][Y1 - x] = 0;

	//	AND[X1 - y][Y1 + x] = 0;

	//	AND[X1 - y][Y1 - x] = 0;

	//	error = 2 * (delta + y) - 1;
	//	if ((delta < 0) && (error <= 0)) {
	//		delta += 2 * ++x + 1;
	//		continue;
	//	}
	//	if ((delta > 0) && (error > 0)) {
	//		delta -= 2 * --y + 1;
	//		continue;

	//	}
	//	delta += 2 * (++x - --y);
	//}

	//BYTE* mas = (BYTE*)malloc(r * 2*4 * sizeof(BYTE));

	//for (int i = 0; i < r*2; i++)
	//{
	//	for (int j = 0; j < 4; j++) {
	//		for (int k = 0; k < 8; k++) {
	//			mas[i * 4 + j] += AND[i][k + j * 8] * pow(2, 7 - k);
	//		}
	//	}
	//}
	//
	//BYTE* XORmaskCursor = (BYTE*)malloc(r * 2*4 * sizeof(BYTE));
	//


	//hCurs = CreateCursor(hInst,   // app. instance 
	//	r,                // horizontal position of hot spot 
	//	r,                 // vertical position of hot spot 
	//	r*2,                // cursor width 
	//	r*2,                // cursor height 
	//	mas,     // AND mask 
	//	XORmaskCursor);   // XOR mask 
	////delete(XORmaskCursor);
	////delete(mas);
//}
	BYTE AND[32][32];
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++) {
			AND[i][j] = 1;
		}

	}
	int X1 = 15;
	int Y1 = 15;
	int r1 = 15;
	int x = 0;
	int y = r1;
	int delta = 1 - 2 * r1;
	int error = 0;
	while (y >= x) {
		AND[X1 + x][Y1 + y] = 0;
		AND[X1 + x][Y1 - y] = 0;

		AND[X1 - x][Y1 + y] = 0;

		AND[X1 - x][Y1 - y] = 0;

		AND[X1 + y][Y1 + x] = 0;

		AND[X1 + y][Y1 - x] = 0;

		AND[X1 - y][Y1 + x] = 0;

		AND[X1 - y][Y1 - x] = 0;

		error = 2 * (delta + y) - 1;
		if ((delta < 0) && (error <= 0)) {
			delta += 2 * ++x + 1;
			continue;
		}
		if ((delta > 0) && (error > 0)) {
			delta -= 2 * --y + 1;
			continue;

		}
		delta += 2 * (++x - --y);
	}

	BYTE mas[32 * 4] = { 0 };

	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 8; k++) {
				mas[i * 4 + j] += AND[i][k + j * 8] * pow(2, 7 - k);
			}
		}
	}
	
	BYTE XORmaskCursor[32 * 4] = { 0 };
	


	hCursCircle = CreateCursor(hInst,   // app. instance 
		16,                // horizontal position of hot spot 
		16,                 // vertical position of hot spot 
		32,                // cursor width 
		32,                // cursor height 
		mas,     // AND mask 
		XORmaskCursor);   // XOR mask 
}

