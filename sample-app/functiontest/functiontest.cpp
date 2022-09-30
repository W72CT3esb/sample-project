#include <iostream>
#include <Shlwapi.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>

const int DEFINE_STRING_SIZE = 1024;

int count_imagefile(std::string input_image_path);

// �@�\�e�X�g
int ImageData_PositiveTest();

int main(void)
{
	double elapsed_time = 0.0;
	int fps = 0;
	int iret = -1;

	// �Î~��̋@�\�e�X�g�i����n�j
	std::cout << "[ RUN      ] FunctionTest." << std::endl;
	iret = ImageData_PositiveTest();
	if (iret != 0)
	{
		std::cout << "FunctionTest failed! status code:" << iret << std::endl;
		std::cout << "[  FAILED  ] FunctionTest" << std::endl;
		return -1;
	}
	std::cout << "[       OK ] FunctionTest" << std::endl;
	return 0;
}

int ImageData_PositiveTest()
{
	std::chrono::system_clock::time_point  start, end;
	double elapsed_time = 0.0;
	char output_dirpath[DEFINE_STRING_SIZE];
	char input_image_path[DEFINE_STRING_SIZE];
	std::string str_buf;
	std::string str_conma_buf;
	std::string output_filepath;
	std::vector<std::string> line;
	char data_type_pre[DEFINE_STRING_SIZE];
	int frame_num = 0;
	int image_file_num = 0;
	int data_type = -1;
	int iret = -1;

	// ���݂�data_type�̏���ۑ�
	GetPrivateProfileString("input", "data_type", "", data_type_pre, sizeof(data_type_pre), ".\\config.ini");

	// �ݒ�t�@�C������data_type��1:�摜�ɕύX
	WritePrivateProfileString("input", "data_type", "1", ".\\config.ini");

	// �T���v���A�v��(sample-app.exe)�̎��s����
	iret = system(".\\sample-app.exe");

	// �@�i����I�����Ă��邩�j
	if (iret != 0)
	{
		return -1;
	}

	// �ݒ�t�@�C������data_type���擾�i�摜�f�[�^�������Ɗm�F�j
	data_type = GetPrivateProfileInt("input", "data_type", -1, ".\\config.ini");
	if (data_type != 1) //�摜�ȊO�̃f�[�^�̏ꍇ���s
	{
		return -2;
	}

	// �ݒ�t�@�C������o�͌��ʂ̃t�@�C���p�X���擾
	GetPrivateProfileString("output", "output_dirpath", "", output_dirpath, sizeof(output_dirpath), ".\\config.ini");
	output_filepath = std::string(output_dirpath) + "\\result.csv";

	// �A�w��̏ꏊ�ɏ������ʂ��o�͂���Ă��邩
	if (!PathFileExists(output_filepath.c_str())) // �p�X�̏ꏊ�ɏo�̓f�B���N�g�������݂��邩�ǂ���
	{
		return -3;
	}

	// �ݒ�t�@�C������摜�f�[�^�̃t�H���_�p�X���擾
	GetPrivateProfileString("input", "input_image_path", "", input_image_path, sizeof(input_image_path), ".\\config.ini");
	image_file_num = count_imagefile(std::string(input_image_path));

	// �ǂݍ���csv�t�@�C�����J��(std::ifstream�̃R���X�g���N�^�ŊJ��)
	std::ifstream ifs_csv_file(output_filepath);

	// getline�֐���1�s���ǂݍ���(�ǂݍ��񂾓��e��str_buf�Ɋi�[)
	while (getline(ifs_csv_file, str_buf)) {

		line.push_back(str_buf);
	}

	// �Ō�̍s��istringstream�Ɋi�[����
	std::istringstream i_stream(line[line.size() - 1]);

	// �s�̐擪��frame�ԍ����擾���邽�߂Ɉ��̂�getline���Ă�
	getline(i_stream, str_conma_buf, ',');
	frame_num = atoi(str_conma_buf.c_str()) + 1;

	// �B���ʃt�@�C���ɓ��͉摜�������̌��ʂ��o�͂���Ă��邩
	if (image_file_num != frame_num)
	{
		return -4;
	}

	// �ݒ�t�@�C������data_type��O�̏��ɖ߂�
	WritePrivateProfileString("input", "data_type", data_type_pre, ".\\config.ini");

	return 0;
}

int count_imagefile(std::string input_image_path)
{
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;
	std::vector<std::string> file_names;
	std::vector<std::string> extension = { "png" ,"jpg", "bmp" };

	for (int i = 0; i < extension.size(); i++)
	{

		std::string search_name = input_image_path + "\\*." + extension[i];

		// �w�肵���t�@�C�����Ɉ�v����t�@�C����f�B���N�g��������(�߂�l�͐����F�����n���h��,���s�F-1(INVALID_HANDLE_VALUE))
		hFind = FindFirstFile(search_name.c_str(), &win32fd);

		if (hFind == INVALID_HANDLE_VALUE) // �t�@�C�������Ɏ��s�����ꍇ(return������ƁA�摜�t�@�C����jpg�����̎��Ȃǂ�png��bmp�͑��݂��Ȃ����߁A�����I�����Ă��܂�)
		{
			continue;
		}
		do
		{
			file_names.push_back(input_image_path + "\\" + win32fd.cFileName);
		} while (FindNextFile(hFind, &win32fd)); // FindFirstFile �֐��̌Ăяo���ɂ�錟���𑱍s(�߂�l�͐����F0�ȊO,���s�F0)

												 // �w�肳�ꂽ�����n���h�����N���[�Y(�߂�l�͐����F0�ȊO,���s�F0)
		FindClose(hFind);
	}
	return int(file_names.size());
}