#ifndef _FILEWRITER_H_
#define _FILEWRITER_H_

#include <fstream>
#include <string>

class FileWriter
{
public:
	//�R���X�g���N�^
	FileWriter();

	//�f�X�g���N�^
	~FileWriter();

	

private:
	std::ofstream writing_file;
	const std::string OUTPUT_FILE_NAME = "result.csv";
};

#endif