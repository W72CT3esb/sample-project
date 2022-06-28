#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <thread>
#include "../sample2/myfunc.h"

constexpr int TIME_TO_SLEEP = 3000;

bool test1(void);
bool test2(void);

int main(void)
{
	std::cout << "#####Start Testing#####\n" << std::endl;
	if (test1() == true && test2() == true)
	{
		std::cout << "\n@@@Test successful@@@\n" << std::endl;
	}
	else
	{
		std::cout << "Test failed" << std::endl;
		throw std::exception();
		//exit(1);
	}
	std::cout << "#####Finish Testing#####" << std::endl;
	//std::cout << "Sleeping....." << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
	return 0;
}

bool test1(void)
{
	std::string path = "C:/Users/NES/Desktop/hayakawa/FieldAnalyst»•iŠJ”­ì‹ÆŒø—¦‰»‚ÉŒü‚¯‚½CI^CD‚Ì“±“üŒŸØ/sample.png";
	if (myfunc(path) == "file is ok")
	{
		std::cout << "test1 OK" << std::endl;
		return true;
	}
	else
	{
		std::cout << "test1 NG" << std::endl;
		return false;
	}
}
bool test2(void)
{
	std::string path = "C:/Users/NES/Documents/hayakawa/FieldAnalyst»•iŠJ”­ì‹ÆŒø—¦‰»‚ÉŒü‚¯‚½CI^CD‚Ì“±“üŒŸØ/sample.png";
	if (myfunc(path) == "file is empty")
	{
		std::cout << "test2 OK" << std::endl;
		return true;
	}
	else
	{
		std::cout << "test2 NG" << std::endl;
		return false;
	}
}
