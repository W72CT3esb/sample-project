#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <Shlwapi.h>
#include "dataloader.h"
#include "common.h"

using ::testing::Mock;
using ::testing::_;
using ::testing::Return;
using ::testing::Test;

std::string INPUT_MOVIE_PATH = "C:\\ICF_AutoCapsule_disabled\\sample.avi";
std::string INPUT_MOVIE_PATH2 = "C:\\ICF_AutoCapsule_disabled\\sample2.avi";

std::string INPUT_IMAGE_PATH = "C:\\ICF_AutoCapsule_disabled\\image";
std::string INPUT_IMAGE_PATH2 = "C:\\ICF_AutoCapsule_disabled\\image2";


class mock_DataLoader : public DataLoader {
public:
	MOCK_METHOD1(load_mv, int(cv::Mat&));
	MOCK_METHOD1(load_img, int(cv::Mat&));
};

TEST(CommonTest, DataLoad_constructor) {
	bool ans = -1;
	ans = SetWorkingDirectory();

	EXPECT_EQ(true, ans);
}

// コンストラクタのテスト（例外が発生しないかチェック）
TEST(DataLoaderTest, DataLoad_constructor) {

	EXPECT_NO_THROW(DataLoader());
}

// デストラクタのテスト（例外が発生しないかチェック）
TEST(DataLoaderTest, DataLoad_destructor) {

	EXPECT_NO_THROW(DataLoader().~DataLoader());
}

TEST(DataLoaderTest, get_frame_index) {
	int ans = 0;
	DataLoader dataloader;

	ans = dataloader.get_frame_index();
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, get_frame_num) {
	int ans = 0;
	DataLoader dataloader;

	ans = dataloader.get_frame_num();
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, load_mv_img_empty_Test) {
	int ans = -1;
	int iret = -1;
	cv::Mat result; //grab_imageの引数用
	DataLoader dataloader;

	// 入力データのタイプを動画に設定
	Params params;
	params.data_type = 0;

	// 存在する動画のファイルパスを設定
	params.input_movie_path = INPUT_MOVIE_PATH2;

	iret = dataloader.initialize(params);
	iret = dataloader.open_data();

	iret = dataloader.load_mv(result);
	iret = dataloader.load_mv(result);
	iret = dataloader.load_mv(result);
	iret = dataloader.load_mv(result);
	iret = dataloader.load_mv(result);

	ans = dataloader.load_mv(result);


	EXPECT_EQ(-2, ans);
}

TEST(DataLoaderTest, load_img_img_empty_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	cv::Mat result; //load_mvの引数用

	// 入力データのタイプを静止画に設定
	Params params;
	params.data_type = 1;

	// 作成したディレクトリパスを設定
	params.input_image_path = INPUT_IMAGE_PATH2;

	iret = dataloader.initialize(params);
	iret = dataloader.open_data();
	
	ans = dataloader.load_img(result);

	EXPECT_EQ(-1, ans);
}

TEST(DataLoaderTest, get_frame_info_data_type_0) {
	std::string ans = "";
	int iret = -1;
	cv::Mat result; //grab_imageの引数用
	DataLoader dataloader;

	// 入力データのタイプを動画に設定
	Params params;
	params.data_type = 0;

	// 存在する動画のファイルパスを設定
	params.input_movie_path = INPUT_MOVIE_PATH;

	iret = dataloader.initialize(params);
	iret = dataloader.open_data();
	iret = dataloader.grab_image(result);

	ans = dataloader.get_frame_info();

	EXPECT_STREQ("0", ans.c_str());
}

TEST(DataLoaderTest, get_frame_info_data_type_1) {
	std::string ans = "";
	int iret = -1;
	cv::Mat result; //grab_imageの引数用
	DataLoader dataloader;

	// 入力データのタイプを静止画に設定
	Params params;
	params.data_type = 1;

	// 作成したダミーフォルダを設定
	params.input_image_path = INPUT_IMAGE_PATH;

	std::string image_file_name = "0001.png";
	std::string image_file_path = INPUT_IMAGE_PATH + "\\" + image_file_name;

	iret = dataloader.initialize(params);
	iret = dataloader.open_data();
	iret = dataloader.grab_image(result);

	ans = dataloader.get_frame_info();

	EXPECT_STREQ(image_file_path.c_str(), ans.c_str());
}

TEST(DataLoaderTest, get_frame_info_data_type_2) {
	std::string ans = "";
	int iret = -1;
	cv::Mat result; //grab_imageの引数用
	DataLoader dataloader;

	// 入力データのタイプをカメラに設定
	Params params;
	params.data_type = 2;
	params.device_id = 0;
	params.c_frame_height = 480;
	params.c_frame_width = 640;
	params.c_fps = 15;

	iret = dataloader.initialize(params);
	iret = dataloader.open_data();
	iret = dataloader.grab_image(result);

	ans = dataloader.get_frame_info();

	EXPECT_STREQ("0", ans.c_str());
}


// GrabImageのテスト。load_mvに失敗し戻り値として-1が返却されることを想定
TEST(DataLoaderTest, GrabImage1) {

	// モックオブジェクトを作成
	mock_DataLoader *mock_d = new mock_DataLoader();

	// GrabImageの引数用
	cv::Mat temp;

	// load_mvの戻り値として-1が返却されるよう設定。引数は任意とする
	EXPECT_CALL(*mock_d, load_mv(testing::_)).WillRepeatedly(Return(-1));

	DataLoader* dataloader = mock_d;

	int iret = dataloader->grab_image(temp);

	// モックオブジェクトの解放
	delete mock_d;

	EXPECT_EQ(iret, -1);

}

// GrabImageのテスト。load_imgに失敗し戻り値として-2が返却されることを想定
TEST(DataLoaderTest, GrabImage2) {

	int iret = -1;

	// モックオブジェクトを作成
	mock_DataLoader* mock_d = new mock_DataLoader();

	// 静止画処理のパラメータに設定
	Params params;
	params.data_type = 1;

	// imagesはフォルダとしてあらかじめ作成済み
	params.input_image_path = ".\\images";

	// 静止画処理で初期化
	iret = mock_d->initialize(params);

	// GrabImageの引数用
	cv::Mat temp;

	// load_imgの戻り値として-1が返却されるよう設定。引数は任意とする
	EXPECT_CALL(*mock_d, load_img(testing::_)).WillRepeatedly(Return(-1));

	DataLoader* dataloader = mock_d;

	iret = mock_d->grab_image(temp);

	// モックオブジェクトの解放
	delete mock_d;

	EXPECT_EQ(iret, -2);

}


