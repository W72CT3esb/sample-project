#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Shlwapi.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <direct.h>
#include <fstream>
#include <chrono>
#include "../sample-app/common.h"
#include "../sample-app/paramloader.h"
#include "../sample-app/facedetector.h"
#include "../sample-app/dataloader.h"
#include "../sample-app/filewriter.h"

using ::testing::Mock;
using ::testing::_;
using ::testing::Return;
using ::testing::Test;

const int DEFINE_STRING_SIZE = 1024;

// 絶対パスの場合
std::string CONFIG_FILEPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\src\\sample-app\\sample-app\\sample-app\\config.ini";
char COPIED_CONFIG_FILEPATH[DEFINE_STRING_SIZE];

std::string INPUT_MOVIE_PATH1 = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data\\movie\\sample1\\sample1.avi";
std::string INPUT_MOVIE_PATH2 = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data\\movie\\sample2\\sample2.avi";
std::string TMP_INPUT_MOVIE_DIRPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data\\movie\\tmp";
std::string INPUT_MOVIE_PATH_DUMMY1 = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data_\\movie\\sample1\\sample.avi";
std::string INPUT_MOVIE_PATH_DUMMY2 = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data\\movie\\sample1";

std::string INPUT_IMAGE_PATH1 = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data\\image\\sample1";
std::string INPUT_IMAGE_PATH2 = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data\\image\\sample2";
std::string TMP_INPUT_IMAGE_DIRPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data\\image\\tmp";
std::string INPUT_IMAGE_PATH_DUMMY1 = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data_\\image\\sample1";
std::string INPUT_IMAGE_PATH_DUMMY2 = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data\\image\\sample1\\pic_0000.jpg";

std::string CASCADE_FILEPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data\\cascade\\haarcascade_frontalface_alt.xml";
char TMP_CASCADE_DIRPATH[DEFINE_STRING_SIZE] = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data\\cascade\\tmp";
char TMP_CASCADE_FILEPATH[DEFINE_STRING_SIZE] = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data\\cascade\\tmp\\test.xml";
std::string CASCADE_FILEPATH_DUMMY1 = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data_\\cascade\\haarcascade_frontalface_alt.xml";
std::string CASCADE_FILEPATH_DUMMY2 = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data\\cascade";

std::string OUTPUT_DIRPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\Output";
std::string OUTPUT_FILEPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\Output\\result.csv";
std::string OUTPUT_DIRPATH_DUMMY1 = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\data_\\Output";

/*
// 相対パスの場合
std::string CONFIG_FILEPATH = "..\\..\\sample-app\\config.ini";
char COPIED_CONFIG_FILEPATH[DEFINE_STRING_SIZE];

std::string INPUT_MOVIE_PATH1 = "..\\..\\..\\..\\..\\data\\movie\\sample1\\sample1.avi";
std::string INPUT_MOVIE_PATH2 = "..\\..\\..\\..\\..\\data\\movie\\sample2\\sample2.avi";
std::string TMP_INPUT_MOVIE_DIRPATH = "..\\..\\..\\..\\..\\data\\movie\\tmp";
std::string INPUT_MOVIE_PATH_DUMMY1 = "..\\..\\..\\..\\..\\data_\\movie\\sample1\\sample.avi";
std::string INPUT_MOVIE_PATH_DUMMY2 = "..\\..\\..\\..\\..\\data\\movie\\sample1";

std::string INPUT_IMAGE_PATH1 = "..\\..\\..\\..\\..\\data\\image\\sample1";
std::string INPUT_IMAGE_PATH2 = "..\\..\\..\\..\\..\\data\\image\\sample2";
std::string TMP_INPUT_IMAGE_DIRPATH = "..\\..\\..\\..\\..\\data\\image\\tmp";
std::string INPUT_IMAGE_PATH_DUMMY1 = "..\\..\\..\\..\\..\\data_\\image\\sample1";
std::string INPUT_IMAGE_PATH_DUMMY2 = "..\\..\\..\\..\\..\\data\\image\\sample1\\pic_0000.jpg";

std::string CASCADE_FILEPATH = "..\\..\\..\\..\\..\\data\\cascade\\haarcascade_frontalface_alt.xml";
char TMP_CASCADE_DIRPATH[DEFINE_STRING_SIZE] = "..\\..\\..\\..\\..\\data\\cascade\\tmp";
char TMP_CASCADE_FILEPATH[DEFINE_STRING_SIZE] = "..\\..\\..\\..\\..\\data\\cascade\\tmp\\test.xml";
std::string CASCADE_FILEPATH_DUMMY1 = "..\\..\\..\\..\\..\\data_\\cascade\\haarcascade_frontalface_alt.xml";
std::string CASCADE_FILEPATH_DUMMY2 = "..\\..\\..\\..\\..\\data\\cascade";

std::string OUTPUT_DIRPATH = "..\\..\\..\\..\\..\\Output";
std::string OUTPUT_FILEPATH = "..\\..\\..\\..\\..\\Output\\result.csv";
std::string OUTPUT_DIRPATH_DUMMY1 = "..\\..\\..\\..\\..\\data_\\Output";
*/

