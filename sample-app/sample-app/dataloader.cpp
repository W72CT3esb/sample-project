#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <shlwapi.h>
#include "dataloader.h"
#include "common.h"

// �R���X�g���N�^
DataLoader::DataLoader()
{
	//std::cout << "LoadData�I�u�W�F�N�g����" << std::endl;
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

// �f�X�g���N�^
DataLoader::~DataLoader()
{
	//std::cout << "LoadData�I�u�W�F�N�g�j��" << std::endl;
}

// �t���[���ԍ����擾����֐�
int DataLoader::get_frame_index()
{
	return this->frame_index;
}

// �����摜�̃t���[�������擾����֐�
int DataLoader::get_frame_num()
{
	return this->frame_num;
}

// �������֐�
int DataLoader::initialize(const Params &params)
{
	this->data_type = params.data_type;
	if (this->data_type == 0) // ���̓f�[�^������̏ꍇ
	{
		if (!PathFileExists(params.input_movie_path.c_str())) // �p�X�̏ꏊ�Ƀt�@�C�������݂��Ȃ��ꍇ�Ɏ��s
		{
			return -1;
		}
		if (PathIsDirectory(params.input_movie_path.c_str())) // �t�@�C���ł͂Ȃ��f�B���N�g���̏ꍇ�Ɏ��s
		{
			return -2;
		}
		this->input_movie_path = params.input_movie_path; // ���͓���f�[�^�̃p�X��ݒ�
	}
	else if (this->data_type == 1) // ���̓f�[�^���摜�̏ꍇ
	{
		if (!PathFileExists(params.input_image_path.c_str())) // �p�X�̏ꏊ�Ƀf�B���N�g�������݂��Ȃ��ꍇ�Ɏ��s
		{
			return -3;
		}
		if (!PathIsDirectory(params.input_image_path.c_str())) // �f�B���N�g���ł͂Ȃ��ꍇ�Ɏ��s
		{
			return -4;
		}
		this->input_image_path = params.input_image_path; // ���͉摜�Q������f�B���N�g���̃p�X��ݒ�
	}
	else // ���̓f�[�^���J��������̉f���̏ꍇ
	{
		this->device_id = params.device_id;
		this->img_h = params.c_frame_height;
		this->img_w = params.c_frame_width;
		this->fps = params.c_fps;
	}

	return 0;
}

// �t���[�����ɂ��ĕ\������֐��i�f�o�b�O�p�j
void DataLoader::print_info()
{
	std::cout << "�ő�t���[����" << this->frame_num << std::endl;
	std::cout << "�t���[���̍���:" << this->img_h << std::endl;
	std::cout << "�t���[���̕�:" << this->img_w << std::endl;
	std::cout << "�t���[����fps:" << this->fps << std::endl;
}

// ���̓f�[�^���I�[�v������֐�
int DataLoader::open_data()
{
	int iret = -1;
	if(this->file_open_flag) // �֐�����ȏ�͎��s�����Ȃ�(false�̎��Ɏ��s)
	{
		return -1;
	}
	if (this->data_type == 0) // ���̓f�[�^������̏ꍇ
	{
		this->cap.open(this->input_movie_path);
		if (!this->cap.isOpened()) // �t�@�C�����J���Ȃ��ꍇ�Ɏ��s
		{
			std::cout << "����t�@�C�����J���܂���" << std::endl;
			return -2;
		}

		this->frame_num = (int)this->cap.get(cv::CAP_PROP_FRAME_COUNT);
		this->img_h = (int)this->cap.get(cv::CAP_PROP_FRAME_HEIGHT);
		this->img_w = (int)this->cap.get(cv::CAP_PROP_FRAME_WIDTH);
		this->fps = this->cap.get(cv::CAP_PROP_FPS);
	}
	else if (this->data_type == 1) // ���̓f�[�^���摜�̏ꍇ
	{
		iret = get_filelist(); // ���͉摜�f�[�^�̃f�B���N�g�����炷�ׂẲ摜�t�@�C���̃p�X���擾
		if (this->file_names.size() == 0) // �f�B���N�g�����ɉ摜�t�@�C�����Ȃ������ꍇ�Ɏ��s
		{
			return -3;
		}
		this->frame_num = (int)this->file_names.size();
	}
	else // ���̓f�[�^���J��������̉f���̏ꍇ
	{
		this->cap.open(this->device_id);
		if (!this->cap.isOpened()) // �t�@�C�����J���Ȃ��ꍇ�Ɏ��s
		{
			std::cout << "camera���J���܂���" << std::endl;
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
	this->file_open_flag = true; //�֐�����x�ǂ񂾂�t���O��true�ɂ���

	return 0;
}

// ���̓f�[�^������̏ꍇ�Ƀt���[�����Ƃɉ摜�Ƃ��ĕۑ�����֐��i�f�o�b�O�p�j
void DataLoader::save_frame(cv::Mat &img)
{
	//�擾�����摜��A�ԉ摜�ŕۑ�
	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(4) << this->frame_index;
	//cv::imwrite("C:\\Users\\1134142029087\\Desktop\\data2\\pic_" + oss.str() + ".jpg", img);
}

// �����ǂݍ��ފ֐�
int DataLoader::load_mv(cv::Mat &img)
{
	if (!this->file_open_flag) // ����t�@�C�����I�[�v�����Ă��Ȃ��ꍇ��load���Ȃ�
	{
		return -1;
	}
	this->cap >> img;
	if (img.empty()) // img���󂾂�����
	{
		return -2;
	}
	cv::resize(img, img, cv::Size(), 0.5, 0.5);
	std::cout << "�t���[���ԍ� " << this->frame_index << std::endl;
	//save_frame(img);
	return 0;
}

// �摜��ǂݍ��ފ֐�
int DataLoader::load_img(cv::Mat &img)
{
	std::cout << this->file_names[this->frame_index] << std::endl;
	img = cv::imread(this->file_names[this->frame_index]);
	if (img.empty()) // img���󂾂�����
	{
		return -1;
	}
	cv::resize(img, img, cv::Size(), 0.5, 0.5);
	std::cout << "�t���[���ԍ� " << this->frame_index << std::endl;
	return 0;
}

// �t���[���ԍ���t�@�C���p�X��Ԃ��֐�
std::string DataLoader::get_frame_info()
{
	if (this->data_type == 0) // ����̎��̓t���[���ԍ���Ԃ�
	{
		return std::to_string(get_frame_index() - 1);
	}
	else if (this->data_type == 1) // �摜�̎��̓t�@�C���p�X��Ԃ�
	{
		return this->file_names[this->frame_index - 1];
	}
	else // �J�����f���̎��̓t���[���ԍ���Ԃ�
	{
		return std::to_string(get_frame_index() - 1);
	}
}

// 1�t���[�������o���֐�
int DataLoader::grab_image(cv::Mat &img)
{
	int iret = -1;
	if (this->data_type == 0) // ���̓f�[�^������̏ꍇ
	{
		iret = load_mv(img);
		if (iret != 0)
		{
			return -1;
		}
	}
	else if (this->data_type == 1) // ���̓f�[�^���摜�̏ꍇ
	{
		iret = load_img(img);
		if (iret != 0)
		{
			return -2;
		}
	}
	else // ���̓f�[�^���J��������̉f���̏ꍇ
	{
		iret = load_mv(img);
		if (iret != 0)
		{
			return -3;
		}
	}

	this->frame_index++; // 1�t���[�����o������J�E���g

	return 0;
}

// ���͉摜�f�[�^�̃f�B���N�g�����炷�ׂẲ摜�t�@�C���̃p�X���擾����֐�
int DataLoader::get_filelist()
{
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;
	std::vector<std::string> file_names;

	std::vector<std::string> extension = { "png" ,"jpg", "bmp"};

	for (int i = 0; i < extension.size(); i++)
	{

		std::string search_name = this->input_image_path + "\\*." + extension[i];

		// �w�肵���t�@�C�����Ɉ�v����t�@�C����f�B���N�g��������(�߂�l�͐����F�����n���h��,���s�F-1(INVALID_HANDLE_VALUE))
		hFind = FindFirstFile(search_name.c_str(), &win32fd);

		if (hFind == INVALID_HANDLE_VALUE) // �t�@�C�������Ɏ��s�����ꍇ(return������ƁA�摜�t�@�C����jpg�����̎��Ȃǂ�png��bmp�͑��݂��Ȃ����߁A�����I�����Ă��܂�)
		{
			continue;
		}
		do
		{
			this->file_names.push_back(this->input_image_path + "\\" + win32fd.cFileName);
		} while (FindNextFile(hFind, &win32fd)); // FindFirstFile �֐��̌Ăяo���ɂ�錟���𑱍s(�߂�l�͐����F0�ȊO,���s�F0)

		// �w�肳�ꂽ�����n���h�����N���[�Y(�߂�l�͐����F0�ȊO,���s�F0)
		FindClose(hFind);
	}
	return 0;
}