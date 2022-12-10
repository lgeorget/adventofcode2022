#include <iostream>
#include <string>
#include <array>

int main()
{
	std::array<char, 240> screen;

	int x = 1;
	int cycles = 1;
	long total = 0;

	std::string instr;
	int add = 0;
	bool inAdd = false;

	screen[0] = '#';

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

		int column = cycles % 40;
		screen[cycles] = (x >= column - 1 && x <= column + 1) ? '#' : '.';
		cycles++;
	}

	for (int l=0 ; l<6 ; l++) {
		for (int c=0 ; c<40 ; c++) {
			std::cout << screen[l * 40 + c];
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}