void copy_config_file();

// テストフィクスチャクラスの定義(ParamLoader)
class ParamLoaderTest : public Test {
protected:

	// 試験開始時に一回だけ実行
	static void SetUpTestCase() {
		//std::cout << "#####Start Test#####\n" << std::endl;
	}

	// 試験終了時に一回だけ実行
	static void TearDownTestCase() {
		//std::cout << "#####Finish Test#####" << std::endl;
	}

	// 各テストケース実行前に実行
	virtual void SetUp() {
		// 事前に設定ファイルのマスターをカレントディレクトリにコピー
		copy_config_file();
		//std::cout << "#####Start TestCase#####\n" << std::endl;
	}

	// 各テストケース実行後に実行
	virtual void TearDown() {
		//std::cout << "#####Finish TestCase#####" << std::endl;
	}
};

// テストフィクスチャクラスの定義(FileWriter)
class FileWriterTest : public Test {
protected:

	// 試験開始時に一回だけ実行
	static void SetUpTestCase() {
		//std::cout << "#####Start Test#####\n" << std::endl;
	}

	// 試験終了時に一回だけ実行
	static void TearDownTestCase() {
		//std::cout << "#####Finish Test#####" << std::endl;
	}

	// 各テストケース実行前に実行
	virtual void SetUp() {
		// 出力ファイルとディレクトリの削除
		DeleteFile(OUTPUT_FILEPATH.c_str());
		RemoveDirectory(OUTPUT_DIRPATH.c_str());
		//std::cout << "#####Start TestCase#####\n" << std::endl;
	}

	// 各テストケース実行後に実行
	virtual void TearDown() {
		DeleteFile(OUTPUT_FILEPATH.c_str());
		RemoveDirectory(OUTPUT_DIRPATH.c_str());
		//std::cout << "#####Finish TestCase#####" << std::endl;
	}
};

// テストフィクスチャクラスの定義()
class ProcessingTimeTest : public Test {
protected:

	// 試験開始時に一回だけ実行
	static void SetUpTestCase() {
		//std::cout << "#####Start Test#####\n" << std::endl;
	}

	// 試験終了時に一回だけ実行
	static void TearDownTestCase() {
		//std::cout << "#####Finish Test#####" << std::endl;
	}

	// 各テストケース実行前に実行
	virtual void SetUp() {
		// 出力ファイルとディレクトリの削除
		DeleteFile(OUTPUT_FILEPATH.c_str());
		RemoveDirectory(OUTPUT_DIRPATH.c_str());
		//std::cout << "#####Start TestCase#####\n" << std::endl;
	}

	// 各テストケース実行後に実行
	virtual void TearDown() {
		DeleteFile(OUTPUT_FILEPATH.c_str());
		RemoveDirectory(OUTPUT_DIRPATH.c_str());
		//std::cout << "#####Finish TestCase#####" << std::endl;
	}
};

// DataLoaderのモッククラス
class mock_DataLoader : public DataLoader {
public:
	MOCK_METHOD(int, load_mv, (cv::Mat&), (override));
	MOCK_METHOD(int, load_img, (cv::Mat&), (override));
};

void copy_config_file()
{
	char buff[DEFINE_STRING_SIZE] = {};
	char drive[DEFINE_STRING_SIZE] = {};
	char dir[DEFINE_STRING_SIZE] = {};

	// 設定ファイルのマスターをコピーするための準備
	GetModuleFileName(nullptr, buff, DEFINE_STRING_SIZE);
	_splitpath_s(buff, drive, DEFINE_STRING_SIZE, dir, DEFINE_STRING_SIZE, nullptr, 0, nullptr, 0);
	sprintf_s(COPIED_CONFIG_FILEPATH, DEFINE_STRING_SIZE, "%s%s", drive, dir);
	strcat_s(COPIED_CONFIG_FILEPATH, DEFINE_STRING_SIZE, "config.ini");

	// 設定ファイルのマスターをコピー
	CopyFile(CONFIG_FILEPATH.c_str(), COPIED_CONFIG_FILEPATH, FALSE);
}

// ###Commonのテストここから###
TEST(CommonTest, SetWorkingDirectory_Test) {
	bool ans = false;
	ans = SetWorkingDirectory();

	EXPECT_EQ(true, ans);
}
// ###Commonのテストここまで###

// ###ParamLoaderのテストここから###
// コンストラクタのテスト（例外が発生しないかチェック）
TEST_F(ParamLoaderTest, constructor_Test) {

	EXPECT_NO_THROW(ParamLoader());
}

// デストラクタのテスト（例外が発生しないかチェック）
TEST_F(ParamLoaderTest, destructor_Test) {

	EXPECT_NO_THROW(ParamLoader().~ParamLoader());
}

TEST_F(ParamLoaderTest, load_param_PathFileExists_Test) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイルを削除
	DeleteFile(COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-2, ans);
}

TEST_F(ParamLoaderTest, load_param_params_device_id_Test) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("camera", "device_id", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-3, ans);
}

TEST_F(ParamLoaderTest, load_param_params_c_frame_width_Test1) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("camera", "c_frame_width", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-4, ans);
}

