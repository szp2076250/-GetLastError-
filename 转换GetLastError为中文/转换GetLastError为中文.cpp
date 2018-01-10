#include "stdafx.h"
#include <iostream>
#include <Windows.h>

wchar_t * ConverErrorMessage(UINT dwError)
{
	HLOCAL hlocal = NULL;
	DWORD systemLocale = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);

	auto fOk = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
		FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL, dwError, systemLocale,
		(PTSTR)&hlocal, 0, NULL);

	if (!fOk) {
		HMODULE hDll = LoadLibraryEx(TEXT("netmsg.dll"), NULL,
			DONT_RESOLVE_DLL_REFERENCES);

		if (hDll != NULL) 
		{
			fOk = FormatMessage(
			FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_ALLOCATE_BUFFER,
			hDll, dwError, systemLocale,
			(PTSTR)&hlocal, 0, NULL);
			FreeLibrary(hDll);
		}
	}

	if (fOk && (hlocal != NULL)) 
	{
		auto buf = new wchar_t[fOk];
		auto tempbuf = (PCTSTR)LocalLock(hlocal);
		auto length = wcslen(tempbuf);
		wcscpy_s(buf, length + sizeof(wchar_t), tempbuf);
		LocalFree(hlocal);
		return buf;
	}
	else return L"find nothing about this code";
}

int main(int argc, char *argv[])
{
	do
	{
		setlocale(LC_ALL, "chs");
		wprintf_s(L"ÇëÊäÈëGetLastErrorµÄ´íÎóÂë:\n");
		UINT code;
		std::cin >> code;
		auto ret = ConverErrorMessage(code);
		MessageBox(NULL, ret, NULL, NULL);
		wprintf_s(L"%ls\n", ret);
		wprintf_s(L"ÊÇ·ñ¼ÌÐø(Y/N):\n");
	} while (getchar()=='Y'|| getchar()=='y');
	return 0;
}
