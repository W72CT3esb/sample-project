#include <iostream>
#include <string>
#include <Shlwapi.h>
#include "paramloader.h"
#include "common.h"

const int DEFINE_CHAR_SIZE = 1024;

// コンストラクタ
ParamLoader::ParamLoader()
{
	std::cout << "ParamLoaderオブジェクト生成" << std::endl;
}

// デストラクタ
ParamLoader::~ParamLoader()
{
	std::cout << "ParamLoaderオブジェクト破棄" << std::endl;
}

// 設定ファイルからパラメータをロードする関数
int ParamLoader::load_param(Params &params)
{
	char str_buf[DEFINE_CHAR_SIZE]; // char型のバッファ
	DWORD dret = 0;
	bool iret = false;

	iret = SetWorkingDirectory(); // カレントディレクトリに移動
	if (!iret) // カレントディレクトリに移動失敗
	{
		return -1;
	}

	if (!PathFileExists(this->CONFIG_FILEPATH.c_str())) // 設定ファイルがなくて失敗
	{
		return -2;
	}
	
	params.device_id = GetPrivateProfileInt("camera", "device_id", -1, this->CONFIG_FILEPATH.c_str());
	if (params.device_id != 0) // 0以外は失敗（セクションからキーワードを取れてこれなかった）
	{
		return -3;
	}

	params.c_frame_width = GetPrivateProfileInt("camera", "c_frame_width", -1, this->CONFIG_FILEPATH.c_str());
	if (params.c_frame_width == -1) // -1は失敗（セクションからキーワードを取れてこれなかった）
	{
		return -4;
	}
	if (params.c_frame_width <= 0) // 0以下は失敗
	{
		return -5;
	}

	params.c_frame_height = GetPrivateProfileInt("camera", "c_frame_height", -1, this->CONFIG_FILEPATH.c_str());
	if (params.c_frame_height == -1) // -1は失敗（セクションからキーワードを取れてこれなかった）
	{
		return -6;
	}
	if (params.c_frame_height <= 0) // 0以下は失敗
	{
		return -7;
	}

	params.c_fps = GetPrivateProfileInt("camera", "c_fps", -1, this->CONFIG_FILEPATH.c_str());
	if (params.c_fps == -1) // -1は失敗（セクションからキーワードを取れてこれなかった）
	{
		return -8;
	}
	if (params.c_fps <= 0) // 0以下は失敗
	{
		return -9;
	}

	params.data_type = GetPrivateProfileInt("input", "data_type", -1, this->CONFIG_FILEPATH.c_str());
	if (params.data_type == -1) // -1は失敗（セクションからキーワードを取れてこれなかった）
	{
		return -10;
	}
	if (params.data_type != 0 && params.data_type != 1 && params.data_type != 2) // 0,1,2以外は失敗
	{
		return -11;
	}

	dret = GetPrivateProfileString("input", "input_movie_path", "", str_buf, sizeof(str_buf), this->CONFIG_FILEPATH.c_str());
	if (dret <= 0) // 0以下は失敗（セクションからキーワードを取れてこれなかった）
	{
		return -12;
	}
	if (std::strlen(str_buf) == 0) // stringが空の場合は失敗
	{
		return -13;
	}
	params.input_movie_path = str_buf;

	dret = GetPrivateProfileString("input", "input_image_path", "", str_buf, sizeof(str_buf), this->CONFIG_FILEPATH.c_str());
	if (dret <= 0) // 0以下は失敗（セクションからキーワードを取れてこれなかった）
	{
		return -14;
	}
	if (std::strlen(str_buf) == 0) // stringが空の場合は失敗
	{
		return -15;
	}
	params.input_image_path = str_buf;

	dret = GetPrivateProfileString("detector", "cascade_filepath", "", str_buf, sizeof(str_buf), this->CONFIG_FILEPATH.c_str());
	if (dret <= 0) // 0以下は失敗（セクションからキーワードを取れてこれなかった）
	{
		return -16;
	}
	if (std::strlen(str_buf) == 0) // stringが空の場合は失敗
	{
		return -17;
	}

	params.face_detect_width = GetPrivateProfileInt("detector", "face_detect_width", -1, this->CONFIG_FILEPATH.c_str());
	if (params.face_detect_width == -1) // -1は失敗（セクションからキーワードを取れてこれなかった）
	{
		return -18;
	}
	if (params.face_detect_width <= 0) // 0以下は失敗
	{
		return -19;
	}

	params.face_detect_height = GetPrivateProfileInt("detector", "face_detect_height", -1, this->CONFIG_FILEPATH.c_str());
	if (params.face_detect_height == -1) // -1は失敗（セクションからキーワードを取れてこれなかった）
	{
		return -20;
	}
	if (params.face_detect_height <= 0) // 0以下は失敗
	{
		return -21;
	}
	params.cascade_filepath = str_buf;

	dret = GetPrivateProfileString("output", "output_dirpath", "", str_buf, sizeof(str_buf), this->CONFIG_FILEPATH.c_str());
	if (dret <= 0) //0以下は失敗（セクションからキーワードを取れてこれなかった）
	{
		return -22;
	}
	if (std::strlen(str_buf) == 0) // stringが空の場合は失敗
	{
		return -23;
	}
	params.output_dirpath = str_buf;

	return 0;
}
