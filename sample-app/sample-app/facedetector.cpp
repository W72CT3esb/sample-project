#include <opencv2/opencv.hpp>
#include <iostream>
#include <shlwapi.h>
#include "facedetector.h"
#include "common.h"

// �R���X�g���N�^
FaceDetector::FaceDetector()
{
	std::cout << "FaceDetector�I�u�W�F�N�g����" << std::endl;
	this->cascade_filepath = "";
	this->face_detect_width = 0;
	this->face_detect_height = 0;
}

// �f�X�g���N�^
FaceDetector::~FaceDetector()
{
	std::cout << "FaceDetector�I�u�W�F�N�g�j��" << std::endl;
}

// �������֐�
int FaceDetector::initialize(const Params &params)
{
	bool bret = false;
	if (!PathFileExists(params.cascade_filepath.c_str())) // �p�X�̏ꏊ�Ƀt�@�C�������݂��Ȃ��ꍇ�Ɏ��s
	{
		return -1;
	}
	if (PathIsDirectory(params.cascade_filepath.c_str())) // �t�@�C���ł͂Ȃ��f�B���N�g���̏ꍇ�Ɏ��s
	{
		return -2;
	}
	this->cascade_filepath = params.cascade_filepath;

	// ���ʊ��񂪓����Ă���J�X�P�[�h���ފ�����[�h
	bret = this->cascade.load(this->cascade_filepath);

	if (!bret) //�J�X�P�[�h���ފ�����[�h�ł��Ȃ��ꍇ�Ɏ��s
	{
		return -3;
	}

	this->face_detect_width = params.face_detect_width;
	this->face_detect_height = params.face_detect_height;

	return 0;
}

// �t���[������猟�o����֐�
void FaceDetector::detect_face(cv::Mat &img, std::vector<cv::Rect> &faces)
{
	// �猟�o�̏����N���A
	faces.clear();

	// �i�[���ꂽ�t���[���ɑ΂��ăJ�X�P�[�h�t�@�C���Ɋ�Â��Ċ�����m
	this->cascade.detectMultiScale(img, faces, 1.1, 3, 0, cv::Size(this->face_detect_width, this->face_detect_height));
}