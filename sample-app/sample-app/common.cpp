#include <stdio.h>
#include <Windows.h>
#include <iostream>

const int DEFINE_STRING_SIZE=1024;

// �J�����g�f�B���N�g���Ɉړ�����֐�
bool SetWorkingDirectory()
{
	DWORD dret = 0;
	BOOL bret = false;

	char buff[DEFINE_STRING_SIZE] = {};
	char drive[DEFINE_STRING_SIZE] = {};
	char dir[DEFINE_STRING_SIZE] = {};
	char path[DEFINE_STRING_SIZE] = {};

	dret = GetModuleFileName(nullptr, buff, DEFINE_STRING_SIZE);

	if (!dret) // ���s�����ꍇ
	{
		return false;
	}

	_splitpath_s(buff, drive, DEFINE_STRING_SIZE, dir, DEFINE_STRING_SIZE, nullptr, 0, nullptr, 0);
	sprintf_s(path, DEFINE_STRING_SIZE, "%s%s", drive, dir);
	bret = SetCurrentDirectory(path);

	if (!bret) // ���s�����ꍇ
	{
		return false;
	}

	return true;
}