#include <iostream>
#include <string>

int main()
{
	std::string line;
	int sum = 0;
	int max = 0;

	while (std::cin) {
		std::getline(std::cin, line, '\n');

		if (line.empty()) {
			if (sum > max) {
				max = sum;
			}
			sum = 0;
		} else {
			sum += std::stoi(line);
		}
	}

	std::cout << max << std::endl;
}
