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
	// コンストラクタ
	FileWriter();

	// デストラクタ
	~FileWriter();

	// 初期化関数
	int initialize(const Params &params);

	// ファイルをオープンする関数
	int open_file();

	// ファイル出力する関数
	int output_file(DataLoader &dataloader, cv::Mat &img, std::vector<cv::Rect> &faces);

private:
	std::ofstream writing_file;
	const std::string OUTPUT_FILE_NAME = "result.csv";
	std::string output_dirpath;
	bool file_open_flag; // ファイルを開いたか判定するフラグ
};

#endif