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

// ��΃p�X�̏ꍇ
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
// ���΃p�X�̏ꍇ
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

// �e�X�g�t�B�N�X�`���N���X�̒�`(ParamLoader)
class ParamLoaderTest : public Test {
protected:

	// �����J�n���Ɉ�񂾂����s
	static void SetUpTestCase() {
		//std::cout << "#####Start Test#####\n" << std::endl;
	}

	// �����I�����Ɉ�񂾂����s
	static void TearDownTestCase() {
		//std::cout << "#####Finish Test#####" << std::endl;
	}

	// �e�e�X�g�P�[�X���s�O�Ɏ��s
	virtual void SetUp() {
		// ���O�ɐݒ�t�@�C���̃}�X�^�[���J�����g�f�B���N�g���ɃR�s�[
		copy_config_file();
		//std::cout << "#####Start TestCase#####\n" << std::endl;
	}

	// �e�e�X�g�P�[�X���s��Ɏ��s
	virtual void TearDown() {
		//std::cout << "#####Finish TestCase#####" << std::endl;
	}
};

// �e�X�g�t�B�N�X�`���N���X�̒�`(FileWriter)
class FileWriterTest : public Test {
protected:

	// �����J�n���Ɉ�񂾂����s
	static void SetUpTestCase() {
		//std::cout << "#####Start Test#####\n" << std::endl;
	}

	// �����I�����Ɉ�񂾂����s
	static void TearDownTestCase() {
		//std::cout << "#####Finish Test#####" << std::endl;
	}

	// �e�e�X�g�P�[�X���s�O�Ɏ��s
	virtual void SetUp() {
		// �o�̓t�@�C���ƃf�B���N�g���̍폜
		DeleteFile(OUTPUT_FILEPATH.c_str());
		RemoveDirectory(OUTPUT_DIRPATH.c_str());
		//std::cout << "#####Start TestCase#####\n" << std::endl;
	}

	// �e�e�X�g�P�[�X���s��Ɏ��s
	virtual void TearDown() {
		DeleteFile(OUTPUT_FILEPATH.c_str());
		RemoveDirectory(OUTPUT_DIRPATH.c_str());
		//std::cout << "#####Finish TestCase#####" << std::endl;
	}
};

// �e�X�g�t�B�N�X�`���N���X�̒�`()
class ProcessingTimeTest : public Test {
protected:

	// �����J�n���Ɉ�񂾂����s
	static void SetUpTestCase() {
		//std::cout << "#####Start Test#####\n" << std::endl;
	}

	// �����I�����Ɉ�񂾂����s
	static void TearDownTestCase() {
		//std::cout << "#####Finish Test#####" << std::endl;
	}

	// �e�e�X�g�P�[�X���s�O�Ɏ��s
	virtual void SetUp() {
		// �o�̓t�@�C���ƃf�B���N�g���̍폜
		DeleteFile(OUTPUT_FILEPATH.c_str());
		RemoveDirectory(OUTPUT_DIRPATH.c_str());
		//std::cout << "#####Start TestCase#####\n" << std::endl;
	}

	// �e�e�X�g�P�[�X���s��Ɏ��s
	virtual void TearDown() {
		DeleteFile(OUTPUT_FILEPATH.c_str());
		RemoveDirectory(OUTPUT_DIRPATH.c_str());
		//std::cout << "#####Finish TestCase#####" << std::endl;
	}
};

// DataLoader�̃��b�N�N���X
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

	// �ݒ�t�@�C���̃}�X�^�[���R�s�[���邽�߂̏���
	GetModuleFileName(nullptr, buff, DEFINE_STRING_SIZE);
	_splitpath_s(buff, drive, DEFINE_STRING_SIZE, dir, DEFINE_STRING_SIZE, nullptr, 0, nullptr, 0);
	sprintf_s(COPIED_CONFIG_FILEPATH, DEFINE_STRING_SIZE, "%s%s", drive, dir);
	strcat_s(COPIED_CONFIG_FILEPATH, DEFINE_STRING_SIZE, "config.ini");

	// �ݒ�t�@�C���̃}�X�^�[���R�s�[
	CopyFile(CONFIG_FILEPATH.c_str(), COPIED_CONFIG_FILEPATH, FALSE);
}