TEST_F(ParamLoaderTest, load_param_params_c_frame_width_Test2) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("camera", "c_frame_width", "-2", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-5, ans);
}

TEST_F(ParamLoaderTest, load_param_params_c_frame_height_Test1) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("camera", "c_frame_height", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-6, ans);
}

TEST_F(ParamLoaderTest, load_param_params_c_frame_height_Test2) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("camera", "c_frame_height", "-2", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-7, ans);
}

TEST_F(ParamLoaderTest, load_param_params_c_fps_Test1) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("camera", "c_fps", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-8, ans);
}

TEST_F(ParamLoaderTest, load_param_params_c_fps_Test2) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("camera", "c_fps", "-2", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-9, ans);
}

TEST_F(ParamLoaderTest, load_param_params_data_type_Test1) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("input", "data_type", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-10, ans);
}

TEST_F(ParamLoaderTest, load_param_params_data_type_Test2) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("input", "data_type", "3", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-11, ans);
}

TEST_F(ParamLoaderTest, load_param_params_input_movie_path_Test) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("input", "input_movie_path", "", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-12, ans);
}

TEST_F(ParamLoaderTest, load_param_params_input_image_path_Test) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("input", "input_image_path", "", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-13, ans);
}

TEST_F(ParamLoaderTest, load_param_params_cascade_filepath_Test) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("detector", "cascade_filepath", "", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-14, ans);
}

TEST_F(ParamLoaderTest, load_param_params_face_detect_width_Test1) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("detector", "face_detect_width", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-15, ans);
}

TEST_F(ParamLoaderTest, load_param_params_face_detect_width_Test2) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("detector", "face_detect_width", "-2", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-16, ans);
}

TEST_F(ParamLoaderTest, load_param_params_face_detect_height_Test1) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("detector", "face_detect_height", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-17, ans);
}

TEST_F(ParamLoaderTest, load_param_params_face_detect_height_Test2) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("detector", "face_detect_height", "-2", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-18, ans);
}

TEST_F(ParamLoaderTest, load_param_params_output_dirpath_Test) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// 設定ファイル内のパラメータ変更
	WritePrivateProfileString("output", "output_dirpath", "", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-19, ans);
}

TEST_F(ParamLoaderTest, load_param_Positive_Test) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	ans = paramloader.load_param(params);
	EXPECT_EQ(0, ans);
}
// ###ParamLoaderのテストここまで###

// ###DataLoaderのテストここから###
// コンストラクタのテスト（例外が発生しないかチェック）
TEST(DataLoaderTest, constructor_Test) {

	//EXPECT_THROW(DataLoader(), std::exception);
	EXPECT_NO_THROW(DataLoader());
}

// デストラクタのテスト（例外が発生しないかチェック）
TEST(DataLoaderTest, destructor_Test) {

	EXPECT_NO_THROW(DataLoader().~DataLoader());
}

TEST(DataLoaderTest, get_frame_index_Test) {
	int ans = 0;
	DataLoader dataloader;

	ans = dataloader.get_frame_index();
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, get_frame_num_Test) {
	int ans = 0;
	DataLoader dataloader;

	ans = dataloader.get_frame_num();
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, initialize_data_type_0_PathFileExists_Test) {
	int ans = 0;
	DataLoader dataloader;

	// 入力データのタイプを動画に設定
	Params params;
	params.data_type = 0;

	// ファイルが存在しないパスを設定
	params.input_movie_path = INPUT_MOVIE_PATH_DUMMY1;

	ans = dataloader.initialize(params);
	EXPECT_EQ(-1, ans);
}

TEST(DataLoaderTest, initialize_data_type_0_PathIsDirectory_Test) {
	int ans = 0;
	DataLoader dataloader;

	// 入力データのタイプを動画に設定
	Params params;
	params.data_type = 0;

	// ディレクトリのパスを設定
	params.input_movie_path = INPUT_MOVIE_PATH_DUMMY2;

	ans = dataloader.initialize(params);
	EXPECT_EQ(-2, ans);
}

TEST(DataLoaderTest, initialize_data_type_0_Positive_Test) {
	int ans = 0;
	DataLoader dataloader;

	// 入力データのタイプを動画に設定
	Params params;
	params.data_type = 0;

	// 存在する動画のファイルパスを設定
	params.input_movie_path = INPUT_MOVIE_PATH1;

	ans = dataloader.initialize(params);
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, initialize_data_type_1_PathFileExists_Test) {
	int ans = 0;
	DataLoader dataloader;

	// 入力データのタイプを画像に設定
	Params params;
	params.data_type = 1;

	// ディレクトリが存在しないパスを設定
	params.input_image_path = INPUT_IMAGE_PATH_DUMMY1;

	ans = dataloader.initialize(params);
	EXPECT_EQ(-3, ans);
}

TEST(DataLoaderTest, initialize_data_type_1_PathIsDirectory_Test) {
	int ans = 0;
	DataLoader dataloader;

	// 入力データのタイプを画像に設定
	Params params;
	params.data_type = 1;

	// ファイルのパスを設定
	params.input_image_path = INPUT_IMAGE_PATH_DUMMY2;

	ans = dataloader.initialize(params);
	EXPECT_EQ(-4, ans);
}

