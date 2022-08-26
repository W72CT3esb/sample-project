#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <shlwapi.h>
#include "dataloader.h"
#include "common.h"

// コンストラクタ
DataLoader::DataLoader()
{
	//std::cout << "LoadDataオブジェクト生成" << std::endl;
	this->frame_num = 0;
	this->frame_index = 0;
	this->img_h = 0;
	this->img_w = 0;
	this->fps = 0.0;
	this->input_movie_path = "";
	this->input_image_path = "";
	this->data_type = 0;
	this->file_open_flag = false;
	this->device_id = 0;
}

// デストラクタ
DataLoader::~DataLoader()
{
	//std::cout << "LoadDataオブジェクト破棄" << std::endl;
}

// フレーム番号を取得する関数
int DataLoader::get_frame_index()
{
	return this->frame_index;
}

// 動画や画像のフレーム数を取得する関数
int DataLoader::get_frame_num()
{
	return this->frame_num;
}

// 初期化関数
int DataLoader::initialize(const Params &params)
{
	this->data_type = params.data_type;
	if (this->data_type == 0) // 入力データが動画の場合
	{
		if (!PathFileExists(params.input_movie_path.c_str())) // パスの場所にファイルが存在しない場合に失敗
		{
			return -1;
		}
		if (PathIsDirectory(params.input_movie_path.c_str())) // ファイルではなくディレクトリの場合に失敗
		{
			return -2;
		}
		this->input_movie_path = params.input_movie_path; // 入力動画データのパスを設定
	}
	else if (this->data_type == 1) // 入力データが画像の場合
	{
		if (!PathFileExists(params.input_image_path.c_str())) // パスの場所にディレクトリが存在しない場合に失敗
		{
			return -3;
		}
		if (!PathIsDirectory(params.input_image_path.c_str())) // ディレクトリではない場合に失敗
		{
			return -4;
		}
		this->input_image_path = params.input_image_path; // 入力画像群があるディレクトリのパスを設定
	}
	else // 入力データがカメラからの映像の場合
	{
		this->device_id = params.device_id;
		this->img_h = params.c_frame_height;
		this->img_w = params.c_frame_width;
		this->fps = params.c_fps;
	}

	return 0;
}

// フレーム情報について表示する関数（デバッグ用）
void DataLoader::print_info()
{
	std::cout << "最大フレーム数" << this->frame_num << std::endl;
	std::cout << "フレームの高さ:" << this->img_h << std::endl;
	std::cout << "フレームの幅:" << this->img_w << std::endl;
	std::cout << "フレームのfps:" << this->fps << std::endl;
}

// 入力データをオープンする関数
int DataLoader::open_data()
{
	int iret = -1;
	if(this->file_open_flag) // 関数を二回以上は実行させない(falseの時に実行)
	{
		return -1;
	}
	if (this->data_type == 0) // 入力データが動画の場合
	{
		this->cap.open(this->input_movie_path);
		if (!this->cap.isOpened()) // ファイルが開けない場合に失敗
		{
			std::cout << "動画ファイルが開けません" << std::endl;
			return -2;
		}

		this->frame_num = (int)this->cap.get(cv::CAP_PROP_FRAME_COUNT);
		this->img_h = (int)this->cap.get(cv::CAP_PROP_FRAME_HEIGHT);
		this->img_w = (int)this->cap.get(cv::CAP_PROP_FRAME_WIDTH);
		this->fps = this->cap.get(cv::CAP_PROP_FPS);
	}
	else if (this->data_type == 1) // 入力データが画像の場合
	{
		iret = get_filelist(); // 入力画像データのディレクトリからすべての画像ファイルのパスを取得
		if (this->file_names.size() == 0) // ディレクトリ内に画像ファイルがなかった場合に失敗
		{
			return -3;
		}
		this->frame_num = (int)this->file_names.size();
	}
	else // 入力データがカメラからの映像の場合
	{
		this->cap.open(this->device_id);
		if (!this->cap.isOpened()) // ファイルが開けない場合に失敗
		{
			std::cout << "cameraを開けません" << std::endl;
			return -4;
		}
		cap.set(cv::CAP_PROP_FRAME_WIDTH, this->img_w);
		cap.set(cv::CAP_PROP_FRAME_HEIGHT, this->img_h);
		cap.set(cv::CAP_PROP_FPS, this->fps);
		this->img_w = (int)this->cap.get(cv::CAP_PROP_FRAME_WIDTH);
		this->img_h = (int)this->cap.get(cv::CAP_PROP_FRAME_HEIGHT);
		this->fps = this->cap.get(cv::CAP_PROP_FPS);
		//print_info();
	}
	this->file_open_flag = true; //関数を一度読んだらフラグをtrueにする

	return 0;
}