// ###Common�̃e�X�g��������###
TEST(CommonTest, SetWorkingDirectory_Test) {
	bool ans = false;
	ans = SetWorkingDirectory();

	EXPECT_EQ(true, ans);
}
// ###Common�̃e�X�g�����܂�###

// ###ParamLoader�̃e�X�g��������###
// �R���X�g���N�^�̃e�X�g�i��O���������Ȃ����`�F�b�N�j
TEST_F(ParamLoaderTest, constructor_Test) {

	EXPECT_NO_THROW(ParamLoader());
}

// �f�X�g���N�^�̃e�X�g�i��O���������Ȃ����`�F�b�N�j
TEST_F(ParamLoaderTest, destructor_Test) {

	EXPECT_NO_THROW(ParamLoader().~ParamLoader());
}

TEST_F(ParamLoaderTest, load_param_PathFileExists_Test) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����폜
	DeleteFile(COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-2, ans);
}

TEST_F(ParamLoaderTest, load_param_params_device_id_Test) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("camera", "device_id", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-3, ans);
}

TEST_F(ParamLoaderTest, load_param_params_c_frame_width_Test1) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("camera", "c_frame_width", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-4, ans);
}

TEST_F(ParamLoaderTest, load_param_params_c_frame_width_Test2) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("camera", "c_frame_width", "-2", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-5, ans);
}

TEST_F(ParamLoaderTest, load_param_params_c_frame_height_Test1) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("camera", "c_frame_height", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-6, ans);
}

TEST_F(ParamLoaderTest, load_param_params_c_frame_height_Test2) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("camera", "c_frame_height", "-2", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-7, ans);
}

TEST_F(ParamLoaderTest, load_param_params_c_fps_Test1) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("camera", "c_fps", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-8, ans);
}

TEST_F(ParamLoaderTest, load_param_params_c_fps_Test2) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("camera", "c_fps", "-2", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-9, ans);
}

TEST_F(ParamLoaderTest, load_param_params_data_type_Test1) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("input", "data_type", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-10, ans);
}

TEST_F(ParamLoaderTest, load_param_params_data_type_Test2) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("input", "data_type", "3", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-11, ans);
}

TEST_F(ParamLoaderTest, load_param_params_input_movie_path_Test) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("input", "input_movie_path", "", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-12, ans);
}

TEST_F(ParamLoaderTest, load_param_params_input_image_path_Test) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("input", "input_image_path", "", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-13, ans);
}

TEST_F(ParamLoaderTest, load_param_params_cascade_filepath_Test) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("detector", "cascade_filepath", "", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-14, ans);
}

TEST_F(ParamLoaderTest, load_param_params_face_detect_width_Test1) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("detector", "face_detect_width", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-15, ans);
}

TEST_F(ParamLoaderTest, load_param_params_face_detect_width_Test2) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("detector", "face_detect_width", "-2", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-16, ans);
}

TEST_F(ParamLoaderTest, load_param_params_face_detect_height_Test1) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("detector", "face_detect_height", "-1", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-17, ans);
}

TEST_F(ParamLoaderTest, load_param_params_face_detect_height_Test2) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
	WritePrivateProfileString("detector", "face_detect_height", "-2", COPIED_CONFIG_FILEPATH);

	ans = paramloader.load_param(params);
	EXPECT_EQ(-18, ans);
}

TEST_F(ParamLoaderTest, load_param_params_output_dirpath_Test) {
	int ans = 0;
	Params params;
	ParamLoader paramloader;

	// �ݒ�t�@�C�����̃p�����[�^�ύX
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
// ###ParamLoader�̃e�X�g�����܂�###

// ###DataLoader�̃e�X�g��������###
// �R���X�g���N�^�̃e�X�g�i��O���������Ȃ����`�F�b�N�j
TEST(DataLoaderTest, constructor_Test) {

	//EXPECT_THROW(DataLoader(), std::exception);
	EXPECT_NO_THROW(DataLoader());
}

// �f�X�g���N�^�̃e�X�g�i��O���������Ȃ����`�F�b�N�j
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

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	Params params;
	params.data_type = 0;

	// �t�@�C�������݂��Ȃ��p�X��ݒ�
	params.input_movie_path = INPUT_MOVIE_PATH_DUMMY1;

	ans = dataloader.initialize(params);
	EXPECT_EQ(-1, ans);
}

