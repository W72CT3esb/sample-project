#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>

// �J�����g�f�B���N�g���Ɉړ�����֐�
bool SetWorkingDirectory();

struct Params{

	// [camera section]
	int device_id; // �J������device ID
	int c_frame_width; // �J�����œǂݍ��ޓ���̉���
	int c_frame_height; // �J�����œǂݍ��ޓ���̏c��
	int c_fps; // �J�����œǂݍ��ޓ����fps

	// [input section]
	int data_type; // 0:����,1:�摜,2:�J����
	std::string input_movie_path; // ���͓���̃p�X
	std::string input_image_path; // ���͉摜�Q�̃t�H���_�̃p�X
	std::string cascade_filepath; // �J�X�P�[�h���ފ�̃t�@�C���̃p�X

	// [detector section]
	int face_detect_width; // �猟�o�̉�����臒l
	int face_detect_height; // �猟�o�̏c����臒l

	// [output section]
	std::string output_dirpath; // �o�͌��ʂ̃t�H���_�̃p�X

	// �R���X�g���N�^
	Params(){
		device_id = 0; // �J������device ID
		c_frame_width = 1280; // �J�����̃t���[���̉���
		c_frame_height = 720; // �J�����̃t���[���̏c��
		c_fps = 30; // �J������fps

		data_type = 0; // 0:����,1:�摜,2:�J����
		input_movie_path = ""; // ���͓���̃p�X
		input_image_path = ""; // ���͉摜�Q�̃t�H���_�̃p�X
		cascade_filepath = ""; // �J�X�P�[�h���ފ�t�@�C���̃p�X

		face_detect_width = 20; // �猟�o�̉�����臒l
		face_detect_height = 20; // �猟�o�̏c����臒l

		output_dirpath = ""; // �o�͌��ʃt�H���_�̃p�X
	}
};

#endif