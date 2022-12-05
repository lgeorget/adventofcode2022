#include <iostream>
#include <deque>
#include <limits>
#include <algorithm>

int main()
{
	std::string line;
	std::getline(std::cin, line, '\n');
	int nbStacks = (line.size() + 1) / 4;

	std::deque<char> stacks[nbStacks];

	while (!line.empty()) {
		for (int i=0 ; i<nbStacks ; i++) {
			if (line[4 * i + 1] != ' ') {
				stacks[i].push_front(line[4 * i + 1]);
			}
		}
		std::getline(std::cin, line, '\n');
	}

	for (auto&& s : stacks) {
		for (char c : s) {
			std::cout << c << " ";
		}
		std::cout << "\n";
	}


	std::string wmove, wfrom, wto;
	int nb, from, to;
	std::cin >> wmove >> nb >> wfrom >> from >> wto >> to;
	while (std::cin) {
		auto& sFrom = stacks[from - 1];
		auto& sTo = stacks[to - 1];
		std::copy(sFrom.end() - nb, sFrom.end(),
			std::back_inserter(sTo));
		sFrom.erase(sFrom.end() - nb, sFrom.end());

		std::cin >> wmove >> nb >> wfrom >> from >> wto >> to;
	}

	for (auto&& s : stacks) {
		for (char c : s) {
			std::cout << c << " ";
		}
		std::cout << "\n";
	}

	for (auto&& s : stacks) {
		std::cout << s.back();
	}
	std::cout << std::endl;
}