TEST(DataLoaderTest, initialize_data_type_0_PathIsDirectory_Test) {
	int ans = 0;
	DataLoader dataloader;

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	Params params;
	params.data_type = 0;

	// �f�B���N�g���̃p�X��ݒ�
	params.input_movie_path = INPUT_MOVIE_PATH_DUMMY2;

	ans = dataloader.initialize(params);
	EXPECT_EQ(-2, ans);
}

TEST(DataLoaderTest, initialize_data_type_0_Positive_Test) {
	int ans = 0;
	DataLoader dataloader;

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	Params params;
	params.data_type = 0;

	// ���݂��铮��̃t�@�C���p�X��ݒ�
	params.input_movie_path = INPUT_MOVIE_PATH1;

	ans = dataloader.initialize(params);
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, initialize_data_type_1_PathFileExists_Test) {
	int ans = 0;
	DataLoader dataloader;

	// ���̓f�[�^�̃^�C�v���摜�ɐݒ�
	Params params;
	params.data_type = 1;

	// �f�B���N�g�������݂��Ȃ��p�X��ݒ�
	params.input_image_path = INPUT_IMAGE_PATH_DUMMY1;

	ans = dataloader.initialize(params);
	EXPECT_EQ(-3, ans);
}

TEST(DataLoaderTest, initialize_data_type_1_PathIsDirectory_Test) {
	int ans = 0;
	DataLoader dataloader;

	// ���̓f�[�^�̃^�C�v���摜�ɐݒ�
	Params params;
	params.data_type = 1;

	// �t�@�C���̃p�X��ݒ�
	params.input_image_path = INPUT_IMAGE_PATH_DUMMY2;

	ans = dataloader.initialize(params);
	EXPECT_EQ(-4, ans);
}

TEST(DataLoaderTest, initialize_data_type_1_Positive_Test) {
	int ans = 0;
	DataLoader dataloader;

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	Params params;
	params.data_type = 1;

	// ���݂��铮��̃t�@�C���p�X��ݒ�
	params.input_image_path = INPUT_IMAGE_PATH1;

	ans = dataloader.initialize(params);
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, initialize_data_type_2_Positive_Test) {
	int ans = 0;
	DataLoader dataloader;

	// ���̓f�[�^�̃^�C�v���J�����f���ɐݒ�
	Params params;
	params.data_type = 2;

	// �J�����f���̃p�����[�^��ݒ�
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

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// ���揈���ŏ�����
	iret = dataloader.initialize(params);

	// ���open_data()���Ă��flag��true�ɂ���
	ans = dataloader.open_data();
	ans = dataloader.open_data();
	EXPECT_EQ(-1, ans);
}

TEST(DataLoaderTest, open_data_file_data_type_0_capisOpened_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// ���揈���ŏ�����
	iret = dataloader.initialize(params);

	// ���̓f�[�^��ʂ̃f�B���N�g���Ɉړ�
	_mkdir(TMP_INPUT_MOVIE_DIRPATH.c_str());
	MoveFile(INPUT_MOVIE_PATH1.c_str(), (TMP_INPUT_MOVIE_DIRPATH+"\\sample.avi").c_str());

	ans = dataloader.open_data();
	EXPECT_EQ(-2, ans);

	// ���̓f�[�^�����̃f�B���N�g���Ɉړ�
	MoveFile((TMP_INPUT_MOVIE_DIRPATH + "\\sample.avi").c_str(), INPUT_MOVIE_PATH1.c_str());
	RemoveDirectory(TMP_INPUT_MOVIE_DIRPATH.c_str());
}

TEST(DataLoaderTest, open_data_file_data_type_0_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// ���揈���ŏ�����
	iret = dataloader.initialize(params);

	ans = dataloader.open_data();
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, open_data_file_data_type_1_file_namessize_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// ���̓f�[�^�̃^�C�v���摜�ɐݒ�
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH1;

	// �摜�����ŏ�����
	iret = dataloader.initialize(params);

	// ���̓f�[�^��ʂ̃f�B���N�g���Ɉړ�
	_mkdir(TMP_INPUT_IMAGE_DIRPATH.c_str());
	MoveFile(INPUT_IMAGE_PATH1.c_str(), (TMP_INPUT_IMAGE_DIRPATH +"\\sample1").c_str());

	ans = dataloader.open_data();
	EXPECT_EQ(-3, ans);

	// ���̓f�[�^�����̃f�B���N�g���Ɉړ�
	MoveFile((TMP_INPUT_IMAGE_DIRPATH + "\\sample1").c_str(), INPUT_IMAGE_PATH1.c_str());
	RemoveDirectory(TMP_INPUT_IMAGE_DIRPATH.c_str());
}

