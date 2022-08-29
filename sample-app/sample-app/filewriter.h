#ifndef _FILEWRITER_H_
#define _FILEWRITER_H_

#include <fstream>
#include <string>

class FileWriter
{
public:
	//コンストラクタ
	FileWriter();

	//デストラクタ
	~FileWriter();

	

private:
	std::ofstream writing_file;
	const std::string OUTPUT_FILE_NAME = "result.csv";
};

#endif