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
#include "filewriter.h"


int main()
{
	DataLoader dataloader;
	FaceDetector facedetector;
	Params params;
	ParamLoader paramloader;
	FileWriter filewriter;

	int iret = -1;

	// �ݒ�t�@�C������p�����[�^��ǂݍ���
	iret = paramloader.load_param(params);
	if (iret != 0) // �ُ�I��
	{
		std::cout << "load_param�����s���܂���! status code:" << iret << std::endl;
		return -1;
	}

	// �f�[�^�ǂݍ��݋@�\�̏�����
	iret = dataloader.initialize(params);
	if (iret != 0) // �ُ�I��
	{
		std::cout << "initialize�����s���܂���! status code:" << iret << std::endl;
		return -2;
	}

	// ���̓f�[�^���I�[�v��
	iret = dataloader.open_data();
	if (iret != 0) // �ُ�I��
	{
		std::cout << "open_data�����s���܂���! status code:" << iret << std::endl;
		return -3;
	}

	// �猟�o��̏�����
	iret = facedetector.initialize(params);
	if (iret != 0) // �ُ�I��
	{
		std::cout << "initialize�����s���܂���! status code:" << iret << std::endl;
		return -4;
	}

	// 1�t���[���̊i�[�ꏊ
	cv::Mat img;

	// 1�t���[���̗֊s���i�[�ꏊ
	std::vector<cv::Rect> faces;

	// �t�@�C���o�͊�̏�����
	iret = filewriter.initialize(params);
	if (iret != 0) // �ُ�I��
	{
		std::cout << "initialize�����s���܂���! status code:" << iret << std::endl;
		return -5;
	}

	// �o�̓t�@�C�����I�[�v��
	iret = filewriter.open_file();
	if (iret != 0) // �ُ�I��
	{
		std::cout << "open_file�����s���܂���! status code:" << iret << std::endl;
		return -6;
	}

	while (1)
	{
		// 1�t���[�������o��
		iret = dataloader.grab_image(img);
		if (iret != 0) // �ُ�I��
		{
			std::cout << "GrabImage�����s���܂���! status code:" << iret << std::endl;
			return -7;
		}

		// �t���[������猟�o
		iret = facedetector.detect_face(img, faces);

		// �o�̓t�@�C���ɏ�������
		iret = filewriter.output_file(dataloader, img, faces);
		if (iret != 0) // �ُ�I��
		{
			std::cout << "output_file�����s���܂���! status code:" << iret << std::endl;
			return -8;
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