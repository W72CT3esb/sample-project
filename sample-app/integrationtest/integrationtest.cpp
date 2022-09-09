#include <gtest/gtest.h>
#include <Shlwapi.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

std::string OUTPUT_FILEPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\Output\\result.csv";
std::string ORIGINAL_OUTPUT_FILEPATH = "C:\\Users\\NES\\Desktop\\hayakawa\\CICD\\Output_original\\result.csv";

// 総合テスト
int calc_elapsed_time_Test(double &elapsed_time, int &fps);
int compare_outputfile_Test();

int main(void)
{
	double elapsed_time = 0.0;
	int fps = 0;
	int iret = -1;

	// 処理時間を計測
	std::cout << "[ RUN      ] IntegrationTest.elapsed_time_Test" << std::endl;
	iret = calc_elapsed_time_Test(elapsed_time, fps);
	if (iret != 0)
	{
		std::cout << "calc_elapsed_time_Test failed! status code:" << iret << std::endl;
		std::cout << "[  FAILED  ] IntegrationTest.elapsed_time_Test" << std::endl;
		return -1;
	}
	std::cout << "[       OK ] IntegrationTest.elapsed_time_Test" << std::endl;

	// 出力ファイルを比較
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

// 出力ファイルを比較する関数
int compare_outputfile_Test()
{
	int iret = -1;
	// std::string cmd = "fc /n " + ORIGINAL_OUTPUT_FILEPATH + " " + OUTPUT_FILEPATH;
	std::string cmd = "\"C:\\Program Files\\WinMerge\\WinMergeU.exe\" "+ ORIGINAL_OUTPUT_FILEPATH + " " + OUTPUT_FILEPATH + " /minimize /noninteractive /u /or .\\out.html";
	iret = system(cmd.c_str());
	if (iret != 0) // コマンドを実行できない場合
	{
		return -1;
	}
	if (!PathFileExists(".\\out.html")) // パスの場所にファイルが存在しない場合に失敗
	{
		return -2;
	}
	return 0;
}


// 処理時間を計測する関数
int calc_elapsed_time_Test(double &elapsed_time, int &fps)
{
	std::chrono::system_clock::time_point  start, end;
	std::string str_buf;
	std::string str_conma_buf;
	std::vector<std::string> line;
	int frame_num;
	int iret = -1;

	// サンプルアプリ(sample-app.exe)の実行時間
	start = std::chrono::system_clock::now(); // 計測開始時間
	iret = system(".\\sample-app.exe");
	end = std::chrono::system_clock::now();  // 計測終了時間

	if (iret != 0) // ファイルを実行できない場合
	{
		return -1;
	}

	// 処理に要した時間をミリ秒に変換
	elapsed_time = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	// 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
	std::ifstream ifs_csv_file(OUTPUT_FILEPATH);

	if (!ifs_csv_file) //csvファイルが開けない場合
	{
		return -2;
	}

	// getline関数で1行ずつ読み込む(読み込んだ内容はstr_bufに格納)
	while (getline(ifs_csv_file, str_buf)) {

		line.push_back(str_buf);
	}
	// 最後の行をistringstreamに格納する
	std::istringstream i_stream(line[line.size() - 1]);

	// 行の先頭のframe番号を取得するために一回のみgetlineを呼ぶ
	getline(i_stream, str_conma_buf, ',');
	frame_num = atoi(str_conma_buf.c_str()) + 1;

	// 取得したフレーム数をサンプルアプリの実行時間で割ってfpsを計算
	fps =  (int)((double)frame_num / (elapsed_time * 0.001));

	// ファイルを閉じる
	ifs_csv_file.close();

	// 計算結果を出力
	std::cout << "Elapsed_time: " << elapsed_time << " msec" << std::endl;
	std::cout << "Fps: " << fps << std::endl;

	return 0;
}
