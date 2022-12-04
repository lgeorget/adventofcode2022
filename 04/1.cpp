#include <iostream>


int main()
{
	int total = 0;

	int min1, max1, min2, max2;
	std::cin >> min1;
	std::cin.ignore(1);
	std::cin >> max1;
	std::cin.ignore(1);
	std::cin >> min2;
	std::cin.ignore(1);
	std::cin >> max2;

	while (std::cin)
	{
		if ((min1 <= min2 && max1 >= max2) ||
		    (min2 <= min1 && max2 >= max1)) {
			total++;
		}

		std::cin >> min1;
		std::cin.ignore(1);
		std::cin >> max1;
		std::cin.ignore(1);
		std::cin >> min2;
		std::cin.ignore(1);
		std::cin >> max2;
	}

	std::cout << total << std::endl;
}