TEST(DataLoaderTest, initialize_data_type_1_Positive_Test) {
	int ans = 0;
	DataLoader dataloader;

	// 入力データのタイプを動画に設定
	Params params;
	params.data_type = 1;

	// 存在する動画のファイルパスを設定
	params.input_image_path = INPUT_IMAGE_PATH1;

	ans = dataloader.initialize(params);
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, initialize_data_type_2_Positive_Test) {
	int ans = 0;
	DataLoader dataloader;

	// 入力データのタイプをカメラ映像に設定
	Params params;
	params.data_type = 2;

	// カメラ映像のパラメータを設定
	params.device_id = 0;
	params.c_frame_width = 0;
	params.c_frame_height = 0;
	params.c_fps = 0;

	ans = dataloader.initialize(params);
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, open_data_file_open_flag_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを動画に設定
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// 二回open_data()を呼んでflagをtrueにする
	ans = dataloader.open_data();
	ans = dataloader.open_data();
	EXPECT_EQ(-1, ans);
}

TEST(DataLoaderTest, open_data_file_data_type_0_capisOpened_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを動画に設定
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// 入力データを別のディレクトリに移動
	_mkdir(TMP_INPUT_MOVIE_DIRPATH.c_str());
	MoveFile(INPUT_MOVIE_PATH1.c_str(), (TMP_INPUT_MOVIE_DIRPATH+"\\sample.avi").c_str());

	ans = dataloader.open_data();
	EXPECT_EQ(-2, ans);

	// 入力データを元のディレクトリに移動
	MoveFile((TMP_INPUT_MOVIE_DIRPATH + "\\sample.avi").c_str(), INPUT_MOVIE_PATH1.c_str());
	RemoveDirectory(TMP_INPUT_MOVIE_DIRPATH.c_str());
}

TEST(DataLoaderTest, open_data_file_data_type_0_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを動画に設定
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	ans = dataloader.open_data();
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, open_data_file_data_type_1_file_namessize_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを画像に設定
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH1;

	// 画像処理で初期化
	iret = dataloader.initialize(params);

	// 入力データを別のディレクトリに移動
	_mkdir(TMP_INPUT_IMAGE_DIRPATH.c_str());
	MoveFile(INPUT_IMAGE_PATH1.c_str(), (TMP_INPUT_IMAGE_DIRPATH +"\\sample1").c_str());

	ans = dataloader.open_data();
	EXPECT_EQ(-3, ans);

	// 入力データを元のディレクトリに移動
	MoveFile((TMP_INPUT_IMAGE_DIRPATH + "\\sample1").c_str(), INPUT_IMAGE_PATH1.c_str());
	RemoveDirectory(TMP_INPUT_IMAGE_DIRPATH.c_str());
}

TEST(DataLoaderTest, open_data_file_data_type_1_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを画像に設定
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH1;

	// 画像処理で初期化
	iret = dataloader.initialize(params);

	ans = dataloader.open_data();
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, open_data_file_data_type_2_capisOpened_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプをカメラ映像に設定
	params.data_type = 2;
	params.device_id = -1;

	// カメラ映像処理で初期化
	iret = dataloader.initialize(params);

	ans = dataloader.open_data();
	EXPECT_EQ(-4, ans);
}

// カメラ映像を取得するのに時間がかかることに注意
TEST(DataLoaderTest, open_data_file_data_type_2_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプをカメラ映像に設定
	params.data_type = 2;
	params.device_id = 0;

	// カメラ映像処理で初期化
	iret = dataloader.initialize(params);

	ans = dataloader.open_data();
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, load_mv_file_open_flag_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを動画に設定
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// GrabImageの引数用
	cv::Mat img;

	ans = dataloader.load_mv(img);
	EXPECT_EQ(-1, ans);
}

TEST(DataLoaderTest, load_mv_img_empty_Test) {
	int ans = -1;
	int iret = -1;
	cv::Mat img; //grab_imageの引数用
	DataLoader dataloader;

	// 入力データのタイプを動画に設定
	Params params;
	params.data_type = 0;

	// 存在する動画のファイルパスを設定
	params.input_movie_path = INPUT_MOVIE_PATH2;

	iret = dataloader.initialize(params);
	iret = dataloader.open_data();

	iret = dataloader.load_mv(img);
	iret = dataloader.load_mv(img);
	iret = dataloader.load_mv(img);
	iret = dataloader.load_mv(img);
	iret = dataloader.load_mv(img);

	ans = dataloader.load_mv(img);


	EXPECT_EQ(-2, ans);
}

TEST(DataLoaderTest, load_mv_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを動画に設定
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// open_data()を呼んでflagをtrueにする
	iret = dataloader.open_data();

	// GrabImageの引数用
	cv::Mat img;

	ans = dataloader.load_mv(img);
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, load_img_img_empty_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	cv::Mat img; //load_imgの引数用

				 // 入力データのタイプを静止画に設定
	Params params;
	params.data_type = 1;

	// 作成したディレクトリパスを設定
	params.input_image_path = INPUT_IMAGE_PATH2;

	iret = dataloader.initialize(params);
	iret = dataloader.open_data();

	ans = dataloader.load_img(img);

	EXPECT_EQ(-1, ans);
}

