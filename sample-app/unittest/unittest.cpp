#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Shlwapi.h>
#include <string.h>
#include "../sample-app/common.h"
#include "../sample-app/paramloader.h"
#include "../sample-app/facedetector.h"
#include "../sample-app/dataloader.h"

using ::testing::Mock;
using ::testing::_;
using ::testing::Return;
using ::testing::Test;

const int DEFINE_STRING_SIZE = 1024;
std::string CONFIG_FILEPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\GitHub\\sample-project\\sample-app\\sample-app\\config.ini";
char COPIED_CONFIG_FILEPATH[DEFINE_STRING_SIZE];

std::string INPUT_MOVIE_PATH = "C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\movie\\sample.avi";
char TMP_INPUT_MOVIE_PATH[DEFINE_STRING_SIZE] = "C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\tmp\\sample.avi";

std::string INPUT_IMAGE_PATH = "C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\image";
char TMP_INPUT_IMAGE_PATH[DEFINE_STRING_SIZE] = "C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\tmp\\image";

std::string CASCADE_FILEPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\cascade\\haarcascade_frontalface_alt.xml";

void copy_config_file();

// テストフィクスチャクラスの定義
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

// ###DataLoaderのテストここから###
TEST(DataLoaderTest, initialize_data_type_0_PathFileExists_Test) {
	int ans = 0;
	DataLoader dataloader;

	// 入力データのタイプを動画に設定
	Params params;
	params.data_type = 0;

	// ファイルが存在しないパスを設定
	params.input_movie_path = "C:\\Users\\NES\\Documents\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\movie\\sample.avi";

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
	params.input_movie_path = "C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\movie";

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
	params.input_movie_path = "C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\movie\\sample.avi";

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
	params.input_image_path = "C:\\Users\\NES\\Documents\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\image";

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
	params.input_image_path = "C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\image\\pic_0000.jpg";

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
	params.input_image_path = "C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\image";

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
	params.input_movie_path = INPUT_MOVIE_PATH;

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
	params.input_movie_path = INPUT_MOVIE_PATH;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// 入力データを別のディレクトリに移動
	MoveFile(INPUT_MOVIE_PATH.c_str(), TMP_INPUT_MOVIE_PATH);

	ans = dataloader.open_data();
	EXPECT_EQ(-2, ans);

	// 入力データを元のディレクトリに移動
	MoveFile(TMP_INPUT_MOVIE_PATH, INPUT_MOVIE_PATH.c_str());
}

TEST(DataLoaderTest, open_data_file_data_type_0_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを動画に設定
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH;

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
	params.input_image_path = INPUT_IMAGE_PATH;

	// 画像処理で初期化
	iret = dataloader.initialize(params);

	// 入力データを別のディレクトリに移動
	MoveFile(INPUT_IMAGE_PATH.c_str(), TMP_INPUT_IMAGE_PATH);

	ans = dataloader.open_data();
	EXPECT_EQ(-3, ans);

	// 入力データを元のディレクトリに移動
	MoveFile(TMP_INPUT_IMAGE_PATH, INPUT_IMAGE_PATH.c_str());
}

TEST(DataLoaderTest, open_data_file_data_type_1_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを画像に設定
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH;

	// 画像処理で初期化
	iret = dataloader.initialize(params);

	ans = dataloader.open_data();
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, open_data_file_data_type_2_file_namessize_Test) {
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
	params.input_movie_path = INPUT_MOVIE_PATH;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// GrabImageの引数用
	cv::Mat img;

	ans = dataloader.load_mv(img);
	EXPECT_EQ(-1, ans);
}

// load_mvのemptyのやつができない（保留）
TEST(DataLoaderTest, load_mv_img_empty_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを動画に設定
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// 入力データを別のディレクトリに移動
	MoveFile(INPUT_MOVIE_PATH.c_str(), TMP_INPUT_MOVIE_PATH);

	// open_data()を呼んでflagをtrueにする
	iret = dataloader.open_data(); //-2

	// GrabImageの引数用
	cv::Mat img;

	ans = dataloader.load_mv(img);
	EXPECT_EQ(-2, ans);

	// 入力データを元のディレクトリに移動
	MoveFile(TMP_INPUT_MOVIE_PATH, INPUT_MOVIE_PATH.c_str());
}

TEST(DataLoaderTest, load_mv_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを動画に設定
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// open_data()を呼んでflagをtrueにする
	iret = dataloader.open_data();

	// GrabImageの引数用
	cv::Mat img;

	ans = dataloader.load_mv(img);
	EXPECT_EQ(0, ans);
}

