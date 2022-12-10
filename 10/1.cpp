#include <iostream>
#include <string>

int main()
{
	int x = 1;
	int cycles = 1;
	long total = 0;

	std::string instr;
	int add = 0;
	bool inAdd = false;
	while (std::cin)
	{
		if (inAdd) {
			x += add;
			inAdd = false;
		} else {
			std::cin >> instr;
			if (std::cin && instr == "addx") {
				std::cin >> add;
				inAdd = true;
			}
		}

		cycles++;
		if (cycles == 20) {
			std::cout << x << std::endl;
			total += x * 20;
		} else if (cycles == 60) {
			std::cout << x << std::endl;
			total += x * 60;
		} else if (cycles == 100) {
			std::cout << x << std::endl;
			total += x * 100;
		} else if (cycles == 140) {
			std::cout << x << std::endl;
			total += x * 140;
		} else if (cycles == 180) {
			std::cout << x << std::endl;
			total += x * 180;
		} else if (cycles == 220) {
			std::cout << x << std::endl;
			total += x * 220;
		}
	}

	std::cout << total << std::endl;
}
