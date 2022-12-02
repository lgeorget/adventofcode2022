#include <iostream>


int main()
{
	char them, us;
	int score = 0;

	std::cin >> them >> us;
	while (std::cin) {
		if ((them == 'C' && us == 'Z') ||
		    (them == 'A' && us == 'Y') ||
		    (them == 'B' && us == 'X')) {
			score += 1;
		} else if ((them == 'A' && us == 'Z') ||
			   (them == 'B' && us == 'Y') ||
			   (them == 'C' && us == 'X')) {
			score += 2;
		} else {
			score += 3;
		}

		if (us == 'Z') {
			score += 6;
		} else if (us == 'Y') {
			score += 3;
		}
		std::cin >> them >> us;
	}
	std::cout << score << std::endl;
}

