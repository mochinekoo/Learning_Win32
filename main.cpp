#include <Windows.h>
#include "resource.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int initWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	if (initWindow(hInstance, hPrevInstance, lpCmdLine, nShowCmd) == -1) {
		return -1;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
            case ID_40001: {
                MessageBoxA(hWnd, "ああ", "aa", MB_OK);
                break;
            }
            case ID_40002: {
                PostQuitMessage(0); //メッセージループ終了（=アプリを終了）
                DestroyWindow(hWnd);
                break;
            }
        }
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0); //メッセージループ終了（=アプリを終了）
        DestroyWindow(hWnd);
        break;
    }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}


int initWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpszClassName = "WindowClass";
	wndClass.lpfnWndProc = WndProc;
	wndClass.style = CS_VREDRAW | CS_HREDRAW;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	RegisterClassEx(&wndClass);

    //ウインドウを作成する
    HWND hwnd;
    ZeroMemory(&hwnd, sizeof(HWND));
    hwnd = CreateWindow(
        "WindowClass", //クラス名
        "テストウインドウ", //ウインドウタイトル
        WS_BORDER | WS_OVERLAPPEDWINDOW, //ウインドウスタイル
        CW_USEDEFAULT, //表示位置左（デフォルト）
        CW_USEDEFAULT, //表示位置上（デフォルト）
        WINDOW_WIDTH, //ウインドウ幅
        WINDOW_HEIGHT, //ウインドウ高さ
        NULL, //親ウインドウ
        LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)), //メニュー
        hInstance, //インスタンス
        NULL //パラメータ
    );

    if (hwnd == NULL) {
        return -1;
    }

    ShowWindow(hwnd, nShowCmd); //ウインドウを表示
    UpdateWindow(hwnd);

    //メッセージ
    MSG msg;
    ZeroMemory(&msg, sizeof(msg)); //初期化する
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	return 0;
}