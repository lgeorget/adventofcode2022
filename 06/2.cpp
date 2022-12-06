#include <iostream>
#include <algorithm>

int main()
{
	constexpr int MARKER_LENGTH = 14;
	char buffer[MARKER_LENGTH];
	int pos = 0;
	int i = 0;
	int wrong_until = 0;

	while (std::cin && i - wrong_until < 14) {
		std::cin >> buffer[pos];

		for (int j=(pos + MARKER_LENGTH - 1) % MARKER_LENGTH, w=i ;
			 j != pos ;
			 j=(j + MARKER_LENGTH - 1) % MARKER_LENGTH, w--
		) {
			if (buffer[j] == buffer[pos]) {
				wrong_until = std::max(wrong_until, w);
				break;
			}
		}

		i++;
		pos = (pos + 1) % MARKER_LENGTH;
	}

	std::cout << (wrong_until + MARKER_LENGTH) << std::endl;
}
