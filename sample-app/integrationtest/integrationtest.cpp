#include <gtest/gtest.h>
#include <Shlwapi.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

std::string OUTPUT_FILEPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\Output\\result.csv";
std::string ORIGINAL_OUTPUT_FILEPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\Output_original\\result.csv";

// �����e�X�g
int calc_elapsed_time_Test(double &elapsed_time, int &fps);
int compare_outputfile_Test();

int main(void)
{
	double elapsed_time = 0.0;
	int fps = 0;
	int iret = -1;

	// �������Ԃ��v��
	std::cout << "[ RUN      ] IntegrationTest.elapsed_time_Test" << std::endl;
	iret = calc_elapsed_time_Test(elapsed_time, fps);
	if (iret != 0)
	{
		std::cout << "calc_elapsed_time_Test failed! status code:" << iret << std::endl;
		std::cout << "[  FAILED  ] IntegrationTest.elapsed_time_Test" << std::endl;
		return -1;
	}
	std::cout << "[       OK ] IntegrationTest.elapsed_time_Test" << std::endl;

	// �o�̓t�@�C�����r
	std::cout << "[ RUN      ] IntegrationTest.compare_outputfile_Test" << std::endl;
	iret = compare_outputfile_Test();
	if (iret != 0)
	{
		std::cout << "compare_outputfile_Test failed! status code:" << iret << std::endl;
		std::cout << "[  FAILED  ] IntegrationTest.compare_outputfile_Test" << std::endl;
		return -2;
	}
	std::cout << "[       OK ] IntegrationTest.compare_outputfile_Test" << std::endl;
}

// �o�̓t�@�C�����r����֐�
int compare_outputfile_Test()
{
	int iret = -1;
	// std::string cmd = "fc /n " + ORIGINAL_OUTPUT_FILEPATH + " " + OUTPUT_FILEPATH;
	std::string cmd = "\"C:\\Program Files\\WinMerge\\WinMergeU.exe\" "+ ORIGINAL_OUTPUT_FILEPATH + " " + OUTPUT_FILEPATH + " /minimize /noninteractive /u /or .\\out.html";
	iret = system(cmd.c_str());
	if (iret != 0) // �R�}���h�����s�ł��Ȃ��ꍇ
	{
		return -1;
	}
	if (!PathFileExists(".\\out.html")) // �p�X�̏ꏊ�Ƀt�@�C�������݂��Ȃ��ꍇ�Ɏ��s
	{
		return -2;
	}
	return 0;
}


// �������Ԃ��v������֐�
int calc_elapsed_time_Test(double &elapsed_time, int &fps)
{
	std::chrono::system_clock::time_point  start, end;
	std::string str_buf;
	std::string str_conma_buf;
	std::vector<std::string> line;
	int frame_num;
	int iret = -1;

	// �T���v���A�v��(sample-app.exe)�̎��s����
	start = std::chrono::system_clock::now(); // �v���J�n����
	iret = system(".\\sample-app.exe");
	end = std::chrono::system_clock::now();  // �v���I������

	if (iret != 0) // �t�@�C�������s�ł��Ȃ��ꍇ
	{
		return -1;
	}

	// �����ɗv�������Ԃ��~���b�ɕϊ�
	elapsed_time = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	// �ǂݍ���csv�t�@�C�����J��(std::ifstream�̃R���X�g���N�^�ŊJ��)
	std::ifstream ifs_csv_file(OUTPUT_FILEPATH);

	if (!ifs_csv_file) //csv�t�@�C�����J���Ȃ��ꍇ
	{
		return -2;
	}

	// getline�֐���1�s���ǂݍ���(�ǂݍ��񂾓��e��str_buf�Ɋi�[)
	while (getline(ifs_csv_file, str_buf)) {

		line.push_back(str_buf);
	}
	// �Ō�̍s��istringstream�Ɋi�[����
	std::istringstream i_stream(line[line.size() - 1]);

	// �s�̐擪��frame�ԍ����擾���邽�߂Ɉ��̂�getline���Ă�
	getline(i_stream, str_conma_buf, ',');
	frame_num = atoi(str_conma_buf.c_str()) + 1;

	// �擾�����t���[�������T���v���A�v���̎��s���ԂŊ�����fps���v�Z
	fps =  (int)((double)frame_num / (elapsed_time * 0.001));

	// �t�@�C�������
	ifs_csv_file.close();

	// �v�Z���ʂ��o��
	std::cout << "Elapsed_time: " << elapsed_time << " msec" << std::endl;
	std::cout << "Fps: " << fps << std::endl;

	return 0;
}
