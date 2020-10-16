#include <windows.h>
#include <commctrl.h>
#include "cresize.h"

static INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static CRESIZE *s_pResize = NULL;
    UINT id;
    switch (uMsg)
    {
    case WM_INITDIALOG:
        s_pResize = cresize_Create(hwnd, TRUE);
        if (s_pResize == NULL)
        {
            EndDialog(hwnd, IDCLOSE);
            break;
        }
        cresize_SetLayoutAnchorByID(s_pResize, edt1, LA_TOP_LEFT, LA_BOTTOM_RIGHT);
        cresize_SetLayoutAnchorByID(s_pResize, IDOK, LA_BOTTOM_RIGHT, LA_BOTTOM_RIGHT);
        cresize_SetLayoutAnchorByID(s_pResize, IDCANCEL, LA_BOTTOM_RIGHT, LA_BOTTOM_RIGHT);
        return TRUE;
    case WM_COMMAND:
        id = LOWORD(wParam);
        switch (id)
        {
        case IDOK:
        case IDCANCEL:
            EndDialog(hwnd, id);
            break;
        }
        break;
    case WM_SIZE:
        if (s_pResize)
            cresize_OnSize(s_pResize, NULL);
        break;
    case WM_DESTROY:
        cresize_Destroy(s_pResize);
        s_pResize = NULL;
        break;
    }
    return 0;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    InitCommonControls();
    DialogBox(hInstance, MAKEINTRESOURCE(1), NULL, DialogProc);
    return 0;
}
