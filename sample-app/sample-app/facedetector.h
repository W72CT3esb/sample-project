#ifndef _FACEDETECTOR_H_
#define _FACEDETECTOR_H_

#include <opencv2/opencv.hpp>
#include <string>
#include "common.h"

class FaceDetector
{
public:
	// �R���X�g���N�^
	FaceDetector();

	// �f�X�g���N�^
	~FaceDetector();

	// �������֐�
	int initialize(const Params &params);

	// �t���[������猟�o����֐�
	void detect_face(cv::Mat &img, std::vector<cv::Rect> &faces);

private:
	cv::CascadeClassifier cascade; // �J�X�P�[�h���ފ�
	std::string cascade_filepath; // �J�X�P�[�h���ފ�t�@�C���̐�΃p�X
	int face_detect_width; // �猟�o�̉�����臒l
	int face_detect_height; // �猟�o�̏c����臒l
};

#endif