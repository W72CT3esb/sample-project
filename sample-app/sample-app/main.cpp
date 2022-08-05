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

	// 設定ファイルからパラメータを読み込み
	iret = paramloader.load_param(params);
	if (iret != 0) // 異常終了
	{
		std::cout << "load_paramが失敗しました! status code:" << iret << std::endl;
		return 0;
	}

	// データ読み込みの初期化
	iret = dataloader.initialize(params);
	if (iret != 0) // 異常終了
	{
		std::cout << "initializeが失敗しました! status code:" << iret << std::endl;
		return 0;
	}

	// 入力データをオープン
	iret = dataloader.open_data();
	if (iret != 0) // 異常終了
	{
		std::cout << "open_dataが失敗しました! status code:" << iret << std::endl;
		return 0;
	}

	// 顔検出器の初期化
	iret = facedetector.initialize(params);
	if (iret != 0) // 異常終了
	{
		std::cout << "initializeが失敗しました! status code:" << iret << std::endl;
		return 0;
	}

	// 1フレームの格納場所
	cv::Mat img;

	// 1フレームの輪郭情報格納場所
	std::vector<cv::Rect> faces;

	// 結果を出力するファイルを開く
	std::ofstream writing_file;
	const std::string OUTPUT_FILE_NAME = "result.csv";

	if (!PathFileExists(params.output_dirpath.c_str())) // パスの場所に出力ディレクトリが存在するかどうか
	{
		if (_mkdir(params.output_dirpath.c_str()) == 0) // ディレクトリの作成できたかどうか
		{
			std::cout << "出力ディレクトリを作成しました" << std::endl;
		}
		else
		{
			std::cout << "出力ディレクトリを作成できませんでした" << std::endl;
			return 0;
		}
	}

	writing_file.open(params.output_dirpath + "\\" + OUTPUT_FILE_NAME);

	if (!writing_file.is_open()) // 異常終了
	{
		std::cout << "ファイルを開けませんでした" << std::endl;
		return 0;
	}

	// 出力ファイルにフィールドを記入
	writing_file << "frame番号" << "," << "x座標" << "," << "y座標" << "," << "横幅" << "," << "縦幅" << std::endl;

	while (1)
	{
		// 1フレームずつ取り出す
		iret = dataloader.GrabImage(img);
		if (iret != 0) // 異常終了
		{
			std::cout << "GrabImageが失敗しました! status code:" << iret << std::endl;
			return 0;
		}

		// フレームから顔検出
		facedetector.detect_face(img, faces);

		if (faces.size() == 0) // フレームから顔検出がなかった場合
		{
			// ファイル書き込み
			writing_file << dataloader.get_frame_info() << "," << "-1" << "," << "-1" << "," << "-1" << "," << "-1" << std::endl;
		}
		else
		{
			// 検出した顔の個数"faces.size()"分ループを行う
			for (int i = 0; i < faces.size(); i++)
			{
				// 検出した顔を赤色矩形で囲む
				cv::rectangle(img, cv::Point(faces[i].x, faces[i].y), cv::Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), cv::Scalar(0, 0, 255), 2);

				// ファイル書き込み
				writing_file << dataloader.get_frame_info() << "," << faces[i].x << "," << faces[i].y << "," << faces[i].width << "," << faces[i].height << std::endl;
			}
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