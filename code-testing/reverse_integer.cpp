#include <iostream>
#include <cmath>

int reverse_interger(int x)
{
	int64_t res = 0 ;
	int idx_first_digit=0;
	for (int i = 9; i > 0; i--)
	{
		int tmp = std::pow(10, i);
		
		if (x/tmp) {
			idx_first_digit = i;
			break;
		}
	}

	
	auto find_first_digit = false;
	for (int i=0 ; i <= idx_first_digit; i++)
	{
		int curr_digit = (x % 10);
		if (find_first_digit == false && curr_digit) 
			find_first_digit = true;
		if (find_first_digit) {
			res += curr_digit * std::pow(10 ,idx_first_digit - i);
			if (res > INT32_MAX)
				return 0;
			else if (res < INT32_MIN)
				return 0;
		}
		
		x = (int)(x / 10);
	}

	return static_cast<int>(res);
}


int main()
{
	int i = -1534236469;
	std::cout  << reverse_interger(i) << std::endl;
	return 0;
}
