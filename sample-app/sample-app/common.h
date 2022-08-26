#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>

// カレントディレクトリに移動する関数
bool SetWorkingDirectory();

struct Params{

	// [camera section]
	int device_id; // カメラのdevice ID
	int c_frame_width; // カメラで読み込む動画の横幅
	int c_frame_height; // カメラで読み込む動画の縦幅
	int c_fps; // カメラで読み込む動画のfps

	// [input section]
	int data_type; // 0:動画,1:画像,2:カメラ
	std::string input_movie_path; // 入力動画の絶対パス
	std::string input_image_path; // 入力画像群のフォルダの絶対パス
	std::string cascade_filepath; // カスケード分類器のファイルの絶対パス

	// [detector section]
	int face_detect_width; // 顔検出の横幅の閾値
	int face_detect_height; // 顔検出の縦幅の閾値

	// [output section]
	std::string output_dirpath; // 出力結果のフォルダの絶対パス

	// コンストラクタ
	Params(){
		device_id = 0;
		c_frame_width = 1280;
		c_frame_height = 720;
		c_fps = 30;

		data_type = 0;
		input_movie_path = "";
		input_image_path = "";
		cascade_filepath = "";

		face_detect_width = 20;
		face_detect_height = 20;

		output_dirpath = "";
	}
};

#endif