TEST(DataLoaderTest, open_data_file_data_type_1_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// ���̓f�[�^�̃^�C�v���摜�ɐݒ�
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH1;

	// �摜�����ŏ�����
	iret = dataloader.initialize(params);

	ans = dataloader.open_data();
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, open_data_file_data_type_2_capisOpened_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// ���̓f�[�^�̃^�C�v���J�����f���ɐݒ�
	params.data_type = 2;
	params.device_id = -1;

	// �J�����f�������ŏ�����
	iret = dataloader.initialize(params);

	ans = dataloader.open_data();
	EXPECT_EQ(-4, ans);
}

// �J�����f�����擾����̂Ɏ��Ԃ������邱�Ƃɒ���
TEST(DataLoaderTest, open_data_file_data_type_2_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// ���̓f�[�^�̃^�C�v���J�����f���ɐݒ�
	params.data_type = 2;
	params.device_id = 0;

	// �J�����f�������ŏ�����
	iret = dataloader.initialize(params);

	ans = dataloader.open_data();
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, load_mv_file_open_flag_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// ���揈���ŏ�����
	iret = dataloader.initialize(params);

	// GrabImage�̈����p
	cv::Mat img;

	ans = dataloader.load_mv(img);
	EXPECT_EQ(-1, ans);
}

TEST(DataLoaderTest, load_mv_img_empty_Test) {
	int ans = -1;
	int iret = -1;
	cv::Mat img; //grab_image�̈����p
	DataLoader dataloader;

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	Params params;
	params.data_type = 0;

	// ���݂��铮��̃t�@�C���p�X��ݒ�
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

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// ���揈���ŏ�����
	iret = dataloader.initialize(params);

	// open_data()���Ă��flag��true�ɂ���
	iret = dataloader.open_data();

	// GrabImage�̈����p
	cv::Mat img;

	ans = dataloader.load_mv(img);
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, load_img_img_empty_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	cv::Mat img; //load_img�̈����p

				 // ���̓f�[�^�̃^�C�v��Î~��ɐݒ�
	Params params;
	params.data_type = 1;

	// �쐬�����f�B���N�g���p�X��ݒ�
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

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH1;

	// ���揈���ŏ�����
	iret = dataloader.initialize(params);

	// open_data()���Ă��flag��true�ɂ���
	iret = dataloader.open_data();

	// GrabImage�̈����p
	cv::Mat img;

	ans = dataloader.load_img(img);
	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, get_frame_info_Test) {
	std::string ans = "";
	int iret = -1;
	cv::Mat img; //grab_image�̈����p
	DataLoader dataloader;

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	Params params;
	params.data_type = 0;

	// ���݂��铮��̃t�@�C���p�X��ݒ�
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
//	cv::Mat img; //grab_image�̈����p
//	DataLoader dataloader;
//
//	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
//	Params params;
//	params.data_type = 0;
//
//	// ���݂��铮��̃t�@�C���p�X��ݒ�
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
//	cv::Mat img; //grab_image�̈����p
//	DataLoader dataloader;
//
//	// ���̓f�[�^�̃^�C�v��Î~��ɐݒ�
//	Params params;
//	params.data_type = 1;
//
//	// ���݂���摜�f�B���N�g���p�X��ݒ�
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

// �J�����f�����擾����̂Ɏ��Ԃ������邱�Ƃɒ���
//TEST(DataLoaderTest, get_frame_info_data_type_2_Test) {
//	std::string ans = "";
//	int iret = -1;
//	cv::Mat img; //grab_image�̈����p
//	DataLoader dataloader;
//
//	// ���̓f�[�^�̃^�C�v���J�����ɐݒ�
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

	// ���b�N�I�u�W�F�N�g���쐬
	mock_DataLoader *mock_d = new mock_DataLoader();

	//���揈���̃p�����[�^�ɐݒ�
	Params params;
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// GrabImage�̈����p
	cv::Mat img;

	// load_mv�̖߂�l�Ƃ���-1���ԋp�����悤�ݒ�A�����͔C�ӂƂ���
	EXPECT_CALL(*mock_d, load_mv(testing::_)).WillRepeatedly(Return(-1));

	DataLoader* dataloader = mock_d;

	ans = dataloader->grab_image(img);

	// ���b�N�I�u�W�F�N�g�̉��
	delete mock_d;

	EXPECT_EQ(-1, ans);
}