TEST(DataLoaderTest, load_img_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを動画に設定
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH1;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// open_data()を呼んでflagをtrueにする
	iret = dataloader.open_data();

	// GrabImageの引数用
	cv::Mat img;

	ans = dataloader.load_img(img);
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, get_frame_info_Test) {
	std::string ans = "";
	int iret = -1;
	cv::Mat img; //grab_imageの引数用
	DataLoader dataloader;

	// 入力データのタイプを動画に設定
	Params params;
	params.data_type = 0;

	// 存在する動画のファイルパスを設定
	params.input_movie_path = INPUT_MOVIE_PATH1;

	iret = dataloader.initialize(params);
	iret = dataloader.open_data();
	iret = dataloader.grab_image(img);

	ans = dataloader.get_frame_info();

	EXPECT_STREQ("0", ans.c_str());
}

//TEST(DataLoaderTest, get_frame_info_data_type_0_Test) {
//	std::string ans = "";
//	int iret = -1;
//	cv::Mat img; //grab_imageの引数用
//	DataLoader dataloader;
//
//	// 入力データのタイプを動画に設定
//	Params params;
//	params.data_type = 0;
//
//	// 存在する動画のファイルパスを設定
//	params.input_movie_path = INPUT_MOVIE_PATH1;
//
//	iret = dataloader.initialize(params);
//	iret = dataloader.open_data();
//	iret = dataloader.grab_image(img);
//
//	ans = dataloader.get_frame_info();
//
//	EXPECT_STREQ("0", ans.c_str());
//}

//TEST(DataLoaderTest, get_frame_info_data_type_1_Test) {
//	std::string ans = "";
//	int iret = -1;
//	cv::Mat img; //grab_imageの引数用
//	DataLoader dataloader;
//
//	// 入力データのタイプを静止画に設定
//	Params params;
//	params.data_type = 1;
//
//	// 存在する画像ディレクトリパスを設定
//	params.input_image_path = INPUT_IMAGE_PATH1;
//
//	std::string image_file_name = "pic_0000.jpg";
//	std::string image_file_path = INPUT_IMAGE_PATH1 + "\\" + image_file_name;
//
//	iret = dataloader.initialize(params);
//	iret = dataloader.open_data();
//	iret = dataloader.grab_image(img);
//
//	ans = dataloader.get_frame_info();
//
//	EXPECT_STREQ(image_file_path.c_str(), ans.c_str());
//}

// カメラ映像を取得するのに時間がかかることに注意
//TEST(DataLoaderTest, get_frame_info_data_type_2_Test) {
//	std::string ans = "";
//	int iret = -1;
//	cv::Mat img; //grab_imageの引数用
//	DataLoader dataloader;
//
//	// 入力データのタイプをカメラに設定
//	Params params;
//	params.data_type = 2;
//	params.device_id = 0;
//	params.c_frame_height = 480;
//	params.c_frame_width = 640;
//	params.c_fps = 15;
//
//	iret = dataloader.initialize(params);
//	iret = dataloader.open_data();
//	iret = dataloader.grab_image(img);
//
//	ans = dataloader.get_frame_info();
//
//	EXPECT_STREQ("0", ans.c_str());
//}

TEST(DataLoaderTest, grab_image_data_type_0_Test) {
	int ans = 0;
	int iret = -1;

	// モックオブジェクトを作成
	mock_DataLoader *mock_d = new mock_DataLoader();

	//動画処理のパラメータに設定
	Params params;
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// GrabImageの引数用
	cv::Mat img;

	// load_mvの戻り値として-1が返却されるよう設定、引数は任意とする
	EXPECT_CALL(*mock_d, load_mv(testing::_)).WillRepeatedly(Return(-1));

	DataLoader* dataloader = mock_d;

	ans = dataloader->grab_image(img);

	// モックオブジェクトの解放
	delete mock_d;

	EXPECT_EQ(-1, ans);
}

TEST(DataLoaderTest, grab_image_data_type_0_Positive_Test) {
	int ans = 0;
	int iret = -1;

	// モックオブジェクトを作成
	mock_DataLoader *mock_d = new mock_DataLoader();

	//動画処理のパラメータに設定
	Params params;
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// GrabImageの引数用
	cv::Mat img;

	// load_mvの戻り値として0が返却されるよう設定、引数は任意とする
	EXPECT_CALL(*mock_d, load_mv(testing::_)).WillRepeatedly(Return(0));

	DataLoader* dataloader = mock_d;

	ans = dataloader->grab_image(img);

	// モックオブジェクトの解放
	delete mock_d;

	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, grab_image_data_type_1_Test) {
	int ans = -1;
	int iret = -1;

	// モックオブジェクトを作成
	mock_DataLoader* mock_d = new mock_DataLoader();

	// 画像処理のパラメータに設定
	Params params;
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH1;

	// 画像処理で初期化
	iret = mock_d->initialize(params);

	// GrabImageの引数用
	cv::Mat img;

	// load_imgの戻り値として-1が返却されるよう設定。引数は任意とする
	EXPECT_CALL(*mock_d, load_img(testing::_)).WillRepeatedly(Return(-1));

	DataLoader* dataloader = mock_d;

	ans = mock_d->grab_image(img);

	// モックオブジェクトの解放
	delete mock_d;

	EXPECT_EQ(-2, ans);
}

