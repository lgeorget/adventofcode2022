#include <iostream>


int main()
{
	char them, us;
	int score = 0;

	std::cin >> them >> us;
	while (std::cin) {
		score += us == 'X' ? 1 : us == 'Y' ? 2 : 3;
		if ((us == 'X' && them == 'C') ||
		    (us == 'Y' && them == 'A') ||
		    (us == 'Z' && them == 'B')) {
			score += 6;
		} else if ((us == 'X' && them == 'A') ||
		           (us == 'Y' && them == 'B') ||
		           (us == 'Z' && them == 'C')) {
			score += 3;
		}
		std::cin >> them >> us;
	}
	std::cout << score << std::endl;
}

