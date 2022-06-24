#include <opencv2/opencv.hpp>
#include <iostream>

std::string myfunc(std::string input_imgpath)
{
	// 画像を格納するオブジェクトを宣言する
	cv::Mat	src, dst;

	// 画像ファイルから画像データを読み込む
	src = cv::imread(input_imgpath);

	//エラー処理
	if (src.empty() == true) {
		// 画像の中身が空なら終了する
		return "file is empty";
	}
	else
	{
		// グレイスケール画像に変換する.カラーはBGR順である（RGBではない）ことに注意
		cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
		// ウィンドウに画像を表示する
		//cv::imshow("before", src);
		//cv::imshow("after", dst);

		// 画像を保存する
		cv::imwrite("sample_gray.png", dst);

		return "file is ok";
	}
}