#ifndef _DATALOADER_H_
#define _DATALOADER_H_

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "common.h"

class DataLoader
{
public:
	// �R���X�g���N�^
	DataLoader();

	// �f�X�g���N�^
	~DataLoader();

	// �t���[���ԍ����擾����֐�
	int get_frame_index();

	// �����摜�̃t���[�������擾����֐�
	int get_frame_num();

	// �������֐�
	int initialize(const Params &params);

	// �t���[�����ɂ��ĕ\������֐��i�f�o�b�O�p�j
	void print_info();

	// ���̓f�[�^���I�[�v������֐�
	int open_data();

	// ���̓f�[�^������̏ꍇ�Ƀt���[�����Ƃɉ摜�Ƃ��ĕۑ�����֐��i�f�o�b�O�p�j
	void save_frame(cv::Mat &img);

	// �����ǂݍ��ފ֐�
	virtual int load_mv(cv::Mat &img);

	// �摜��ǂݍ��ފ֐�
	virtual int load_img(cv::Mat &img);

	// �t���[���ԍ���t�@�C���p�X��Ԃ��֐�
	std::string DataLoader::get_frame_info();

	// 1�t���[�������o���֐�
	int grab_image(cv::Mat &img);

	// ���͉摜�f�[�^�̃f�B���N�g�����炷�ׂẲ摜�t�@�C���̃p�X���擾����֐�
	int get_filelist();

private:
	int device_id; // �J������device ID
	int frame_num; // �t���[����
	int frame_index; //�t���[���ԍ�
	int img_w; // �t���[���̉���
	int img_h; // �t���[���̏c��
	std::string input_movie_path; // ���͓���̐�΃p�X
	std::string input_image_path; // ���͉摜�Q�̃t�H���_�̐�΃p�X
	int data_type; // 0:����,1:�摜,2:�J����
	std::vector<std::string> file_names; // �摜�̃t�@�C���p�X�̃��X�g
	double fps; // fps
	cv::VideoCapture cap; // ����̃L���v�`��
	bool file_open_flag; // �t�@�C�����J���������肷��t���O
};

#endif