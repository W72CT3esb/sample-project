#include <iostream>
#include <string>
#include <Shlwapi.h>
#include "paramloader.h"
#include "common.h"

const int DEFINE_CHAR_SIZE = 1024;

// �R���X�g���N�^
ParamLoader::ParamLoader()
{
	//std::cout << "ParamLoader�I�u�W�F�N�g����" << std::endl;
}

// �f�X�g���N�^
ParamLoader::~ParamLoader()
{
	//std::cout << "ParamLoader�I�u�W�F�N�g�j��" << std::endl;
}

// �ݒ�t�@�C������p�����[�^�����[�h����֐�
int ParamLoader::load_param(Params &params)
{
	char str_buf[DEFINE_CHAR_SIZE]; // char�^�̃o�b�t�@
	DWORD dret = 0;
	bool iret = false;

	iret = SetWorkingDirectory(); // �J�����g�f�B���N�g���Ɉړ�
	if (!iret) // �J�����g�f�B���N�g���Ɉړ����s
	{
		return -1;
	}

	if (!PathFileExists(this->CONFIG_FILEPATH.c_str())) // �ݒ�t�@�C�����Ȃ��Ď��s
	{
		return -2;
	}
	
	params.device_id = GetPrivateProfileInt("camera", "device_id", -1, this->CONFIG_FILEPATH.c_str());
	if (params.device_id != 0) // 0�ȊO�͎��s�i�Z�N�V��������L�[���[�h�����Ă���Ȃ������j
	{
		return -3;
	}

	params.c_frame_width = GetPrivateProfileInt("camera", "c_frame_width", -1, this->CONFIG_FILEPATH.c_str());
	if (params.c_frame_width == -1) // -1�͎��s�i�Z�N�V��������L�[���[�h�����Ă���Ȃ������j
	{
		return -4;
	}
	if (params.c_frame_width <= 0) // 0�ȉ��͎��s
	{
		return -5;
	}

	params.c_frame_height = GetPrivateProfileInt("camera", "c_frame_height", -1, this->CONFIG_FILEPATH.c_str());
	if (params.c_frame_height == -1) // -1�͎��s�i�Z�N�V��������L�[���[�h�����Ă���Ȃ������j
	{
		return -6;
	}
	if (params.c_frame_height <= 0) // 0�ȉ��͎��s
	{
		return -7;
	}

	params.c_fps = GetPrivateProfileInt("camera", "c_fps", -1, this->CONFIG_FILEPATH.c_str());
	if (params.c_fps == -1) // -1�͎��s�i�Z�N�V��������L�[���[�h�����Ă���Ȃ������j
	{
		return -8;
	}
	if (params.c_fps <= 0) // 0�ȉ��͎��s
	{
		return -9;
	}

	params.data_type = GetPrivateProfileInt("input", "data_type", -1, this->CONFIG_FILEPATH.c_str());
	if (params.data_type == -1) // -1�͎��s�i�Z�N�V��������L�[���[�h�����Ă���Ȃ������j
	{
		return -10;
	}
	if (params.data_type != 0 && params.data_type != 1 && params.data_type != 2) // 0,1,2�ȊO�͎��s
	{
		return -11;
	}

	dret = GetPrivateProfileString("input", "input_movie_path", "", str_buf, sizeof(str_buf), this->CONFIG_FILEPATH.c_str());
	if (dret <= 0 || std::strlen(str_buf) == 0) // 0�ȉ��i�Z�N�V��������L�[���[�h�����Ă���Ȃ������j�܂��́Astring����̏ꍇ�͎��s
	{
		return -12;
	}
	params.input_movie_path = str_buf;

	dret = GetPrivateProfileString("input", "input_image_path", "", str_buf, sizeof(str_buf), this->CONFIG_FILEPATH.c_str());
	if (dret <= 0 || std::strlen(str_buf) == 0) // 0�ȉ��i�Z�N�V��������L�[���[�h�����Ă���Ȃ������j�܂��́Astring����̏ꍇ�͎��s
	{
		return -13;
	}
	params.input_image_path = str_buf;

	dret = GetPrivateProfileString("detector", "cascade_filepath", "", str_buf, sizeof(str_buf), this->CONFIG_FILEPATH.c_str());
	if (dret <= 0 || std::strlen(str_buf) == 0) // 0�ȉ��i�Z�N�V��������L�[���[�h�����Ă���Ȃ������j�܂��́Astring����̏ꍇ�͎��s
	{
		return -14;
	}
	params.cascade_filepath = str_buf;

	params.face_detect_width = GetPrivateProfileInt("detector", "face_detect_width", -1, this->CONFIG_FILEPATH.c_str());
	if (params.face_detect_width == -1) // -1�͎��s�i�Z�N�V��������L�[���[�h�����Ă���Ȃ������j
	{
		return -15;
	}
	if (params.face_detect_width <= 0) // 0�ȉ��͎��s
	{
		return -16;
	}

	params.face_detect_height = GetPrivateProfileInt("detector", "face_detect_height", -1, this->CONFIG_FILEPATH.c_str());
	if (params.face_detect_height == -1) // -1�͎��s�i�Z�N�V��������L�[���[�h�����Ă���Ȃ������j
	{
		return -17;
	}
	if (params.face_detect_height <= 0) // 0�ȉ��͎��s
	{
		return -18;
	}

	dret = GetPrivateProfileString("output", "output_dirpath", "", str_buf, sizeof(str_buf), this->CONFIG_FILEPATH.c_str());
	if (dret <= 0 || std::strlen(str_buf) == 0) // 0�ȉ��i�Z�N�V��������L�[���[�h�����Ă���Ȃ������j�܂��́Astring����̏ꍇ�͎��s
	{
		return -19;
	}
	params.output_dirpath = str_buf;

	return 0;
}
