// 해커톤- WinAPI.cpp : Defines the entry point for the application.
//

#pragma warning(disable:4996)
#include "framework.h"
#include "해커톤- WinAPI.h"
#include <sstream>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszClassName  = szWindowClass;
	wcex.lpszMenuName = NULL;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
		
    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_DISABLED,
      0, 0, 0, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   SetWindowTextA(hWnd, "로딩중..");
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

string RangeToString(const int i)
{
	if (i < 5) return "없음";
	else if (i < 10) return "부족";
	else if (i < 15) return "보통";
	else return "풍족";
}

LRESULT CALLBACK MsgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static EventManager evt_mng;
	static Event now_event("없음");
	static vector<EventSelectItem> now_event_item;
	static int select = 0;
	const static int RadioButtons[] = { IDC_RADIO1 , IDC_RADIO2 , IDC_RADIO3 ,IDC_RADIO4 ,IDC_RADIO5 ,IDC_RADIO6 };
	static bool reset = false;

	switch (message)
	{
	case WM_INITDIALOG:
	{
		setlocale(LC_ALL, "");
		Load(evt_mng);

		const wchar_t* fontName = L"Consolas";
		long nFontSize = 15;

		HDC hdc = GetDC(hdlg);

		LOGFONT logFont = { 0 };
		logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		logFont.lfWeight = FW_BOLD;
		_tcscpy_s(logFont.lfFaceName, fontName);

		auto s_hFont = CreateFontIndirect(&logFont);
		SendMessage(GetDlgItem(hdlg, IDC_FOOD), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(GetDlgItem(hdlg, IDC_MONEY), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(GetDlgItem(hdlg, IDC_MAN), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(GetDlgItem(hdlg, IDC_FAITH), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(GetDlgItem(hdlg, IDC_MILLI), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(GetDlgItem(hdlg, IDC_DIPLO), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(GetDlgItem(hdlg, IDC_RADIO1), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(GetDlgItem(hdlg, IDC_RADIO2), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(GetDlgItem(hdlg, IDC_RADIO3), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(GetDlgItem(hdlg, IDC_RADIO4), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(GetDlgItem(hdlg, IDC_RADIO5), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		SendMessage(GetDlgItem(hdlg, IDC_RADIO6), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

		SendMessage(GetDlgItem(hdlg, IDC_RADIO1), BM_SETCHECK, (WPARAM)TRUE, (LPARAM)NULL);
		
		nFontSize = 20;

		logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		logFont.lfWeight = FW_BOLD;
		_tcscpy_s(logFont.lfFaceName, fontName);
		s_hFont = CreateFontIndirect(&logFont);

		SendMessage(GetDlgItem(hdlg, IDC_LOG), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
		
		SendMessage(GetDlgItem(hdlg, IDC_OK), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

		nFontSize = 11;

		logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		logFont.lfWeight = FW_BOLD;
		_tcscpy_s(logFont.lfFaceName, fontName);
		s_hFont = CreateFontIndirect(&logFont);

		SendMessage(GetDlgItem(hdlg, IDC_SELECT_CONTENT), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

		nFontSize = 32;

		logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		logFont.lfWeight = FW_BOLD;
		_tcscpy_s(logFont.lfFaceName, fontName);
		s_hFont = CreateFontIndirect(&logFont);

		SendMessage(GetDlgItem(hdlg, IDC_NATION), WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

		ReleaseDC(hdlg, hdc); 
		try
		{
			now_event = evt_mng.GetNewEvent();
		}
		catch (exception)
		{
			size_t size = SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_GETCOUNT, 0, 0);
			for (int i = 0; i < size; ++i) SendMessageW(GetDlgItem(hdlg, IDC_LOG), LB_DELETESTRING, 0, 0);

			SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"게임오버, 가능한 이벤트가 없습니다.");
			SetDlgItemTextA(hdlg, IDC_OK, "재시작"); 
			for (size_t i = 0; i < 6; ++i)
			{
				SetDlgItemTextA(hdlg, RadioButtons[i], "");
				EnableWindow(GetDlgItem(hdlg, RadioButtons[i]), FALSE);
				CheckDlgButton(hdlg, RadioButtons[i], FALSE);
			}
			reset = true;
			break;
		}
		now_event_item.clear();

		SendMessageW(GetDlgItem(hdlg, IDC_LOG), LB_DELETESTRING, 0, 0);
		SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)now_event.name.c_str());
		istringstream iss(now_event.content);
		string buf;
		while (getline(iss, buf))
		{

			wchar_t* wc = new wchar_t[512];

			mbstowcs(wc, buf.data(), buf.size() + 1);

			wstring ws(wc);

			if (ws.size() > 45)
			{
				for (size_t i = 0; i < ws.size(); i += 45)
				{
					SendMessageW(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)ws.substr(i, 45).c_str());
				}
			}
			else
			{
				SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)buf.c_str());
			}
		}

		size_t i = 0;
		
		for (i = 0; i < 6; ++i)
		{
			SetDlgItemTextA(hdlg, RadioButtons[i], "");
			EnableWindow(GetDlgItem(hdlg, RadioButtons[i]), FALSE);
		}

		i = 0;
		for (const auto& s : now_event.item)
			if (s.CanVisible(evt_mng.gamedata))
			{
				now_event_item.push_back(s);
				EnableWindow(GetDlgItem(hdlg, RadioButtons[i]), TRUE);
				SetDlgItemTextA(hdlg, RadioButtons[i++], s.name.c_str());
			}
		iss = istringstream(now_event_item.at(0).content);

		while (getline(iss, buf))
		{
			wchar_t* wc = new wchar_t[512];

			mbstowcs(wc, buf.data(), buf.size() + 1);

			wstring ws(wc);

			if (ws.size() > 20)
			{
				for (size_t i = 0; i < ws.size(); i += 20)
				{
					SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)ws.substr(i, 20).c_str());
				}
			}
			else
			{
				SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)buf.c_str());
			}
		}

		SetDlgItemTextA(hdlg, IDC_FOOD, ("식량 " + RangeToString(evt_mng.gamedata.player.res.food)).c_str());
		SetDlgItemTextA(hdlg, IDC_MONEY, ("돈 " + RangeToString(evt_mng.gamedata.player.res.money)).c_str());
		SetDlgItemTextA(hdlg, IDC_MAN, ("인력 " + RangeToString(evt_mng.gamedata.player.res.human)).c_str());
		SetDlgItemTextA(hdlg, IDC_DIPLO, ("외교력 " + RangeToString(evt_mng.gamedata.player.res.diplo)).c_str());
		SetDlgItemTextA(hdlg, IDC_MILLI, ("군사력 " + RangeToString(evt_mng.gamedata.player.res.milli)).c_str());
		SetDlgItemTextA(hdlg, IDC_FAITH, ("신앙 " + RangeToString(evt_mng.gamedata.player.res.faith)).c_str());
		SetDlgItemTextA(hdlg, IDC_NATION, evt_mng.gamedata.dict["플레이어"].c_str());
				
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_RADIO1:
		{
			select = 0;
			size_t size = SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_GETCOUNT, 0, 0);
			for (int i = 0; i < size; ++i) SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_DELETESTRING, 0, 0);
			istringstream iss(now_event_item.at(0).content);
			string buf;
			while (getline(iss, buf))
			{
				wchar_t* wc = new wchar_t[512];

				mbstowcs(wc, buf.data(), buf.size() + 1);

				wstring ws(wc);

				if (ws.size() > 20)
				{
					for (size_t i = 0; i < ws.size(); i += 20)
					{
						SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)ws.substr(i, 20).c_str());
					}
				}
				else
				{
					SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)buf.c_str());
				}
			}
		}
		break;
		case IDC_RADIO2:
		{
			select = 1;
			size_t size = SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_GETCOUNT, 0, 0);
			for (int i = 0; i < size; ++i) SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_DELETESTRING, 0, 0);
			istringstream iss(now_event_item.at(1).content);
			string buf;
			while (getline(iss, buf))
			{
				wchar_t* wc = new wchar_t[512];

				mbstowcs(wc, buf.data(), buf.size() + 1);

				wstring ws(wc);

				if (ws.size() > 20)
				{
					for (size_t i = 0; i < ws.size(); i += 20)
					{
						SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)ws.substr(i, 20).c_str());
					}
				}
				else
				{
					SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)buf.c_str());
				}
			}
		}
		break;
		case IDC_RADIO3:
		{
			select = 2;
			size_t size = SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_GETCOUNT, 0, 0);
			for (int i = 0; i < size; ++i) SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_DELETESTRING, 0, 0);
			istringstream iss(now_event_item.at(2).content);
			string buf;
			while (getline(iss, buf))
			{
				wchar_t* wc = new wchar_t[512];

				mbstowcs(wc, buf.data(), buf.size() + 1);

				wstring ws(wc);

				if (ws.size() > 20)
				{
					for (size_t i = 0; i < ws.size(); i += 20)
					{
						SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)ws.substr(i, 20).c_str());
					}
				}
				else
				{
					SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)buf.c_str());
				}
			}
		}
		break;
		case IDC_RADIO4:
		{
			select = 3;
			size_t size = SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_GETCOUNT, 0, 0);
			for (int i = 0; i < size; ++i) SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_DELETESTRING, 0, 0);
			istringstream iss(now_event_item.at(3).content);
			string buf;
			while (getline(iss, buf))
			{
				wchar_t* wc = new wchar_t[512];

				mbstowcs(wc, buf.data(), buf.size() + 1);

				wstring ws(wc);

				if (ws.size() > 20)
				{
					for (size_t i = 0; i < ws.size(); i += 20)
					{
						SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)ws.substr(i, 20).c_str());
					}
				}
				else
				{
					SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)buf.c_str());
				}
			}
		}
		break;
		case IDC_RADIO5:
		{
			select = 4;
			size_t size = SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_GETCOUNT, 0, 0);
			for (int i = 0; i < size; ++i) SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_DELETESTRING, 0, 0);
			istringstream iss(now_event_item.at(0).content);
			string buf;
			while (getline(iss, buf))
			{
				wchar_t* wc = new wchar_t[512];

				mbstowcs(wc, buf.data(), buf.size() + 1);

				wstring ws(wc);

				if (ws.size() > 20)
				{
					for (size_t i = 0; i < ws.size(); i += 20)
					{
						SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)ws.substr(i, 20).c_str());
					}
				}
				else
				{
					SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)buf.c_str());
				}
			}
		}
		break;
		case IDC_RADIO6:
		{
			select = 5;
			size_t size = SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_GETCOUNT, 0, 0);
			for (int i = 0; i < size; ++i) SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_DELETESTRING, 0, 0);
			istringstream iss(now_event_item.at(0).content);
			string buf;
			while (getline(iss, buf))
			{
				wchar_t* wc = new wchar_t[512];

				mbstowcs(wc, buf.data(), buf.size() + 1);

				wstring ws(wc);

				if (ws.size() > 20)
				{
					for (size_t i = 0; i < ws.size(); i += 20)
					{
						SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)ws.substr(i, 20).c_str());
					}
				}
				else
				{
					SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)buf.c_str());
				}
			}
		}
		break;
		case IDC_OK:
			if (reset)
			{
				size_t size = SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_GETCOUNT, 0, 0);
				for (int i = 0; i < size; ++i) SendMessageW(GetDlgItem(hdlg, IDC_LOG), LB_DELETESTRING, 0, 0);
				evt_mng.gamedata = Gamedata();
				SetDlgItemTextA(hdlg, IDC_OK, "확인");
				reset = false;
			}
			else
			{
				if (now_event_item.size())
				{
					size_t size = SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_GETCOUNT, 0, 0);
					for (int i = 0; i < size; ++i) SendMessageW(GetDlgItem(hdlg, IDC_LOG), LB_DELETESTRING, 0, 0);
					SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)("〈" + now_event_item.at(select).name + "〉").c_str());
					istringstream iss(now_event_item.at(select).content);
					string buf;
					while (getline(iss, buf))
					{
						wchar_t* wc = new wchar_t[512];

						mbstowcs(wc, buf.data(), buf.size() + 1);

						wstring ws(wc);

						if (ws.size() > 45)
						{
							for (size_t i = 0; i < ws.size(); i += 45)
							{
								SendMessageW(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)ws.substr(i, 45).c_str());
							}
						}
						else
						{
							SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)buf.c_str());
						}
					}
					now_event_item.at(select).Effect(evt_mng.gamedata);
				}
				if (evt_mng.gamedata.player.res.diplo < 0)
				{
					if (-evt_mng.gamedata.player.res.diplo <= evt_mng.gamedata.player.res.faith)
					{
						evt_mng.gamedata.player.res.faith += evt_mng.gamedata.player.res.diplo;
						evt_mng.gamedata.player.res.diplo = 0;
					}
					else
					{
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"======================================================================");
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"당신의 국가는 외교가 부족하여 멸망했습니다.그 누구도 당신의 외침을 들으려 하지 ");
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"않습니다. 외교적인 노력의 부족함이 낳은 결과입니다...");
						SendMessage(GetDlgItem(hdlg, IDC_LOG), EM_LINESCROLL, 0, 32767);
						SetDlgItemTextA(hdlg, IDC_OK, "재시작");
						for (size_t i = 0; i < 6; ++i)
						{
							SetDlgItemTextA(hdlg, RadioButtons[i], "");
							EnableWindow(GetDlgItem(hdlg, RadioButtons[i]), FALSE);
							CheckDlgButton(hdlg, RadioButtons[i], FALSE);
						}
						reset = true;
						break;
					}
				}
				if (evt_mng.gamedata.player.res.milli < 0)
				{
					if (-evt_mng.gamedata.player.res.milli <= evt_mng.gamedata.player.res.faith)
					{
						evt_mng.gamedata.player.res.faith += evt_mng.gamedata.player.res.milli;
						evt_mng.gamedata.player.res.milli = 0;
					}
					else
					{
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"======================================================================");
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"당신의 국가는 무력이 부족하여 멸망했습니다.당신의 군대는 맞서지 않고 후퇴에 후퇴를");
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"거듭한 끝에 당신의 궁성에 도달했습니다.군사적 노력의 부족함이 낳은 결과입니다...");
						SendMessage(GetDlgItem(hdlg, IDC_LOG), EM_LINESCROLL, 0, 32767);
						SetDlgItemTextA(hdlg, IDC_OK, "재시작");
						for (size_t i = 0; i < 6; ++i)
						{
							SetDlgItemTextA(hdlg, RadioButtons[i], "");
							EnableWindow(GetDlgItem(hdlg, RadioButtons[i]), FALSE);
							CheckDlgButton(hdlg, RadioButtons[i], FALSE);
						}
						reset = true;
						break;
					}
				}
				if (evt_mng.gamedata.player.res.food < 0)
				{
					if (-evt_mng.gamedata.player.res.food <= evt_mng.gamedata.player.res.faith)
					{
						evt_mng.gamedata.player.res.faith += evt_mng.gamedata.player.res.food;
						evt_mng.gamedata.player.res.food = 0;
					}
					else
					{
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"======================================================================");
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"당신의 국가는 식량이 부족하여 멸망했습니다.당신의 식량창고에는 단 한 톨의 쌀도 남");
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"지 않았고 관리들은 전부 떠났습니다.식량이 없이는 어떤 국가도 존속할 수 없습니다.");
						SendMessage(GetDlgItem(hdlg, IDC_LOG), EM_LINESCROLL, 0, 32767);
						SetDlgItemTextA(hdlg, IDC_OK, "재시작");
						for (size_t i = 0; i < 6; ++i)
						{
							SetDlgItemTextA(hdlg, RadioButtons[i], "");
							EnableWindow(GetDlgItem(hdlg, RadioButtons[i]), FALSE);
							CheckDlgButton(hdlg, RadioButtons[i], FALSE);
						}
						reset = true;
						break;
					}
				}
				if (evt_mng.gamedata.player.res.human < 0)
				{
					if (-evt_mng.gamedata.player.res.human <= evt_mng.gamedata.player.res.faith)
					{
						evt_mng.gamedata.player.res.faith += evt_mng.gamedata.player.res.human;
						evt_mng.gamedata.player.res.human = 0;
					}
					else
					{
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"======================================================================");
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"당신의 국가는 인력이 부족하여 멸망했습니다.아무도 성에 남아 있지 않습니다. 더 이");
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"상 부족이라고도 부끄러운 수준입니다.사람이 있어야 국가도 있는법입니다.");
						SendMessage(GetDlgItem(hdlg, IDC_LOG), EM_LINESCROLL, 0, 32767);
						SetDlgItemTextA(hdlg, IDC_OK, "재시작");
						for (size_t i = 0; i < 6; ++i)
						{
							SetDlgItemTextA(hdlg, RadioButtons[i], "");
							EnableWindow(GetDlgItem(hdlg, RadioButtons[i]), FALSE);
							CheckDlgButton(hdlg, RadioButtons[i], FALSE);
						}
						reset = true;
						break;
					}
				}
				if (evt_mng.gamedata.player.res.money < 0)
				{
					if (-evt_mng.gamedata.player.res.money <= evt_mng.gamedata.player.res.faith)
					{
						evt_mng.gamedata.player.res.faith += evt_mng.gamedata.player.res.money;
						evt_mng.gamedata.player.res.money = 0;
					}
					else
					{
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"======================================================================");
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"당신의 국가는 돈이 부족하여 멸망했습니다. 더 이상 관리에게 지급해줄 돈이 없고 관");
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"리는 월급체불에 질려 모두 궁성을 떠났습니다.돈이 없다면 아무것도 할 수 없습니다.");
						SendMessage(GetDlgItem(hdlg, IDC_LOG), EM_LINESCROLL, 0, 32767);
						SetDlgItemTextA(hdlg, IDC_OK, "재시작");
						for (size_t i = 0; i < 6; ++i)
						{
							SetDlgItemTextA(hdlg, RadioButtons[i], "");
							EnableWindow(GetDlgItem(hdlg, RadioButtons[i]), FALSE);
							CheckDlgButton(hdlg, RadioButtons[i], FALSE);
						}
						reset = true;
						break;
					}
				}
				if (evt_mng.gamedata.player.res.faith < 0)
				{
					SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"======================================================================");
					SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"당신의 국가는 신앙이 부족하여 멸망했습니다.국민들은 아무도 서로 믿으려 하지 않고");
					SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"신하들조차 왕을 따르려 하지 않습니다.신앙이 없다면 그 국가는 존재할 수 없습니다.");
					SetDlgItemTextA(hdlg, IDC_OK, "재시작");
					for (size_t i = 0; i < 6; ++i)
					{
						SetDlgItemTextA(hdlg, RadioButtons[i], "");
						EnableWindow(GetDlgItem(hdlg, RadioButtons[i]), FALSE);
						CheckDlgButton(hdlg, RadioButtons[i], FALSE);
					}
					reset = true;
					break;
				}
			}
			SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"=============================================================");
			SendMessage(GetDlgItem(hdlg, IDC_RADIO1), BM_SETCHECK, (WPARAM)TRUE, (LPARAM)NULL);
			{
				size_t size = SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_GETCOUNT, 0, 0);
				for (int i = 0; i < size; ++i) SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_DELETESTRING, 0, 0);

				try
				{
					now_event = evt_mng.GetNewEvent();
				}
				catch (exception)
				{
					size_t size = SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_GETCOUNT, 0, 0);
					for (int i = 0; i < size; ++i) SendMessageW(GetDlgItem(hdlg, IDC_LOG), LB_DELETESTRING, 0, 0);

					SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)"게임오버, 가능한 이벤트가 없습니다.");
					SetDlgItemTextA(hdlg, IDC_OK, "재시작");
					reset = true;
					for (size_t i = 0; i < 6; ++i)
					{
						SetDlgItemTextA(hdlg, RadioButtons[i], "");
						EnableWindow(GetDlgItem(hdlg, RadioButtons[i]), FALSE);
						CheckDlgButton(hdlg, RadioButtons[i], FALSE);
					}
					break;
				}
				now_event_item.clear();

				SendMessageW(GetDlgItem(hdlg, IDC_LOG), LB_DELETESTRING, 0, 0);
				SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)("「" + now_event.name + "」").c_str());
				istringstream iss(now_event.content);
				string buf;
				while (getline(iss, buf))
				{

					wchar_t* wc = new wchar_t[512];

					mbstowcs(wc, buf.data(), buf.size() + 1);

					wstring ws(wc);

					if (ws.size() > 45)
					{
						for (size_t i = 0; i < ws.size(); i += 45)
						{
							SendMessageW(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)ws.substr(i, 45).c_str());
						}
					}
					else
					{
						SendMessageA(GetDlgItem(hdlg, IDC_LOG), LB_ADDSTRING, 0, (LPARAM)buf.c_str());
					}
				}

				size_t i = 0;

				for (i = 0; i < 6; ++i)
				{
					SetDlgItemTextA(hdlg, RadioButtons[i], "");
					EnableWindow(GetDlgItem(hdlg, RadioButtons[i]), FALSE);
				}

				i = 0;
				for (const auto& s : now_event.item)
					if (s.CanVisible(evt_mng.gamedata))
					{
						now_event_item.push_back(s);
						EnableWindow(GetDlgItem(hdlg, RadioButtons[i]), TRUE);
						SetDlgItemTextA(hdlg, RadioButtons[i++], s.name.c_str());
					}

				select = 0;


				for (i = 0; i < 6; ++i) SendMessage(GetDlgItem(hdlg, RadioButtons[i]), BM_SETCHECK, (WPARAM)FALSE, (LPARAM)NULL);
				SendMessage(GetDlgItem(hdlg, RadioButtons[0]), BM_SETCHECK, (WPARAM)TRUE, (LPARAM)NULL);
			}
			if (now_event_item.size() > 0)
			{
				SetDlgItemTextA(hdlg, IDC_FOOD, ("식량 " + RangeToString(evt_mng.gamedata.player.res.food)).c_str());
				SetDlgItemTextA(hdlg, IDC_MONEY, ("돈 " + RangeToString(evt_mng.gamedata.player.res.money)).c_str());
				SetDlgItemTextA(hdlg, IDC_MAN, ("인력 " + RangeToString(evt_mng.gamedata.player.res.human)).c_str());
				SetDlgItemTextA(hdlg, IDC_DIPLO, ("외교력 " + RangeToString(evt_mng.gamedata.player.res.diplo)).c_str());
				SetDlgItemTextA(hdlg, IDC_MILLI, ("군사력 " + RangeToString(evt_mng.gamedata.player.res.milli)).c_str());
				SetDlgItemTextA(hdlg, IDC_FAITH, ("신앙 " + RangeToString(evt_mng.gamedata.player.res.faith)).c_str());
				SetDlgItemTextA(hdlg, IDC_NATION, evt_mng.gamedata.dict["플레이어"].c_str());
				istringstream iss(now_event_item.at(0).content);
				string buf;
				while (getline(iss, buf))
				{
					wchar_t* wc = new wchar_t[512];

					mbstowcs(wc, buf.data(), buf.size() + 1);

					wstring ws(wc);

					if (ws.size() > 20)
					{
						for (size_t i = 0; i < ws.size(); i += 20)
						{
							SendMessageW(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)ws.substr(i, 20).c_str());
						}
					}
					else
					{
						SendMessageA(GetDlgItem(hdlg, IDC_SELECT_CONTENT), LB_ADDSTRING, 0, (LPARAM)buf.c_str());
					}
				}
			}
			break;
		case IDCANCEL:
		case IDABORT:
			EndDialog(hdlg, 0);
			break;
		}
		break;	
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		DialogBoxA(hInst, MAKEINTRESOURCEA(IDD_DIALOG1), hWnd, MsgProc);
		PostQuitMessage(0);
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
