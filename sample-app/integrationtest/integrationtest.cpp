#include <gtest/gtest.h>
#include <Shlwapi.h>
#include <string>

std::string OUTPUT_DIRPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\Output";
std::string OUTPUT_FILEPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\Output\\result.csv";

// サンプルアプリ(sample-app.exe)の実行時間
TEST(IntegrationTest, sample_app_elapsed_time_Test) {
	std::chrono::system_clock::time_point  start, end;
	double elapsed_time;

	start = std::chrono::system_clock::now(); // 計測開始時間
	system(".\\sample-app.exe");
	end = std::chrono::system_clock::now();  // 計測終了時間

	// 処理に要した時間をミリ秒に変換
	elapsed_time = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	//std::cout << elapsed_time << " msec" << std::endl;

	// 結果ファイルを消す
	DeleteFile(OUTPUT_FILEPATH.c_str());
	RemoveDirectory(OUTPUT_DIRPATH.c_str());
}
