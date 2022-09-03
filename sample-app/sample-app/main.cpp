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

	// 設定ファイルからパラメータを読み込み
	iret = paramloader.load_param(params);
	if (iret != 0) // 異常終了
	{
		std::cout << "load_paramが失敗しました! status code:" << iret << std::endl;
		return -1;
	}

	// データ読み込み機能の初期化
	iret = dataloader.initialize(params);
	if (iret != 0) // 異常終了
	{
		std::cout << "initializeが失敗しました! status code:" << iret << std::endl;
		return -2;
	}

	// 入力データをオープン
	iret = dataloader.open_data();
	if (iret != 0) // 異常終了
	{
		std::cout << "open_dataが失敗しました! status code:" << iret << std::endl;
		return -3;
	}

	// 顔検出器の初期化
	iret = facedetector.initialize(params);
	if (iret != 0) // 異常終了
	{
		std::cout << "initializeが失敗しました! status code:" << iret << std::endl;
		return -4;
	}

	// 1フレームの格納場所
	cv::Mat img;

	// 1フレームの輪郭情報格納場所
	std::vector<cv::Rect> faces;

	// ファイル出力器の初期化
	iret = filewriter.initialize(params);
	if (iret != 0) // 異常終了
	{
		std::cout << "initializeが失敗しました! status code:" << iret << std::endl;
		return -5;
	}

	// 出力ファイルをオープン
	iret = filewriter.open_file();
	if (iret != 0) // 異常終了
	{
		std::cout << "open_fileが失敗しました! status code:" << iret << std::endl;
		return -6;
	}

	while (1)
	{
		// 1フレームずつ取り出す
		iret = dataloader.grab_image(img);
		if (iret != 0) // 異常終了
		{
			std::cout << "GrabImageが失敗しました! status code:" << iret << std::endl;
			return -7;
		}

		// フレームから顔検出
		iret = facedetector.detect_face(img, faces);

		// 出力ファイルに書き込み
		iret = filewriter.output_file(dataloader, img, faces);
		if (iret != 0) // 異常終了
		{
			std::cout << "output_fileが失敗しました! status code:" << iret << std::endl;
			return -8;
		}

		// 画面表示
		cv::imshow("Window", img);
		
		if (cv::waitKey(10) == 'q') // "q"が押されたら終了
		{
			break;
		}

		// 最終フレームになったらループを抜ける
		if (dataloader.get_frame_index() == dataloader.get_frame_num())
		{
			break;
		}
	}
	return 0;
}