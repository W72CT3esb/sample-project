#include <opencv2/opencv.hpp>
#include <iostream>

std::string myfunc(std::string input_imgpath)
{
	// �摜���i�[����I�u�W�F�N�g��錾����
	cv::Mat	src, dst;

	// �摜�t�@�C������摜�f�[�^��ǂݍ���
	src = cv::imread(input_imgpath);

	//�G���[����
	if (src.empty() == true) {
		// �摜�̒��g����Ȃ�I������
		return "file is empty";
	}
	else
	{
		// �O���C�X�P�[���摜�ɕϊ�����.�J���[��BGR���ł���iRGB�ł͂Ȃ��j���Ƃɒ���
		cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
		// �E�B���h�E�ɉ摜��\������
		//cv::imshow("before", src);
		//cv::imshow("after", dst);

		// �摜��ۑ�����
		cv::imwrite("sample_gray.png", dst);

		return "file is ok";
	}
}