// 入力データが動画の場合にフレームごとに画像として保存する関数（デバッグ用）
void DataLoader::save_frame(cv::Mat &img)
{
	//取得した画像を連番画像で保存
	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(4) << this->frame_index;
	//cv::imwrite("C:\\Users\\1134142029087\\Desktop\\data2\\pic_" + oss.str() + ".jpg", img);
}

// 動画を読み込む関数
int DataLoader::load_mv(cv::Mat &img)
{
	if (!this->file_open_flag) // 動画ファイルがオープンしていない場合はloadしない
	{
		return -1;
	}
	this->cap >> img;
	if (img.empty()) // imgが空だったら
	{
		return -2;
	}
	cv::resize(img, img, cv::Size(), 0.5, 0.5);
	std::cout << "フレーム番号 " << this->frame_index << std::endl;
	//save_frame(img);
	return 0;
}

// 画像を読み込む関数
int DataLoader::load_img(cv::Mat &img)
{
	std::cout << this->file_names[this->frame_index] << std::endl;
	img = cv::imread(this->file_names[this->frame_index]);
	if (img.empty()) // imgが空だったら
	{
		return -1;
	}
	cv::resize(img, img, cv::Size(), 0.5, 0.5);
	std::cout << "フレーム番号 " << this->frame_index << std::endl;
	return 0;
}

// フレーム番号やファイルパスを返す関数
std::string DataLoader::get_frame_info()
{
	if (this->data_type == 0) // 動画の時はフレーム番号を返す
	{
		return std::to_string(get_frame_index() - 1);
	}
	else if (this->data_type == 1) // 画像の時はファイルパスを返す
	{
		return this->file_names[this->frame_index - 1];
	}
	else // カメラ映像の時はフレーム番号を返す
	{
		return std::to_string(get_frame_index() - 1);
	}
}

// 1フレームずつ取り出す関数
int DataLoader::grab_image(cv::Mat &img)
{
	int iret = -1;
	if (this->data_type == 0) // 入力データが動画の場合
	{
		iret = load_mv(img);
		if (iret != 0)
		{
			return -1;
		}
	}
	else if (this->data_type == 1) // 入力データが画像の場合
	{
		iret = load_img(img);
		if (iret != 0)
		{
			return -2;
		}
	}
	else // 入力データがカメラからの映像の場合
	{
		iret = load_mv(img);
		if (iret != 0)
		{
			return -3;
		}
	}

	this->frame_index++; // 1フレーム取り出したらカウント

	return 0;
}

// 入力画像データのディレクトリからすべての画像ファイルのパスを取得する関数
int DataLoader::get_filelist()
{
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;
	std::vector<std::string> file_names;

	std::vector<std::string> extension = { "png" ,"jpg", "bmp"};

	for (int i = 0; i < extension.size(); i++)
	{

		std::string search_name = this->input_image_path + "\\*." + extension[i];

		// 指定したファイル名に一致するファイルやディレクトリを検索(戻り値は成功：検索ハンドル,失敗：-1(INVALID_HANDLE_VALUE))
		hFind = FindFirstFile(search_name.c_str(), &win32fd);

		if (hFind == INVALID_HANDLE_VALUE) // ファイル検索に失敗した場合(returnをすると、画像ファイルがjpgだけの時などにpngとbmpは存在しないため、強制終了してしまう)
		{
			continue;
		}
		do
		{
			this->file_names.push_back(this->input_image_path + "\\" + win32fd.cFileName);
		} while (FindNextFile(hFind, &win32fd)); // FindFirstFile 関数の呼び出しによる検索を続行(戻り値は成功：0以外,失敗：0)

		// 指定された検索ハンドルをクローズ(戻り値は成功：0以外,失敗：0)
		FindClose(hFind);
	}
	return 0;
}