// load_imgのemptyのやつができない（保留）
//TEST(DataLoaderTest, load_mv_img_empty_Test) {
//	int ans = 0;
//	int iret = -1;
//	DataLoader dataloader;
//	Params params;
//
//	// 入力データのタイプを動画に設定
//	params.data_type = 1;
//	params.input_image_path = INPUT_IMAGE_PATH;
//
//	// 動画処理で初期化
//	iret = dataloader.initialize(params);
//
//	// 入力データを別のディレクトリに移動
//	MoveFile(INPUT_MOVIE_PATH.c_str(), TMP_INPUT_MOVIE_PATH);
//
//	// open_data()を呼んでflagをtrueにする
//	iret = dataloader.open_data(); //-2
//
//	// GrabImageの引数用
//	cv::Mat img;
//
//	ans = dataloader.load_mv(img);
//	EXPECT_EQ(-2, ans);
//
//	// 入力データを元のディレクトリに移動
//	MoveFile(TMP_INPUT_MOVIE_PATH, INPUT_MOVIE_PATH.c_str());
//}

TEST(DataLoaderTest, load_img_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを動画に設定
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	// open_data()を呼んでflagをtrueにする
	iret = dataloader.open_data();

	// GrabImageの引数用
	cv::Mat img;

	ans = dataloader.load_img(img);
	EXPECT_EQ(0, ans);
}

// stringからwchar_t*への変換がわからず保留
//TEST(DataLoaderTest, get_file_info_data_type_0_Test) {
//	std::string ans = 0;
//	int iret = -1;
//
//	DataLoader dataloader;
//	Params params;
//
//	ans = dataloader.get_frame_info();
//
//	EXPECT_STREQ((std::to_string(get_frame_index() - 1)).c_str(), ans.c_str());
//}

// stringからwchar_t*への変換がわからず保留
//TEST(DataLoaderTest, get_file_info_data_type_1_Test) {
//	std::string ans = 0;
//	int iret = -1;
//
//	DataLoader dataloader;
//	Params params;
//
//	ans = dataloader.get_frame_info();
//
//	EXPECT_STREQ();
//}

// stringからwchar_t*への変換がわからず保留
//TEST(DataLoaderTest, get_file_info_data_type_2_Test) {
//	std::string ans = 0;
//	int iret = -1;
//
//	DataLoader dataloader;
//	Params params;
//
//	ans = dataloader.get_frame_info();
//
//	EXPECT_STREQ();
//}

TEST(DataLoaderTest, grab_image_data_type_0_Test) {
	int ans = 0;
	int iret = -1;

	// モックオブジェクトを作成
	mock_DataLoader *mock_d = new mock_DataLoader();

	//動画処理のパラメータに設定
	Params params;
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH;

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
	params.input_movie_path = INPUT_MOVIE_PATH;

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
	params.input_image_path = INPUT_IMAGE_PATH;

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

	EXPECT_EQ(ans, -2);
}

TEST(DataLoaderTest, grab_image_data_type_1_Positive_Test) {
	int ans = -1;
	int iret = -1;

	// モックオブジェクトを作成
	mock_DataLoader* mock_d = new mock_DataLoader();

	// 画像処理のパラメータに設定
	Params params;
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH;

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

	EXPECT_EQ(ans, -3);
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

	EXPECT_EQ(ans, 0);
}

TEST(DataLoaderTest, get_filelist_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// 入力データのタイプを画像に設定
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH;

	// 動画処理で初期化
	iret = dataloader.initialize(params);

	ans = dataloader.get_filelist();
	EXPECT_EQ(0, ans);
}
// ###DataLoaderのテストここまで###

// ###ParamLoaderのテストここから###
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

// ###FaceDetectorのテストここから###
TEST(FaceDetectorTest, initialize_PathFileExists_Test) {
	int ans = 0;
	FaceDetector facedetector;

	// 入力データのタイプを動画に設定
	Params params;

	// ファイルが存在しないパスを設定
	params.cascade_filepath = "C:\\Users\\NES\\Documents\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\cascade\\haarcascade_frontalface_alt.xml";

	ans = facedetector.initialize(params);
	EXPECT_EQ(-1, ans);
}

TEST(FaceDetectorTest, initialize_PathIsDirectory_Test) {
	int ans = 0;
	FaceDetector facedetector;

	// 入力データのタイプを動画に設定
	Params params;

	// ディレクトリのパスを設定
	params.cascade_filepath = "C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\cascade";

	ans = facedetector.initialize(params);
	EXPECT_EQ(-2, ans);
}

TEST(FaceDetectorTest, initialize_cascadeload_Test) {
	int ans = 0;
	FaceDetector facedetector;

	// 入力データのタイプを動画に設定
	Params params;

	// カスケード分類器のダミーデータを作成
	_mkdir("C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\dummy");
	CreateFile("C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\dummy\\test.xml", GENERIC_WRITE, FILE_SHARE_DELETE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	// カスケード分類器のダミーデータのファイルパスを設定
	params.cascade_filepath = "C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\dummy\\test.xml";

	ans = facedetector.initialize(params);
	EXPECT_EQ(-3, ans);

	// カスケード分類器のダミーデータのファイルとディレクトリを削除
	DeleteFile("C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\dummy\\test.xml");
	RemoveDirectory("C:\\Users\\NES\\Desktop\\hayakawa\\FieldAnalyst製品開発作業効率化に向けたCI／CDの導入検証\\data\\dummy");
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
	params.input_movie_path = INPUT_MOVIE_PATH;
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