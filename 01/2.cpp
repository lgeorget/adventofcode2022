#include <iostream>
#include <string>

int main()
{
	std::string line;
	int sum = 0;
	int top1 = 0;
	int top2 = 0;
	int top3 = 0;

	while (std::cin) {
		std::getline(std::cin, line, '\n');

		if (line.empty()) {
			if (sum > top1) {
				std::swap(top2, top3);
				std::swap(top1, top2);
				top1 = sum;
			} else if (sum > top2) {
				std::swap(top2, top3);
				top2 = sum;
			} else if (sum > top3) {
				top3 = sum;
			}
			sum = 0;
		} else {
			sum += std::stoi(line);
		}
	}

	std::cout << (top1 + top2 + top3) << std::endl;
}
