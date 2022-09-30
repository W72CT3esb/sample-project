#include <iostream>
#include <Shlwapi.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>

const int DEFINE_STRING_SIZE = 1024;

int count_imagefile(std::string input_image_path);

// 機能テスト
int ImageData_PositiveTest();

int main(void)
{
	double elapsed_time = 0.0;
	int fps = 0;
	int iret = -1;

	// 静止画の機能テスト（正常系）
	std::cout << "[ RUN      ] FunctionTest." << std::endl;
	iret = ImageData_PositiveTest();
	if (iret != 0)
	{
		std::cout << "FunctionTest failed! status code:" << iret << std::endl;
		std::cout << "[  FAILED  ] FunctionTest" << std::endl;
		return -1;
	}
	std::cout << "[       OK ] FunctionTest" << std::endl;
	return 0;
}

int ImageData_PositiveTest()
{
	std::chrono::system_clock::time_point  start, end;
	double elapsed_time = 0.0;
	char output_dirpath[DEFINE_STRING_SIZE];
	char input_image_path[DEFINE_STRING_SIZE];
	std::string str_buf;
	std::string str_conma_buf;
	std::string output_filepath;
	std::vector<std::string> line;
	char data_type_pre[DEFINE_STRING_SIZE];
	int frame_num = 0;
	int image_file_num = 0;
	int data_type = -1;
	int iret = -1;

	// 現在のdata_typeの情報を保存
	GetPrivateProfileString("input", "data_type", "", data_type_pre, sizeof(data_type_pre), ".\\config.ini");

	// 設定ファイル内のdata_typeを1:画像に変更
	WritePrivateProfileString("input", "data_type", "1", ".\\config.ini");

	// サンプルアプリ(sample-app.exe)の実行時間
	iret = system(".\\sample-app.exe");

	// ①（正常終了しているか）
	if (iret != 0)
	{
		return -1;
	}

	// 設定ファイルからdata_typeを取得（画像データかちゃんと確認）
	data_type = GetPrivateProfileInt("input", "data_type", -1, ".\\config.ini");
	if (data_type != 1) //画像以外のデータの場合失敗
	{
		return -2;
	}

	// 設定ファイルから出力結果のファイルパスを取得
	GetPrivateProfileString("output", "output_dirpath", "", output_dirpath, sizeof(output_dirpath), ".\\config.ini");
	output_filepath = std::string(output_dirpath) + "\\result.csv";

	// ②指定の場所に処理結果が出力されているか
	if (!PathFileExists(output_filepath.c_str())) // パスの場所に出力ディレクトリが存在するかどうか
	{
		return -3;
	}

	// 設定ファイルから画像データのフォルダパスを取得
	GetPrivateProfileString("input", "input_image_path", "", input_image_path, sizeof(input_image_path), ".\\config.ini");
	image_file_num = count_imagefile(std::string(input_image_path));

	// 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
	std::ifstream ifs_csv_file(output_filepath);

	// getline関数で1行ずつ読み込む(読み込んだ内容はstr_bufに格納)
	while (getline(ifs_csv_file, str_buf)) {

		line.push_back(str_buf);
	}

	// 最後の行をistringstreamに格納する
	std::istringstream i_stream(line[line.size() - 1]);

	// 行の先頭のframe番号を取得するために一回のみgetlineを呼ぶ
	getline(i_stream, str_conma_buf, ',');
	frame_num = atoi(str_conma_buf.c_str()) + 1;

	// ③結果ファイルに入力画像枚数分の結果が出力されているか
	if (image_file_num != frame_num)
	{
		return -4;
	}

	// 設定ファイル内のdata_typeを前の情報に戻す
	WritePrivateProfileString("input", "data_type", data_type_pre, ".\\config.ini");

	return 0;
}

int count_imagefile(std::string input_image_path)
{
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;
	std::vector<std::string> file_names;
	std::vector<std::string> extension = { "png" ,"jpg", "bmp" };

	for (int i = 0; i < extension.size(); i++)
	{

		std::string search_name = input_image_path + "\\*." + extension[i];

		// 指定したファイル名に一致するファイルやディレクトリを検索(戻り値は成功：検索ハンドル,失敗：-1(INVALID_HANDLE_VALUE))
		hFind = FindFirstFile(search_name.c_str(), &win32fd);

		if (hFind == INVALID_HANDLE_VALUE) // ファイル検索に失敗した場合(returnをすると、画像ファイルがjpgだけの時などにpngとbmpは存在しないため、強制終了してしまう)
		{
			continue;
		}
		do
		{
			file_names.push_back(input_image_path + "\\" + win32fd.cFileName);
		} while (FindNextFile(hFind, &win32fd)); // FindFirstFile 関数の呼び出しによる検索を続行(戻り値は成功：0以外,失敗：0)

												 // 指定された検索ハンドルをクローズ(戻り値は成功：0以外,失敗：0)
		FindClose(hFind);
	}
	return int(file_names.size());
}