#include <string>
#include "fizzbuzz.h"

std::string FizzBuzz(int x)
{
	if (x > 0)
	{
		if (x % 15 == 0) {
			return "FizzBuzz";
		}
		else if (x % 5 == 0) {
			return "Buzz";
		}
		else if (x % 3 == 0) {
			return "Fizz";
		}
		else
		{
			return std::to_string(x);
		}
	}
	else
	{
		return "Error";
	}
}