#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <stdlib.h>

constexpr int TIME_TO_SLEEP = 3000;

std::string myfunc(std::string input_imgpath);

int main(void)
{
	std::string path = "C:/Users/NES/Desktop/hayakawa/FieldAnalyst»•iŠJ”­ì‹ÆŒø—¦‰»‚ÉŒü‚¯‚½CI^CD‚Ì“±“üŒŸØ/sample.png";
	std::cout << "Hello Visual Studio!" << std::endl;
	int a, b;

	int *p = (int *)malloc(sizeof(int) * 10);
	if (p == NULL) {
		std::cout << "Memory cannot be allocated." << std::endl;
	}
	else {
		std::cout << "Memory has been allocated. The address is " << p << std::endl;
	}
	//free(p);

	std::string status = myfunc(path);

	std::cout << "Sleeping....." << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
	return 0;
}