TEST(DataLoaderTest, grab_image_data_type_0_Positive_Test) {
	int ans = 0;
	int iret = -1;

	// ���b�N�I�u�W�F�N�g���쐬
	mock_DataLoader *mock_d = new mock_DataLoader();

	//���揈���̃p�����[�^�ɐݒ�
	Params params;
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;

	// GrabImage�̈����p
	cv::Mat img;

	// load_mv�̖߂�l�Ƃ���0���ԋp�����悤�ݒ�A�����͔C�ӂƂ���
	EXPECT_CALL(*mock_d, load_mv(testing::_)).WillRepeatedly(Return(0));

	DataLoader* dataloader = mock_d;

	ans = dataloader->grab_image(img);

	// ���b�N�I�u�W�F�N�g�̉��
	delete mock_d;

	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, grab_image_data_type_1_Test) {
	int ans = -1;
	int iret = -1;

	// ���b�N�I�u�W�F�N�g���쐬
	mock_DataLoader* mock_d = new mock_DataLoader();

	// �摜�����̃p�����[�^�ɐݒ�
	Params params;
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH1;

	// �摜�����ŏ�����
	iret = mock_d->initialize(params);

	// GrabImage�̈����p
	cv::Mat img;

	// load_img�̖߂�l�Ƃ���-1���ԋp�����悤�ݒ�B�����͔C�ӂƂ���
	EXPECT_CALL(*mock_d, load_img(testing::_)).WillRepeatedly(Return(-1));

	DataLoader* dataloader = mock_d;

	ans = mock_d->grab_image(img);

	// ���b�N�I�u�W�F�N�g�̉��
	delete mock_d;

	EXPECT_EQ(-2, ans);
}

TEST(DataLoaderTest, grab_image_data_type_1_Positive_Test) {
	int ans = -1;
	int iret = -1;

	// ���b�N�I�u�W�F�N�g���쐬
	mock_DataLoader* mock_d = new mock_DataLoader();

	// �摜�����̃p�����[�^�ɐݒ�
	Params params;
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH1;

	// �摜�����ŏ�����
	iret = mock_d->initialize(params);

	// GrabImage�̈����p
	cv::Mat img;

	// load_img�̖߂�l�Ƃ���-1���ԋp�����悤�ݒ�B�����͔C�ӂƂ���
	EXPECT_CALL(*mock_d, load_img(testing::_)).WillRepeatedly(Return(0));

	DataLoader* dataloader = mock_d;

	ans = mock_d->grab_image(img);

	// ���b�N�I�u�W�F�N�g�̉��
	delete mock_d;

	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, grab_image_data_type_2_Test) {
	int ans = 0;
	int iret = -1;

	// ���b�N�I�u�W�F�N�g���쐬
	mock_DataLoader *mock_d = new mock_DataLoader();

	//���揈���̃p�����[�^�ɐݒ�
	Params params;
	params.data_type = 2;

	// �摜�����ŏ�����
	iret = mock_d->initialize(params);

	// GrabImage�̈����p
	cv::Mat img;

	// load_mv�̖߂�l�Ƃ���-1���ԋp�����悤�ݒ�A�����͔C�ӂƂ���
	EXPECT_CALL(*mock_d, load_mv(testing::_)).WillRepeatedly(Return(-1));

	DataLoader* dataloader = mock_d;

	ans = dataloader->grab_image(img);

	// ���b�N�I�u�W�F�N�g�̉��
	delete mock_d;

	EXPECT_EQ(-3, ans);
}

