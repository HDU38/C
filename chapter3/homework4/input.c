#include <windows.h>
#include<stdio.h>

#define ID_EDITBOX    1        //文本编辑框控件
#define ID_TXTPATH    2        //路径编辑框控件
#define ID_SAVEBTN    3        //保存文件按钮
#define ID_CLSBTN    4        //清空编辑区按钮
#define ID_GROUP    5        //组合框


LRESULT CALLBACK MyProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG      msg;
	HWND     hwnd;
	static TCHAR szAppName[] = TEXT("demo");
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;/* 风格 */
	/*
	*  表示窗口实例之后分配的额外的字节数。系统将该值初始
	*  化为0.如果使用资源文件里的CLASS指令创建对话框，并用WN
	*  DCLASS注册该对话框时，cbWndExtra必须设置成DLGWNDOWEXT
	*  RA。
	*/
	wndclass.cbClsExtra = 0;
	/* 表示窗口类结构之后分配的额外的字节数。系统将该值初始化为0. */
	wndclass.cbWndExtra = 0;
	/* 指向窗口过程的指针,必须使用CallWindowProc函数调用窗口过程 */
	wndclass.lpfnWndProc = MyProc;
	/*  包含该类实例的句柄，该实例包含了窗口过程。 */
	wndclass.hInstance = hInstance;
	/* 类图标的句柄。该成员必须为一个图标资源的句柄。如果hIcon为NULL，系统将提供默认图标。*/
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
	/*
	鼠标指针的句柄。改成员必须为一个指针资源的句柄。如果
	*  hCursor为NULL，应用程序必须在指针移入应用程序窗口时
	*  显式设置指针类型。
	*/
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	/* 背景画刷的句柄。该成员或者是用于绘制背景的物理画刷的句柄，或者是一个颜色值。*/ 
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	/* 
	*  指向NULL结束的字符串，该字符串描述菜单的资源名，如同在资源文件里显示
	*  的名字一样。若使用一个整数标识菜单，可以使用MAKEINTRESOURCE宏。如果
	*  lpszMenuName为NULL，那么该窗口类的窗口将没有默认菜单。
	*/
	wndclass.lpszMenuName = NULL;
	/* 
	*  指 向NULL结束的字符串，或者是一个原型(atom)。若该参数是一个原型，它必须是一个有
	*  先前调用RegisterClass或者 RegisterClassEx函数产生的类原型。类原型必须作为lpszCl
	*  assName的低字，高字必须为0.若lpszClassName是一个 字符串，它描述了窗口类名。这个类
	*  名可以是由RegisterClass或者RegisterClassEx注册的名字，或者是任何预定义的控件类名。
	*/
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("error"), TEXT("title"), MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName,
		TEXT("文本输入框"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK MyProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static        HWND hwndChild[5];
	HDC            hdc;
	PAINTSTRUCT ps;

	RECT    rect;
	static    TCHAR *szBuffer;        //缓冲区
	static    TCHAR szPath[256];        //文本路径
	static  TCHAR szLineNum[32];
	static    TCHAR szCharNum[32];
	static int        iLength;
	int iLineCount, iCharCount;

	switch (message)
	{
	case WM_CREATE:
		CreateChildWindow(hwnd, hwndChild, lParam);
		return 0;

	case WM_SIZE:
		GetClientRect(hwnd, &rect);
		MoveWindow(hwndChild[ID_EDITBOX], 0, 0, rect.right, rect.bottom - 50, TRUE);        //调整文本编辑区
		MoveWindow(hwndChild[ID_TXTPATH], 60, rect.bottom - 31, 200, 20, TRUE);            //调整文本路径输入框
		MoveWindow(hwndChild[ID_SAVEBTN], 280, rect.bottom - 35, 50, 25, TRUE);            //调整保存按钮
		MoveWindow(hwndChild[ID_CLSBTN], 400, rect.bottom - 35, 50, 25, TRUE);            //调整清空按钮
		MoveWindow(hwndChild[ID_GROUP], 10, rect.bottom - 50, 330, 48, TRUE);            //调整组合框
		return 0;

	case WM_PAINT:
		GetClientRect(hwnd, &rect);
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 20, rect.bottom - 30, TEXT("路径:"), lstrlen(TEXT("路径:")));
		TextOut(hdc, 500, rect.bottom - 30, szLineNum, lstrlen(szLineNum));
		EndPaint(hwnd, &ps);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_EDITBOX:
			switch (HIWORD(wParam))
			{
			case EN_UPDATE:
				iLineCount = SendMessage(hwndChild[ID_EDITBOX], EM_GETLINECOUNT, 0, 0);
				iCharCount = GetWindowTextLength(hwndChild[ID_EDITBOX]);
				wsprintf(szLineNum, "行数: %i    字符数量: %i", iLineCount, iCharCount);
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			default:
				break;
			}
			return 0;

		case ID_SAVEBTN:
			iLength = GetWindowTextLength(hwndChild[ID_EDITBOX]);
			if (iLength != 0)
				szBuffer = malloc(iLength * 2);
			else
				return -1;
			GetWindowText(hwndChild[ID_EDITBOX], szBuffer, GetWindowTextLength(hwndChild[ID_EDITBOX]) + 1);
			if (GetWindowText(hwndChild[ID_TXTPATH], szPath, 256) < 1)
			{
				MessageBox(NULL, TEXT("路径不能为空"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
				return -1;
			}
			SavaInputContent(szPath, szBuffer);
			return 0;

		case ID_CLSBTN:
			SetWindowText(hwndChild[ID_EDITBOX], TEXT(""));
			return 0;

		default:
			break;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

int CreateChildWindow(HWND hwnd, HWND *hwndChild, LPARAM lParam)
{
	HINSTANCE hInst = ((LPCREATESTRUCT)lParam)->hInstance;

	//创建编辑区
	hwndChild[ID_EDITBOX] = CreateWindow(TEXT("edit"), NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
		ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
		0, 0, 0, 0,
		hwnd, (HMENU)ID_EDITBOX, hInst, NULL);

	//路径输入框
	hwndChild[ID_TXTPATH] = CreateWindow(TEXT("edit"), NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOVSCROLL,
		0, 0, 0, 0,
		hwnd, (HMENU)ID_TXTPATH, hInst, NULL);

	//保存按钮
	hwndChild[ID_SAVEBTN] = CreateWindow(TEXT("button"), TEXT("保存"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 0, 0,
		hwnd, (HMENU)ID_SAVEBTN, hInst, NULL);

	//清空按钮
	hwndChild[ID_CLSBTN] = CreateWindow(TEXT("button"), TEXT("清空"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 0, 0,
		hwnd, (HMENU)ID_CLSBTN, hInst, NULL);

	//组合框
	hwndChild[ID_GROUP] = CreateWindow(TEXT("button"), NULL,
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 0, 0, 0, 0,
		hwnd, (HMENU)ID_GROUP, hInst, NULL);

	return 0;
}

int SavaInputContent(TCHAR *path, TCHAR *content)
{
	FILE *fSvae;

	fSvae = fopen(path, "w");
	if (fSvae == NULL)
	{
		MessageBox(NULL, TEXT("文件创建失败!"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
		return -1;
	}
	fputs(content, fSvae);
	fclose(fSvae);
	MessageBox(NULL, TEXT("保存成功!"), TEXT("成功"), MB_OK | MB_ICONINFORMATION);

	return 0;
}