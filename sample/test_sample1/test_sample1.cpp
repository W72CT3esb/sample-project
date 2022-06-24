#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <thread>
#include "../sample1/fizzbuzz.h"

constexpr int TIME_TO_SLEEP = 3000;

bool test1(void);
bool test2(void);
bool test3(void);
bool test4(void);
bool test5(void);

int main(void)
{
	std::cout << "#####Start Testing#####\n" << std::endl;
	if (test1() == true && test2() == true && test3() == true && test4() == true && test5() == true)
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
	if (FizzBuzz(15) == "FizzBuzz")
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
	if (FizzBuzz(5) == "Buzz")
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
bool test3(void)
{
	if (FizzBuzz(3) == "Fizz")
	{
		std::cout << "test3 OK" << std::endl;
		return true;
	}
	else
	{
		std::cout << "test3 NG" << std::endl;
		return false;
	}
}
bool test4(void)
{
	if (FizzBuzz(1) == "1")
	{
		std::cout << "test4 OK" << std::endl;
		return true;
	}
	else
	{
		std::cout << "test4 NG" << std::endl;
		return false;
	}
}
bool test5(void)
{
	if (FizzBuzz(0) == "Error")
	{
		std::cout << "test5 OK" << std::endl;
		return true;
	}
	else
	{
		std::cout << "test5 NG" << std::endl;
		return false;
	}
}
