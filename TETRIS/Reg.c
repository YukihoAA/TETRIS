#include "TETRIS.h"

// 정수값을 읽는다.
UINT RegReadInt(HKEY hKey, LPCSTR lpKey, LPCSTR lpValue, INT nDefault)
{
	HKEY key;
	DWORD dwDisp;
	UINT Result;
	DWORD Size;
	if (RegCreateKeyExA(hKey, lpKey,0,NULL,
		REG_OPTION_NON_VOLATILE, KEY_READ,NULL,&key,&dwDisp)
		!=ERROR_SUCCESS) 
		return 0;
	Size=sizeof(LONG);
	if (RegQueryValueExA(key, lpValue, 0, NULL,(LPBYTE)&Result, &Size)
		!=ERROR_SUCCESS)
		Result=nDefault;
	RegCloseKey(key);
	return Result;
}

// 문자열을 읽는다.
BOOL RegReadStr(HKEY hKey, LPCSTR lpKey, LPCSTR lpValue, LPCSTR lpDefault, 
	LPSTR lpRet, DWORD nSize) 
{
	HKEY key;
	DWORD dwDisp;
	DWORD Size;
	if (RegCreateKeyExA(hKey, lpKey,0,NULL,
		REG_OPTION_NON_VOLATILE, KEY_READ,NULL,&key,&dwDisp)
		!=ERROR_SUCCESS) 
		return FALSE;
	Size=nSize;
	if (RegQueryValueExA(key, lpValue, 0, NULL,(LPBYTE)lpRet, &Size)
		!=ERROR_SUCCESS) {
			strcpy(lpRet, lpDefault);
			return FALSE;
	}
	RegCloseKey(key);
	return TRUE;
}

// 정수값을 쓴다.
BOOL RegWriteInt(HKEY hKey, LPCSTR lpKey, LPCSTR lpValue, UINT nData)
{
	HKEY key;
	DWORD dwDisp;
	if (RegCreateKeyExA(hKey, lpKey,0,NULL,
		REG_OPTION_NON_VOLATILE, KEY_WRITE,NULL,&key,&dwDisp)
		!=ERROR_SUCCESS) {
			return FALSE;
	}
	if (RegSetValueExA(key, lpValue,0,REG_DWORD,(LPBYTE)&nData,sizeof(UINT))
		!=ERROR_SUCCESS) 
		return FALSE;
	RegCloseKey(key);
	return TRUE;
}

// 문자열을 쓴다.
BOOL RegWriteStr(HKEY hKey, LPCSTR lpKey, LPCSTR lpValue, LPCSTR lpData)
{
	HKEY key;
	DWORD dwDisp;
	if (RegCreateKeyExA(hKey, lpKey,0,NULL,
		REG_OPTION_NON_VOLATILE, KEY_WRITE,NULL,&key,&dwDisp)
		!=ERROR_SUCCESS) 
		return FALSE;
	if (RegSetValueExA(key,lpValue,0,REG_SZ,(LPBYTE)lpData,sizeof(LPCSTR)*strlen(lpData))
		!=ERROR_SUCCESS) 
		return FALSE;
	RegCloseKey(key);
	return TRUE;
}


