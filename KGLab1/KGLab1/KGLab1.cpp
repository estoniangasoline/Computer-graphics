// KGLab1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "KGLab1.h"
#include "vector"
#include "cmath"
#include "numbers"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

double pi = std::acos(-1);

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
    LoadStringW(hInstance, IDC_KGLAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KGLAB1));

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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KGLAB1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KGLAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
void Draw(HWND, std::vector<std::vector<double>>);
std::vector<std::vector<double>> Scale(std::vector<std::vector<double>>,
    std::vector<std::vector<double>> scaleMatrix);

std::vector<std::vector<double>> scaleMatrixY = { {1, 0, 0}, {0, 0.7692, 0}, {0, 0, 1} };

std::vector<std::vector<double>> scaleMatrixX = { {2.7, 0, 0}, {0, 1, 0}, {0, 0, 1} };

std::vector<std::vector<double>> ReflectMatrixX(std::vector<std::vector<double>> catCoords);

std::vector<std::vector<double>> reflectMatrixX;

std::vector<std::vector<double>> RotateMatrix(std::vector<std::vector<double>> catCoords, double angle);

std::vector<std::vector<double>> rotateMatrix;

std::vector<double> Center(std::vector<std::vector<double>> catCoords);

std::vector<std::vector<double>> startCatCoords =
{ { 200, 200, 1 }, { 200, 215, 1 }, { 210, 215, 1 }, { 250, 200, 1 },
{ 250, 215, 1 }, { 240, 215, 1 }, { 225, 205, 1 }, { 190, 230, 1 }, { 225, 255, 1 }, { 260, 230, 1 },
{ 225, 255, 1 }, { 180, 350, 1 }, { 270, 350, 1 }, { 220, 350, 1 }, { 220, 330, 1 }, { 205, 350, 1 },
{ 230, 350, 1 }, { 230, 330, 1 }, { 245, 350, 1 }, { 270, 350, 1 }, { 320, 350, 1 }, { 320, 250, 1 } };

std::vector<std::vector<double>> tempCatCoords = startCatCoords;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
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
    case WM_KEYDOWN:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case VK_UP:
            InvalidateRect(NULL, NULL, NULL);
            reflectMatrixX = ReflectMatrixX(tempCatCoords);
            tempCatCoords = Scale(tempCatCoords, reflectMatrixX);
            Draw(hWnd, tempCatCoords);
            break;
        case VK_DOWN:
            InvalidateRect(NULL, NULL, NULL);
            rotateMatrix = RotateMatrix(tempCatCoords, pi / 4);
            tempCatCoords = Scale(tempCatCoords, rotateMatrix);
            Draw(hWnd, tempCatCoords);
            break;
        case VK_LEFT:
            InvalidateRect(NULL, NULL, NULL);
            tempCatCoords = Scale(tempCatCoords, scaleMatrixY);
            Draw(hWnd, tempCatCoords);
            break;
        case VK_RIGHT:
            InvalidateRect(NULL, NULL, NULL);
            tempCatCoords = Scale(tempCatCoords, scaleMatrixX);
            Draw(hWnd, tempCatCoords);
            break;
        case VK_SPACE:
            InvalidateRect(NULL, NULL, NULL);
            tempCatCoords = startCatCoords;
            Draw(hWnd, tempCatCoords);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
        Draw(hWnd, startCatCoords);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

std::vector<std::vector<double>> ReflectMatrixX(std::vector<std::vector<double>> catCoords) {
    std::vector<double> center = Center(catCoords);
    std::vector<std::vector<double>> reflectMatrixX = { {1, 0, 0}, {0, -1, 0}, {0, center[1] * 2, 1} };

    return reflectMatrixX;
}

