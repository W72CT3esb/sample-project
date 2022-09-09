#include <iostream>
#include <Shlwapi.h>
#include <direct.h>
#include <fstream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "common.h"
#include "dataloader.h"
#include "filewriter.h"

std::ofstream writing_file;

// �R���X�g���N�^
FileWriter::FileWriter()
{
	//std::cout << "FileWriter�I�u�W�F�N�g����" << std::endl;
	this->output_dirpath = "";
	this->file_open_flag = false;
	//throw std::exception();
}

// �f�X�g���N�^
FileWriter::~FileWriter()
{
	//std::cout << "FileWriter�I�u�W�F�N�g�j��" << std::endl;
	writing_file.close();
	//throw std::exception();
}

// �������֐�
int FileWriter::initialize(const Params &params)
{
	if (!PathFileExists(params.output_dirpath.c_str())) // �p�X�̏ꏊ�ɏo�̓f�B���N�g�������݂��邩�ǂ���
	{
		if (_mkdir(params.output_dirpath.c_str()) != 0) // �f�B���N�g���̍쐬�ł������ǂ���
		{
			//std::cout << "�o�̓f�B���N�g�����쐬�ł��܂���ł���" << std::endl;
			return -1;
		}
	}
	this->output_dirpath = params.output_dirpath;

	return 0;
}

// �t�@�C�����I�[�v������֐�
int FileWriter::open_file()
{
	if (this->file_open_flag) // �֐�����ȏ�͎��s�����Ȃ�(false�̎��Ɏ��s)
	{
		return -1;
	}

	writing_file.open(this->output_dirpath + "\\" + this->OUTPUT_FILE_NAME);

	if (!writing_file.is_open()) // �ُ�I��
	{
		//std::cout << "�t�@�C�����J���܂���ł���" << std::endl;
		return -2;
	}
	this->file_open_flag = true;

	// �o�̓t�@�C���Ƀt�B�[���h���L��
	writing_file << "frame�ԍ�" << "," << "x���W" << "," << "y���W" << "," << "����" << "," << "�c��" << std::endl;

	return 0;
}

// �t�@�C���o�͂���֐�
int FileWriter::output_file(DataLoader &dataloader, cv::Mat &img, std::vector<cv::Rect> &faces)
{
	if (!this->file_open_flag) // �o�̓t�@�C�����I�[�v�����Ă��Ȃ��ꍇ�͎��s���Ȃ�
	{
		return -1;
	}

	if (faces.size() == 0) // �t���[���猟�o������Ȃ������ꍇ
	{
		// �t�@�C����������
		writing_file << dataloader.get_frame_info() << "," << "-1" << "," << "-1" << "," << "-1" << "," << "-1" << std::endl;
	}
	else
	{
		// ���o������̌�faces.size()�����[�v���s��
		for (int i = 0; i < faces.size(); i++)
		{
			// ���o�������ԐF��`�ň͂�
			cv::rectangle(img, cv::Point(faces[i].x, faces[i].y), cv::Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), cv::Scalar(0, 0, 255), 2);

			// �t�@�C����������
			writing_file << dataloader.get_frame_info() << "," << faces[i].x << "," << faces[i].y << "," << faces[i].width << "," << faces[i].height << std::endl;
		}
	}
	return 0;
}