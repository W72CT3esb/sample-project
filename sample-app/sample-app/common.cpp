#include <stdio.h>
#include <Windows.h>
#include <iostream>

const int DEFINE_STRING_SIZE=1024;

// カレントディレクトリに移動する関数
bool SetWorkingDirectory()
{
	DWORD dret = 0;
	BOOL bret = false;

	char buff[DEFINE_STRING_SIZE] = {};
	char drive[DEFINE_STRING_SIZE] = {};
	char dir[DEFINE_STRING_SIZE] = {};
	char path[DEFINE_STRING_SIZE] = {};

	dret = GetModuleFileName(nullptr, buff, DEFINE_STRING_SIZE);

	if (!dret) // 失敗した場合
	{
		return false;
	}

	_splitpath_s(buff, drive, DEFINE_STRING_SIZE, dir, DEFINE_STRING_SIZE, nullptr, 0, nullptr, 0);
	sprintf_s(path, DEFINE_STRING_SIZE, "%s%s", drive, dir);
	bret = SetCurrentDirectory(path);

	if (!bret) // 失敗した場合
	{
		return false;
	}

	return true;
}