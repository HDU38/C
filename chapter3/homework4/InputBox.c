#include <windows.h>
#include<stdio.h>

#define ID_EDITBOX 0 /* �ı��༭��ؼ� */
#define ID_OUTBTN 1 /* ȷ����ť */
#define ID_CLSBTN 2 /* ��ձ༭����ť */

LRESULT CALLBACK MyProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int CreateChildWindow(HWND hwnd, HWND *hwndChild, LPARAM lParam);
int OutputContent(TCHAR *content);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG      msg;
	HWND     hwnd;
	static TCHAR szAppName[] = TEXT("demo");
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;/* ��� */
	/*
	*  ��ʾ����ʵ��֮�����Ķ�����ֽ�����ϵͳ����ֵ��ʼ
	*  ��Ϊ0.���ʹ����Դ�ļ����CLASSָ����Ի��򣬲���WN
	*  DCLASSע��öԻ���ʱ��cbWndExtra�������ó�DLGWNDOWEXT
	*  RA��
	*/
	wndclass.cbClsExtra = 0;
	/* ��ʾ������ṹ֮�����Ķ�����ֽ�����ϵͳ����ֵ��ʼ��Ϊ0. */
	wndclass.cbWndExtra = 0;
	/* ָ�򴰿ڹ��̵�ָ��,����ʹ��CallWindowProc�������ô��ڹ��� */
	wndclass.lpfnWndProc = MyProc;
	/*  ��������ʵ���ľ������ʵ�������˴��ڹ��̡� */
	wndclass.hInstance = hInstance;
	/* ��ͼ��ľ�����ó�Ա����Ϊһ��ͼ����Դ�ľ�������hIconΪNULL��ϵͳ���ṩĬ��ͼ�ꡣ*/
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
	/*
	���ָ��ľ�����ĳ�Ա����Ϊһ��ָ����Դ�ľ�������
	*  hCursorΪNULL��Ӧ�ó��������ָ������Ӧ�ó��򴰿�ʱ
	*  ��ʽ����ָ�����͡�
	*/
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	/* ������ˢ�ľ�����ó�Ա���������ڻ��Ʊ���������ˢ�ľ����������һ����ɫֵ��*/ 
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	/* 
	*  ָ��NULL�������ַ��������ַ��������˵�����Դ������ͬ����Դ�ļ�����ʾ
	*  ������һ������ʹ��һ��������ʶ�˵�������ʹ��MAKEINTRESOURCE�ꡣ���
	*  lpszMenuNameΪNULL����ô�ô�����Ĵ��ڽ�û��Ĭ�ϲ˵���
	*/
	wndclass.lpszMenuName = NULL;
	/* 
	*  ָ ��NULL�������ַ�����������һ��ԭ��(atom)�����ò�����һ��ԭ�ͣ���������һ����
	*  ��ǰ����RegisterClass���� RegisterClassEx������������ԭ�͡���ԭ�ͱ�����ΪlpszCl
	*  assName�ĵ��֣����ֱ���Ϊ0.��lpszClassName��һ�� �ַ������������˴��������������
	*  ����������RegisterClass����RegisterClassExע������֣��������κ�Ԥ����Ŀؼ�������
	*/
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("error"), TEXT("title"), MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName,
		TEXT("�ı������"),
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
	static HWND hwndChild[3];
	HDC hdc;
	PAINTSTRUCT ps;

	RECT rect;
	static TCHAR *szBuffer;        /* ������ */
	static TCHAR szLineNum[32];
	static TCHAR szCharNum[32];
	static int iLength;

	switch (message)
	{
	case WM_CREATE:/* �����༭���������� */
		CreateChildWindow(hwnd, hwndChild, lParam);
		return 0;

	case WM_SIZE:/* �������ڴ�С */
		GetClientRect(hwnd, &rect);
		MoveWindow(hwndChild[ID_EDITBOX], 0, 0, rect.right, rect.bottom - 50, TRUE);/* �����ı��༭�� */
		MoveWindow(hwndChild[ID_OUTBTN], 0, rect.bottom - 35, 100, 25, TRUE); /* ����ȷ����ť */
		MoveWindow(hwndChild[ID_CLSBTN], 100, rect.bottom - 35, 100, 25, TRUE); /* ������հ�ť */
		return 0;

	case WM_PAINT:/* ��ʾ���� */
		GetClientRect(hwnd, &rect);
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 500, rect.bottom - 30, szLineNum, lstrlen(szLineNum));
		EndPaint(hwnd, &ps);
		return 0;

	case WM_COMMAND:/* ��Ӧ����¼� */
		switch (LOWORD(wParam))
		{
		case ID_OUTBTN:/* ��� */
			iLength = GetWindowTextLength(hwndChild[ID_EDITBOX]);
			if (iLength != 0)
				szBuffer = malloc(iLength * 2);
			else
				return -1;
			/* ��ȡ�ı����� */
			if (szBuffer != 0)
			{
				GetWindowText(hwndChild[ID_EDITBOX], szBuffer, GetWindowTextLength(hwndChild[ID_EDITBOX]) + 1);
				OutputContent(szBuffer);/* ���������̨ */
			}
			return 0;

		case ID_CLSBTN:/* ��� */
			SetWindowText(hwndChild[ID_EDITBOX], TEXT(""));
			return 0;

		default:
			break;
		}
		return 0;

	case WM_DESTROY:/* �ر� */
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

/* �������� */
int CreateChildWindow(HWND hwnd, HWND *hwndChild, LPARAM lParam)
{
	HINSTANCE hInst = ((LPCREATESTRUCT)lParam)->hInstance;

	/* �����༭�� */
	hwndChild[ID_EDITBOX] = CreateWindow(TEXT("edit"), NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
		ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
		0, 0, 0, 0,
		hwnd, (HMENU)ID_EDITBOX, hInst, NULL);

	/* ���水ť */
	hwndChild[ID_OUTBTN] = CreateWindow(TEXT("button"), TEXT("ȷ��"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 0, 0,
		hwnd, (HMENU)ID_OUTBTN, hInst, NULL);

	/* ��հ�ť */
	hwndChild[ID_CLSBTN] = CreateWindow(TEXT("button"), TEXT("���"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 0, 0,
		hwnd, (HMENU)ID_CLSBTN, hInst, NULL);
	return 0;
}

/* ��� */
int OutputContent(TCHAR *content)
{
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CON", "r", stdin);/* �ض��������� */
	freopen_s(&stream, "CON", "w", stdout);/* �ض��������� */
	printf("%s",content);
	return 0;
}