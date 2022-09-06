#include <gtest/gtest.h>
#include <Shlwapi.h>
#include <string>

std::string OUTPUT_DIRPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\Output";
std::string OUTPUT_FILEPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\Output\\result.csv";

// �T���v���A�v��(sample-app.exe)�̎��s����
TEST(IntegrationTest, sample_app_elapsed_time_Test) {
	std::chrono::system_clock::time_point  start, end;
	double elapsed_time;

	start = std::chrono::system_clock::now(); // �v���J�n����
	system(".\\sample-app.exe");
	end = std::chrono::system_clock::now();  // �v���I������

	// �����ɗv�������Ԃ��~���b�ɕϊ�
	elapsed_time = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	//std::cout << elapsed_time << " msec" << std::endl;

	// ���ʃt�@�C��������
	DeleteFile(OUTPUT_FILEPATH.c_str());
	RemoveDirectory(OUTPUT_DIRPATH.c_str());
}
