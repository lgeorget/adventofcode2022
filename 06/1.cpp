#include <iostream>

int main()
{
	std::string line;
	char marker[4];

	std::getline(std::cin, line, '\n');
	for (int i=0 ; i<4 ; i++) {
		marker[i] = line[i];
	}
	bool found = false;
	int pos = 0;
	int i = 3;
	do {
		found = marker[0] != marker[1] &&
			marker[0] != marker[2] &&
			marker[0] != marker[3] &&
			marker[1] != marker[2] &&
			marker[1] != marker[3] &&
			marker[2] != marker[3];
		++i;
		marker[pos] = line[i];
		pos = (pos + 1) % 4;
	} while (!found);

	std::cout << i << std::endl;
}