TEST(DataLoaderTest, grab_image_data_type_2_Positive_Test) {
	int ans = 0;
	int iret = -1;

	// ���b�N�I�u�W�F�N�g���쐬
	mock_DataLoader *mock_d = new mock_DataLoader();

	//���揈���̃p�����[�^�ɐݒ�
	Params params;
	params.data_type = 2;

	// �摜�����ŏ�����
	iret = mock_d->initialize(params);

	// GrabImage�̈����p
	cv::Mat img;

	// load_mv�̖߂�l�Ƃ���-1���ԋp�����悤�ݒ�A�����͔C�ӂƂ���
	EXPECT_CALL(*mock_d, load_mv(testing::_)).WillRepeatedly(Return(0));

	DataLoader* dataloader = mock_d;

	ans = dataloader->grab_image(img);

	// ���b�N�I�u�W�F�N�g�̉��
	delete mock_d;

	EXPECT_EQ(0, ans);
}

TEST(DataLoaderTest, get_filelist_Positive_Test) {
	int ans = 0;
	int iret = -1;
	DataLoader dataloader;
	Params params;

	// ���̓f�[�^�̃^�C�v���摜�ɐݒ�
	params.data_type = 1;
	params.input_image_path = INPUT_IMAGE_PATH1;

	// ���揈���ŏ�����
	iret = dataloader.initialize(params);

	ans = dataloader.get_filelist();
	EXPECT_EQ(0, ans);
}
// ###DataLoader�̃e�X�g�����܂�###

// ###FaceDetector�̃e�X�g��������###
// �R���X�g���N�^�̃e�X�g�i��O���������Ȃ����`�F�b�N�j
TEST(FaceDetectorTest, constructor_Test) {

	EXPECT_NO_THROW(FaceDetector());
}

// �f�X�g���N�^�̃e�X�g�i��O���������Ȃ����`�F�b�N�j
TEST(FaceDetectorTest, destructor_Test) {

	EXPECT_NO_THROW(FaceDetector().~FaceDetector());
}

TEST(FaceDetectorTest, initialize_PathFileExists_Test) {
	int ans = 0;
	FaceDetector facedetector;

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	Params params;

	// �t�@�C�������݂��Ȃ��p�X��ݒ�
	params.cascade_filepath = CASCADE_FILEPATH_DUMMY1;

	ans = facedetector.initialize(params);
	EXPECT_EQ(-1, ans);
}

TEST(FaceDetectorTest, initialize_PathIsDirectory_Test) {
	int ans = 0;
	FaceDetector facedetector;

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	Params params;

	// �f�B���N�g���̃p�X��ݒ�
	params.cascade_filepath = CASCADE_FILEPATH_DUMMY2;

	ans = facedetector.initialize(params);
	EXPECT_EQ(-2, ans);
}

