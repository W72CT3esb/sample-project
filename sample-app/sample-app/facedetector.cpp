#include <opencv2/opencv.hpp>
#include <iostream>
#include <shlwapi.h>
#include "facedetector.h"
#include "common.h"

// コンストラクタ
FaceDetector::FaceDetector()
{
	std::cout << "FaceDetectorオブジェクト生成" << std::endl;
	this->cascade_filepath = "";
	this->face_detect_width = 0;
	this->face_detect_height = 0;
}

// デストラクタ
FaceDetector::~FaceDetector()
{
	std::cout << "FaceDetectorオブジェクト破棄" << std::endl;
}

// 初期化関数
int FaceDetector::initialize(const Params &params)
{
	bool bret = false;
	if (!PathFileExists(params.cascade_filepath.c_str())) // パスの場所にファイルが存在しない場合に失敗
	{
		return -1;
	}
	if (PathIsDirectory(params.cascade_filepath.c_str())) // ファイルではなくディレクトリの場合に失敗
	{
		return -2;
	}
	this->cascade_filepath = params.cascade_filepath;

	// 正面顔情報が入っているカスケード分類器をロード
	bret = this->cascade.load(this->cascade_filepath);

	if (!bret) //カスケード分類器をロードできない場合に失敗
	{
		return -3;
	}

	this->face_detect_width = params.face_detect_width;
	this->face_detect_height = params.face_detect_height;

	return 0;
}

// フレームから顔検出する関数
void FaceDetector::detect_face(cv::Mat &img, std::vector<cv::Rect> &faces)
{
	// 顔検出の情報をクリア
	faces.clear();

	// 格納されたフレームに対してカスケードファイルに基づいて顔を検知
	this->cascade.detectMultiScale(img, faces, 1.1, 3, 0, cv::Size(this->face_detect_width, this->face_detect_height));
}