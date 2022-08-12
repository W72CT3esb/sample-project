#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../sample-app/common.h"
#include "../sample-app/paramloader.h"
#include "../sample-app/facedetector.h"
#include "../sample-app/dataloader.h"

using ::testing::Mock;
using ::testing::_;
using ::testing::Return;
using ::testing::Test;

/*
// モッククラスの宣言
class TestMock {
public:
	//MOCK_METHODn(関数名, 戻り値の型(引数1, 引数2, ...))
	//nは引数の数
	//MOCK_METHOD0(SetWorkingDirectory, bool());
	MOCK_METHOD0(SetWorkingDirectory, bool());
}testMock;

// テストフィクスチャクラスの定義
class FuncTest : public Test {
protected:
	// 試験開始時に一回だけ実行
	static void SetUpTestCase() {
	}

	// 試験終了時に一回だけ実行
	static void TearDownTestCase() {
	}

	// 各テストケース実行前に実行
	virtual void SetUp() {
		printf("######start######\n\n");
	}

	// 各テストケース実行後に実行
	virtual void TearDown() {
		printf("######finish######\n\n");
	}

	// 試験対象の引数などを宣言
	int ans;
};
*/

/*
TEST(TestParamLoader, unittest1)
{
	Params params;
	ParamLoader paramloader;

	int ans;

	ans = paramloader.load_param(params);
	EXPECT_EQ(0, ans);
}
*/


//モック化したい関数を書く
/*
bool SetWorkingDirectory() {
	return testMock.SetWorkingDirectory();
}

//TEST_F(テストフィクスチャクラス名, テストケース名)
TEST_F(FuncTest, TestParamLoader) {
	Params params;
	ParamLoader paramloader;

	//sub_func呼び出し時、常に0を返すように設定
	EXPECT_CALL(testMock, SetWorkingDirectory()).WillRepeatedly(Return(false));

	// 試験対象呼び出し
	ans = paramloader.load_param(params);

	// 戻り値が期待するものか確認
	EXPECT_EQ(0, ans);
}
*/