TEST(FaceDetectorTest, initialize_cascadeload_Test) {
	int ans = 0;
	FaceDetector facedetector;

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	Params params;

	// �J�X�P�[�h���ފ�̃_�~�[�f�[�^���쐬
	_mkdir(TMP_CASCADE_DIRPATH);
	CreateFile(TMP_CASCADE_FILEPATH, GENERIC_WRITE, FILE_SHARE_DELETE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	// �J�X�P�[�h���ފ�̃_�~�[�f�[�^�̃t�@�C���p�X��ݒ�
	params.cascade_filepath = TMP_CASCADE_FILEPATH;

	ans = facedetector.initialize(params);
	EXPECT_EQ(-3, ans);

	// �J�X�P�[�h���ފ�̃_�~�[�f�[�^�̃t�@�C���ƃf�B���N�g�����폜
	DeleteFile(TMP_CASCADE_FILEPATH);
	RemoveDirectory(TMP_CASCADE_DIRPATH);
}

TEST(FaceDetectorTest, initialize_Positive_Test) {
	int ans = 0;
	FaceDetector facedetector;

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	Params params;

	// �J�X�P�[�h���ފ�̃t�@�C���p�X��ݒ�
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

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;
	params.cascade_filepath = CASCADE_FILEPATH;

	// ���揈���ŏ�����
	iret = dataloader.initialize(params);

	// ����f�[�^���I�[�v��
	iret = dataloader.open_data();

	// �猟�o��̏�����
	iret = facedetector.initialize(params);

	ans = facedetector.detect_face(img, faces);
	EXPECT_EQ(0, ans);
}
// ###FaceDetector�̃e�X�g�����܂�###

// ###FileWriter�̃e�X�g��������###
// �R���X�g���N�^�̃e�X�g�i��O���������Ȃ����`�F�b�N�j
TEST_F(FileWriterTest, constructor_Test) {

	EXPECT_NO_THROW(FileWriter());
}

// �f�X�g���N�^�̃e�X�g�i��O���������Ȃ����`�F�b�N�j
TEST_F(FileWriterTest, destructor_Test) {
	EXPECT_NO_THROW(FileWriter().~FileWriter());
}

TEST_F(FileWriterTest, initialize_mkdir_Test)
{
	int ans = 0;
	FileWriter filewriter;

	// ���݂��Ȃ��f�B���N�g���p�X��ݒ�
	Params params;
	params.output_dirpath = OUTPUT_DIRPATH_DUMMY1;

	ans = filewriter.initialize(params);
	EXPECT_EQ(-1, ans);
}

TEST_F(FileWriterTest, initialize_Positive_Test)
{
	int ans = 0;
	FileWriter filewriter;

	// �o�̓f�B���N�g���̃p�X��ݒ�
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

	// �o�̓f�B���N�g���̃p�X��ݒ�
	Params params;
	params.output_dirpath = OUTPUT_DIRPATH;

	// ������
	iret = filewriter.initialize(params);

	// 2��Ă�Ńt���O��true�ɂ���
	ans = filewriter.open_file();
	ans = filewriter.open_file();

	EXPECT_EQ(-1, ans);
}

TEST_F(FileWriterTest, open_file_writing_file_is_open_Test)
{
	int ans = 0;
	int iret = -1;
	FileWriter filewriter;

	// �o�̓f�B���N�g���̃p�X��ݒ�
	Params params;
	params.output_dirpath = OUTPUT_DIRPATH;

	// ������
	iret = filewriter.initialize(params);

	// �쐬�����f�B���N�g�����폜
	RemoveDirectory(params.output_dirpath.c_str());

	ans = filewriter.open_file();

	EXPECT_EQ(-2, ans);
}

TEST_F(FileWriterTest, open_file_Positive_Test)
{
	int ans = 0;
	int iret = -1;
	FileWriter filewriter;

	// �o�̓f�B���N�g���̃p�X��ݒ�
	Params params;
	params.output_dirpath = OUTPUT_DIRPATH;

	// ������
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

	// �o�̓f�B���N�g���̃p�X��ݒ�
	Params params;
	params.output_dirpath = OUTPUT_DIRPATH;

	// ������
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

	// �p�����[�^��ݒ�
	Params params;
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH1;
	params.cascade_filepath = CASCADE_FILEPATH;
	params.face_detect_width = 20;
	params.face_detect_height = 20;
	params.output_dirpath = OUTPUT_DIRPATH;

	// �f�[�^�ǂݍ��݋@�\�̏�����
	iret = dataloader.initialize(params);

	// ���̓f�[�^���I�[�v��
	iret = dataloader.open_data();

	// �猟�o��̏�����
	iret = facedetector.initialize(params);

	// �t�@�C���o�͊�̏�����
	iret = filewriter.initialize(params);

	// �o�̓t�@�C�����I�[�v��
	iret = filewriter.open_file();

	// 1�t���[�����o��
	iret = dataloader.grab_image(img);

	// �t���[������猟�o
	iret = facedetector.detect_face(img, faces);

	// �o�̓t�@�C���ɏ�������
	ans = filewriter.output_file(dataloader, img, faces);

	EXPECT_EQ(0, ans);

}
// ###FileWriter�̃e�X�g�����܂�###

// ###�������Ԃ̃e�X�g��������###
// 1�t���[���̎擾���Ԃ��e�X�g
TEST_F(ProcessingTimeTest, DataLoader_grab_image_elapsed_time_Test) {
	int iret = -1;
	DataLoader dataloader;
	Params params;
	ParamLoader paramloader;

	cv::Mat img;
	std::vector<cv::Rect> faces;

	std::chrono::system_clock::time_point  start, end;
	double elapsed_time, sum_time = 0.0, mean_elapsed_time;

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH2;

	// ���揈���ŏ�����
	iret = dataloader.initialize(params);

	// ����f�[�^���I�[�v��
	iret = dataloader.open_data();

	while (1)
	{
		// 1�t���[�������o��
		start = std::chrono::system_clock::now(); // �v���J�n����
		iret = dataloader.grab_image(img);
		end = std::chrono::system_clock::now();  // �v���I������

		// �����ɗv�������Ԃ��~���b�ɕϊ�
		elapsed_time = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		sum_time += elapsed_time;
		//std::cout << elapsed_time << " msec" << std::endl;

		// �ŏI�t���[���ɂȂ����烋�[�v�𔲂���
		if (dataloader.get_frame_index() == dataloader.get_frame_num())
		{
			break;
		}
	}
	mean_elapsed_time = sum_time / dataloader.get_frame_num();
	//std::cout << "mean: " << mean_elapsed_time << " msec" << std::endl;
	//ASSERT_TRUE(mean_elapsed_time <= 50); //50ms�ȉ���������A�Ƃ肠����OK
}

// 1�t���[���̊猟�o���Ԃ��e�X�g
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

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH2;
	params.cascade_filepath = CASCADE_FILEPATH;

	// ���揈���ŏ�����
	iret = dataloader.initialize(params);

	// ����f�[�^���I�[�v��
	iret = dataloader.open_data();

	// �猟�o��̏�����
	iret = facedetector.initialize(params);

	while (1)
	{
		// 1�t���[�������o��
		iret = dataloader.grab_image(img);

		// �t���[������猟�o
		start = std::chrono::system_clock::now(); // �v���J�n����
		iret = facedetector.detect_face(img, faces);
		end = std::chrono::system_clock::now();  // �v���I������

		// �����ɗv�������Ԃ��~���b�ɕϊ�
		elapsed_time = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		sum_time += elapsed_time;
		//std::cout << elapsed_time << " msec" << std::endl;

		// �ŏI�t���[���ɂȂ����烋�[�v�𔲂���
		if (dataloader.get_frame_index() == dataloader.get_frame_num())
		{
			break;
		}
	}
	mean_elapsed_time = sum_time / dataloader.get_frame_num();
	//std::cout << "mean: " << mean_elapsed_time << " msec" << std::endl;
	//ASSERT_TRUE(mean_elapsed_time <= 500); //500ms�ȉ���������A�Ƃ肠����OK
}