TEST(DataLoaderTest, grab_image_data_type_1_Positive_Test) {
	int ans = -1;
	int iret = -1;

	// モックオブジェクトを作成
	mock_DataLoader* mock_d = new mock_DataLoader();

	// 画像処理のパラメータに設定
	Params params;
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH1;

	// 画像処理で初期化
	iret = mock_d->initialize(params);

	// GrabImageの引数用
	cv::Mat img;

	// load_imgの戻り値として-1が返却されるよう設定。引数は任意とする
	EXPECT_CALL(*mock_d, load_img(testing::_)).WillRepeatedly(Return(0));

	DataLoader* dataloader = mock_d;

	ans = mock_d->grab_image(img);

	// モックオブジェクトの解放
	delete mock_d;

	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, grab_image_data_type_2_Test) {
	int ans = 0;
	int iret = -1;

	// モックオブジェクトを作成
	mock_DataLoader *mock_d = new mock_DataLoader();

	//動画処理のパラメータに設定
	Params params;
	params.data_type = 2;

	// 画像処理で初期化
	iret = mock_d->initialize(params);

	// GrabImageの引数用
	cv::Mat img;

	// load_mvの戻り値として-1が返却されるよう設定、引数は任意とする
	EXPECT_CALL(*mock_d, load_mv(testing::_)).WillRepeatedly(Return(-1));

	DataLoader* dataloader = mock_d;

	ans = dataloader->grab_image(img);

	// モックオブジェクトの解放
	delete mock_d;

	EXPECT_EQ(-3, ans);
}

TEST(DataLoaderTest, grab_image_data_type_2_Positive_Test) {
	int ans = 0;
	int iret = -1;

	// モックオブジェクトを作成
	mock_DataLoader *mock_d = new mock_DataLoader();

	//動画処理のパラメータに設定
	Params params;
	params.data_type = 2;

	// 画像処理で初期化
	iret = mock_d->initialize(params);

	// GrabImageの引数用
	cv::Mat img;

	// load_mvの戻り値として-1が返却されるよう設定、引数は任意とする
	EXPECT_CALL(*mock_d, load_mv(testing::_)).WillRepeatedly(Return(0));

	DataLoader* dataloader = mock_d;

	ans = dataloader->grab_image(img);

	// モックオブジェクトの解放
	delete mock_d;

	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, get_filelist_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを画像に設定
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH1;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	ans = dataloader.get_filelist();
	EXPECT_EQ(0, ans);
}
// ###DataLoaderのテストここまで###

// ###FaceDetectorのテストここから###
// コンストラクタのテスト（例外が発生しないかチェック）
TEST(FaceDetectorTest, constructor_Test) {

	EXPECT_NO_THROW(FaceDetector());
}

// デストラクタのテスト（例外が発生しないかチェック）
TEST(FaceDetectorTest, destructor_Test) {

	EXPECT_NO_THROW(FaceDetector().~FaceDetector());
}

TEST(FaceDetectorTest, initialize_PathFileExists_Test) {
	int ans = 0;
	FaceDetector facedetector;

	// 入力データのタイプを動画に設定
	Params params;

	// ファイルが存在しないパスを設定
	params.cascade_filepath = CASCADE_FILEPATH_DUMMY1;

	ans = facedetector.initialize(params);
	EXPECT_EQ(-1, ans);
}

TEST(FaceDetectorTest, initialize_PathIsDirectory_Test) {
	int ans = 0;
	FaceDetector facedetector;

	// 入力データのタイプを動画に設定
	Params params;

	// ディレクトリのパスを設定
	params.cascade_filepath = CASCADE_FILEPATH_DUMMY2;

	ans = facedetector.initialize(params);
	EXPECT_EQ(-2, ans);
}

