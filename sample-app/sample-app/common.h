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
	std::string input_movie_path; // 入力動画のパス
	std::string input_image_path; // 入力画像群のフォルダのパス
	std::string cascade_filepath; // カスケード分類器のファイルのパス

	// [detector section]
	int face_detect_width; // 顔検出の横幅の閾値
	int face_detect_height; // 顔検出の縦幅の閾値

	// [output section]
	std::string output_dirpath; // 出力結果のフォルダのパス

	// コンストラクタ
	Params(){
		device_id = 0; // カメラのdevice ID
		c_frame_width = 1280; // カメラのフレームの横幅
		c_frame_height = 720; // カメラのフレームの縦幅
		c_fps = 30; // カメラのfps

		data_type = 0; // 0:動画,1:画像,2:カメラ
		input_movie_path = ""; // 入力動画のパス
		input_image_path = ""; // 入力画像群のフォルダのパス
		cascade_filepath = ""; // カスケード分類器ファイルのパス

		face_detect_width = 20; // 顔検出の横幅の閾値
		face_detect_height = 20; // 顔検出の縦幅の閾値

		output_dirpath = ""; // 出力結果フォルダのパス
	}
};

#endif