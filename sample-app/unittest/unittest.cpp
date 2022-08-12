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
// ���b�N�N���X�̐錾
class TestMock {
public:
	//MOCK_METHODn(�֐���, �߂�l�̌^(����1, ����2, ...))
	//n�͈����̐�
	//MOCK_METHOD0(SetWorkingDirectory, bool());
	MOCK_METHOD0(SetWorkingDirectory, bool());
}testMock;

// �e�X�g�t�B�N�X�`���N���X�̒�`
class FuncTest : public Test {
protected:
	// �����J�n���Ɉ�񂾂����s
	static void SetUpTestCase() {
	}

	// �����I�����Ɉ�񂾂����s
	static void TearDownTestCase() {
	}

	// �e�e�X�g�P�[�X���s�O�Ɏ��s
	virtual void SetUp() {
		printf("######start######\n\n");
	}

	// �e�e�X�g�P�[�X���s��Ɏ��s
	virtual void TearDown() {
		printf("######finish######\n\n");
	}

	// �����Ώۂ̈����Ȃǂ�錾
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


//���b�N���������֐�������
/*
bool SetWorkingDirectory() {
	return testMock.SetWorkingDirectory();
}

//TEST_F(�e�X�g�t�B�N�X�`���N���X��, �e�X�g�P�[�X��)
TEST_F(FuncTest, TestParamLoader) {
	Params params;
	ParamLoader paramloader;

	//sub_func�Ăяo�����A���0��Ԃ��悤�ɐݒ�
	EXPECT_CALL(testMock, SetWorkingDirectory()).WillRepeatedly(Return(false));

	// �����ΏیĂяo��
	ans = paramloader.load_param(params);

	// �߂�l�����҂�����̂��m�F
	EXPECT_EQ(0, ans);
}
*/