#ifndef _FILEWRITER_H_
#define _FILEWRITER_H_

#include <fstream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "common.h"
#include "dataloader.h"

class FileWriter
{
public:
	// �R���X�g���N�^
	FileWriter();

	// �f�X�g���N�^
	~FileWriter();

	// �������֐�
	int initialize(const Params &params);

	// �t�@�C�����I�[�v������֐�
	int open_file();

	// �t�@�C���o�͂���֐�
	int output_file(DataLoader &dataloader, cv::Mat &img, std::vector<cv::Rect> &faces);

private:
	std::ofstream writing_file;
	const std::string OUTPUT_FILE_NAME = "result.csv";
	std::string output_dirpath;
	bool file_open_flag; // �t�@�C�����J���������肷��t���O
};

#endif