std::vector<std::vector<double>> RotateMatrix(std::vector<std::vector<double>> catCoords, double angle) {
    std::vector<double> center = Center(catCoords);

    std::vector<std::vector<double>> rotateMatrix = {
    {std::cos(angle), std::sin(angle), 0},
    {std::sin(angle) * -1, std::cos(angle), 0},
    {-1 * center[0] * (std::cos(angle) - 1) + center[1] * std::sin(angle),
    -1 * center[1] * (std::cos(angle) - 1) - center[0] * std::sin(angle) , 1 } };

    return rotateMatrix;
}

std::vector<double> Center(std::vector<std::vector<double>> catCoords) {

    double minX = 100000;
    double maxX = 0;

    double minY = 100000;
    double maxY = 0;

    for (int i = 0; i < catCoords.size(); i++) {
        minX = catCoords[i][0] < minX ? catCoords[i][0] : minX;
        maxX = catCoords[i][0] > maxX ? catCoords[i][0] : maxX;

        minY = catCoords[i][1] < minY ? catCoords[i][1] : minY;
        maxY = catCoords[i][1] > maxY ? catCoords[i][1] : maxY;
    }

    std::vector<double> center = { (maxX + minX) / 2, (maxY + minY) / 2 };

    return center;
}

std::vector<std::vector<double>> Scale(std::vector<std::vector<double>> catCoords,
    std::vector<std::vector<double>> scaleMatrix) {

    std::vector<std::vector<double>> rslt;

    for (int i = 0; i < catCoords.size(); i++) {
        std::vector<double> row;
        for (int j = 0; j < scaleMatrix.size(); j++) {
            row.push_back(catCoords[i][0] * scaleMatrix[0][j]
                + catCoords[i][1] * scaleMatrix[1][j] + catCoords[i][2] * scaleMatrix[2][j]);
        }
        rslt.push_back(row);
    }

    return rslt;
}

void Draw(HWND hWnd, std::vector<std::vector<double>> catCoords)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    // left ear
    MoveToEx(hdc, catCoords[0][0], catCoords[0][1], NULL);
    LineTo(hdc, catCoords[1][0], catCoords[1][1]);
    LineTo(hdc, catCoords[2][0], catCoords[2][1]);
    LineTo(hdc, catCoords[0][0], catCoords[0][1]);

    // right ear

    MoveToEx(hdc, catCoords[3][0], catCoords[3][1], NULL);
    LineTo(hdc, catCoords[4][0], catCoords[4][1]);
    LineTo(hdc, catCoords[5][0], catCoords[5][1]);
    LineTo(hdc, catCoords[3][0], catCoords[3][1]);

    // head
    MoveToEx(hdc, catCoords[6][0], catCoords[6][1], NULL);
    LineTo(hdc, catCoords[7][0], catCoords[7][1]);
    LineTo(hdc, catCoords[8][0], catCoords[8][1]);
    LineTo(hdc, catCoords[9][0], catCoords[9][1]);
    LineTo(hdc, catCoords[6][0], catCoords[6][1]);

    // body
    MoveToEx(hdc, catCoords[10][0], catCoords[10][1], NULL);
    LineTo(hdc, catCoords[11][0], catCoords[11][1]);
    LineTo(hdc, catCoords[12][0], catCoords[12][1]);
    LineTo(hdc, catCoords[10][0], catCoords[10][1]);

    // left leg
    MoveToEx(hdc, catCoords[13][0], catCoords[13][1], NULL);
    LineTo(hdc, catCoords[14][0], catCoords[14][1]);
    LineTo(hdc, catCoords[15][0], catCoords[15][1]);

    // right leg
    MoveToEx(hdc, catCoords[16][0], catCoords[16][1], NULL);
    LineTo(hdc, catCoords[17][0], catCoords[17][1]);
    LineTo(hdc, catCoords[18][0], catCoords[18][1]);

    // tail
    MoveToEx(hdc, catCoords[19][0], catCoords[19][1], NULL);
    LineTo(hdc, catCoords[20][0], catCoords[20][1]);
    LineTo(hdc, catCoords[21][0], catCoords[21][1]);
    LineTo(hdc, catCoords[19][0], catCoords[19][1]);

    EndPaint(hWnd, &ps);
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
