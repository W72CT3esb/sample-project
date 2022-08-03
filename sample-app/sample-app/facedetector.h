#ifndef _FACEDETECTOR_H_
#define _FACEDETECTOR_H_

#include <opencv2/opencv.hpp>
#include <string>
#include "common.h"

class FaceDetector
{
public:
	// コンストラクタ
	FaceDetector();

	// デストラクタ
	~FaceDetector();

	// 初期化関数
	int initialize(const Params &params);

	// フレームから顔検出する関数
	void detect_face(cv::Mat &img, std::vector<cv::Rect> &faces);

private:
	cv::CascadeClassifier cascade; // カスケード分類器
	std::string cascade_filepath; // カスケード分類器ファイルの絶対パス
	int face_detect_width; // 顔検出の横幅の閾値
	int face_detect_height; // 顔検出の縦幅の閾値
};

#endif