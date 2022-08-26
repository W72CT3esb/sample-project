#ifndef _PARAMLOADER_H_
#define _PARAMLOADER_H_

#include <string>
#include "common.h"

class ParamLoader
{
public:
	//コンストラクタ
	ParamLoader();

	//デストラクタ
	~ParamLoader();

	int load_param(Params &params);

private:
	const std::string CONFIG_FILEPATH = ".\\config.ini";
};

#endif
