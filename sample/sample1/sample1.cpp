#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <vector>
#include "fizzbuzz.h"

constexpr int TIME_TO_SLEEP = 3000;

std::string FizzBuzz(int x);

int main(void)
{
	std::cout << "Hello Visual Studio!" << std::endl;

	for (int i = 1; i <= 20; i++)
	{
		std::cout << FizzBuzz(i) << std::endl;
	}

	std::cout << "Sleeping....." << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
	return 0;
}