TEST(FaceDetectorTest, initialize_cascadeload_Test) {
	int ans = 0;
	FaceDetector facedetector;

	// 入力データのタイプを動画に設定
	Params params;

	// カスケード分類器のダミーデータを作成
	_mkdir(TMP_CASCADE_DIRPATH);
	CreateFile(TMP_CASCADE_FILEPATH, GENERIC_WRITE, FILE_SHARE_DELETE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	// カスケード分類器のダミーデータのファイルパスを設定
	params.cascade_filepath = TMP_CASCADE_FILEPATH;

	ans = facedetector.initialize(params);
	EXPECT_EQ(-3, ans);

	// カスケード分類器のダミーデータのファイルとディレクトリを削除
	DeleteFile(TMP_CASCADE_FILEPATH);
	RemoveDirectory(TMP_CASCADE_DIRPATH);
}

TEST(FaceDetectorTest, initialize_Positive_Test) {
	int ans = 0;
	FaceDetector facedetector;

	// 入力データのタイプを動画に設定
	Params params;

	// カスケード分類器のファイルパスを設定
	params.cascade_filepath = CASCADE_FILEPATH;

	ans = facedetector.initialize(params);
	EXPECT_EQ(0, ans);
}

TEST(FaceDetectorTest, detect_face_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	FaceDetector facedetector;
	Params params;
	ParamLoader paramloader;

	cv::Mat img;
	std::vector<cv::Rect> faces;

	// 入力データのタイプを動画に設定
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;
	params.cascade_filepath = CASCADE_FILEPATH;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// 動画データをオープン
	iret = dataloader.open_data();

	// 顔検出器の初期化
	iret = facedetector.initialize(params);

	ans = facedetector.detect_face(img, faces);
	EXPECT_EQ(0, ans);
}
// ###FaceDetectorのテストここまで###

// ###FileWriterのテストここから###
// コンストラクタのテスト（例外が発生しないかチェック）
TEST_F(FileWriterTest, constructor_Test) {

	EXPECT_NO_THROW(FileWriter());
}

// デストラクタのテスト（例外が発生しないかチェック）
TEST_F(FileWriterTest, destructor_Test) {
	EXPECT_NO_THROW(FileWriter().~FileWriter());
}

TEST_F(FileWriterTest, initialize_mkdir_Test)
{
	int ans = 0;
	FileWriter filewriter;

	// 存在しないディレクトリパスを設定
	Params params;
	params.output_dirpath = OUTPUT_DIRPATH_DUMMY1;

	ans = filewriter.initialize(params);
	EXPECT_EQ(-1, ans);
}

TEST_F(FileWriterTest, initialize_Positive_Test)
{
	int ans = 0;
	FileWriter filewriter;

	// 出力ディレクトリのパスを設定
	Params params;
	params.output_dirpath = OUTPUT_DIRPATH;

	ans = filewriter.initialize(params);
	EXPECT_EQ(0, ans);
}

TEST_F(FileWriterTest, open_file_file_open_flag_Test)
{
	int ans = 0;
	int iret = -1;
	FileWriter filewriter;

	// 出力ディレクトリのパスを設定
	Params params;
	params.output_dirpath = OUTPUT_DIRPATH;

	// 初期化
	iret = filewriter.initialize(params);

	// 2回呼んでフラグをtrueにする
	ans = filewriter.open_file();
	ans = filewriter.open_file();

	EXPECT_EQ(-1, ans);
}

TEST_F(FileWriterTest, open_file_writing_file_is_open_Test)
{
	int ans = 0;
	int iret = -1;
	FileWriter filewriter;

	// 出力ディレクトリのパスを設定
	Params params;
	params.output_dirpath = OUTPUT_DIRPATH;

	// 初期化
	iret = filewriter.initialize(params);

	// 作成したディレクトリを削除
	RemoveDirectory(params.output_dirpath.c_str());

	ans = filewriter.open_file();

	EXPECT_EQ(-2, ans);
}

TEST_F(FileWriterTest, open_file_Positive_Test)
{
	int ans = 0;
	int iret = -1;
	FileWriter filewriter;

	// 出力ディレクトリのパスを設定
	Params params;
	params.output_dirpath = OUTPUT_DIRPATH;

	// 初期化
	iret = filewriter.initialize(params);

	ans = filewriter.open_file();

	EXPECT_EQ(0, ans);
}

TEST_F(FileWriterTest, output_file_file_open_flag_Test)
{
	int ans = 0;
	int iret = -1;
	FileWriter filewriter;
	DataLoader dataloader;
	cv::Mat img;
	std::vector<cv::Rect> faces;

	// 出力ディレクトリのパスを設定
	Params params;
	params.output_dirpath = OUTPUT_DIRPATH;

	// 初期化
	iret = filewriter.initialize(params);

	ans = filewriter.output_file(dataloader, img, faces);

	EXPECT_EQ(-1, ans);
}

TEST_F(FileWriterTest, output_file_Positive_Test)
{
	int ans = -1;
	int iret = -1;
	DataLoader dataloader;
	FaceDetector facedetector;
	FileWriter filewriter;
	cv::Mat img;
	std::vector<cv::Rect> faces;

	// パラメータを設定
	Params params;
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;
	params.cascade_filepath = CASCADE_FILEPATH;
	params.face_detect_width = 20;
	params.face_detect_height = 20;
	params.output_dirpath = OUTPUT_DIRPATH;

	// データ読み込み機能の初期化
	iret = dataloader.initialize(params);

	// 入力データをオープン
	iret = dataloader.open_data();

	// 顔検出器の初期化
	iret = facedetector.initialize(params);

	// ファイル出力器の初期化
	iret = filewriter.initialize(params);

	// 出力ファイルをオープン
	iret = filewriter.open_file();

	// 1フレーム取り出す
	iret = dataloader.grab_image(img);

	// フレームから顔検出
	iret = facedetector.detect_face(img, faces);

	// 出力ファイルに書き込み
	ans = filewriter.output_file(dataloader, img, faces);

	EXPECT_EQ(0, ans);

}
// ###FileWriterのテストここまで###

// ###処理時間のテストここから###
// 1フレームの取得時間をテスト
TEST_F(ProcessingTimeTest, DataLoader_grab_image_elapsed_time_Test) {
	int iret = -1;
	DataLoader dataloader;
	Params params;
	ParamLoader paramloader;

	cv::Mat img;
	std::vector<cv::Rect> faces;

	std::chrono::system_clock::time_point  start, end;
	double elapsed_time, sum_time = 0.0, mean_elapsed_time;

	// 入力データのタイプを動画に設定
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH2;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// 動画データをオープン
	iret = dataloader.open_data();

	while (1)
	{
		// 1フレームずつ取り出す
		start = std::chrono::system_clock::now(); // 計測開始時間
		iret = dataloader.grab_image(img);
		end = std::chrono::system_clock::now();  // 計測終了時間

		// 処理に要した時間をミリ秒に変換
		elapsed_time = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		sum_time += elapsed_time;
		//std::cout << elapsed_time << " msec" << std::endl;

		// 最終フレームになったらループを抜ける
		if (dataloader.get_frame_index() == dataloader.get_frame_num())
		{
			break;
		}
	}
	mean_elapsed_time = sum_time / dataloader.get_frame_num();
	//std::cout << "mean: " << mean_elapsed_time << " msec" << std::endl;
	//ASSERT_TRUE(mean_elapsed_time <= 50); //50ms以下だったら、とりあえずOK
}

// 1フレームの顔検出時間をテスト
TEST_F(ProcessingTimeTest, FaceDetector_detect_face_elapsed_time_Test) {
	int iret = -1;
	DataLoader dataloader;
	FaceDetector facedetector;
	Params params;
	ParamLoader paramloader;

	cv::Mat img;
	std::vector<cv::Rect> faces;

	std::chrono::system_clock::time_point  start, end;
	double elapsed_time, sum_time = 0.0, mean_elapsed_time;

	// 入力データのタイプを動画に設定
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH2;
	params.cascade_filepath = CASCADE_FILEPATH;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// 動画データをオープン
	iret = dataloader.open_data();

	// 顔検出器の初期化
	iret = facedetector.initialize(params);

	while (1)
	{
		// 1フレームずつ取り出す
		iret = dataloader.grab_image(img);

		// フレームから顔検出
		start = std::chrono::system_clock::now(); // 計測開始時間
		iret = facedetector.detect_face(img, faces);
		end = std::chrono::system_clock::now();  // 計測終了時間

		// 処理に要した時間をミリ秒に変換
		elapsed_time = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		sum_time += elapsed_time;
		//std::cout << elapsed_time << " msec" << std::endl;

		// 最終フレームになったらループを抜ける
		if (dataloader.get_frame_index() == dataloader.get_frame_num())
		{
			break;
		}
	}
	mean_elapsed_time = sum_time / dataloader.get_frame_num();
	//std::cout << "mean: " << mean_elapsed_time << " msec" << std::endl;
	//ASSERT_TRUE(mean_elapsed_time <= 500); //500ms以下だったら、とりあえずOK
}

// 1フレームのファイル出力時間をテスト
TEST_F(ProcessingTimeTest, FileWrtiter_output_file_elapsed_time_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	FaceDetector facedetector;
	Params params;
	ParamLoader paramloader;
	FileWriter filewriter;

	cv::Mat img;
	std::vector<cv::Rect> faces;

	std::chrono::system_clock::time_point  start, end;
	double elapsed_time, sum_time = 0.0, mean_elapsed_time;

	// 入力データのタイプを動画に設定
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH2;
	params.cascade_filepath = CASCADE_FILEPATH;
	params.output_dirpath = OUTPUT_DIRPATH;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// 動画データをオープン
	iret = dataloader.open_data();

	// 顔検出器の初期化
	iret = facedetector.initialize(params);

	// ファイル出力器の初期化
	iret = filewriter.initialize(params);

	// 出力ファイルをオープン
	iret = filewriter.open_file();

	while (1)
	{
		// 1フレームずつ取り出す
		iret = dataloader.grab_image(img);

		// フレームから顔検出
		iret = facedetector.detect_face(img, faces);

		// 出力ファイルに書き込み
		start = std::chrono::system_clock::now(); // 計測開始時間
		iret = filewriter.output_file(dataloader, img, faces);
		end = std::chrono::system_clock::now();  // 計測終了時間

		// 処理に要した時間をミリ秒に変換
		//elapsed_time = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		elapsed_time = (double)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		sum_time += elapsed_time;
		//std::cout << elapsed_time << " microsec" << std::endl;

		// 最終フレームになったらループを抜ける
		if (dataloader.get_frame_index() == dataloader.get_frame_num())
		{
			break;
		}
	}
	mean_elapsed_time = sum_time / dataloader.get_frame_num();
	//std::cout << "mean: " << mean_elapsed_time << " microsec" << std::endl;
	//ASSERT_TRUE(mean_elapsed_time <= 200); //200microsec以下だったら、とりあえずOK
}
// ###処理時間のテストここまで###