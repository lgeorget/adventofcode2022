#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <functional>
#include <algorithm>

struct Monkey
{
	std::deque<int> items;
	std::function<int(int)> worry;
	std::function<int(int)> test;
	int total = 0;
};

bool operator<(const Monkey& m1, const Monkey& m2) {
	return m1.total < m2.total;
}


int main()
{
	std::string line;
	std::vector<Monkey> monkeys;

	while (std::cin) {
		Monkey m;
		std::getline(std::cin, line, '\n');
		std::cout << line << std::endl;
		std::cin.ignore(18);

		char sep = ',';
		do {
			int item;
			std::cin >> item;
			sep = std::cin.get();
			m.items.push_back(item);
		} while (sep != '\n');

		std::cin.ignore(23);
		char opChar;
		std::string operandStr;
		std::cin >> opChar >> operandStr;
		std::cout << "new = old " << opChar << " " << operandStr << "\n";
		std::function<int(int, int)> op;
		if (opChar == '+') {
			op = std::plus<int>();
		} else {
			op = std::multiplies<int>();
		}
		if (operandStr == "old") {
			m.worry = [op](int old) { return op(old, old); };
		} else {
			int operandInt = std::stoi(operandStr);
			m.worry = [op, operandInt](int old) { return op(old, operandInt); };
		}

		std::cin.ignore(21);
		int div;
		std::cin >> div;
		std::cin.ignore(29);
		int monkeyTrue;
		std::cin >> monkeyTrue;
		std::cin.ignore(30);
		int monkeyFalse;
		std::cin >> monkeyFalse;
		m.test = [div, monkeyTrue, monkeyFalse](int value) { return value % div == 0 ? monkeyTrue : monkeyFalse; };
		std::cin.ignore(1);

		monkeys.push_back(m);

		std::getline(std::cin, line, '\n');
	}


	for (int loop = 1 ; loop <= 20 ; loop++) {
		for (Monkey& m : monkeys) {
			while (!m.items.empty()) {
				int item = m.items.front();
				std::cout << "Monkey is inspecting " << item << std::endl;
				m.items.pop_front();
				m.total++;

				int newWorry = m.worry(item) / 3;
				monkeys[m.test(newWorry)].items.push_back(newWorry);
			}
		}

		std::cout << "After round " << loop << "\n";
		for (int mId = 0 ; mId < monkeys.size() ; mId++) {
			std::cout << "Monkey " << mId << ": ";
			for (int item : monkeys[mId].items) {
				std::cout << item << ", ";
			}
			std::cout << "\n";
		}
	}

	for (int mId = 0 ; mId < monkeys.size() ; mId++) {
		std::cout << "Monkey " << mId << ": inspected items " << monkeys[mId].total << " times.\n";
	}

	std::make_heap(monkeys.begin(), monkeys.end());
	int total = 1;
	for (int i=0 ; i<2 ; i++) {
		std::pop_heap(monkeys.begin(), monkeys.end());
		total *= monkeys.back().total;
		monkeys.pop_back();
	}
	std::cout << total << std::endl;
}
