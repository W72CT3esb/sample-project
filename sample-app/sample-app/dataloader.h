#ifndef _DATALOADER_H_
#define _DATALOADER_H_

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "common.h"

class DataLoader
{
public:
	// コンストラクタ
	DataLoader();

	// デストラクタ
	~DataLoader();

	// フレーム番号を取得する関数
	int get_frame_index();

	// 動画や画像のフレーム数を取得する関数
	int get_frame_num();

	// 初期化関数
	int initialize(const Params &params);

	// フレーム情報について表示する関数（デバッグ用）
	void print_info();

	// 入力データをオープンする関数
	int open_data();

	// 入力データが動画の場合にフレームごとに画像として保存する関数（デバッグ用）
	void save_frame(cv::Mat &img);

	// 動画を読み込む関数
	virtual int load_mv(cv::Mat &img);

	// 画像を読み込む関数
	virtual int load_img(cv::Mat &img);

	// フレーム番号やファイルパスを返す関数
	std::string DataLoader::get_frame_info();

	// 1フレームずつ取り出す関数
	int grab_image(cv::Mat &img);

	// 入力画像データのディレクトリからすべての画像ファイルのパスを取得する関数
	int get_filelist();

private:
	int device_id; // カメラのdevice ID
	int frame_num; // フレーム数
	int frame_index; //フレーム番号
	int img_w; // フレームの横幅
	int img_h; // フレームの縦幅
	std::string input_movie_path; // 入力動画の絶対パス
	std::string input_image_path; // 入力画像群のフォルダの絶対パス
	int data_type; // 0:動画,1:画像,2:カメラ
	std::vector<std::string> file_names; // 画像のファイルパスのリスト
	double fps; // fps
	cv::VideoCapture cap; // 動画のキャプチャ
	bool file_open_flag; // ファイルを開いたか判定するフラグ
};

#endif