// 1�t���[���̃t�@�C���o�͎��Ԃ��e�X�g
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

	// ���̓f�[�^�̃^�C�v�𓮉�ɐݒ�
	params.data_type = 0;
	params.input_movie_path = INPUT_MOVIE_PATH2;
	params.cascade_filepath = CASCADE_FILEPATH;
	params.output_dirpath = OUTPUT_DIRPATH;

	// ���揈���ŏ�����
	iret = dataloader.initialize(params);

	// ����f�[�^���I�[�v��
	iret = dataloader.open_data();

	// �猟�o��̏�����
	iret = facedetector.initialize(params);

	// �t�@�C���o�͊�̏�����
	iret = filewriter.initialize(params);

	// �o�̓t�@�C�����I�[�v��
	iret = filewriter.open_file();

	while (1)
	{
		// 1�t���[�������o��
		iret = dataloader.grab_image(img);

		// �t���[������猟�o
		iret = facedetector.detect_face(img, faces);

		// �o�̓t�@�C���ɏ�������
		start = std::chrono::system_clock::now(); // �v���J�n����
		iret = filewriter.output_file(dataloader, img, faces);
		end = std::chrono::system_clock::now();  // �v���I������

		// �����ɗv�������Ԃ��~���b�ɕϊ�
		//elapsed_time = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		elapsed_time = (double)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		sum_time += elapsed_time;
		//std::cout << elapsed_time << " microsec" << std::endl;


		// �ŏI�t���[���ɂȂ����烋�[�v�𔲂���
		if (dataloader.get_frame_index() == dataloader.get_frame_num())
		{
			break;
		}
	}
	mean_elapsed_time = sum_time / dataloader.get_frame_num();
	//std::cout << "mean: " << mean_elapsed_time << " microsec" << std::endl;
	//ASSERT_TRUE(mean_elapsed_time <= 200); //200microsec�ȉ���������A�Ƃ肠����OK
}
// ###�������Ԃ̃e�X�g�����܂�###