#include <iostream>
#include <chrono>
#include <thread>
#include <stdlib.h>

constexpr int TIME_TO_SLEEP = 3000;

int main(void)
{
	int a = 0;
	int b;
	int *p = (int *)malloc(sizeof(int) * 10);
	if (p == NULL) {
		std::cout << "Memory cannot be allocated." << std::endl;
	}
	else {
		std::cout << "Memory has been allocated. The address is " << p << std::endl;
	}

	//free(p);

	std::cout << "Sleeping....." << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
	return 0;
}
