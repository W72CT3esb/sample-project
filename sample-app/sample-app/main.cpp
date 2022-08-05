#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>
#include <shlwapi.h>
#include <direct.h>
#include "dataloader.h"
#include "facedetector.h"
#include "paramloader.h"
#include "common.h"

int main()
{
	DataLoader dataloader;
	FaceDetector facedetector;
	Params params;
	ParamLoader paramloader;

	int iret = -1;

	// �ݒ�t�@�C������p�����[�^��ǂݍ���
	iret = paramloader.load_param(params);
	if (iret != 0) // �ُ�I��
	{
		std::cout << "load_param�����s���܂���! status code:" << iret << std::endl;
		return 0;
	}

	// �f�[�^�ǂݍ��݂̏�����
	iret = dataloader.initialize(params);
	if (iret != 0) // �ُ�I��
	{
		std::cout << "initialize�����s���܂���! status code:" << iret << std::endl;
		return 0;
	}

	// ���̓f�[�^���I�[�v��
	iret = dataloader.open_data();
	if (iret != 0) // �ُ�I��
	{
		std::cout << "open_data�����s���܂���! status code:" << iret << std::endl;
		return 0;
	}

	// �猟�o��̏�����
	iret = facedetector.initialize(params);
	if (iret != 0) // �ُ�I��
	{
		std::cout << "initialize�����s���܂���! status code:" << iret << std::endl;
		return 0;
	}

	// 1�t���[���̊i�[�ꏊ
	cv::Mat img;

	// 1�t���[���̗֊s���i�[�ꏊ
	std::vector<cv::Rect> faces;

	// ���ʂ��o�͂���t�@�C�����J��
	std::ofstream writing_file;
	const std::string OUTPUT_FILE_NAME = "result.csv";

	if (!PathFileExists(params.output_dirpath.c_str())) // �p�X�̏ꏊ�ɏo�̓f�B���N�g�������݂��邩�ǂ���
	{
		if (_mkdir(params.output_dirpath.c_str()) == 0) // �f�B���N�g���̍쐬�ł������ǂ���
		{
			std::cout << "�o�̓f�B���N�g�����쐬���܂���" << std::endl;
		}
		else
		{
			std::cout << "�o�̓f�B���N�g�����쐬�ł��܂���ł���" << std::endl;
			return 0;
		}
	}

	writing_file.open(params.output_dirpath + "\\" + OUTPUT_FILE_NAME);

	if (!writing_file.is_open()) // �ُ�I��
	{
		std::cout << "�t�@�C�����J���܂���ł���" << std::endl;
		return 0;
	}

	// �o�̓t�@�C���Ƀt�B�[���h���L��
	writing_file << "frame�ԍ�" << "," << "x���W" << "," << "y���W" << "," << "����" << "," << "�c��" << std::endl;

	while (1)
	{
		// 1�t���[�������o��
		iret = dataloader.GrabImage(img);
		if (iret != 0) // �ُ�I��
		{
			std::cout << "GrabImage�����s���܂���! status code:" << iret << std::endl;
			return 0;
		}

		// �t���[������猟�o
		facedetector.detect_face(img, faces);

		if (faces.size() == 0) // �t���[������猟�o���Ȃ������ꍇ
		{
			// �t�@�C����������
			writing_file << dataloader.get_frame_info() << "," << "-1" << "," << "-1" << "," << "-1" << "," << "-1" << std::endl;
		}
		else
		{
			// ���o������̌�"faces.size()"�����[�v���s��
			for (int i = 0; i < faces.size(); i++)
			{
				// ���o�������ԐF��`�ň͂�
				cv::rectangle(img, cv::Point(faces[i].x, faces[i].y), cv::Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), cv::Scalar(0, 0, 255), 2);

				// �t�@�C����������
				writing_file << dataloader.get_frame_info() << "," << faces[i].x << "," << faces[i].y << "," << faces[i].width << "," << faces[i].height << std::endl;
			}
		}

		// ��ʕ\��
		cv::imshow("Window", img);
		
		if (cv::waitKey(10) == 'q') // "q"�������ꂽ��I��
		{
			break;
		}

		// �ŏI�t���[���ɂȂ����烋�[�v�𔲂���
		if (dataloader.get_frame_index() == dataloader.get_frame_num())
		{
			break;
		}
	}
	return 0;
}