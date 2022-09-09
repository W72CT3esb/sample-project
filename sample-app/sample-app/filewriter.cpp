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

// コンストラクタ
FileWriter::FileWriter()
{
	//std::cout << "FileWriterオブジェクト生成" << std::endl;
	this->output_dirpath = "";
	this->file_open_flag = false;
	//throw std::exception();
}

// デストラクタ
FileWriter::~FileWriter()
{
	//std::cout << "FileWriterオブジェクト破棄" << std::endl;
	writing_file.close();
	//throw std::exception();
}

// 初期化関数
int FileWriter::initialize(const Params &params)
{
	if (!PathFileExists(params.output_dirpath.c_str())) // パスの場所に出力ディレクトリが存在するかどうか
	{
		if (_mkdir(params.output_dirpath.c_str()) != 0) // ディレクトリの作成できたかどうか
		{
			//std::cout << "出力ディレクトリを作成できませんでした" << std::endl;
			return -1;
		}
	}
	this->output_dirpath = params.output_dirpath;

	return 0;
}

// ファイルをオープンする関数
int FileWriter::open_file()
{
	if (this->file_open_flag) // 関数を二回以上は実行させない(falseの時に実行)
	{
		return -1;
	}

	writing_file.open(this->output_dirpath + "\\" + this->OUTPUT_FILE_NAME);

	if (!writing_file.is_open()) // 異常終了
	{
		//std::cout << "ファイルを開けませんでした" << std::endl;
		return -2;
	}
	this->file_open_flag = true;

	// 出力ファイルにフィールドを記入
	writing_file << "frame番号" << "," << "x座標" << "," << "y座標" << "," << "横幅" << "," << "縦幅" << std::endl;

	return 0;
}

// ファイル出力する関数
int FileWriter::output_file(DataLoader &dataloader, cv::Mat &img, std::vector<cv::Rect> &faces)
{
	if (!this->file_open_flag) // 出力ファイルがオープンしていない場合は実行しない
	{
		return -1;
	}

	if (faces.size() == 0) // フレーム顔検出がされなかった場合
	{
		// ファイル書き込み
		writing_file << dataloader.get_frame_info() << "," << "-1" << "," << "-1" << "," << "-1" << "," << "-1" << std::endl;
	}
	else
	{
		// 検出した顔の個数faces.size()分ループを行う
		for (int i = 0; i < faces.size(); i++)
		{
			// 検出した顔を赤色矩形で囲む
			cv::rectangle(img, cv::Point(faces[i].x, faces[i].y), cv::Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), cv::Scalar(0, 0, 255), 2);

			// ファイル書き込み
			writing_file << dataloader.get_frame_info() << "," << faces[i].x << "," << faces[i].y << "," << faces[i].width << "," << faces[i].height << std::endl;
		}
	}
	return 0;
}